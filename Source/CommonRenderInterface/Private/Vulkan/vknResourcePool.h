#ifndef VK_RESOURCE_POOL__H
#define VK_RESOURCE_POOL__H
////////////////////////////////////////////////////////////////
// секция компиляция файла
////////////////////////////////////////////////////////////////
#include "../../../RenderConfig.h"
#if defined(FE_RENDER) && defined(FE_RENDER_VULKAN) && FE_RENDER == FE_RENDER_VULKAN
////////////////////////////////////////////////////////////////
// секция родительского класса
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция форвард-декларации
////////////////////////////////////////////////////////////////
#include "../../Vulkan\Vulkan.h"
#include "../../CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////


namespace FE {

	namespace CRI {

		namespace VULKAN {

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Невозможно создать CVKResourcePool.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			class e_vk_resource_pool_create_fail : public e_vulkan_common {};



			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Информация для создания CVKResourcePool.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			struct VK_RESOURCE_POOL_CREATE_INFO {

				CVKContext*	m_Context;

			}; // struct VK_RESOURCE_POOL_CREATE_INFO



			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Пул ресурсов.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			class CVKResourcePool {

			// VKResourcePool.cpp
			public:

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Создание CVKResourcePool.

				\exception e_vk_resource_pool_create_fail Если создание CVKResourcePool невозможно.
				\param[in] context Контекст, который будет владеть пулом.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void create(const VK_RESOURCE_POOL_CREATE_INFO *createInfo);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Запросить множество VKRenderPass.

				\param[out] renderPasses Возвращает множество полученных VKRenderPass.
				\param[in] createInfos Информация для создания множества VKRenderPass.	
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline void create(VKRenderPass renderPass) { m_CreateRenderPasses.push_back(renderPass); }

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Запросить множество VKPipeline.

				\param[out] pipeline Возвращает множество полученных VKPipeline.
				\param[in] createInfo Информация для создания множества VKPipeline.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void getPipeline(CRIPipelineArr *pipeline, const CRI_PIPELINE_CI_ARR *createInfo);
				inline void create(VKPipeline pipeline) { m_CreatePipelines.push_back(pipeline); }

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Создать множество VKDataBuffer.

				\param[out] dataBuffer Возвращает множество полученных VKDataBuffer.
				\param[in] createInfo Информация для создания множества VKDataBuffer.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline void create(VKDataBuffer dataBuffer) { m_CreateDataBuffers.push_back(dataBuffer); }
				inline void update(VKDataBuffer dataBuffer) { m_UpdateDataBuffers.push_back(dataBuffer); }

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Запросить множество VKImageBuffer.

				\param[out] imageBuffers Возвращает множество полученных VKImageBuffer.
				\param[in] createInfos Информация для создания множества VKImageBuffer.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			
				inline void create(VKImageBuffer vknImageBuffer) { m_CreateImageBuffers.push_back(vknImageBuffer); }
				inline void update(VKImageBuffer imageBuffer) { m_UpdateImageBuffers.push_back(imageBuffer); }
				inline void destroy(VKImageBuffer imageBuffer) { 
					auto _it = std::find(m_DestroyImageBuffers.begin(), m_DestroyImageBuffers.end(), imageBuffer);
					if(_it == m_DestroyImageBuffers.end()) m_DestroyImageBuffers.push_back(imageBuffer); 
				}

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Запросить множество VKDrawBuffer.

				\param[out] drawBuffer Возвращает множество полученных VKDrawBuffer.
				\param[in] createInfo Информация для создания множества VKDrawBuffer.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline void create(VKDrawBuffer drawBuffer) { m_CreateDrawBuffers.push_back(drawBuffer); }

				inline void executeCmdBuffer(VkCommandBuffer cmdBuffer) { m_CmdBuffers.push_back(cmdBuffer); }
				inline const VkCommandBufferArr& getCmdBuffer(void) { return m_CmdBuffers; }

				inline VkCommandPool getVkPool(void) { return m_Pool; }
				inline VkDescriptorPool getVkDescriptorPool(void) { return m_DescriptorPool; }
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Обновить состояние пула.


				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void update(void);

				void get(VKRenderPass *vknRenderPass);
				void ret(VKRenderPass vknRenderPass);

				void get(VKImageBuffer *vknImageBuffer);
				void ret(VKImageBuffer vknImageBuffer);

			private:

				CVKContext*						m_Context;
				VKRenderPassArr					m_CreateRenderPasses;
				VKPipelineArr					m_CreatePipelines;
				VKDataBufferArr					m_CreateDataBuffers;
				VKImageBufferArr				m_CreateImageBuffers;
				VKDrawBufferArr					m_CreateDrawBuffers;

				VKDataBufferArr					m_UpdateDataBuffers;
				VKImageBufferArr				m_UpdateImageBuffers;

				VKRenderPassArr					m_DestroyRenderPasses;
				VKImageBufferArr				m_DestroyImageBuffers;

				VkCommandPool					m_Pool;
				VkCommandBufferArr				m_CmdBuffers;

				VkDescriptorPool				m_DescriptorPool;

				VKRenderPassArr					m_RenderPasses;
				VKImageBufferArr				m_ImageBuffers;

			}; // class CVKResourcePool

		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE

#endif // #if defined(FE_RENDER) && defined(FE_RENDER_VULKAN) && FE_RENDER == FE_RENDER_VULKAN

#endif // VK_RESOURCE_POOL__H