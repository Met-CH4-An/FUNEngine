#ifndef VK_IMAGE_BUFFER__H
#define VK_IMAGE_BUFFER__H
////////////////////////////////////////////////////////////////
// ������ ���������� �����
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ ������������� ������
////////////////////////////////////////////////////////////////
#include "../CRIImageBuffer.h"
////////////////////////////////////////////////////////////////
// ������ �������-����������
////////////////////////////////////////////////////////////////
#include "Vulkan.h"
#include "../CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// ������ ��� ����������
////////////////////////////////////////////////////////////////

namespace FE {

	namespace CRI {

		namespace VULKAN {

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
				/*!	\brief �����������.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				CVKImageBuffer(void);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief ����������.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				~CVKImageBuffer(void);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief ������� VKImageBuffer. 
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void create(const CRI_IMAGE_BUFFER_CREATE_INFO *createInfo);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief ���������� VKImageBuffer.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void destroy(void);

			public:						

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief �������� VkImageView.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline VkImageView getVkImageView(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief �������� VkFormat.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline VkFormat getFormat(void) const;

			public:

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief ��� VKImageBuffer ��� �����?

				\return true - ��, false - ���
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline bool isColor(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief ��� VKImageBuffer ��� �������?

				\return true - ��, false - ���
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

		using CCRIImageBufferPrivate = VulkanRenderInterfaceImpl<VULKAN::CVKImageBuffer, CCRIImageBuffer>;
		inline VULKAN::VKImageBuffer cri2vk_ImageBuffer(CRIImageBuffer criImageBuffer) { return static_cast<CCRIImageBufferPrivate*>(criImageBuffer)->getImpl(); }

	} // namespace RENDER

} // namespace FE

#include "vknImagerBuffer.hpp"

#endif // VK_IMAGE_BUFFER__H