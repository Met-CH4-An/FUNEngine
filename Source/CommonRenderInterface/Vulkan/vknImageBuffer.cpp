////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "vknImageBuffer.h"
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
#include "vknDataBuffer.h"

#include "../CRIContext.h"
#include "../CRIDataBuffer.h"
#include "../CRIImageBuffer.h"

namespace FE {

	namespace CRI {

		namespace VULKAN {

			//==============================================================
			//==============================================================

			CVKImageBuffer::CVKImageBuffer() {

				m_CreateInfo = {};
				m_Format = VK_FORMAT_UNDEFINED;
				m_Image = VK_NULL_HANDLE;
				m_ImageType = VK_IMAGE_TYPE_MAX_ENUM;
				m_ImageUsage = 0;
				m_ImageAspect = 0;
				m_View = VK_NULL_HANDLE;
				m_ViewType = VK_IMAGE_VIEW_TYPE_MAX_ENUM;
				m_Memory = VK_NULL_HANDLE;
				m_ImageMemoryProperty = 0;


			}

			//==============================================================
			//==============================================================

			CVKImageBuffer::~CVKImageBuffer(void) {

				m_CreateInfo = {};
				m_Format = VK_FORMAT_UNDEFINED;
				m_Image = VK_NULL_HANDLE;
				m_ImageType = VK_IMAGE_TYPE_MAX_ENUM;
				m_ImageUsage = 0;
				m_ImageAspect = 0;
				m_View = VK_NULL_HANDLE;
				m_ViewType = VK_IMAGE_VIEW_TYPE_MAX_ENUM;
				m_Memory = VK_NULL_HANDLE;
				m_ImageMemoryProperty = 0;

			}		

			//==============================================================
			//==============================================================

			void CVKImageBuffer::create(const CRI_IMAGE_BUFFER_CREATE_INFO *createInfo) {

				m_CreateInfo = *createInfo;

				auto _vknContext = cri2vkn_Context(m_CreateInfo.m_CRIContext);

				// ~~~~~~~~~~~~~~~~
				// ~~~~~~~~~~~~~~~~

				// VkImageType
				if (m_CreateInfo.m_Type == CRI_IMAGE_BUFFER_CREATE_INFO::TYPE::_1D) m_ImageType = VK_IMAGE_TYPE_1D;
				if (m_CreateInfo.m_Type == CRI_IMAGE_BUFFER_CREATE_INFO::TYPE::_2D) m_ImageType = VK_IMAGE_TYPE_2D;
				if (m_CreateInfo.m_Type == CRI_IMAGE_BUFFER_CREATE_INFO::TYPE::_3D) m_ImageType = VK_IMAGE_TYPE_3D;

				// VkImageViewType
				if (m_CreateInfo.m_Type == CRI_IMAGE_BUFFER_CREATE_INFO::TYPE::_1D) m_ViewType = VK_IMAGE_VIEW_TYPE_1D;
				if (m_CreateInfo.m_Type == CRI_IMAGE_BUFFER_CREATE_INFO::TYPE::_2D) m_ViewType = VK_IMAGE_VIEW_TYPE_2D;
				if (m_CreateInfo.m_Type == CRI_IMAGE_BUFFER_CREATE_INFO::TYPE::_3D) m_ViewType = VK_IMAGE_VIEW_TYPE_3D;

				// VkImageUsageFlags
				if (COMMON::FORMAT::isColor(m_CreateInfo.m_Format)) m_ImageUsage |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
				if (COMMON::FORMAT::isDepth(m_CreateInfo.m_Format)) m_ImageUsage |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
				if (m_CreateInfo.m_Attachment == CRI_IMAGE_BUFFER_CREATE_INFO::ATTACHMENT::SAMPLED) m_ImageUsage |= VK_IMAGE_USAGE_SAMPLED_BIT;
				if (m_CreateInfo.m_Attachment == CRI_IMAGE_BUFFER_CREATE_INFO::ATTACHMENT::INPUT) m_ImageUsage |= VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;

				// VkImageAspectFlags
				if (COMMON::FORMAT::isColor(m_CreateInfo.m_Format)) m_ImageAspect |= VK_IMAGE_ASPECT_COLOR_BIT;
				if (COMMON::FORMAT::isDepth(m_CreateInfo.m_Format)) m_ImageAspect |= VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;

				// VkMemoryPropertyFlags
				if (m_CreateInfo.m_Storage == CRI_IMAGE_BUFFER_CREATE_INFO::STORAGE::DEVICE) m_ImageMemoryProperty = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
				if (m_CreateInfo.m_Storage == CRI_IMAGE_BUFFER_CREATE_INFO::STORAGE::HOST) m_ImageMemoryProperty = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

				m_Format = cri2vkn_Format(m_CreateInfo.m_Format);

				// ~~~~~~~~~~~~~~~~
				// VkImage
				// ~~~~~~~~~~~~~~~~

				// описываем VkImageCreateInfo
				VkImageCreateInfo _imageCI = {};

				_imageCI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
				_imageCI.imageType = m_ImageType;
				_imageCI.format = m_Format;
				_imageCI.extent.width = m_CreateInfo.m_Width;
				_imageCI.extent.height = m_CreateInfo.m_Height;
				_imageCI.extent.depth = 1;
				_imageCI.mipLevels = m_CreateInfo.m_MipLevels;
				_imageCI.arrayLayers = 1;
				_imageCI.samples = VK_SAMPLE_COUNT_1_BIT;
				_imageCI.tiling = VK_IMAGE_TILING_OPTIMAL;
				//_imageCI.tiling = VK_IMAGE_TILING_LINEAR;
				_imageCI.usage = m_ImageUsage;
				_imageCI.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

				VK_ASSERT_EX(_vknContext->vkCreateImage(_vknContext->getDevice(), &_imageCI, nullptr, &m_Image),
					"Не удалось создать VkImage.",
					{ destroy(); throw e_vkn_image_buffer_create_failed(); });

				// ~~~~~~~~~~~~~~~~
				// создаём VkDeviceMemory и связываем с VkImage
				// ~~~~~~~~~~~~~~~~

				//
				int32_t _memoryTypeIndex = _vknContext->getIndexMemory(m_ImageMemoryProperty);

				// запрашиваем требования к памяти
				VkMemoryRequirements _memReqs;
				_vknContext->vkGetImageMemoryRequirements(_vknContext->getDevice(), m_Image, &_memReqs);

				// описываем VkMemoryAllocateInfo
				VkMemoryAllocateInfo _memAllocI = {};

				_memAllocI.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				_memAllocI.pNext = nullptr;
				_memAllocI.allocationSize = _memReqs.size;
				_memAllocI.memoryTypeIndex = _memoryTypeIndex;

				// выделяем память
				VK_ASSERT_EX(_vknContext->vkAllocateMemory(_vknContext->getDevice(), &_memAllocI, nullptr, &m_Memory),
					"Не удалось аллоцировать память.",
					{ destroy(); throw e_vkn_image_buffer_create_failed(); });

				// связываем память и буфер
				VK_ASSERT_EX(_vknContext->vkBindImageMemory(_vknContext->getDevice(), m_Image, m_Memory, 0),
					"Не удалось привязать буфер к памяти.",
					{ destroy(); throw e_vkn_image_buffer_create_failed(); });

				// ~~~~~~~~~~~~~~~~
				// создаём VkImageView
				// ~~~~~~~~~~~~~~~~

				// описываем VkImageViewCreateInfo
				VkImageViewCreateInfo _depthStencilViewCI = {};

				_depthStencilViewCI.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				_depthStencilViewCI.viewType = m_ViewType;
				_depthStencilViewCI.format = m_Format;
				_depthStencilViewCI.subresourceRange = {};
				_depthStencilViewCI.subresourceRange.aspectMask = m_ImageAspect;
				_depthStencilViewCI.subresourceRange.baseMipLevel = 0;
				_depthStencilViewCI.subresourceRange.levelCount = 1;
				_depthStencilViewCI.subresourceRange.baseArrayLayer = 0;
				_depthStencilViewCI.subresourceRange.layerCount = 1;
				_depthStencilViewCI.image = m_Image;
				_vknContext->vkCreateImageView(_vknContext->getDevice(), &_depthStencilViewCI, nullptr, &m_View);
				VK_ASSERT_EX(_vknContext->vkCreateImageView(_vknContext->getDevice(), &_depthStencilViewCI, nullptr, &m_View),
					"Не удалось создать VkImageView",
					{ destroy(); throw e_vkn_image_buffer_create_failed(); });

				// ~~~~~~~~~~~~~~~~
				// ~~~~~~~~~~~~~~~~

				m_CreateInfo = *createInfo;

			}

			//==============================================================
			//==============================================================

			void CVKImageBuffer::destroy() {

				auto _vknContext = cri2vkn_Context(m_CreateInfo.m_CRIContext);

				_vknContext->vkDestroyImageView(_vknContext->getDevice(), m_View, nullptr);
				_vknContext->vkDestroyImage(_vknContext->getDevice(), m_Image, nullptr);
				_vknContext->vkFreeMemory(_vknContext->getDevice(), m_Memory, nullptr);

			}

			//==============================================================
			//==============================================================

		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE