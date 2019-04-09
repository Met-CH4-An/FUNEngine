////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "vknDrawBuffer.h"
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
#include "vknResourcePool.h"
#include "../../Vulkan/vknRenderPass.h"
#include "../../Vulkan/vknPipeline.h"
#include "../../Vulkan/vknDataBuffer.h"
#include "../../Vulkan/vknImageBuffer.h"

#include "../../CRIContext.h"
#include "../../CRIRenderPass.h"
#include "../../CRIPipeline.h"
#include "../../CRIDataBuffer.h"
#include "../CRIDrawBuffer.h"

namespace FE {

	namespace CRI {

		namespace VULKAN {

			//==============================================================
			//==============================================================

			void CVKDrawBuffer::get(const CRI_DRAW_BUFFER_CREATE_INFO *createInfo, CRIDrawBuffer *drawBuffer) {

				//*drawBuffer = nullptr;
				
				//
				
				auto _vknContext = cri2vkn_Context(createInfo->m_Context);
				//auto _vknContext = nullptr;
				auto _vknResPool = _vknContext->getResourcePool();

				// новый CRIDrawBuffer
				CRIDrawBuffer _criDrawBuffer = new CCRIDrawBuffer(createInfo);
				_criDrawBuffer->create();

				// если новый CRIDrawBuffer удачен
				if (_criDrawBuffer->isValid()) {

					// новый VKPipeline
					VKDrawBuffer _vknDrawBuffer = new CVKDrawBuffer(createInfo);

					_vknDrawBuffer->create();

					// сохраняем
					_vknDrawBuffer->setCRI(_criDrawBuffer);
					_criDrawBuffer->setImpl(_vknDrawBuffer);

					*drawBuffer = _criDrawBuffer;

					//
					_vknResPool->create(_vknDrawBuffer);

				} // if (_criDrawBuffer->isValid())*/

			}

			//==============================================================
			//==============================================================

			void CVKDrawBuffer::create() {

				// перебираем пиплайны
				//for (uint32_t ctDrawBuffer = 0; ctDrawBuffer < drawBuffers->size(); ++ctDrawBuffer) {
					
					//auto _criDrawBuffer = (*drawBuffers)[ctDrawBuffer]->getCRI();
					//auto _vknDrawBuffer = (*drawBuffers)[ctDrawBuffer];
					//auto _vknContext = static_cast<VULKAN::CVKContext*>(_vknDrawBuffer->m_CI.m_Context);
					auto _CI = this->m_CI;
					
					// VkDescriptorSet
					
					this->m_DescriptorSet = cri2vkn_Pipeline(this->m_CI.m_Pipeline)->getDescriptorSet();
					std::vector<VkWriteDescriptorSet> _writeDescriptorSets = {};

					std::vector<VkDescriptorBufferInfo> bufferInfos(_CI.m_UniformDBs.size());

					// перебираем DataBuffer
					for (uint32_t ctDataBuffer = 0; ctDataBuffer < _CI.m_UniformDBs.size(); ++ctDataBuffer) {
						
						auto _uniformDataBufferI = _CI.m_UniformDBs[ctDataBuffer];
						auto _vknDataBuffer = std::static_pointer_cast<VULKAN::CVKDataBuffer>(_uniformDataBufferI.m_Buffer);

						// VkDescriptorBufferInfo
						VkDescriptorBufferInfo &_descriptorBuffer = bufferInfos[ctDataBuffer];
						_descriptorBuffer.buffer = _vknDataBuffer->getVkBuffer();
						_descriptorBuffer.offset = 0;
						_descriptorBuffer.range = _vknDataBuffer->getRealSize();

						// VkWriteDescriptorSet
						VkWriteDescriptorSet writeDescriptorSet = {};

						writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
						writeDescriptorSet.dstSet = this->m_DescriptorSet;
						writeDescriptorSet.descriptorCount = 1;
						writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
						writeDescriptorSet.pBufferInfo = &_descriptorBuffer;
						writeDescriptorSet.dstBinding = _uniformDataBufferI.m_Binding;

						_writeDescriptorSets.push_back(writeDescriptorSet);
					}

					std::vector<VkDescriptorImageInfo> ImageInfos(_CI.m_UniformIBs.size());

					// перебираем ImageBuffer
					for (uint32_t ctImageBuffer = 0; ctImageBuffer < _CI.m_UniformIBs.size(); ++ctImageBuffer) {

						auto _uniformImageBufferI = _CI.m_UniformIBs[ctImageBuffer];
						auto _vknImageBuffer = cri2vk_ImageBuffer(_uniformImageBufferI.m_Buffer);

						// VkDescriptorImageInfo
						VkDescriptorImageInfo &_descriptorImage = ImageInfos[ctImageBuffer];
						_descriptorImage.sampler = VK_NULL_HANDLE;
						_descriptorImage.imageView = _vknImageBuffer->getVkImageView();
						_descriptorImage.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

						// VkWriteDescriptorSet
						VkWriteDescriptorSet writeDescriptorSet = {};
						static uint32_t asd = 1;
						writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
						writeDescriptorSet.dstSet = this->m_DescriptorSet;
						writeDescriptorSet.descriptorCount = 1;
						writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
						writeDescriptorSet.pImageInfo = &_descriptorImage;
						writeDescriptorSet.dstBinding = ctImageBuffer;
						//writeDescriptorSet.dstBinding = asd;
						--asd;

						_writeDescriptorSets.push_back(writeDescriptorSet);
					}

					m_Context->vkUpdateDescriptorSets(m_Context->getDevice(), _writeDescriptorSets.size(), _writeDescriptorSets.data(), 0, NULL);

				//}
			}

			//==============================================================
			//==============================================================

			inline CVKDrawBuffer::CVKDrawBuffer(const CRI_DRAW_BUFFER_CREATE_INFO *createInfo)
				: m_CI(*createInfo) {

				m_Context = cri2vkn_Context(m_CI.m_Context);
				m_RenderPass = std::static_pointer_cast<CCRIRenderPassPrivate>(m_CI.m_RenderPass)->getImpl();
				m_Pipeline = cri2vkn_Pipeline(m_CI.m_Pipeline);
				m_Vertices = std::static_pointer_cast<VULKAN::CVKDataBuffer>(m_CI.m_Vertices);
				m_Indices = std::static_pointer_cast<VULKAN::CVKDataBuffer>(m_CI.m_Indices);

				//m_Context = static_cast<VKContext>(m_CI.m_Context);
				//m_RenderPass = static_cast<VKRenderPass>(m_CI.m_RenderPass->getImpl());
				//m_RenderPass = std::static_pointer_cast<VULKAN::CCRIRenderPassImpl>(m_CI.m_RenderPass)->getConst();
				//m_Pipeline = std::static_pointer_cast<VULKAN::CCRIPipelineImpl>(m_CI.m_Pipeline)->getConst();
				//m_Vertices = static_cast<VKDataBuffer>(m_CI.m_Vertices->getHardware());
				//m_Indices = static_cast<VKDataBuffer>(m_CI.m_Indices->getHardware());
//
			}

			//==============================================================
			//==============================================================

		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE

#endif // #if defined(FE_RENDER) && defined(FE_RENDER_VULKAN) && FE_RENDER == FE_RENDER_VULKAN