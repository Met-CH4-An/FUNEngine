////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "vknResourcePool.h"
////////////////////////////////////////////////////////////////
// секция компиляция файла
////////////////////////////////////////////////////////////////
#include "../../../RenderConfig.h"
#if defined(FE_RENDER) && defined(FE_RENDER_VULKAN) && FE_RENDER == FE_RENDER_VULKAN
////////////////////////////////////////////////////////////////
// секция форвард-декларации
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция для исключений
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////
#include "../../Vulkan\vknContext.h"
#include "vknBatch.h"
#include "../../Vulkan/vknRenderPass.h"
#include "../../Vulkan/vknPipeline.h"
#include "../../Vulkan\vknDataBuffer.h"
#include "../../Vulkan/vknImageBuffer.h"
#include "vknDrawBuffer.h"
#include "vknRecordCmdBufferTask.h"

#include "../../CRIContext.h"
#include "../../CRIRenderPass.h"
#include "../../CRIPipeline.h"
#include "../../CRIDataBuffer.h"
#include "../../CRIImageBuffer.h"
#include "../CRIDrawBuffer.h"

namespace FE {

	namespace CRI {

		//==============================================================
		//==============================================================

		namespace VULKAN {

			//==============================================================
			//==============================================================

			void CVKResourcePool::create(const VK_RESOURCE_POOL_CREATE_INFO *createInfo) {
				
				m_Context = createInfo->m_Context;

				VkDescriptorPoolSizeArr _poolSizes;

				// описываем VkDescriptorPoolSize
				VkDescriptorPoolSize _poolSize = {};

				_poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
				_poolSize.descriptorCount = 100;

				_poolSizes.push_back(_poolSize);

				_poolSize = {};

				_poolSize.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				_poolSize.descriptorCount = 100;

				_poolSizes.push_back(_poolSize);

				_poolSize = {};

				_poolSize.type = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
				_poolSize.descriptorCount = 100;

				_poolSizes.push_back(_poolSize);

				// описываем VkDescriptorPoolCreateInfo
				VkDescriptorPoolCreateInfo _descriptorPoolCI = {};

				_descriptorPoolCI.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
				_descriptorPoolCI.pNext = NULL;
				_descriptorPoolCI.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
				_descriptorPoolCI.maxSets = 1000;
				_descriptorPoolCI.poolSizeCount = static_cast<uint32_t>(_poolSizes.size());
				_descriptorPoolCI.pPoolSizes = _poolSizes.data();

				// создаём vkCreateDescriptorPool
				VkDescriptorPool _pool;
				VK_ASSERT_EX(m_Context->vkCreateDescriptorPool(m_Context->getDevice(), &_descriptorPoolCI, nullptr, &m_DescriptorPool), "", );

			}

			//==============================================================
			//==============================================================

			void CVKResourcePool::get(VKRenderPass *vknRenderPass) {

				

			}

			//==============================================================
			//==============================================================

			void CVKResourcePool::ret(VKRenderPass vknRenderPass) {

			

			}

			//==============================================================
			//==============================================================

			void CVKResourcePool::get(VKImageBuffer *vknImageBuffer) {

				

			}

			//==============================================================
			//==============================================================

			void CVKResourcePool::ret(VKImageBuffer vknImageBuffer) {

			
	
			}

			//==============================================================
			//==============================================================

			/*void CVKResourcePool::allocDrawBatch(VKDrawBatchArr *drawBatches, VK_DRAW_BATCH_CREATE_INFO_ARR *createInfo) {

				size_t _countCI = createInfo->size();
				drawBatches->resize(_countCI);

				// перебираем createInfo
				for (uint32_t ctCI = 0; ctCI < _countCI; ++ctCI) {

					// новый объект
					VKDrawBatch _newBatch = new CVKDrawBatch();

					// сохраняем описание
					_newBatch->setCreateInfo(&(*createInfo)[ctCI]);

					(*drawBatches)[ctCI] = _newBatch;

					// добавляем в кэш для последующего создания
					m_DrawBatches.push_back(_newBatch);

				} // for (uint32_t ctCI = 0; ctCI < _countCI; ++ctCI)

			}*/

			//==============================================================
			//==============================================================

