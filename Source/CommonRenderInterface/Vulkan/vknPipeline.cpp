////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "vknPipeline.h"
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
#include "vknRenderPass.h"
#include "vknProgram.h"

//#include "../../CRIContext.h"
#include "../CRIRenderPass.h"
//#include "../CRIPipeline.h"

#include "../Private/Vulkan/vknResourcePool.h"


namespace FE {

	namespace CRI {

		namespace VULKAN {

			//==============================================================
			//==============================================================

			CVKPipeline::CVKPipeline(VKContext vknContext)
				: m_VKNContext(vknContext),
				m_VKResourcePool(),

				m_IAStateCI(),
				m_RasterizationStateCI(),
				m_ColorBlendAttachmentCIs(),
				m_ColorBlendStateCI(),

				m_Pipeline(VK_NULL_HANDLE),
				m_PipelineCache(VK_NULL_HANDLE),
				m_PipelineLayout(VK_NULL_HANDLE),
				m_DescriptorSetLayouts() {
			}

			//==============================================================
			//==============================================================

			void CVKPipeline::create(const CRI_PIPELINE_CI *createInfo) {
				m_VKNContext = cri2vkn_Context(createInfo->m_criContext);
				m_CI = *createInfo;
				auto _criRenderPass = createInfo->m_RenderPass;
				auto _vknRenderPass = cri2vkn_RenderPass(createInfo->m_RenderPass);

				// ~~~~~~~~~~~~~~~~
				// VkPipelineInputAssemblyStateCreateInfo
				// ~~~~~~~~~~~~~~~~

				// VkPrimitiveTopology
				VkPrimitiveTopology _topology = {};

				switch (createInfo->m_InputAssembly.m_Topology) {
					case CRI_PIPELINE_INPUT_PRIMITIVE::TOPOLOGY::TRIANGLE_LIST:		_topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
				}

				m_IAStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
				m_IAStateCI.pNext;
				m_IAStateCI.flags;
				m_IAStateCI.topology = _topology;
				m_IAStateCI.primitiveRestartEnable;

				// ~~~~~~~~~~~~~~~~
				// VkPipelineRasterizationStateCreateInfo
				// ~~~~~~~~~~~~~~~~
					
				// VkPolygonMode
				VkPolygonMode _polygonMode = {};

				switch (createInfo->m_Rasterization.m_Polygon) {
					case CRI_PIPELINE_RASTERIZATION::POLYGON::FILL:			_polygonMode = VK_POLYGON_MODE_FILL;		break;
					case CRI_PIPELINE_RASTERIZATION::POLYGON::LINE:			_polygonMode = VK_POLYGON_MODE_LINE;		break;
					case CRI_PIPELINE_RASTERIZATION::POLYGON::POINT:		_polygonMode = VK_POLYGON_MODE_POINT;		break;
				}

				// VkCullModeFlags
				VkCullModeFlags _cullMode = {};

				switch (createInfo->m_Rasterization.m_Cull) {
					case CRI_PIPELINE_RASTERIZATION::CULL::FRONT:				_cullMode = VK_CULL_MODE_FRONT_BIT;			break;
					case CRI_PIPELINE_RASTERIZATION::CULL::BACK:				_cullMode = VK_CULL_MODE_BACK_BIT;				break;
					case CRI_PIPELINE_RASTERIZATION::CULL::FRONT_AND_BACK:		_cullMode = VK_CULL_MODE_FRONT_AND_BACK;		break;
				}

				// VkFrontFace
				VkFrontFace _frontFace = {};

				switch (createInfo->m_Rasterization.m_FrontFace) {
					case CRI_PIPELINE_RASTERIZATION::FRONT_FACE::CLOCKWISE:					_frontFace = VK_FRONT_FACE_CLOCKWISE;				break;
					case CRI_PIPELINE_RASTERIZATION::FRONT_FACE::COUNTER_CLOCKWISE:			_frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;		break;
				}

				m_RasterizationStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
				m_RasterizationStateCI.pNext;
				m_RasterizationStateCI.flags;
				m_RasterizationStateCI.depthClampEnable = VK_FALSE;
				m_RasterizationStateCI.rasterizerDiscardEnable = VK_FALSE;
				m_RasterizationStateCI.polygonMode = _polygonMode;
				m_RasterizationStateCI.cullMode = _cullMode;
				m_RasterizationStateCI.frontFace = _frontFace;
				m_RasterizationStateCI.depthBiasEnable = VK_FALSE;
				m_RasterizationStateCI.depthBiasConstantFactor;
				m_RasterizationStateCI.depthBiasClamp;
				m_RasterizationStateCI.depthBiasSlopeFactor;
				//m_RasterizationStateCI.lineWidth = createInfo->m_Rasterization.m_LineWidth;
				m_RasterizationStateCI.lineWidth = 1.0f;

				// ~~~~~~~~~~~~~~~~
				// VkPipelineColorBlendStateCreateInfo
				// ~~~~~~~~~~~~~~~~

				uint32_t _countColorAttachment = _vknRenderPass->getAttachmentColorRefPerSubpass(_criRenderPass->getIDSubpass());

				m_ColorBlendAttachmentCIs.resize(_countColorAttachment);

				//if (_countColorAttachment > 1) _countColorAttachment = 1;
				for (uint32_t ctColorBlend = 0; ctColorBlend < _countColorAttachment; ++ctColorBlend) {

					// VkPipelineColorBlendAttachmentState
					VkPipelineColorBlendAttachmentState _colorBlendAttachmentState = {};

					_colorBlendAttachmentState.blendEnable = VK_FALSE;
					_colorBlendAttachmentState.srcColorBlendFactor;
					_colorBlendAttachmentState.dstColorBlendFactor;
					_colorBlendAttachmentState.colorBlendOp;
					_colorBlendAttachmentState.srcAlphaBlendFactor;
					_colorBlendAttachmentState.dstAlphaBlendFactor;
					_colorBlendAttachmentState.alphaBlendOp;
					_colorBlendAttachmentState.colorWriteMask = 0xf;

					m_ColorBlendAttachmentCIs[ctColorBlend] = _colorBlendAttachmentState;
				}

				m_ColorBlendStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
				m_ColorBlendStateCI.pNext;
				m_ColorBlendStateCI.flags;
				m_ColorBlendStateCI.logicOpEnable;
				m_ColorBlendStateCI.logicOp;
				m_ColorBlendStateCI.attachmentCount = m_ColorBlendAttachmentCIs.size();
				m_ColorBlendStateCI.pAttachments = m_ColorBlendAttachmentCIs.data();
				m_ColorBlendStateCI.blendConstants;

				// ~~~~~~~~~~~~~~~~
				// VkPipelineViewportStateCreateInfo
				// ~~~~~~~~~~~~~~~~

				// описываем VkPipelineViewportStateCreateInfo
				VkPipelineViewportStateCreateInfo _viewportStateCI = {};

				_viewportStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
				_viewportStateCI.pNext;
				_viewportStateCI.flags;
				_viewportStateCI.viewportCount = 1;
				_viewportStateCI.pViewports;
				_viewportStateCI.scissorCount = 1;
				_viewportStateCI.pScissors;

				// ~~~~~~~~~~~~~~~~
				// VkPipelineDepthStencilStateCreateInfo
				// ~~~~~~~~~~~~~~~~

				// описываем VkPipelineDepthStencilStateCreateInfo
				VkPipelineDepthStencilStateCreateInfo _depthStencilStateCI = {};

				_depthStencilStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
				_depthStencilStateCI.depthTestEnable = VK_TRUE;
				_depthStencilStateCI.depthWriteEnable = VK_TRUE;
				_depthStencilStateCI.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
				_depthStencilStateCI.depthBoundsTestEnable = VK_FALSE;
				_depthStencilStateCI.back.failOp = VK_STENCIL_OP_KEEP;
				_depthStencilStateCI.back.passOp = VK_STENCIL_OP_KEEP;
				_depthStencilStateCI.back.compareOp = VK_COMPARE_OP_ALWAYS;
				_depthStencilStateCI.stencilTestEnable = VK_FALSE;
				_depthStencilStateCI.front = _depthStencilStateCI.back;

				// ~~~~~~~~~~~~~~~~
				// VkPipelineMultisampleStateCreateInfo
				// ~~~~~~~~~~~~~~~~

				// VkPipelineMultisampleStateCreateInfo
				VkPipelineMultisampleStateCreateInfo _multisampleStateCI = {};

				_multisampleStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
				_multisampleStateCI.pSampleMask = NULL;
				_multisampleStateCI.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

				// ~~~~~~~~~~~~~~~~
				// VkPipelineDynamicStateCreateInfo
				// ~~~~~~~~~~~~~~~~

				// описываем VkDynamicState
				std::vector<VkDynamicState> _dynamicStates;
				_dynamicStates.push_back(VK_DYNAMIC_STATE_VIEWPORT);
				_dynamicStates.push_back(VK_DYNAMIC_STATE_SCISSOR);

				// VkPipelineDynamicStateCreateInfo
				VkPipelineDynamicStateCreateInfo _dynamicStateCI = {};

				_dynamicStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
				_dynamicStateCI.pNext;
				_dynamicStateCI.flags;
				_dynamicStateCI.dynamicStateCount = static_cast<uint32_t>(_dynamicStates.size());
				_dynamicStateCI.pDynamicStates = _dynamicStates.data();

				// ~~~~~~~~~~~~~~~~
				// VkPipelineLayout
				// ~~~~~~~~~~~~~~~~

				// перебираем Layout
				for (uint32_t ctLayout = 0; ctLayout < createInfo->m_Uniformlayout.size(); ++ctLayout) {

					std::vector<VkDescriptorSetLayoutBinding> _descriptorSetBindings;

					// перебираем LayoutBinding
					for (uint32_t ctBinding = 0; ctBinding < createInfo->m_Uniformlayout[ctLayout].size(); ++ctBinding) {

						auto &_itBinding = createInfo->m_Uniformlayout[ctLayout][ctBinding];
							
						// ~~~~~~~~~~~~~~~~
						// VkDescriptorSetLayoutBinding
						// ~~~~~~~~~~~~~~~~

						// VkDescriptorType
						VkDescriptorType _descriptorType = {};

						switch (_itBinding.m_Type) {
							case CRI_PIPELINE_UNIFORM_LAYOUT::BINDING::TYPE::UNIFORM:		_descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;		break;
							case CRI_PIPELINE_UNIFORM_LAYOUT::BINDING::TYPE::INPUT:			_descriptorType = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;		break;
						}

						// VkShaderStageFlags
						VkShaderStageFlags _shaderStage = {};

						switch (_itBinding.m_Stage) {
							case CRI_PIPELINE_UNIFORM_LAYOUT::BINDING::STAGE::VERTEX:			_shaderStage = VK_SHADER_STAGE_VERTEX_BIT;				break;
							case CRI_PIPELINE_UNIFORM_LAYOUT::BINDING::STAGE::FRAGMENT:			_shaderStage = VK_SHADER_STAGE_FRAGMENT_BIT;			break;
						}

						// VkDescriptorSetLayoutBinding
						VkDescriptorSetLayoutBinding _layoutBinding = {};

						_layoutBinding.binding = ctBinding;
						_layoutBinding.descriptorType = _descriptorType;
						_layoutBinding.descriptorCount = 1;
						_layoutBinding.stageFlags = _shaderStage;
						_layoutBinding.pImmutableSamplers = NULL;

						_descriptorSetBindings.push_back(_layoutBinding);

					} // for (uint32_t itBinding

					// описываем VkDescriptorSetLayoutCreateInfo
					VkDescriptorSetLayoutCreateInfo _descriptorLayoutCreate = {};

					_descriptorLayoutCreate.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
					_descriptorLayoutCreate.pNext = NULL;
					_descriptorLayoutCreate.flags;
					_descriptorLayoutCreate.bindingCount = _descriptorSetBindings.size();
					_descriptorLayoutCreate.pBindings = _descriptorSetBindings.data();

					// создаём vkCreateDescriptorSetLayout
					VkDescriptorSetLayout _descriptorSetLayout;
					VK_ASSERT_EX(m_VKNContext->vkCreateDescriptorSetLayout(m_VKNContext->getDevice(), &_descriptorLayoutCreate, nullptr, &_descriptorSetLayout), "", );

					m_DescriptorSetLayouts.push_back(_descriptorSetLayout);

				} // for (uint32_t itLayout

				// VkPipelineLayoutCreateInfo
				VkPipelineLayoutCreateInfo _pipelineLayoutCI = {};

				_pipelineLayoutCI.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
				_pipelineLayoutCI.pNext = NULL;
				_pipelineLayoutCI.flags;
				_pipelineLayoutCI.setLayoutCount = (uint32_t)m_DescriptorSetLayouts.size();
				_pipelineLayoutCI.pSetLayouts = m_DescriptorSetLayouts.data();
				_pipelineLayoutCI.pushConstantRangeCount;
				_pipelineLayoutCI.pPushConstantRanges;

				VK_ASSERT_EX(m_VKNContext->vkCreatePipelineLayout(m_VKNContext->getDevice(), &_pipelineLayoutCI, nullptr, &m_PipelineLayout), "",);

				// ~~~~~~~~~~~~~~~~
				// VkPipelineVertexInputStateCreateInfo
				// ~~~~~~~~~~~~~~~~

				std::vector<VkVertexInputBindingDescription> _vertexInputBindingList;
				std::vector<VkVertexInputAttributeDescription> _vertexInputAttributeList;

				// перебираем биндинги
				for (uint32_t ctBindings = 0; ctBindings < createInfo->m_VertexLayout.size(); ++ctBindings) {

					auto &_itBinding = createInfo->m_VertexLayout[ctBindings];

					uint32_t _stride = 0;

					// перебираем атрибуты
					for (uint32_t ctAttributes = 0; ctAttributes < _itBinding.size(); ++ctAttributes) {

						auto &_itAttribute = createInfo->m_VertexLayout[ctBindings][ctAttributes];

						VkFormat _format = {};

						switch (_itAttribute.m_Format) {
						case COMMON::FORMAT::DATA::_32_32_SFLOAT:				_format = VK_FORMAT_R32G32_SFLOAT;		_stride += 8;		break;
						case COMMON::FORMAT::DATA::_32_32_32_SFLOAT:			_format = VK_FORMAT_R32G32B32_SFLOAT;	_stride += 12;		break;
						}

						// описываем VkVertexInputAttributeDescription
						VkVertexInputAttributeDescription _vertexInputAttribute = {};

						_vertexInputAttribute.binding = ctBindings;
						_vertexInputAttribute.location = ctAttributes;
						_vertexInputAttribute.format = _format;
						_vertexInputAttribute.offset = _itAttribute.m_Offset;

						_vertexInputAttributeList.push_back(_vertexInputAttribute);

					} // for (uint32_t itAttributes

					// описываем VkVertexInputBindingDescription
					VkVertexInputBindingDescription _vertexInputBinding = {};

					_vertexInputBinding.binding = ctBindings;
					_vertexInputBinding.stride = _stride;
					_vertexInputBinding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

					_vertexInputBindingList.push_back(_vertexInputBinding);

				} // for (uint32_t itBindings

				// ~~~~~~~~~~~~~~~~
				// VkPipelineVertexInputStateCreateInfo
				// ~~~~~~~~~~~~~~~~

				VkPipelineVertexInputStateCreateInfo _vertexInputStateCI = {};

				_vertexInputStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
				_vertexInputStateCI.pNext = NULL;
				_vertexInputStateCI.flags = 0;
				_vertexInputStateCI.vertexBindingDescriptionCount = static_cast<uint32_t>(_vertexInputBindingList.size());
				_vertexInputStateCI.pVertexBindingDescriptions = _vertexInputBindingList.data();
				_vertexInputStateCI.vertexAttributeDescriptionCount = static_cast<uint32_t>(_vertexInputAttributeList.size());
				_vertexInputStateCI.pVertexAttributeDescriptions = _vertexInputAttributeList.data();

				// ~~~~~~~~~~~~~~~~
				// VkPipelineCache
				// ~~~~~~~~~~~~~~~~

				VkPipelineCacheCreateInfo _pipelineCacheCI = {};

				_pipelineCacheCI.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
				_pipelineCacheCI.pNext;
				_pipelineCacheCI.flags;
				_pipelineCacheCI.initialDataSize;
				_pipelineCacheCI.pInitialData;

				VK_ASSERT_EX(m_VKNContext->vkCreatePipelineCache(m_VKNContext->getDevice(), &_pipelineCacheCI, nullptr, &m_PipelineCache), "",);

				// ~~~~~~~~~~~~~~~~
				// VkPipeline
				// ~~~~~~~~~~~~~~~~

				VkGraphicsPipelineCreateInfo _pipelineCI = {};

				_pipelineCI.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
				_pipelineCI.layout = m_PipelineLayout;
				_pipelineCI.renderPass = _vknRenderPass->getVkRenderPass();
				_pipelineCI.pStages = cri2vkn_Program_const(createInfo->m_criProgram)->getVkPipelineShaederStage().data();
				_pipelineCI.stageCount = cri2vkn_Program_const(createInfo->m_criProgram)->getVkPipelineShaederStage().size();
				_pipelineCI.pVertexInputState = &_vertexInputStateCI;
				_pipelineCI.pInputAssemblyState = &m_IAStateCI;
				_pipelineCI.pRasterizationState = &m_RasterizationStateCI;
				_pipelineCI.pColorBlendState = &m_ColorBlendStateCI;
				_pipelineCI.pMultisampleState = &_multisampleStateCI;
				_pipelineCI.pViewportState = &_viewportStateCI;
				_pipelineCI.pDepthStencilState = &_depthStencilStateCI;
				_pipelineCI.pDynamicState = &_dynamicStateCI;
				_pipelineCI.subpass = _criRenderPass->getIDSubpass();

				VK_ASSERT_EX(m_VKNContext->vkCreateGraphicsPipelines(m_VKNContext->getDevice(), m_PipelineCache, 1, &_pipelineCI, nullptr, &m_Pipeline), "",);

			}

