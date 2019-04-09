////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "vknBatch.h"
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
#include "vknDrawBuffer.h"
#include "../../Vulkan/vknRenderPass.h"
#include "../../Vulkan/vknProgram.h"
#include "../../Vulkan/vknPipeline.h"
#include "../../Vulkan/vknDataBuffer.h"
#include "../../Vulkan/vknImageBuffer.h"

#include "../CRIDrawBuffer.h"
#include "../../CRIRenderPass.h"
#include "../../CRIPipeline.h"
#include "../../CRIDataBuffer.h"
#include "../../CRIImageBuffer.h"



namespace FE {

	namespace CRI {

		namespace VULKAN {

			//==============================================================
			//==============================================================

			void CVKBatch::create(const VK_BATCH_CREATE_INFO *createInfo) {

				// информация для создания для текущего CVKDrawBatch
				m_CreateInfo = *createInfo;
				//vknContext _VKContext = m_CreateInfo.m_Context;
				//m_VKNContext = m_CreateInfo.m_VKNContext;
				
				
			}

			//==============================================================
			//==============================================================

			VKRenderPass CVKBatch::getRenderPass(const CRI_RENDER_PASS_CI *criRenderPassCI, uint32_t* idSubpass) {
				
				// перебираем VKBatchNode_RenderPass
				for (size_t ct_renderPassNode = 0; ct_renderPassNode < m_BatchNodeRenderPasses.size(); ++ct_renderPassNode) {

					// ~~~~~~~~~~~~~~~~
					// VKBatchNode_RenderPass
					// ~~~~~~~~~~~~~~~~

					VKBatchNode_RenderPass &_vknNodeRenderPass = m_BatchNodeRenderPasses[ct_renderPassNode];

					// ~~~~~~~~~~~~~~~~
					// VKRenderPass
					// ~~~~~~~~~~~~~~~~

					VKRenderPass _vknRenderPass = _vknNodeRenderPass.m_VKNRenderPass;

					_vknRenderPass->add(criRenderPassCI);

					for (size_t ct_subPassNode = 0; ct_subPassNode < _vknNodeRenderPass.m_SubpassNodes.size(); ++ct_subPassNode) {

						auto &_vknSubpassNode = _vknNodeRenderPass.m_SubpassNodes[ct_subPassNode];

						for (size_t ct_pipelineNode = 0; ct_pipelineNode < _vknSubpassNode.m_PipelineNodes.size(); ++ct_pipelineNode) {

							auto &_vknPipelineNode = _vknSubpassNode.m_PipelineNodes[ct_pipelineNode];

							auto _criCreateInfo = _vknPipelineNode.m_VKPipeline->getCRICreateInfo();

							//_criCreateInfo.m_RenderPass = _vknRenderPass;

							_vknPipelineNode.m_VKPipeline->create(&_criCreateInfo);

						}

					}

					// ~~~~~~~~~~~~~~~~
					// VKBatchNode_RenderSubpass
					// ~~~~~~~~~~~~~~~~

					VKBatchNode_RenderSubpass _vknNodeRenderSubpass;

					_vknNodeRenderPass.m_SubpassNodes.push_back(_vknNodeRenderSubpass);

					// ~~~~~~~~~~~~~~~~
					// ~~~~~~~~~~~~~~~~

					*idSubpass = _vknRenderPass->getSubpassCount() - 1;

					return _vknRenderPass;
				}

				// ~~~~~~~~~~~~~~~~
				// VKRenderPass
				// ~~~~~~~~~~~~~~~~

				VKRenderPass _vknRenderPass = std::make_shared<CVKRenderPass>(m_VKNContext);

				_vknRenderPass->create(criRenderPassCI);

				// ~~~~~~~~~~~~~~~~
				// VKBatchNode_RenderPass
				// ~~~~~~~~~~~~~~~~

				VKBatchNode_RenderPass			_vknNodeRenderPass;
				VKBatchNode_RenderSubpass		_vknNodeRenderSubpass;				

				_vknNodeRenderPass.m_VKNRenderPass = _vknRenderPass;
				_vknNodeRenderPass.m_SubpassNodes.push_back(_vknNodeRenderSubpass);

				m_BatchNodeRenderPasses.push_back(_vknNodeRenderPass);

				// ~~~~~~~~~~~~~~~~
				// ~~~~~~~~~~~~~~~~

				*idSubpass = 0;

				return _vknRenderPass;
						
			}

			//==============================================================
			//==============================================================

			VKProgram CVKBatch::getProgram(const CRI_PROGRAM_CREATE_INFO *criCreateInfo) {

				// ~~~~~~~~~~~~~~~~
				// VKProgram
				// ~~~~~~~~~~~~~~~~

				VKProgram _vknProgram = std::make_shared<CVKProgram>();

				_vknProgram->create(criCreateInfo);

				return _vknProgram;
			}

			//==============================================================
			//==============================================================

			VKPipeline  CVKBatch::getPipeline(const CRI_PIPELINE_CI *criCreateInfo) {

				VKPipeline _vknPipeline;
				// ~~~~~~~~~~~~~~~~				
				// VKBatchNode_RenderPass
				// ~~~~~~~~~~~~~~~~

				for (size_t ct_renderPassNode = 0; ct_renderPassNode < m_BatchNodeRenderPasses.size(); ++ct_renderPassNode) {

					// текущий
					auto &_nodeRenderPass = m_BatchNodeRenderPasses[ct_renderPassNode];

					if (_nodeRenderPass.m_VKNRenderPass == cri2vkn_RenderPass(criCreateInfo->m_RenderPass)) {

						// ~~~~~~~~~~~~~~~~
						// VKBatchNode_RenderSubpass
						// ~~~~~~~~~~~~~~~~

						for (size_t ct_renderSubpassNode = 0; ct_renderSubpassNode < _nodeRenderPass.m_SubpassNodes.size(); ++ct_renderSubpassNode) {

							// текущий
							auto &_nodeRenderSubpass = _nodeRenderPass.m_SubpassNodes[ct_renderSubpassNode];

							if (ct_renderSubpassNode == criCreateInfo->m_RenderPass->getIDSubpass()) {

								// ~~~~~~~~~~~~~~~~
								// VKPipeline
								// ~~~~~~~~~~~~~~~~

								_vknPipeline = std::make_shared<CVKPipeline>(m_VKNContext);

								_vknPipeline->create(criCreateInfo);

								VKBatchNode_Pipeline _pipelineNode;
								_pipelineNode.m_VKPipeline = _vknPipeline;

								_nodeRenderSubpass.m_PipelineNodes.push_back(_pipelineNode);

							}

						}
					}
				}

				return _vknPipeline;
			}

			//==============================================================
			//==============================================================

			VKImageBuffer CVKBatch::getImageBuffer(const CRI_IMAGE_BUFFER_CREATE_INFO *criCreateInfo) {

				// ~~~~~~~~~~~~~~~~
				// new ImageBuffer
				// ~~~~~~~~~~~~~~~~

				auto _vknImageBuffer = std::make_shared<CVKImageBuffer>();

				// ~~~~~~~~~~~~~~~~
				// create ImageBuffer
				// ~~~~~~~~~~~~~~~~

				_vknImageBuffer->create(criCreateInfo);

				// ~~~~~~~~~~~~~~~~
				// ~~~~~~~~~~~~~~~~

				return _vknImageBuffer;

			}

			//==============================================================
			//==============================================================
			
			void CVKBatch::addDrawBuffer(CRIDrawBufferArr *drawbuffer) {

				// перебираем объекты отрисовки
				for (auto &itDrawBuffer : *drawbuffer) {

					//auto _CRIRenderPassCI = itDrawBuffer->getRenderPass()->getCreateInfo();
					auto _VKDrawBuffer = static_cast<VKDrawBuffer>(itDrawBuffer->getImpl());
					auto _VKRenderPass = _VKDrawBuffer->getRenderPass();
					auto _VKPipelne = _VKDrawBuffer->getPipeline();
					auto _VKVertices = _VKDrawBuffer->getVertices();
					auto _VKIndices = _VKDrawBuffer->getIndices();
					//auto _VKUniforms = static_cast<VKDataBuffer>(_VKDrawBuffer->getUniforms()->getImpl());
					auto _numberSubpass = _VKDrawBuffer->getSubpass();
					bool _newPassNode = true;
					bool _newSubpassNode = true;
					bool _newPipelineNode = true;

					// перебираем узлы, содержащие VKRenderPass
					for (auto &itRenderPassNode : m_BatchNodeRenderPasses) {

						// если узел содержит такой же VKRenderPass что и объект отрисовки
						if (itRenderPassNode.m_VKNRenderPass == _VKRenderPass) {
						
							_newPassNode = false;
							
							// перебираем узлы, содержащие 
							//for (auto &itSubpassNode : itRenderPassNode.m_SubpassNodes) {

							// перебираем VKBatchNode_RenderPass
							for (size_t ctSubpassNode = 0; ctSubpassNode < itRenderPassNode.m_SubpassNodes.size(); ++ctSubpassNode) {

								

								if (ctSubpassNode == _numberSubpass) {

									// текущий VKBatchNode_RenderPass
									auto &_nodeRenderSubpass = itRenderPassNode.m_SubpassNodes[ctSubpassNode];

								//if (itSubpassNode.m_Number == _numberSubpass) {

									_newSubpassNode = false;

									for (auto &itPipelineNode : _nodeRenderSubpass.m_PipelineNodes) {

										//
										if (itPipelineNode.m_VKPipeline == _VKPipelne) {

											_newPipelineNode = false;

											BATCH_DRAW_OBJECT _drawObject = {};
											_drawObject.m_DrawBuffer = _VKDrawBuffer;
											_drawObject.m_Vertices = _VKVertices;
											_drawObject.m_Indices = _VKIndices;
											//_drawObject.m_Uniforms = _VKUniforms;

											itPipelineNode.m_DrawObjects.push_back(_drawObject);
										}
									}

									// новый узел subpass
									if (_newPipelineNode) {

										BATCH_DRAW_OBJECT _drawObject = {};
										_drawObject.m_DrawBuffer = _VKDrawBuffer;
										_drawObject.m_Vertices = _VKVertices;
										_drawObject.m_Indices = _VKIndices;
										//_drawObject.m_Uniforms = _VKUniforms;

										// описываем BATCH_PIPELINE_NODE
										VKBatchNode_Pipeline	_pipelineNode = {};
										_pipelineNode.m_VKPipeline = _VKPipelne;
										_pipelineNode.m_DrawObjects.push_back(_drawObject);

										_nodeRenderSubpass.m_PipelineNodes.push_back(_pipelineNode);
									}
									
								}
							}

							// новый узел subpass
							if (_newSubpassNode) {

								BATCH_DRAW_OBJECT _drawObject = {};
								_drawObject.m_DrawBuffer = _VKDrawBuffer;
								_drawObject.m_Vertices = _VKVertices;
								_drawObject.m_Indices = _VKIndices;

								// описываем BATCH_PIPELINE_NODE
								VKBatchNode_Pipeline	_pipelineNode = {};
								_pipelineNode.m_VKPipeline = _VKPipelne;
								_pipelineNode.m_DrawObjects.push_back(_drawObject);

								// описываем BATCH_SUB_PASS_NODE
								VKBatchNode_RenderSubpass _subpassNode = {};
								_subpassNode.m_PipelineNodes.push_back(_pipelineNode);

								itRenderPassNode.m_SubpassNodes.push_back(_subpassNode);

								// сортируем BATCH_SUB_PASS_NODE
								std::sort(itRenderPassNode.m_SubpassNodes.begin(), itRenderPassNode.m_SubpassNodes.end(),
									[](VKBatchNode_RenderSubpass const &a, VKBatchNode_RenderSubpass const &b) -> bool
								{ return a.m_Number < b.m_Number; });

							}

						} // if (_VKRenderPass == itRenderPassNode.m_VKRenderPass)
						
					} // for (auto &itRenderPassNode

					// если 
					if (_newPassNode) {

						BATCH_DRAW_OBJECT _drawObject = {};
						_drawObject.m_DrawBuffer = _VKDrawBuffer;
						_drawObject.m_Vertices = _VKVertices;
						_drawObject.m_Indices = _VKIndices;
						//_drawObject.m_Uniforms = _VKUniforms;

						// описываем узел соедржащий VKPipeline
						VKBatchNode_Pipeline	_pipelineNode = {};
						_pipelineNode.m_VKPipeline = _VKPipelne;
						_pipelineNode.m_DrawObjects.push_back(_drawObject);
						
						// описываем узел содержащий подпроходы
						VKBatchNode_RenderSubpass _subpassNode0 = {};
						//_subpassNode0.m_PipelineNodes.push_back(_pipelineNode);
						_subpassNode0.m_Number = 0;
						_subpassNode0.m_PipelineNodes.push_back(_pipelineNode);

						VKBatchNode_RenderSubpass _subpassNode1 = {};
						//_subpassNode1.m_PipelineNodes.push_back(_pipelineNode);
						_subpassNode1.m_Number = 1;
						VKBatchNode_RenderSubpass _subpassNode2 = {};
						//_subpassNode2.m_PipelineNodes.push_back(_pipelineNode);
						_subpassNode2.m_Number = 2;

						
						// описываем узел содержащий VKRenderPass
						VKBatchNode_RenderPass _passNode = {};
						_passNode.m_Number = 6;
						_passNode.m_VKNRenderPass = _VKRenderPass;
						_passNode.m_SubpassNodes.push_back(_subpassNode0);
						
						//_passNode.m_SubpassNodes[_VKDrawBuffer->getSubpass()].m_PipelineNodes.push_back(_pipelineNode);

						m_BatchNodeRenderPasses.push_back(_passNode);

						// сортируем узлы с VKRenderPass
						std::sort(m_BatchNodeRenderPasses.begin(), m_BatchNodeRenderPasses.end(),
							[](VKBatchNode_RenderPass const &a, VKBatchNode_RenderPass const &b) -> bool
						{ return a.m_Number < b.m_Number; });
											
					} // if (_newPassNode)

				} // for (auto &itDrawObject : *drawObject)
				
			}

			//==============================================================
			//==============================================================
			
			void CVKBatch::update() {
				
				auto _VKContext = m_CreateInfo.m_VKNContext;
		
				for (uint32_t ctRenderPassNode = 0; ctRenderPassNode < m_BatchNodeRenderPasses.size(); ++ctRenderPassNode) {

					auto &_itRenderPassNode = m_BatchNodeRenderPasses[ctRenderPassNode];
					auto _itVKRenderPass = _itRenderPassNode.m_VKNRenderPass;

					if (_itRenderPassNode.m_DrawBuffers.empty()) {

						// количество командных буферов
						uint32_t _cmdBufferCount = (uint32_t)_itVKRenderPass->getVkFramebuffers().size();

						// количество VkCommandBuffer = количеству VkFramebuffer
						_itRenderPassNode.m_DrawBuffers.resize(_cmdBufferCount);

						// описываем VkCommandBufferAllocateInfo
						VkCommandBufferAllocateInfo _cmdBufferAllocateCI = {};

						_cmdBufferAllocateCI.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
						_cmdBufferAllocateCI.commandPool = _VKContext->getVkCommandPool();
						_cmdBufferAllocateCI.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
						_cmdBufferAllocateCI.commandBufferCount = _cmdBufferCount;

						// алоцируем командные буферы
						//md_DrawBuffers.resize(_countCmdBuffer);
						VK_ASSERT_EX(_VKContext->vkAllocateCommandBuffers(_VKContext->getDevice(), &_cmdBufferAllocateCI, _itRenderPassNode.m_DrawBuffers.data()), "", );

						// Fences (Used to check draw command buffer completion)
						VkFenceCreateInfo fenceCreateInfo = {};
						fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
						// Create in signaled state so we don't wait on first render of each command buffer
						fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
						_itRenderPassNode.m_WaitFences.resize(_cmdBufferCount);
						for (auto& fence : _itRenderPassNode.m_WaitFences)
						{
							VK_ASSERT_EX(_VKContext->vkCreateFence(_VKContext->getDevice(), &fenceCreateInfo, nullptr, &fence), "", );
						}
					}

					// перебираем командные буферы отрисовки для текущего CVKDrawBatch
					for (uint32_t ctCmdBuffer = 0; ctCmdBuffer < _itRenderPassNode.m_DrawBuffers.size(); ++ctCmdBuffer) {

						// текущий буфер отрисовки
						auto _itvkCmdBuffer = _itRenderPassNode.m_DrawBuffers[ctCmdBuffer];
						auto _itvkFramebuffer = _itVKRenderPass->getVkFramebuffers()[ctCmdBuffer];
						auto _itvkRenderPass = _itVKRenderPass->getVkRenderPass();

						// ~~~~~~~~~~~~~~~~
						// начало записи командного буфера
						// ~~~~~~~~~~~~~~~~

						// описываем VkCommandBufferBeginInfo
						VkCommandBufferBeginInfo cmdBufferBeginInfo = {};

						cmdBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
						cmdBufferBeginInfo.pNext = NULL;

						_VKContext->vkBeginCommandBuffer(_itvkCmdBuffer, &cmdBufferBeginInfo);

						// ~~~~~~~~~~~~~~~~
						// начало записи прохода
						// ~~~~~~~~~~~~~~~~

						// описываем VkClearValue
						const auto& _clearValue = _itVKRenderPass->getClearValue();

						//uint32_t _clearValuesSize = _clearValue.size();

						//vknClearValueArr _vkClearValues(_clearValuesSize);

						//for (uint32_t ct_clearValue = 0; ct_clearValue < _clearValuesSize; ++ct_clearValue) {

						//	_vkClearValues[ct_clearValue] = _clearValue[ct_clearValue];
						//}
						//clearValues[0].color = { { 0.0f, 1.0f, 0.0f, 1.0f } };
						//clearValues[1].color = { { 1.0f, 0.0f, 0.0f, 1.0f } };
						//clearValues[2].color = { { 1.0f, 0.0f, 0.0f, 1.0f } };
						//clearValues[3].color = { { 1.0f, 0.0f, 0.0f, 1.0f } };
						//clearValues[4].depthStencil = { 1.0f, 0 };
						
						
						// описываем VkRenderPassBeginInfo
						VkRenderPassBeginInfo renderPassBeginInfo = {};
						renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
						renderPassBeginInfo.pNext = nullptr;
						renderPassBeginInfo.renderPass = _itvkRenderPass;
						renderPassBeginInfo.renderArea.offset.x = 0;
						renderPassBeginInfo.renderArea.offset.y = 0;
						renderPassBeginInfo.renderArea.extent.width = _itVKRenderPass->getWidth();
						renderPassBeginInfo.renderArea.extent.height = _itVKRenderPass->getHeight();
						renderPassBeginInfo.clearValueCount = _itVKRenderPass->getClearValue().size();
						renderPassBeginInfo.pClearValues = _itVKRenderPass->getClearValue().data();
						renderPassBeginInfo.framebuffer = _itvkFramebuffer;

						_VKContext->vkCmdBeginRenderPass(_itvkCmdBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

						for (uint32_t ctSubpassNode = 0; ctSubpassNode < _itRenderPassNode.m_SubpassNodes.size(); ++ctSubpassNode) {

							auto &_itSubpassNode = _itRenderPassNode.m_SubpassNodes[ctSubpassNode];

							if(ctSubpassNode != 0) _VKContext->vkCmdNextSubpass(_itvkCmdBuffer, VK_SUBPASS_CONTENTS_INLINE);
							
							for (uint32_t ctPipelineNode = 0; ctPipelineNode < _itSubpassNode.m_PipelineNodes.size(); ++ctPipelineNode) {

								auto &_itPipelineNode = _itSubpassNode.m_PipelineNodes[ctPipelineNode];
								auto _vkPipeline = _itPipelineNode.m_VKPipeline->getVkPipeline();
								auto _vkPipelineLayout = _itPipelineNode.m_VKPipeline->getPipelineLayout();

								VkViewport viewport = {};
								viewport.height = (float)600;
								viewport.width = (float)800;
								viewport.minDepth = (float)0.0f;
								viewport.maxDepth = (float)1.0f;
								_VKContext->vkCmdSetViewport(_itvkCmdBuffer, 0, 1, &viewport);

								VkRect2D scissor = {};
								scissor.extent.width = 800;
								scissor.extent.height = 600;
								scissor.offset.x = 0;
								scissor.offset.y = 0;
								
								_VKContext->vkCmdSetScissor(_itvkCmdBuffer, 0, 1, &scissor);

								_VKContext->vkCmdBindPipeline(_itvkCmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _vkPipeline);
								
								for (uint32_t ctDrawObject = 0; ctDrawObject < _itPipelineNode.m_DrawObjects.size(); ++ctDrawObject) {

									auto &_itDrawObject = _itPipelineNode.m_DrawObjects[ctDrawObject];

									auto _itvkVertexBuffer = _itDrawObject.m_Vertices->getVkBuffer();
									auto _itvkIndexBuffer = _itDrawObject.m_Indices->getVkBuffer();
									auto _vkDescriptorSet = _itDrawObject.m_DrawBuffer->getDescriptorSet();

									

									if (ctSubpassNode == 0) {

										VkDeviceSize offsets[1] = { 0 };
										_VKContext->vkCmdBindVertexBuffers(_itvkCmdBuffer, 0, 1, &_itvkVertexBuffer, offsets);

										_VKContext->vkCmdBindDescriptorSets(_itvkCmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _vkPipelineLayout, 0, 1, &_vkDescriptorSet, 0, NULL);

										_VKContext->vkCmdBindIndexBuffer(_itvkCmdBuffer, _itvkIndexBuffer, 0, VK_INDEX_TYPE_UINT32);
										_VKContext->vkCmdDrawIndexed(_itvkCmdBuffer, 2166, 1, 0, 0, 1);


									}
									//if (ctSubpassNode == 2) {
										
										//_VKContext->vkCmdDrawIndexed(_itvkCmdBuffer, 58806, 1, 0, 0, 1);
									//	_VKContext->vkCmdDrawIndexed(_itvkCmdBuffer, 2166, 1, 0, 0, 1);
										//

									//}
									if (ctSubpassNode == 1) {

										_VKContext->vkCmdBindDescriptorSets(_itvkCmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _vkPipelineLayout, 0, 1, &_vkDescriptorSet, 0, NULL);

										VkDeviceSize offsets[1] = { 0 };
										_VKContext->vkCmdBindVertexBuffers(_itvkCmdBuffer, 0, 1, &_itvkVertexBuffer, offsets);

										_VKContext->vkCmdBindIndexBuffer(_itvkCmdBuffer, _itvkIndexBuffer, 0, VK_INDEX_TYPE_UINT32);
										
										_VKContext->vkCmdDrawIndexed(_itvkCmdBuffer, 6, 1, 0, 0, 1);

										
										//_VKContext->vkCmdDraw(_itvkCmdBuffer, 3, 1, 0, 0);
										
									}									
								}			
							}
						}

						// ~~~~~~~~~~~~~~~~
						// конец записи прохода
						// ~~~~~~~~~~~~~~~~
						_VKContext->vkCmdEndRenderPass(_itvkCmdBuffer);

						// ~~~~~~~~~~~~~~~~
						// конец записи командного буфера
						// ~~~~~~~~~~~~~~~~
						_VKContext->vkEndCommandBuffer(_itvkCmdBuffer);

					} // for (uint32_t ctCmdBuffer = 0; ctCmdBuffer < itBatch->m_DrawBuffers.size(); ++ctCmdBuffer)

				}				

			}

			//==============================================================
			//==============================================================

			void CVKBatch::getCmdBuffers(VkCommandBufferArr *cmdBuffers, uint32_t acquireNextImage) {

				for (auto &itRenderPassNode : m_BatchNodeRenderPasses) {

					if (acquireNextImage < itRenderPassNode.m_DrawBuffers.size()) {

						(*cmdBuffers).push_back(itRenderPassNode.m_DrawBuffers[acquireNextImage]);
					}
					
				}
			}

			//==============================================================
			//==============================================================

			void CVKBatch::getFences(std::vector<VkFence> *fences, uint32_t acquireNextImage) {

				for (auto &itRenderPassNode : m_BatchNodeRenderPasses) {

					if (acquireNextImage < itRenderPassNode.m_WaitFences.size()) {

						(*fences).push_back(itRenderPassNode.m_WaitFences[acquireNextImage]);
					}

				}
			}

			//==============================================================
			//==============================================================
			
			//void CVKBatch::updateVKRenderPass(const CRI_RENDER_PASS_CI *criRenderPassCI, VKRenderPass *vknRenderPass, CRI_RENDER_PASS_IMPL_CI *criImplCreateInfo) {
					
				/*VKRenderPass			_vknRenderPass = (*vknRenderPass);
				VK_RENDER_SUBPASS_CI	_vknRenderSubpassCI = {};


				_vknRenderPassCI.m_vknContext = m_VKNContext;
				_vknRenderPassCI.m_Width = criRenderPassCI->m_Width;
				_vknRenderPassCI.m_Height = criRenderPassCI->m_Height;
				_vknRenderPassCI.m_ClearValue = criRenderPassCI->m_ClearValue;
				
				// ~~~~~~~~~~~~~~~~
				// перебираем CRI_RENDER_PASS_ATTACHMENT_CI
				// ~~~~~~~~~~~~~~~~

				for (size_t idCRIAttachment = 0; idCRIAttachment < criRenderPassCI->m_Attachments.size(); ++idCRIAttachment) {

					// текущий CRI_RENDER_PASS_ATTACHMENT_CI
					auto &_criPassAttachmentCI = criRenderPassCI->m_Attachments[idCRIAttachment];
					auto &_vknPassAttachmentCIs = _vknRenderPassCI.m_Attachments;

					// ~~~~~~~~~~~~~~~~
					// каждый CRI_RENDER_PASS_ATTACHMENT_CI ищем в VK_RENDER_PASS_ATTACHMENT_CI
					// сравниваем в каждом VKImageBuffer
					// ~~~~~~~~~~~~~~~~

					auto _res = std::find_if(
						_vknPassAttachmentCIs.begin(),
						_vknPassAttachmentCIs.end(),
						[&_criPassAttachmentCI](VK_RENDER_PASS_ATTACHMENT_CI const &a) { return a.m_VKNImageBuffer == std::static_pointer_cast<CVKImageBuffer>(_criPassAttachmentCI.m_Texture); });

					// ~~~~~~~~~~~~~~~~
					// если CRI_RENDER_PASS_ATTACHMENT_CI нету в VK_RENDER_PASS_ATTACHMENT_CI
					// ~~~~~~~~~~~~~~~~

					if (_res == _vknPassAttachmentCIs.end()) {

						VK_RENDER_PASS_ATTACHMENT_CI _vknNewPassAtachmentCI = {};
						_vknNewPassAtachmentCI.m_VKNImageBuffer = std::static_pointer_cast<CVKImageBuffer>(_criPassAttachmentCI.m_Texture);

						_vknRenderPassCI.m_Attachments.push_back(_vknNewPassAtachmentCI);
					}

					// ~~~~~~~~~~~~~~~~
					// input CRI_RENDER_PASS_ATTACHMENT_CI становится input VK_RENDER_SUBPASS_ATTACHMENT_CI
					// output CRI_RENDER_PASS_ATTACHMENT_CI становится output VK_RENDER_SUBPASS_ATTACHMENT_CI
					// ~~~~~~~~~~~~~~~~

					VK_RENDER_SUBPASS_ATTACHMENT_CI::TYPE _vknNewAttachmentType = VK_RENDER_SUBPASS_ATTACHMENT_CI::TYPE::UNKNOWN;
					if (_criPassAttachmentCI.m_Type == CRI_RENDER_PASS_ATTACHMENT_CI::TYPE::INPUT) _vknNewAttachmentType = VK_RENDER_SUBPASS_ATTACHMENT_CI::TYPE::INPUT;
					if (_criPassAttachmentCI.m_Type == CRI_RENDER_PASS_ATTACHMENT_CI::TYPE::OUTPUT) _vknNewAttachmentType = VK_RENDER_SUBPASS_ATTACHMENT_CI::TYPE::OUTPUT;

					// ~~~~~~~~~~~~~~~~
					// новый VK_RENDER_SUBPASS_ATTACHMENT_CI
					// ~~~~~~~~~~~~~~~~

					VK_RENDER_SUBPASS_ATTACHMENT_CI _vknNewSubpassAtachmentCI = {};
					_vknNewSubpassAtachmentCI.m_VKNImageBuffer = std::static_pointer_cast<CVKImageBuffer>(_criPassAttachmentCI.m_Texture);
					_vknNewSubpassAtachmentCI.m_Type = _vknNewAttachmentType;

					_vknRenderSubpassCI.m_Attachments.push_back(_vknNewSubpassAtachmentCI);

				} // for (size_t idCRIAttachment = 0;

				// ~~~~~~~~~~~~~~~~
				// пересоздаём VKRenderPass
				// ~~~~~~~~~~~~~~~~

				_vknRenderPassCI.m_Subpasses.push_back(_vknRenderSubpassCI);

				(*vknRenderPass)->create(&_vknRenderPassCI);
				
				// ~~~~~~~~~~~~~~~~
				// новое описание CRI_RENDER_PASS_IMPL_CI
				// ~~~~~~~~~~~~~~~~

				CRI_RENDER_PASS_IMPL_CI _criRenderPassImplCI = {};
				_criRenderPassImplCI.m_SubpassNumber = _vknRenderPassCI.m_Subpasses.size();
				_criRenderPassImplCI.m_VKNRenderPass = *vknRenderPass;

				*criImplCreateInfo = _criRenderPassImplCI;*/

			//}

			//==============================================================
			//==============================================================

		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE

#endif // #if defined(FE_RENDER) && defined(FE_RENDER_VULKAN) && FE_RENDER == FE_RENDER_VULKAN