			void CVKResourcePool::getPipeline(CRIPipelineArr *pipeline, const CRI_PIPELINE_CI_ARR *createInfo) {
				
				/*size_t _countCI = createInfo->size();
				pipeline->resize(_countCI);

				// перебираем createInfo
				for (uint32_t ctCI = 0; ctCI < _countCI; ++ctCI) {

					auto &itCRIPipelineCI = (*createInfo)[ctCI];

					// новый объект
					CRIPipeline _CRIPipeline = new CCRIPipeline();
					VKPipeline _VKPipeline = new CVKPipeline();

					// сохраняем
					_VKPipeline->setCRI(_CRIPipeline);
					_CRIPipeline->setImpl(_VKPipeline);
					_CRIPipeline->create(&itCRIPipelineCI);

					(*pipeline)[ctCI] = _CRIPipeline;

					// добавляем в кэш для последующего создания
					m_CreatePipelines.push_back(_VKPipeline);

				} // for (uint32_t ctCI = 0; ctCI < _countCI; ++ctCI)*/
				
			}

			//==============================================================
			//==============================================================

			/*void CVKResourcePool::getDrawBuffer(CRIDrawBufferArr *drawBuffer, const CRI_DRAW_BUFFER_CREATE_INFO_ARR *createInfo) {

				size_t _countCI = createInfo->size();
				drawBuffer->resize(_countCI);

				// перебираем createInfo
				for (uint32_t ctCI = 0; ctCI < _countCI; ++ctCI) {

					//auto &itCRIdrawBuffer = (*drawBuffer)[ctCI];
					auto &itCRIdrawBufferCI = (*createInfo)[ctCI];

					// новый объект
					CRIDrawBuffer _CRIDrawBuffer = new CCRIDrawBuffer();
					VKDrawBuffer _VKDrawBuffer = new CVKDrawBuffer();

					// сохраняем
					_VKDrawBuffer->setCRI(_CRIDrawBuffer);
					_CRIDrawBuffer->setImpl(_VKDrawBuffer);
					_CRIDrawBuffer->create(&itCRIdrawBufferCI);

					(*drawBuffer)[ctCI] = _CRIDrawBuffer;

					// добавляем в кэш для последующего создания
					m_CreateDrawBuffers.push_back(_VKDrawBuffer);

					//m_UpdatedrawBuffers.push_back(_vkdrawBuffer);

				} // for (uint32_t ctCI = 0; ctCI < _countCI; ++ctCI)
			}*/

			//==============================================================
			//==============================================================

			

			//==============================================================
			//==============================================================
			
			void CVKResourcePool::update(void) {
				
				// ~~~~~~~~~~~~~~~~
				// ~~~~~~~~~~~~~~~~
				
				//CVKDataBuffer::create(&m_CreateDataBuffers);
				//CVKImageBuffer::create(&m_CreateImageBuffers);

				// ~~~~~~~~~~~~~~~~
				// ~~~~~~~~~~~~~~~~

				//CVKDataBuffer::update(&m_UpdateDataBuffers);

				// ~~~~~~~~~~~~~~~~
				// ~~~~~~~~~~~~~~~~
				//CVKRenderPass::create(&m_CreateRenderPasses);
				//for (const auto &itVKRenderPass : m_CreateRenderPasses) {

					//itVKRenderPass->create(m_Context);
				//}

				//CVKPipeline::create(&m_CreatePipelines);
				

				// ~~~~~~~~~~~~~~~~
				// ~~~~~~~~~~~~~~~~
				//CVKDrawBuffer::create(&m_CreateDrawBuffers);

				//CVKImageBuffer::destroy(&m_DestroyImageBuffers);
								
				// очищаем массивы с ресурсами
				m_CreateRenderPasses.clear();
				m_CreatePipelines.clear();
				m_CreateDataBuffers.clear();
				m_CreateImageBuffers.clear();
				m_UpdateDataBuffers.clear();
				m_CreateDrawBuffers.clear();
				m_CreateDrawBuffers.clear();
				m_DestroyImageBuffers.clear();
				//m_CreatePipelines.clear();

				//m_DestroyPipelines.clear();
				
			}

			//==============================================================
			//==============================================================
		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE

#endif // #if defined(FE_RENDER) && defined(FE_RENDER_VULKAN) && FE_RENDER == FE_RENDER_VULKAN