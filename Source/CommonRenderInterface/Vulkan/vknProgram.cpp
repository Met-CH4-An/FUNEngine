////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "vknProgram.h"
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

namespace FE {

	namespace CRI {

		namespace VULKAN {

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			CVKProgram::CVKProgram(void) {				
					
				m_vknContext = nullptr;
				m_vkPipelineShaderStages = {};
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			CVKProgram::~CVKProgram(void) {

				m_vknContext = nullptr;
				m_vkPipelineShaderStages = {};
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			void CVKProgram::create(const CRI_PROGRAM_CREATE_INFO *createInfo) {

				m_vknContext = cri2vkn_Context(createInfo->m_criContext);

				prepare(&createInfo->m_VertexCode, true, false);

				prepare(&createInfo->m_FragmentCode, false, true);

			}

			//==============================================================
			//==============================================================
			
			const VkPipelineShaderStageCreateInfoArr& CVKProgram::getVkPipelineShaederStage(void) const {

				return m_vkPipelineShaderStages;
			}

			//==============================================================
			//==============================================================

			void CVKProgram::prepare(const std::string *code, const bool vertex, const bool fragment) {

				VkShaderStageFlagBits	_vkStage;

				if (vertex) {
					_vkStage = VK_SHADER_STAGE_VERTEX_BIT;
				}

				if (fragment) {
					_vkStage = VK_SHADER_STAGE_FRAGMENT_BIT;
				}

				VkShaderModule _vkShaderModule = createShaderModule(code);

				// VkPipelineShaderStageCreateInfo
				VkPipelineShaderStageCreateInfo _vkShaderStageCI = {};
				_vkShaderStageCI.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				_vkShaderStageCI.pNext;
				_vkShaderStageCI.flags;
				_vkShaderStageCI.stage = _vkStage;
				_vkShaderStageCI.module = _vkShaderModule;
				_vkShaderStageCI.pName = "main";
				_vkShaderStageCI.pSpecializationInfo;

				m_vkPipelineShaderStages.push_back(_vkShaderStageCI);
			}

			//==============================================================
			//==============================================================

			VkShaderModule CVKProgram::createShaderModule(const std::string *code) {
			
				// VkShaderModuleCreateInfo
				VkShaderModuleCreateInfo _vkShaderModuleCI = {};
				_vkShaderModuleCI.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
				_vkShaderModuleCI.pNext;
				_vkShaderModuleCI.flags;
				_vkShaderModuleCI.codeSize = code->size();
				_vkShaderModuleCI.pCode = (uint32_t*)code->data();

				VkShaderModule _vkShaderModule;
				VK_ASSERT_EX(m_vknContext->vkCreateShaderModule(m_vknContext->getDevice(), &_vkShaderModuleCI, nullptr, &_vkShaderModule), "", e_vulkan_program_create_fail());

				return _vkShaderModule;
			}

			//==============================================================

			//==============================================================
		} // namespace VULKAN

	} // namespace CRI

} // namespace FE