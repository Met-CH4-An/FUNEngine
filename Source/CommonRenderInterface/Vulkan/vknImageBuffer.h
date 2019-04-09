#ifndef VK_IMAGE_BUFFER__H
#define VK_IMAGE_BUFFER__H
////////////////////////////////////////////////////////////////
// секция компиляция файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция родительского класса
////////////////////////////////////////////////////////////////
#include "../CRIImageBuffer.h"
////////////////////////////////////////////////////////////////
// секция форвард-декларации
////////////////////////////////////////////////////////////////
#include "Vulkan.h"
#include "../CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////

namespace FE {

	namespace CRI {

		using CCRIImageBufferPrivate = VulkanRenderInterfaceImpl<VULKAN::CVKImageBuffer, CCRIImageBuffer>;

		namespace VULKAN {

			inline VKImageBuffer cri2vk_ImageBuffer(CRIImageBuffer criImageBuffer) { return std::static_pointer_cast<CCRIImageBufferPrivate>(criImageBuffer)->getImpl(); }

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			class e_vkn_image_buffer_create_failed : public e_vulkan_common {};
			


			//==============================================================
			/*!	\brief
			*/
			//==============================================================
			class CVKImageBuffer {
			
			public:

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Конструктор.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				CVKImageBuffer(void);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Деструктор.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				~CVKImageBuffer(void);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Создать VKImageBuffer. 
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void create(const CRI_IMAGE_BUFFER_CREATE_INFO *createInfo);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Уничтожить VKImageBuffer.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void destroy(void);

			public:						

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить VkImageView.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline VkImageView getVkImageView(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить VkFormat.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline VkFormat getFormat(void) const;

			public:

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Это VKImageBuffer для цвета?

				\return true - да, false - нет
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline bool isColor(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Это VKImageBuffer для глубины?

				\return true - да, false - нет
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline bool isDepth(void) const;

			private:

				CRI_IMAGE_BUFFER_CREATE_INFO	m_CreateInfo;
				VkFormat						m_Format;
				VkImage							m_Image;
				VkImageType						m_ImageType;
				VkImageUsageFlags				m_ImageUsage;
				VkImageAspectFlags				m_ImageAspect;
				VkImageView						m_View;
				VkImageViewType					m_ViewType;
				VkDeviceMemory					m_Memory;				
				VkMemoryPropertyFlags			m_ImageMemoryProperty;
				
			}; // class CVKImageBuffer

		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE

#include "vknImagerBuffer.hpp"

#endif // VK_IMAGE_BUFFER__H