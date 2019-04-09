#ifndef VK_DRAW_BATCH__H
#define VK_DRAW_BATCH__H
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
#include "../../Vulkan/vknRenderPass.h"

namespace FE {

	namespace CRI {

		namespace VULKAN {

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			struct BATCH_DRAW_OBJECT {

				VKDataBuffer		m_Vertices;
				VKDataBuffer		m_Indices;
				VKDataBuffer		m_Uniforms;
				VKDrawBuffer		m_DrawBuffer;

			};
			using BATCH_DRAW_OBJECT_ARR = std::vector<BATCH_DRAW_OBJECT>;



			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			struct VKBatchNode_Pipeline {

				VKPipeline					m_VKPipeline;
				BATCH_DRAW_OBJECT_ARR		m_DrawObjects;
			};
			using VKBatchNode_PipelineArr = std::vector<VKBatchNode_Pipeline>;



			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Узел батч-графа. 
			
			Содержит множество VKPipeline.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			struct VKBatchNode_RenderSubpass {

				uint32_t						m_Number;
				VKBatchNode_PipelineArr			m_PipelineNodes;
			};
			using VKBatchNode_RenderSubpassArr = std::vector<VKBatchNode_RenderSubpass>;



			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			class VKBatchNode_RenderPass {
			
			public:

				uint32_t							m_Number;
				VKRenderPass						m_VKNRenderPass;
				VKBatchNode_RenderSubpassArr		m_SubpassNodes;
				VkCommandBufferArr					m_DrawBuffers;
				std::vector<VkFence>				m_WaitFences;
			
			}; // struct BATCH_PASS_NODE
			using VKBatchNode_RenderPassArr = std::vector<VKBatchNode_RenderPass>;



			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Описание для создания CVKBatch.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			struct VK_BATCH_CREATE_INFO {

				CVKContext*				m_VKNContext;
						
			}; // struct VK_BATCH_CREATE_INFO



			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			class CVKBatch {

			public:

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Создание CVKBatch.

				\param[in] createInfo Информация для создания.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void create(const VK_BATCH_CREATE_INFO *createInfo);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить VKRenderPass.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				VKRenderPass getRenderPass(const CRI_RENDER_PASS_CI *criCreateInfo, uint32_t* idSubpass);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить VKProgram.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				VKProgram getProgram(const CRI_PROGRAM_CREATE_INFO *criCreateInfo);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить CRIPipeline.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				VKPipeline getPipeline(const CRI_PIPELINE_CI *criCreateInfo);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить VKImageBuffer.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				VKImageBuffer getImageBuffer(const CRI_IMAGE_BUFFER_CREATE_INFO *criCreateInfo);


				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Добавить объект отрисовки.

				\param[in] drawObject Объект отрисовки.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void addDrawBuffer(CRIDrawBufferArr *drawbuffer);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Обновление CVKBatch.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void update(void);

				void getCmdBuffers(VkCommandBufferArr *cmdBuffers, uint32_t acquireNextImage);
				void getFences(std::vector<VkFence> *fences, uint32_t acquireNextImage);
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Подходит или нет объект отрисовки данному батчу.

				Если проход батча соотвествует проходу объекта отрисовки, объект отрисовки
				считается принадлежащим батчу и возвращается true. Если нет - false.
				\param[in] renderObject Объект отрисовки.
				\return Если объект отрисовки принадлежит батчу - true. Если нет - false.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				//bool isCheck(const VK_RENDER_OBJECT *renderObject);

			// VKDrawBatch.hpp
			private:

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief .
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				//void updateVKRenderPass(const CRI_RENDER_PASS_CI *criCreateInfo, VKRenderPass *vknRenderPass, CRI_RENDER_PASS_IMPL_CI *criImplCreateInfo);

			// данные
			private:

				VKContext							m_VKNContext;
				VK_BATCH_CREATE_INFO				m_CreateInfo;
				VkCommandPool						m_Pool;
				VKBatchNode_RenderPassArr			m_BatchNodeRenderPasses;
				
			}; // class CVKDrawBatch

		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE

#include "vknBatch.hpp"

#endif // #if defined(FE_RENDER) && defined(FE_RENDER_VULKAN) && FE_RENDER == FE_RENDER_VULKAN

#endif // VK_DRAW_BATCH__H