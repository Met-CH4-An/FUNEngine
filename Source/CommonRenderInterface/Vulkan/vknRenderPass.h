#ifndef VK_RENDER_PASS__H
#define VK_RENDER_PASS__H
////////////////////////////////////////////////////////////////
// секция компиляция файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция родительского класса
////////////////////////////////////////////////////////////////
//#include "../CRIRenderPass.h"
////////////////////////////////////////////////////////////////
// секция форвард-декларации
////////////////////////////////////////////////////////////////
#include "Vulkan.h"
#include "../CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////
#include "../CRIRenderPass.h"
#include "../../Maths/maths.h"

namespace FE {

	namespace CRI {

		namespace VULKAN {

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			class e_vulkan_common_render_pass_create_fail : public e_vulkan_common {};



			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Проход рендера.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			class CVKRenderPass {

			public:

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Конструктор.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				CVKRenderPass(VKContext vknContext);
				
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Деструктор.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				~CVKRenderPass(void);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Создать VKRenderPass.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void create(const CRI_RENDER_PASS_CI *criCreateInfo);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Уничтожить VKRenderPass.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void destroy(void);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Объединить VKRenderPass.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void add(const CRI_RENDER_PASS_CI *criCreateInfo);

			public:

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить контекст.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline VKContext getContext(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить ширину.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline uint32_t getWidth(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить высоту.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline uint32_t getHeight(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить количество подпроходов.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline uint32_t getSubpassCount(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить VkRenderPass
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline VkRenderPass getVkRenderPass(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить массив VkFramebuffer.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline const VkFramebufferArr& getVkFramebuffers(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить массив VkClearValue.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline const VkClearValueArr& getClearValue(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить массив VkClearValue.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				VKImageBufferArr& getVKNImageBuffers(void) { return m_vknImageBuffers; }
				inline uint32_t getAttachmentColorRefPerSubpass(uint32_t idSubpass) { return m_vkAttachmentColorPerSubpassReferences[idSubpass].size(); }
			//
			private:

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void create(void);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void prepareSubpass(const CRI_RENDER_PASS_CI *renderPassCreateInfo);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				uint32_t prepareAttachmentDescription(const VKImageBuffer vknImageBuffer, const vec4 *clearColor);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void prepareAttachmentReference(const uint32_t idSubpass, const uint32_t idAttachment, const VKImageBuffer vknImageBuffer, const bool input);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void prepareDependencies(void);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void prepareFramebuffer(void);

			// данные
			private:

				CRI_RENDER_PASS_CI_ARR			m_criCreateInfos;

				VKContext						m_VKNContext;
				VKImageBufferArr				m_vknImageBuffers;
				uint32_t						m_Width;
				uint32_t						m_Height;
				bool							m_Present;	
				uint32_t						m_SubpassCount;

				VkSubpassDescriptionArr			m_vkSubpassDescriptions;
				VkAttachmentReferenceArrs		m_vkAttachmentColorPerSubpassReferences;
				VkAttachmentReferenceArrs		m_vkAttachmentDepthPerSubpassReferences;
				VkAttachmentReferenceArrs		m_vkAttachmentInputPerSubpassReferences;

				VkSubpassDependencyArr			m_vkSubpassDependencies;				
				VkAttachmentDescriptionArr		m_vkAttachmentDescs;
				VkRenderPass					m_vkRenderPass;				
				VkImageViewArrs					m_vkImageViewPerFramebuffers;
				VkFramebufferArr				m_vkFramebuffers;
				VkClearValueArr					m_vkClearValues;
				
			}; // class CVKRenderPass

			using CCRIRenderPassPrivate = VulkanRenderInterfaceImpl<VULKAN::CVKRenderPass, CCRIRenderPass>;
			inline VKRenderPass cri2vkn_RenderPass(CRIRenderPass criRenderPass) { return static_cast<CCRIRenderPassPrivate*>(criRenderPass)->getImpl(); }
			inline const VKRenderPass cri2vkn_RenderPassConst(const CRIRenderPass criRenderPass) { return static_cast<const CCRIRenderPassPrivate*>(criRenderPass)->getImpl(); }

		} // namespace VULKAN	

	} // namespace RENDER

} // namespace FE

#include "vknRenderPass.hpp"

#endif // VK_RENDER_PASS__H