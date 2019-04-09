#ifndef VK_PIPELINE__H
#define VK_PIPELINE__H
////////////////////////////////////////////////////////////////
// секция компиляция файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция родительского класса
////////////////////////////////////////////////////////////////
#include "../CRIPipeline.h"
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

		using CCRIPipelinePrivate = VulkanRenderInterfaceImpl<VULKAN::CVKPipeline, CCRIPipeline>;

		namespace VULKAN {

			inline VKPipeline cri2vkn_Pipeline(CRIPipeline criPipeilne) { return std::static_pointer_cast<CCRIPipelinePrivate>(criPipeilne)->getImpl(); }

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Реализация графического конвеера.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			class CVKPipeline {

			public:

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Конструктор.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				CVKPipeline(VKContext vknContext);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void create(const CRI_PIPELINE_CI *createInfo);
				
				void reCreate(const CRI_PIPELINE_CI *createInfo);
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void isCompatible(const CRI_PIPELINE_CI *createInfo) const;

			public:
				inline const CRI_PIPELINE_CI& getCRICreateInfo(void) const { return m_CI; };
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить VkPipeline.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline VkPipeline getVkPipeline(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить VkDescriptorSet.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				VkDescriptorSet getDescriptorSet(void);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить VkPipelineLayout.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline VkPipelineLayout getPipelineLayout(void) const;

			// данные
			private:
				
				CRI_PIPELINE_CI		m_CI;

				VKContext									m_VKNContext;
				VKResourcePool								m_VKResourcePool;

				VkPipelineInputAssemblyStateCreateInfo		m_IAStateCI;
				VkPipelineRasterizationStateCreateInfo		m_RasterizationStateCI;
				VkPipelineColorBlendAttachmentStateArr		m_ColorBlendAttachmentCIs;
				VkPipelineColorBlendStateCreateInfo			m_ColorBlendStateCI;

				VkPipeline									m_Pipeline;
				VkPipelineCache								m_PipelineCache;
				VkPipelineLayout							m_PipelineLayout;
				VkDescriptorSetLayoutArr					m_DescriptorSetLayouts;

			}; // class CVKPipeline

		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE

#include "vknPipeline.hpp"

#endif // VK_DRAW_BATCH__H