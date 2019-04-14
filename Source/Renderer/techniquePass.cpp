////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "pch.renderer.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "techniquePass.h"
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
#include "renderer.h"
#include "../CommonRenderInterface/criContext.h"
#include "../CommonRenderInterface/criRenderPass.h"

namespace FE {

	namespace RENDERER {

		//==============================================================
		//==============================================================

		CTechniquePass::CTechniquePass(Technique technique) {

			m_technique = technique;
		}

		//==============================================================
		//==============================================================

		void CTechniquePass::create(const TECHNIQUE_PASS *createInfo) {

			const auto& _criImageBuffers = m_technique->getCRIImageBuffers();

			// ~~~~~~~~~~~~~~~~
			// CRI::CRI_RENDER_PASS_ATTACHMENT_CI
			// ~~~~~~~~~~~~~~~~

			CRI::CRI_RENDER_PASS_ATTACHMENT_CI_ARR _criRenderPassAttachments;

			for (uint32_t ct_attachmentDesc = 0; ct_attachmentDesc < createInfo->m_attachmentDescs.size(); ++ct_attachmentDesc) {

				const auto& _attachmentDesc = createInfo->m_attachmentDescs[ct_attachmentDesc];

				// ~~~~~~~~~~~~~~~~
				// CRI::CRI_RENDER_PASS_ATTACHMENT_CI::TYPE
				// ~~~~~~~~~~~~~~~~

				CRI::CRI_RENDER_PASS_ATTACHMENT_CI::TYPE _criRenderPassAttachmentType = {};
				
				if (_attachmentDesc.m_type == TECHNIQUE_PASS::ATTACHMENT::TYPE::INPUT) _criRenderPassAttachmentType = CRI::CRI_RENDER_PASS_ATTACHMENT_CI::TYPE::INPUT;
				if (_attachmentDesc.m_type == TECHNIQUE_PASS::ATTACHMENT::TYPE::OUTPUT) _criRenderPassAttachmentType = CRI::CRI_RENDER_PASS_ATTACHMENT_CI::TYPE::OUTPUT;

				// ~~~~~~~~~~~~~~~~
				// CRI::CRI_RENDER_PASS_ATTACHMENT_CI
				// ~~~~~~~~~~~~~~~~

				CRI::CRI_RENDER_PASS_ATTACHMENT_CI _criRenderPassAttachmentDesc = {};
				_criRenderPassAttachmentDesc.m_Texture = _criImageBuffers[_attachmentDesc.m_bind];
				_criRenderPassAttachmentDesc.m_Type = _criRenderPassAttachmentType;

				//
				_criRenderPassAttachments.push_back(_criRenderPassAttachmentDesc);

			}

			// ~~~~~~~~~~~~~~~~
			// CRI::CCRIRenderPass
			// ~~~~~~~~~~~~~~~~

			CRI::CRI_RENDER_PASS_CI _criRenderPassCI = {};

			_criRenderPassCI.m_CRIContext = m_technique->getRenderer()->getContext();
			_criRenderPassCI.m_Present = true;
			_criRenderPassCI.m_Attachments = _criRenderPassAttachments;
			_criRenderPassCI.m_ClearValue = vec4(0.0f, 0.0f, 0.0f, 0.0f);
			_criRenderPassCI.m_Width = 800;
			_criRenderPassCI.m_Height = 600;

			m_criRenderPass = m_technique->getRenderer()->getContext()->create(&_criRenderPassCI);
		}

		//==============================================================
		//==============================================================

		bool CTechniquePass::find(const MESH_CREATE_INFO *meshCreateInfo) {

			return false;
		}

		//==============================================================
		//==============================================================

		void CTechniquePass::addPipeline(const CRI::CRIPipeline criPipeline) {

			m_criPipelines.push_back(criPipeline);
		}

	} // RENDERER

} // FE