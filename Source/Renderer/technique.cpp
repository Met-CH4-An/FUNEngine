////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "pch.renderer.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "Technique.h"
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
#include "Renderer.h"
#include "../CommonRenderInterface/criRenderPass.h"
#include "../CommonRenderInterface/criImageBuffer.h"

#include <vector>

namespace FE {

	namespace RENDERER {

		//==============================================================
		//==============================================================

		CTechniquePass::CTechniquePass(Technique technique) {

			m_technique = technique;
		}

		//==============================================================
		//==============================================================

		void CTechniquePass::create(const TECHNIQUE_PASS_DESCRIPTION *createInfo) {

			const auto& _criImageBuffers = m_technique->getCRIImageBuffers();

			CRI::CRI_RENDER_PASS_ATTACHMENT_CI_ARR _criRenderPassAttachments;

			for (uint32_t ctInputTexuteBind = 0; ctInputTexuteBind < createInfo->m_inputTextureBinds.size(); ++ctInputTexuteBind) {

				uint32_t _textureBind = createInfo->m_inputTextureBinds[ctInputTexuteBind];

				// ~~~~~~~~~~~~~~~~
				// cri render pass attachment
				// ~~~~~~~~~~~~~~~~

				CRI::CRI_RENDER_PASS_ATTACHMENT_CI _criRenderPassAttachmentColor0CI = {};
				_criRenderPassAttachmentColor0CI.m_Texture = _criImageBuffers[_textureBind];
				_criRenderPassAttachmentColor0CI.m_Type = CRI::CRI_RENDER_PASS_ATTACHMENT_CI::TYPE::INPUT;

				//
				_criRenderPassAttachments.push_back(_criRenderPassAttachmentColor0CI);

			}

			for (uint32_t ctOutputTexuteBind = 0; ctOutputTexuteBind < createInfo->m_outputTextureBinds.size(); ++ctOutputTexuteBind) {

				uint32_t _textureBind = createInfo->m_outputTextureBinds[ctOutputTexuteBind];

				// ~~~~~~~~~~~~~~~~
				// cri render pass attachment
				// ~~~~~~~~~~~~~~~~

				CRI::CRI_RENDER_PASS_ATTACHMENT_CI _criRenderPassAttachmentColor0CI = {};
				_criRenderPassAttachmentColor0CI.m_Texture = _criImageBuffers[_textureBind];
				_criRenderPassAttachmentColor0CI.m_Type = CRI::CRI_RENDER_PASS_ATTACHMENT_CI::TYPE::OUTPUT;

				//
				_criRenderPassAttachments.push_back(_criRenderPassAttachmentColor0CI);

			}

			// ~~~~~~~~~~~~~~~~
			// cri pass
			// ~~~~~~~~~~~~~~~~

			CRI::CRI_RENDER_PASS_CI _criRenderPassCI = {};

			_criRenderPassCI.m_CRIContext = m_technique->getRenderer()->getContext();
			_criRenderPassCI.m_Present = true;
			_criRenderPassCI.m_Attachments = _criRenderPassAttachments;
			_criRenderPassCI.m_ClearValue = vec4(0.0f, 0.0f, 0.0f, 0.0f);
			_criRenderPassCI.m_Width = 800;
			_criRenderPassCI.m_Height = 600;

			m_criRenderPass = CRI::CCRIRenderPass::create(m_technique->getRenderer()->getContext(), &_criRenderPassCI);
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

		//==============================================================
		//==============================================================

		CTechnique::CTechnique(CRenderer* renderer) {

			m_renderer = renderer;
		}

		//==============================================================
		//==============================================================

		void CTechnique::create(const TECHNIQUE_DESCRIPTION *createInfo) {
			
			// ~~~~~~~~~~~~~~~~
			// ищем максимальный bind
			// ~~~~~~~~~~~~~~~~

			auto _itMaxBind = std::max_element(	
				createInfo->m_textures.begin(), 
				createInfo->m_textures.end(),
				[](const TEXTURE_DESCRIPTION &lValue, const TEXTURE_DESCRIPTION &rValue){return lValue.m_bind < rValue.m_bind; }
			);

			uint32_t _idMaxBind = std::distance(createInfo->m_textures.begin(), _itMaxBind);

			uint32_t _maxBind = createInfo->m_textures[_idMaxBind].m_bind;

			m_imageBuffers.resize(_maxBind + 1);

			// ~~~~~~~~~~~~~~~~
			// 
			// ~~~~~~~~~~~~~~~~

			for (uint32_t ctTexture = 0; ctTexture < createInfo->m_textures.size(); ++ctTexture) {

				const auto& _texture = createInfo->m_textures[ctTexture];

				// ~~~~~~~~~~~~~~~~
				// ищем bind
				// во всех TECHNIQUE_PASS_DESCRIPTION::m_inputRenderTargetBinds
				// ~~~~~~~~~~~~~~~~

				bool _input = false;

				// TECHNIQUE_DESCRIPTION :: m_techniquePasses
				for (uint32_t ctTechniquePassDecription = 0; ctTechniquePassDecription < createInfo->m_passes.size(); ++ctTechniquePassDecription) {
				
					const auto& _techniquePassDecription = createInfo->m_passes[ctTechniquePassDecription];

					// TECHNIQUE_PASS_DESCRIPTION :: m_inputRenderTargetBinds
					for (uint32_t ctInputTextureBind = 0; ctInputTextureBind < _techniquePassDecription.m_inputTextureBinds.size(); ++ctInputTextureBind) {

						auto _bind = _techniquePassDecription.m_inputTextureBinds[ctInputTextureBind];
						
						if (_texture.m_bind == _bind) _input = true;

					}
				}

				// ~~~~~~~~~~~~~~~~
				// CRI::CRI_IMAGE_BUFFER_CREATE_INFO::ATTACHMENT
				// ~~~~~~~~~~~~~~~~

				auto _imageBufferAttachment = CRI::CRI_IMAGE_BUFFER_CREATE_INFO::ATTACHMENT::UNKNOWN;

				if(_input)	_imageBufferAttachment = CRI::CRI_IMAGE_BUFFER_CREATE_INFO::ATTACHMENT::INPUT;
				else		_imageBufferAttachment = CRI::CRI_IMAGE_BUFFER_CREATE_INFO::ATTACHMENT::SAMPLED;

				// ~~~~~~~~~~~~~~~~
				// criImageBuffer
				// ~~~~~~~~~~~~~~~~

				// CRI_IMAGE_BUFFER_CREATE_INFO
				CRI::CRI_IMAGE_BUFFER_CREATE_INFO _criImageBufferCI = {};
				_criImageBufferCI.m_CRIContext = m_renderer->getContext();
				_criImageBufferCI.m_Type = CRI::CRI_IMAGE_BUFFER_CREATE_INFO::TYPE::_2D;
				_criImageBufferCI.m_Attachment = _imageBufferAttachment;
				_criImageBufferCI.m_Storage = CRI::CRI_IMAGE_BUFFER_CREATE_INFO::STORAGE::DEVICE;
				_criImageBufferCI.m_Width = _texture.m_width;
				_criImageBufferCI.m_Height = _texture.m_height;
				_criImageBufferCI.m_Format = _texture.m_format;
				_criImageBufferCI.m_MipLevels = 1;

				auto _criImageBuffer = CRI::CCRIImageBuffer::create(&_criImageBufferCI);

				m_imageBuffers[_texture.m_bind] = _criImageBuffer;

			} // for (uint32_t ctTexture = 0;

			// TECHNIQUE_DESCRIPTION :: m_techniquePasses
			for (uint32_t ctTechniquePassDecription = 0; ctTechniquePassDecription < createInfo->m_passes.size(); ++ctTechniquePassDecription) {

				const auto& _techniquePassDecription = createInfo->m_passes[ctTechniquePassDecription];

				TechniquePass _pass = new CTechniquePass(this);
				
				_pass->create(&_techniquePassDecription);

				m_passes.push_back(_pass);
			}

			m_inputPass = m_passes[0];
			m_outputPass = m_passes[1];
		}
		
		//==============================================================
		//==============================================================

	} // namespace RENDERER

} // namespace FE