			//==============================================================
			//==============================================================

			void CVKPipeline::reCreate(const CRI_PIPELINE_CI *createInfo) {


			}

			//==============================================================
			//==============================================================

			void CVKPipeline::isCompatible(const CRI_PIPELINE_CI *createInfo) const {


			}

			//==============================================================
			//==============================================================
			
			VkDescriptorSet CVKPipeline::getDescriptorSet(void) {

				VkDescriptorSet _descriptorSet = 0;

				size_t _maxSetLayout = m_DescriptorSetLayouts.size();
				for (uint32_t ctSetLayout = 0; ctSetLayout < _maxSetLayout; ++ctSetLayout) {

					auto &_itSetLayout = m_DescriptorSetLayouts[ctSetLayout];
			
					// описываем VkDescriptorSetAllocateInfo
					VkDescriptorSetAllocateInfo _descriptorSetAllocCreate = {};
					
					_descriptorSetAllocCreate.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
					_descriptorSetAllocCreate.descriptorPool = m_VKNContext->getResourcePool()->getVkDescriptorPool();
					_descriptorSetAllocCreate.descriptorSetCount = 1;
					_descriptorSetAllocCreate.pSetLayouts = &_itSetLayout;

					VK_ASSERT_EX(m_VKNContext->vkAllocateDescriptorSets(m_VKNContext->getDevice(), &_descriptorSetAllocCreate, &_descriptorSet), "", );

				}

				return _descriptorSet;
			}

			//==============================================================
			//==============================================================

		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE