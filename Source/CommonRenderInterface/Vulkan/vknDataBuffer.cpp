////////////////////////////////////////////////////////////////
// ������ PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// ������ ������������� �����
////////////////////////////////////////////////////////////////
#include "vknDataBuffer.h"
////////////////////////////////////////////////////////////////
// ������ ���������� �����
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ �������-����������
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ ��� ����������
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ ��� ����������
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
				// �� ���������� ��� �������� ���������� ��������� ������
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
				// ���� ������� ����������
				// ~~~~~~~~~~~~~~~~
				//if (vknCreateInfo != nullptr) {

				//	_usage |= vknCreateInfo->m_Usage;
				//}

				// ~~~~~~~~~~~~~~~~
				// ������ VkBuffer
				// ~~~~~~~~~~~~~~~~

				// ��������� VkBufferCreateInfo
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
				// �������� ������
				// ~~~~~~~~~~~~~~~~

				// ����������� ���������� � ������
				VkMemoryRequirements _memReqs = {};
				m_Context->vkGetBufferMemoryRequirements(m_Context->getDevice(), m_Buffer, &_memReqs);

				// ��������� VkMemoryAllocateInfo
				VkMemoryAllocateInfo _memAllocI = {};

				_memAllocI.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				_memAllocI.pNext = nullptr;
				_memAllocI.allocationSize = m_AllocSize = _memReqs.size;
				_memAllocI.memoryTypeIndex = m_Context->getIndexMemory(_memoryPropertyFlags);

				VK_ASSERT_EX(m_Context->vkAllocateMemory(m_Context->getDevice(), &_memAllocI, nullptr, &m_Memory), "�� ������� ������������ ������.", );

				// ~~~~~~~~~~~~~~~~
				// ��������� ��������� ����� � ���������� ������
				// ~~~~~~~~~~~~~~~~

				VK_ASSERT_EX(m_Context->vkBindBufferMemory(m_Context->getDevice(), m_Buffer, m_Memory, 0), "�� ������� ��������� ����� � ������.", );

				// ~~~~~~~~~~~~~~~~
				// ����� ���������� � �����, ��������� � ������ VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
				// ��������� ������������� �����, ��������� � ������ VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT.
				// ������� ������ ���������� � ������������� �����, ����������� map/unmap. � ����� �� �������������� � ��������.
				// ~~~~~~~~~~~~~~~~

				if (_createInfo.m_Storage == CRI_DATA_BUFFER_CREATE_INFO::STORAGE::DEVICE) {

					// ��������� ����� ������
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

				// ���� 
				bool _staging = (m_Staging == nullptr ? false : true);

				// ���� ������������� ����� ��� ������ (�� ����� nullptr)
				// ����� ������� �������� � ����, � ����� ��� � ��������
				if (m_Staging != nullptr) {

					// ~~~~~~~~~~~~~~~~
					// �������� ������ � ������������� �����
					// ~~~~~~~~~~~~~~~~

					// ���������� ������ GPU �� CPU
					void* _mapMemory = nullptr;
					VK_ASSERT_EX(m_Context->vkMapMemory(m_Context->getDevice(), m_Staging->m_Memory, 0, m_Staging->m_AllocSize, 0, &_mapMemory), "", );

					for (const auto &itUpdateInfo : _updateInfo) {
						
						// �������� ������
						memcpy(static_cast<uint8_t*>(_mapMemory) + itUpdateInfo.m_Offset, static_cast<const uint8_t*>(itUpdateInfo.m_Data) + itUpdateInfo.m_Offset, itUpdateInfo.m_Size);

					}

					// ������� �������� ������ GPU �� CPU
					m_Context->vkUnmapMemory(m_Context->getDevice(), m_Staging->m_Memory);

					// ~~~~~~~~~~~~~~~~
					// �������� VkCommandBuffer ��� ����������� �� �������������� � ��������
					// ~~~~~~~~~~~~~~~~

					if (m_CopyCmdBuffer == nullptr) {

						// ��������� VkCommandBufferAllocateInfo
						VkCommandBufferAllocateInfo _cmdBufferAllocateCI = {};

						_cmdBufferAllocateCI.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
						_cmdBufferAllocateCI.commandPool = m_Context->getVkCommandPool();
						_cmdBufferAllocateCI.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
						_cmdBufferAllocateCI.commandBufferCount = 1;

						// ��������� ��������� ������
						VK_ASSERT_EX(m_Context->vkAllocateCommandBuffers(m_Context->getDevice(), &_cmdBufferAllocateCI, &m_CopyCmdBuffer), "", );
					}

					// ~~~~~~~~~~~~~~~~
					// ������ ������ VkCommandBuffer
					// ~~~~~~~~~~~~~~~~

					// ��������� VkCommandBufferBeginInfo
					VkCommandBufferBeginInfo cmdBufferBeginInfo = {};

					cmdBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
					cmdBufferBeginInfo.pNext = NULL;

					// ������ ������ � ��������� �����
					m_Context->vkBeginCommandBuffer(m_CopyCmdBuffer, &cmdBufferBeginInfo);

					// ��������� VkBufferCopy
					VkBufferCopy copyRegion = {};

					copyRegion.size = m_RealSize;
					m_Context->vkCmdCopyBuffer(m_CopyCmdBuffer, m_Staging->m_Buffer, m_Buffer, 1, &copyRegion);

					// ~~~~~~~~~~~~~~~~
					// ����� ������ VkCommandBuffer
					// ~~~~~~~~~~~~~~~~

					m_Context->vkEndCommandBuffer(m_CopyCmdBuffer);

					_vknResPool->executeCmdBuffer(m_CopyCmdBuffer);

				}

				else {

					// ���������� ������ GPU �� CPU
					void* _mapMemory = nullptr;
					VK_ASSERT_EX(m_Context->vkMapMemory(m_Context->getDevice(), m_Memory, 0, m_AllocSize, 0, &_mapMemory), "", );

					for (const auto &itUpdateInfo : _updateInfo) {
						
						// �������� ������
						memcpy(static_cast<uint8_t*>(_mapMemory) + itUpdateInfo.m_Offset, static_cast<const uint8_t*>(itUpdateInfo.m_Data), itUpdateInfo.m_Size);

					}

					// ������� �������� ������ GPU �� CPU
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