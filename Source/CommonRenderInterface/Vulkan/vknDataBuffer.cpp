////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "vknDataBuffer.h"
////////////////////////////////////////////////////////////////
// секция компиляция файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция форвард-декларации
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция для исключений
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////
#include "vknContext.h"
#include "../Private\Vulkan\vknResourcePool.h"

#include "../CRIContext.h"
#include "../CRIDataBuffer.h"

namespace FE {

	namespace CRI {

		namespace VULKAN {

			//==============================================================
			//==============================================================

			CVKDataBuffer::CVKDataBuffer(VKContext vknContext)
				: CCRIDataBuffer(nullptr),
				m_Context(vknContext),
				m_Staging(nullptr),
				m_Buffer(VK_NULL_HANDLE),
				m_Memory(VK_NULL_HANDLE),
				m_RealSize(0),
				m_AllocSize(0),
				m_CopyCmdBuffer(VK_NULL_HANDLE),
				m_Usage(0) {
				
			}

			//==============================================================
			//==============================================================

			void CVKDataBuffer::create(const CRI_DATA_BUFFER_CREATE_INFO *createInfo) {

				auto &_createInfo = *createInfo;

				// ~~~~~~~~~~~~~~~~
				// по информации для создания определяем параметры буфера
				// ~~~~~~~~~~~~~~~~

				if ((_createInfo.m_Props & CRI_DATA_BUFFER_CREATE_INFO::PROPS::STORAGE) == CRI_DATA_BUFFER_CREATE_INFO::PROPS::STORAGE) { m_Usage |= VK_BUFFER_USAGE_STORAGE_BUFFER_BIT; }

				switch (_createInfo.m_Usage) {
				case CRI_DATA_BUFFER_CREATE_INFO::USAGE::VERTEX:		m_Usage |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT; break;
				case CRI_DATA_BUFFER_CREATE_INFO::USAGE::INDEX:			m_Usage |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT; break;
				case CRI_DATA_BUFFER_CREATE_INFO::USAGE::UNIFORM:		m_Usage |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT; break;
				}

				VkMemoryPropertyFlags _memoryPropertyFlags = {};
				switch (_createInfo.m_Storage) {
				case CRI_DATA_BUFFER_CREATE_INFO::STORAGE::HOST:		_memoryPropertyFlags |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT; break;
				case CRI_DATA_BUFFER_CREATE_INFO::STORAGE::DEVICE:		_memoryPropertyFlags |= VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
					m_Usage |= VK_BUFFER_USAGE_TRANSFER_DST_BIT; break;
				}

				// ~~~~~~~~~~~~~~~~
				// если указана информация
				// ~~~~~~~~~~~~~~~~
				//if (vknCreateInfo != nullptr) {

				//	_usage |= vknCreateInfo->m_Usage;
				//}

				// ~~~~~~~~~~~~~~~~
				// создаём VkBuffer
				// ~~~~~~~~~~~~~~~~

				// описываем VkBufferCreateInfo
				VkBufferCreateInfo _bufferCI = {};

				_bufferCI.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
				_bufferCI.pNext = nullptr;
				_bufferCI.flags;
				_bufferCI.size = m_RealSize = _createInfo.m_Size;
				_bufferCI.usage = m_Usage;
				_bufferCI.sharingMode;
				_bufferCI.queueFamilyIndexCount;
				_bufferCI.pQueueFamilyIndices;

				VK_ASSERT_EX(m_Context->vkCreateBuffer(m_Context->getDevice(), &_bufferCI, nullptr, &m_Buffer), "", );

				// ~~~~~~~~~~~~~~~~
				// выделяем память
				// ~~~~~~~~~~~~~~~~

				// запрашиваем требования к памяти
				VkMemoryRequirements _memReqs = {};
				m_Context->vkGetBufferMemoryRequirements(m_Context->getDevice(), m_Buffer, &_memReqs);

				// описываем VkMemoryAllocateInfo
				VkMemoryAllocateInfo _memAllocI = {};

				_memAllocI.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				_memAllocI.pNext = nullptr;
				_memAllocI.allocationSize = m_AllocSize = _memReqs.size;
				_memAllocI.memoryTypeIndex = m_Context->getIndexMemory(_memoryPropertyFlags);

				VK_ASSERT_EX(m_Context->vkAllocateMemory(m_Context->getDevice(), &_memAllocI, nullptr, &m_Memory), "Не удалось аллоцировать память.", );

				// ~~~~~~~~~~~~~~~~
				// связываем созданный буфер и выделенную память
				// ~~~~~~~~~~~~~~~~

				VK_ASSERT_EX(m_Context->vkBindBufferMemory(m_Context->getDevice(), m_Buffer, m_Memory, 0), "Не удалось привязать буфер к памяти.", );

				// ~~~~~~~~~~~~~~~~
				// чтобы записывать в буфер, созданный с флагом VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
				// необходим промежуточный буфер, созданный с флагом VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT.
				// Вначале запись происходит в промежуточный буфер, посредством map/unmap. А затем из промежуточного в основной.
				// ~~~~~~~~~~~~~~~~

				if (_createInfo.m_Storage == CRI_DATA_BUFFER_CREATE_INFO::STORAGE::DEVICE) {

					// описываем буфер данных
					FE::CRI::CRI_DATA_BUFFER_CREATE_INFO _dataBufferCI = {};

					_dataBufferCI.m_Usage = FE::CRI::CRI_DATA_BUFFER_CREATE_INFO::USAGE::UNIFORM;
					_dataBufferCI.m_Storage = FE::CRI::CRI_DATA_BUFFER_CREATE_INFO::STORAGE::HOST;
					_dataBufferCI.m_Size = _createInfo.m_Size;

					m_Staging = new CVKDataBuffer(m_Context);

					m_Staging->m_Usage |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT;

					m_Staging->create(&_dataBufferCI);

				} // if (itCRIDataBuffer->getStorage() == CRI_DATA_BUFFER_CREATE_INFO::STORAGE::DEVICE)
			}

			//==============================================================
			//==============================================================

			void CVKDataBuffer::update(void) {

				auto _vknResPool = m_Context->getResourcePool();

				auto& _updateInfo = this->getUpdateInfo();

				// если 
				bool _staging = (m_Staging == nullptr ? false : true);

				// если промежуточный буфер был создан (не равен nullptr)
				// тогда сначало копируем в него, а после уже в основной
				if (m_Staging != nullptr) {

					// ~~~~~~~~~~~~~~~~
					// копируем данные в промежуточный буфер
					// ~~~~~~~~~~~~~~~~

					// проецируем память GPU на CPU
					void* _mapMemory = nullptr;
					VK_ASSERT_EX(m_Context->vkMapMemory(m_Context->getDevice(), m_Staging->m_Memory, 0, m_Staging->m_AllocSize, 0, &_mapMemory), "", );

					for (const auto &itUpdateInfo : _updateInfo) {
						
						// копируем данные
						memcpy(static_cast<uint8_t*>(_mapMemory) + itUpdateInfo.m_Offset, static_cast<const uint8_t*>(itUpdateInfo.m_Data) + itUpdateInfo.m_Offset, itUpdateInfo.m_Size);

					}

					// убираем проекцию памяти GPU на CPU
					m_Context->vkUnmapMemory(m_Context->getDevice(), m_Staging->m_Memory);

					// ~~~~~~~~~~~~~~~~
					// создание VkCommandBuffer для копирования из промежуточного в основной
					// ~~~~~~~~~~~~~~~~

					if (m_CopyCmdBuffer == nullptr) {

						// описываем VkCommandBufferAllocateInfo
						VkCommandBufferAllocateInfo _cmdBufferAllocateCI = {};

						_cmdBufferAllocateCI.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
						_cmdBufferAllocateCI.commandPool = m_Context->getVkCommandPool();
						_cmdBufferAllocateCI.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
						_cmdBufferAllocateCI.commandBufferCount = 1;

						// алоцируем командные буферы
						VK_ASSERT_EX(m_Context->vkAllocateCommandBuffers(m_Context->getDevice(), &_cmdBufferAllocateCI, &m_CopyCmdBuffer), "", );
					}

					// ~~~~~~~~~~~~~~~~
					// начало записи VkCommandBuffer
					// ~~~~~~~~~~~~~~~~

					// описываем VkCommandBufferBeginInfo
					VkCommandBufferBeginInfo cmdBufferBeginInfo = {};

					cmdBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
					cmdBufferBeginInfo.pNext = NULL;

					// начало записи в командный буфер
					m_Context->vkBeginCommandBuffer(m_CopyCmdBuffer, &cmdBufferBeginInfo);

					// описываем VkBufferCopy
					VkBufferCopy copyRegion = {};

					copyRegion.size = m_RealSize;
					m_Context->vkCmdCopyBuffer(m_CopyCmdBuffer, m_Staging->m_Buffer, m_Buffer, 1, &copyRegion);

					// ~~~~~~~~~~~~~~~~
					// конец записи VkCommandBuffer
					// ~~~~~~~~~~~~~~~~

					m_Context->vkEndCommandBuffer(m_CopyCmdBuffer);

					_vknResPool->executeCmdBuffer(m_CopyCmdBuffer);

				}

				else {

					// проецируем память GPU на CPU
					void* _mapMemory = nullptr;
					VK_ASSERT_EX(m_Context->vkMapMemory(m_Context->getDevice(), m_Memory, 0, m_AllocSize, 0, &_mapMemory), "", );

					for (const auto &itUpdateInfo : _updateInfo) {
						
						// копируем данные
						memcpy(static_cast<uint8_t*>(_mapMemory) + itUpdateInfo.m_Offset, static_cast<const uint8_t*>(itUpdateInfo.m_Data), itUpdateInfo.m_Size);

					}

					// убираем проекцию памяти GPU на CPU
					m_Context->vkUnmapMemory(m_Context->getDevice(), m_Memory);

				}

				//_updateInfo.front().m_Data = nullptr;
				_updateInfo.clear();
				

			}

			//==============================================================
			//==============================================================

		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE