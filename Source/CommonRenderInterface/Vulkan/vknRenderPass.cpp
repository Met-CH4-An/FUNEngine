////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "vknRenderPass.h"
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
#include "../Private/Vulkan/vknBatch.h"
#include "vknImageBuffer.h"

#include "../CRIContext.h"
#include "../CRIRenderPass.h"
#include "../CRIImageBuffer.h"

namespace FE {

	namespace CRI {

		namespace VULKAN {

			//==============================================================
			//==============================================================

			CVKRenderPass::CVKRenderPass(VKContext vknContext) {

				m_VKNContext = nullptr;
				m_vknImageBuffers = {};
				m_Width = 0;
				m_Height = 0;
				m_Present = false;
				m_SubpassCount = 0;

				m_vkSubpassDependencies = {};
				m_vkAttachmentDescs = {};
				m_vkRenderPass = VK_NULL_HANDLE;
				m_vkImageViewPerFramebuffers = {};
				m_vkFramebuffers = {};
				m_vkClearValues = {};

			}

			//==============================================================
			//==============================================================

			CVKRenderPass::~CVKRenderPass(void) {

				m_VKNContext = nullptr;
				m_vknImageBuffers = {};
				m_Width = 0;
				m_Height = 0;
				m_Present = false;
				m_SubpassCount = 0;

				m_vkSubpassDependencies = {};
				m_vkAttachmentDescs = {};
				m_vkRenderPass = VK_NULL_HANDLE;
				m_vkImageViewPerFramebuffers = {};
				m_vkFramebuffers = {};
				m_vkClearValues = {};

			}

			//==============================================================
			//==============================================================

			void CVKRenderPass::create(const CRI_RENDER_PASS_CI *criCreateInfo) {
				
				// ~~~~~~~~~~~~~~~~
				// 
				// ~~~~~~~~~~~~~~~~

				m_criCreateInfos.push_back(*criCreateInfo);

				m_VKNContext = cri2vkn_Context(criCreateInfo->m_CRIContext);

				m_Width = criCreateInfo->m_Width;
				m_Height = criCreateInfo->m_Height;

				create();
			
			}

			//==============================================================
			//==============================================================

			void CVKRenderPass::destroy() {

				// ~~~~~~~~~~~~~~~~
				// other
				// ~~~~~~~~~~~~~~~~

				m_vknImageBuffers.clear();
				m_SubpassCount = 0;
				
				m_vkSubpassDescriptions.clear();
				m_vkAttachmentColorPerSubpassReferences.clear();
				m_vkAttachmentDepthPerSubpassReferences.clear();
				m_vkAttachmentInputPerSubpassReferences.clear();

				m_vkSubpassDependencies.clear();
				m_vkAttachmentDescs.clear();

				// ~~~~~~~~~~~~~~~~
				// destroy m_vkRenderPass
				// ~~~~~~~~~~~~~~~~

				m_VKNContext->vkDestroyRenderPass(m_VKNContext->getDevice(), m_vkRenderPass, nullptr);

				m_vkRenderPass = VK_NULL_HANDLE;

				// ~~~~~~~~~~~~~~~~
				// other
				// ~~~~~~~~~~~~~~~~

				m_vkImageViewPerFramebuffers.clear();

				// ~~~~~~~~~~~~~~~~
				// destroy m_vkFramebuffers
				// ~~~~~~~~~~~~~~~~

				for (const auto &itFramebuffer : m_vkFramebuffers) {

					m_VKNContext->vkDestroyFramebuffer(m_VKNContext->getDevice(), itFramebuffer, nullptr);
				}

				m_vkFramebuffers.clear();

				// ~~~~~~~~~~~~~~~~
				// other
				// ~~~~~~~~~~~~~~~~

				m_vkClearValues.clear();			

			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			void CVKRenderPass::add(const CRI_RENDER_PASS_CI *criCreateInfo) {

				auto _criCreateInfos = m_criCreateInfos;

				destroy();

				m_criCreateInfos = _criCreateInfos;

				create(criCreateInfo);
				
			}

			//==============================================================
			//==============================================================

			void CVKRenderPass::create(void) {

				// ~~~~~~~~~~~~~~~~
				// подготовка данных для создания
				// ~~~~~~~~~~~~~~~~

				// перебираем m_criCreateInfos
				for (uint32_t ct_criCreateInfo = 0; ct_criCreateInfo < m_criCreateInfos.size(); ++ct_criCreateInfo) {

					const auto& _criCreateInfo = m_criCreateInfos[ct_criCreateInfo];

					// подготовка данных подпрохода
					prepareSubpass(&_criCreateInfo);
				}

				// подготовка зависимостей подпроходов
				prepareDependencies();

				// подготовка данных для фреймбуферов
				prepareFramebuffer();

				// ~~~~~~~~~~~~~~~~
				// VkRenderpass
				// ~~~~~~~~~~~~~~~~

				// описываем VkRenderPassCreateInfo
				VkRenderPassCreateInfo renderPassInfo = {};

				renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
				renderPassInfo.attachmentCount = static_cast<uint32_t>(m_vkAttachmentDescs.size());
				renderPassInfo.pAttachments = m_vkAttachmentDescs.data();
				renderPassInfo.subpassCount = static_cast<uint32_t>(m_vkSubpassDescriptions.size());
				renderPassInfo.pSubpasses = m_vkSubpassDescriptions.data();
				renderPassInfo.dependencyCount = static_cast<uint32_t>(m_vkSubpassDependencies.size());
				renderPassInfo.pDependencies = m_vkSubpassDependencies.data();

				VK_ASSERT_EX(m_VKNContext->vkCreateRenderPass(m_VKNContext->getDevice(), &renderPassInfo, nullptr, &m_vkRenderPass), "", throw e_vulkan_common_render_pass_create_fail());

				// ~~~~~~~~~~~~~~~~
				// VkFramebuffer
				// ~~~~~~~~~~~~~~~~

				// перебираем VkImageView для фреймбуферов
				for (const auto &itImageViews : m_vkImageViewPerFramebuffers) {

					// описываем VkFramebufferCreateInfo
					VkFramebufferCreateInfo _framebufferCI = {};

					_framebufferCI.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
					_framebufferCI.renderPass = m_vkRenderPass;
					_framebufferCI.attachmentCount = (uint32_t)itImageViews.size();
					_framebufferCI.pAttachments = itImageViews.data();
					_framebufferCI.width = m_Width;
					_framebufferCI.height = m_Height;
					_framebufferCI.layers = 1;

					VkFramebuffer _framebuffer;
					VK_ASSERT_EX(m_VKNContext->vkCreateFramebuffer(m_VKNContext->getDevice(), &_framebufferCI, nullptr, &_framebuffer), "", throw e_vulkan_common_render_pass_create_fail());
					m_vkFramebuffers.push_back(_framebuffer);

				} // for (const auto &itImageViews : _imageViews)
			}

			//==============================================================
			//==============================================================
			
			void CVKRenderPass::prepareSubpass(const CRI_RENDER_PASS_CI *renderPassCreateInfo) {

				uint32_t _idSubpass = m_SubpassCount;

				++m_SubpassCount;

				m_vkSubpassDescriptions.resize(m_SubpassCount);
				m_vkAttachmentColorPerSubpassReferences.resize(m_SubpassCount);
				m_vkAttachmentDepthPerSubpassReferences.resize(m_SubpassCount);
				m_vkAttachmentInputPerSubpassReferences.resize(m_SubpassCount);

				// ~~~~~~~~~~~~~~~~
				// для present
				// VkAttachmentDescription и VkAttachmentReference
				// ~~~~~~~~~~~~~~~~

				if (renderPassCreateInfo->m_Present) {

					m_Present = true;

					uint32_t _idAttachment = prepareAttachmentDescription(nullptr, &renderPassCreateInfo->m_ClearValue);

					prepareAttachmentReference(_idSubpass, _idAttachment, nullptr, false);

				}

				// ~~~~~~~~~~~~~~~~
				// VkAttachmentDescription и VkAttachmentReference
				// ~~~~~~~~~~~~~~~~

				for (uint32_t ctAttachment = 0; ctAttachment < renderPassCreateInfo->m_Attachments.size(); ++ctAttachment) {

					const auto	_attachment = renderPassCreateInfo->m_Attachments[ctAttachment];
					const auto	_vknImageBuffer = cri2vk_ImageBuffer(_attachment.m_Texture);
					bool		_input = _attachment.m_Type == CRI_RENDER_PASS_ATTACHMENT_CI::TYPE::INPUT ? true : false;

					uint32_t _idAttachment = prepareAttachmentDescription(_vknImageBuffer, &renderPassCreateInfo->m_ClearValue);

					prepareAttachmentReference(_idSubpass, _idAttachment, _vknImageBuffer, _input);

				} // for (uint32_t ctAttachment	

				// ~~~~~~~~~~~~~~~~
				// VkSubpassDescription
				// ~~~~~~~~~~~~~~~~
				
				// описываем VkSubpassDescription 
				VkSubpassDescription _vkSubpassDescription = {};
				_vkSubpassDescription.flags;
				_vkSubpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
				_vkSubpassDescription.inputAttachmentCount = (uint32_t)m_vkAttachmentInputPerSubpassReferences[_idSubpass].size();
				_vkSubpassDescription.pInputAttachments = m_vkAttachmentInputPerSubpassReferences[_idSubpass].data();
				_vkSubpassDescription.colorAttachmentCount = (uint32_t)m_vkAttachmentColorPerSubpassReferences[_idSubpass].size();
				_vkSubpassDescription.pColorAttachments = m_vkAttachmentColorPerSubpassReferences[_idSubpass].data();
				_vkSubpassDescription.pResolveAttachments = nullptr;
				_vkSubpassDescription.pDepthStencilAttachment = m_vkAttachmentDepthPerSubpassReferences[_idSubpass].data();
				_vkSubpassDescription.preserveAttachmentCount = 0;
				_vkSubpassDescription.pPreserveAttachments = nullptr;

				m_vkSubpassDescriptions[_idSubpass] = _vkSubpassDescription;

			}

			//==============================================================
			//==============================================================

			uint32_t  CVKRenderPass::prepareAttachmentDescription(const VKImageBuffer vknImageBuffer, const vec4 *clearColor) {

				// find VKImageBuffer
				auto _resultFind = std::find(m_vknImageBuffers.begin(), m_vknImageBuffers.end(), vknImageBuffer);

				// if found
				if (_resultFind != m_vknImageBuffers.end()) return std::distance(m_vknImageBuffers.begin(), _resultFind);

				m_vknImageBuffers.push_back(vknImageBuffer);

				bool _present = vknImageBuffer == nullptr ? true : false;
				bool _color = vknImageBuffer != nullptr ? vknImageBuffer->isColor() : false;
				bool _depth = vknImageBuffer != nullptr ? vknImageBuffer->isDepth() : false;

				// ~~~~~~~~~~~~~~~~
				// VkImageLayout
				// ~~~~~~~~~~~~~~~~

				VkFormat _format = vknImageBuffer == nullptr ? m_VKNContext->getFormat() : vknImageBuffer->getFormat();
					
				// ~~~~~~~~~~~~~~~~
				// VkImageLayout
				// ~~~~~~~~~~~~~~~~

				VkImageLayout _finalLayout = {};
				if (_present)			_finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
				else if (_color)		_finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
				else if (_depth)		_finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
				
				// ~~~~~~~~~~~~~~~~
				// VkAttachmentStoreOp
				// ~~~~~~~~~~~~~~~~

				VkAttachmentStoreOp _storeOp;
				_present ? _storeOp = VK_ATTACHMENT_STORE_OP_STORE : _storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

				// ~~~~~~~~~~~~~~~~
				// VkAttachmentDescription
				// ~~~~~~~~~~~~~~~~

				VkAttachmentDescription _colorAttachDesc = {};
				_colorAttachDesc.flags;
				_colorAttachDesc.format = _format;
				_colorAttachDesc.samples = VK_SAMPLE_COUNT_1_BIT;							// без мультисэмплинга
				_colorAttachDesc.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;						// содержание атачмента до прохода
				_colorAttachDesc.storeOp = _storeOp;										// содержание атачмента после прохода
				_colorAttachDesc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;			// содержание стенсила до прохода
				_colorAttachDesc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;			// содержание стенсила после прохода
				_colorAttachDesc.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;					// до рендеринга layout вложения не определён
				_colorAttachDesc.finalLayout = _finalLayout;								// после рендеринга layout вложения соотвествует для свопчайна

				m_vkAttachmentDescs.push_back(_colorAttachDesc);

				// ~~~~~~~~~~~~~~~~
				// VkClearValue
				// ~~~~~~~~~~~~~~~~

				VkClearValue _clearValue;

				if(_color || _present) _clearValue.color = { clearColor->x, clearColor->y, clearColor->z, clearColor->w };
				if (_depth) _clearValue.depthStencil = {1.0f, 0};

				m_vkClearValues.push_back(_clearValue);

				return m_vknImageBuffers.size() - 1;

			}

			//==============================================================
			//==============================================================

			void CVKRenderPass::prepareAttachmentReference(const uint32_t idSubpass, const uint32_t idAttachment, const VKImageBuffer vknImageBuffer, const bool input) {

				// ~~~~~~~~~~~~~~~~
				// ~~~~~~~~~~~~~~~~

				bool _color = vknImageBuffer != nullptr ? vknImageBuffer->isColor() : true;
				bool _depth = vknImageBuffer != nullptr ? vknImageBuffer->isDepth() : false;

				// ~~~~~~~~~~~~~~~~
				// VkAttachmentReference
				// ~~~~~~~~~~~~~~~~

				VkAttachmentReference _attachmentRefs;
				_attachmentRefs.attachment = idAttachment;

				if (input) _attachmentRefs.layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
				else if (_color) _attachmentRefs.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
				else if (_depth) _attachmentRefs.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

				if (input) m_vkAttachmentInputPerSubpassReferences[idSubpass].push_back(_attachmentRefs);
				else if (_color) m_vkAttachmentColorPerSubpassReferences[idSubpass].push_back(_attachmentRefs);
				else if (_depth) m_vkAttachmentDepthPerSubpassReferences[idSubpass].push_back(_attachmentRefs);
			}

			//==============================================================
			//==============================================================

			void CVKRenderPass::prepareDependencies(void) {

				// ~~~~~~~~~~~~~~~~
				// VkSubpassDependency
				// ~~~~~~~~~~~~~~~~

				uint32_t _countDependencyBetween = m_SubpassCount - 1;

				// описываем VkSubpassDependency
				VkSubpassDependency _subpassDependencyBegin = {};

				_subpassDependencyBegin.srcSubpass = VK_SUBPASS_EXTERNAL;
				_subpassDependencyBegin.dstSubpass = 0;
				_subpassDependencyBegin.srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
				_subpassDependencyBegin.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				_subpassDependencyBegin.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;
				_subpassDependencyBegin.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				_subpassDependencyBegin.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

				m_vkSubpassDependencies.push_back(_subpassDependencyBegin);

				// описываем зависимости между подпроходами
				for (uint32_t ctSubpass = 0; ctSubpass < _countDependencyBetween; ++ctSubpass) {

					// описываем VkSubpassDependency
					VkSubpassDependency _subpassDependency = {};

					_subpassDependency.srcSubpass = ctSubpass;
					_subpassDependency.dstSubpass = ctSubpass + 1;
					_subpassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
					_subpassDependency.dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
					_subpassDependency.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
					_subpassDependency.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
					_subpassDependency.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

					m_vkSubpassDependencies.push_back(_subpassDependency);
				}

				// описываем VkSubpassDependency
				VkSubpassDependency _subpassDependencyEnd = {};

				_subpassDependencyEnd.srcSubpass = _countDependencyBetween;
				_subpassDependencyEnd.dstSubpass = VK_SUBPASS_EXTERNAL;
				_subpassDependencyEnd.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				_subpassDependencyEnd.dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
				_subpassDependencyEnd.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				_subpassDependencyEnd.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
				_subpassDependencyEnd.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

				m_vkSubpassDependencies.push_back(_subpassDependencyEnd);
			}

			//==============================================================
			//==============================================================

			void CVKRenderPass::prepareFramebuffer(void) {

				uint32_t _countFramebuffer = m_Present ? m_VKNContext->getImageViews().size() : 1;
				uint32_t _countAttachment = m_vknImageBuffers.size();

				m_vkImageViewPerFramebuffers.resize(_countFramebuffer);

				// iterate m_vkImageViewPerFramebuffers
				for (uint32_t ctFramebuffer = 0; ctFramebuffer < _countFramebuffer; ++ctFramebuffer) {

					m_vkImageViewPerFramebuffers[ctFramebuffer].resize(_countAttachment);

					// iterate m_VKNImageBuffers
					for (uint32_t ctVKNImageBuffer = 0; ctVKNImageBuffer < _countAttachment; ++ctVKNImageBuffer) {
						
						if (m_vknImageBuffers[ctVKNImageBuffer] != nullptr)
							m_vkImageViewPerFramebuffers[ctFramebuffer][ctVKNImageBuffer] = m_vknImageBuffers[ctVKNImageBuffer]->getVkImageView();

						else
							m_vkImageViewPerFramebuffers[ctFramebuffer][ctVKNImageBuffer] = m_VKNContext->getImageViews()[ctFramebuffer];
							

					}
				}

			}

			//==============================================================
			//==============================================================

		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE