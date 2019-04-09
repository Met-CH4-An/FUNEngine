////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "CRIRenderPass.h"
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
#include "Vulkan/vknContext.h"
#include "Private/Vulkan/vknBatch.h"
#include "Vulkan/vknRenderPass.h"

namespace FE {

	namespace CRI {

		//==============================================================
		//==============================================================

		bool CRI_RENDER_PASS_CI::isValid(void) const {
			
			if (m_CRIContext == nullptr ||
				m_Width == -1 ||
				m_Height == -1 ||
				m_ClearValue == vec4(-1.0f, -1.0f, -1.0f, -1.0f)) return false;

			for (const auto &itAttachment : m_Attachments) {

				if (itAttachment.m_Texture == nullptr ||
					itAttachment.m_Type == CRI_RENDER_PASS_ATTACHMENT_CI::TYPE::UNKNOWN) 
					
					return false;
			}

			return true;
		}

		//==============================================================
		//==============================================================

		CCRIRenderPass::CCRIRenderPass() {

		}

		//==============================================================
		//==============================================================

		CCRIRenderPass::~CCRIRenderPass() {

		}

		//==============================================================
		//==============================================================

		CRIRenderPass CCRIRenderPass::create(CRIContext criContext, const CRI_RENDER_PASS_CI *createInfo) {

			ASSERT_EX(createInfo->isValid(), ==, true, "Invalid CRI_RENDER_PASS_CREATE_INFO.", throw e_render_pass_create_failed());

			// ~~~~~~~~~~~~~~~~
			// get VKContext
			// ~~~~~~~~~~~~~~~~

			auto _vknContext = VULKAN::cri2vkn_Context(criContext);

			// ~~~~~~~~~~~~~~~~
			// get VKRenderPass
			// ~~~~~~~~~~~~~~~~

			uint32_t _idSubpass = 0;

			auto _vknRenderPass = _vknContext->getBatch()->getRenderPass(createInfo, &_idSubpass);

			// ~~~~~~~~~~~~~~~~
			// new CRIRenderPassPrivate
			// ~~~~~~~~~~~~~~~~

			auto _criRenderPassPrivate = std::make_shared<VULKAN::CCRIRenderPassPrivate>(_vknRenderPass);

			_criRenderPassPrivate->setIDSubpass(_idSubpass);

			// ~~~~~~~~~~~~~~~~

			return _criRenderPassPrivate;

		}

		//==============================================================
		//==============================================================

	} // namespace RENDER

} // namespace FE