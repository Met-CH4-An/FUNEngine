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
#include "techniquePass.h"
#include "../CommonRenderInterface/criContext.h"
#include "../CommonRenderInterface/criRenderPass.h"
#include "../CommonRenderInterface/criImageBuffer.h"

#include <vector>

namespace FE {

	namespace RENDERER {

		

		//==============================================================
		//==============================================================

		CTechnique::CTechnique(CRenderer* renderer) {

			m_renderer = renderer;
		}

		//==============================================================
		//==============================================================

		void CTechnique::create(const TECHNIQUE_CREATE_INFO *createInfo) {
			
			m_createInfo = *createInfo;

			// ~~~~~~~~~~~~~~~~
			// максимальный bind
			// ~~~~~~~~~~~~~~~~

			auto _itMaxBind = std::max_element(	
				createInfo->m_textureDescs.begin(), 
				createInfo->m_textureDescs.end(),
				[](const TECHNIQUE_TEXTURE &lValue, const TECHNIQUE_TEXTURE &rValue){return lValue.m_bind < rValue.m_bind; }
			);

			uint32_t _idMaxBind = std::distance(createInfo->m_textureDescs.begin(), _itMaxBind);

			uint32_t _maxBind = createInfo->m_textureDescs[_idMaxBind].m_bind;

			m_criImageBuffers.resize(_maxBind + 1);

			// ~~~~~~~~~~~~~~~~
			// 
			// ~~~~~~~~~~~~~~~~

			for (uint32_t ctTexture = 0; ctTexture < createInfo->m_textureDescs.size(); ++ctTexture) {

				const auto& _textureDesc = createInfo->m_textureDescs[ctTexture];

				// ~~~~~~~~~~~~~~~~
				// является ли текстура input
				// ~~~~~~~~~~~~~~~~

				bool _input = checkInputTexture(&_textureDesc);

				// ~~~~~~~~~~~~~~~~
				// CRI::CRI_IMAGE_BUFFER_CREATE_INFO::ATTACHMENT
				// ~~~~~~~~~~~~~~~~

				auto _criImageBufferAttachment = CRI::CRI_IMAGE_BUFFER_CREATE_INFO::ATTACHMENT::UNKNOWN;

				if(_input)	_criImageBufferAttachment = CRI::CRI_IMAGE_BUFFER_CREATE_INFO::ATTACHMENT::INPUT;
				else		_criImageBufferAttachment = CRI::CRI_IMAGE_BUFFER_CREATE_INFO::ATTACHMENT::SAMPLED;

				// ~~~~~~~~~~~~~~~~
				// criImageBuffer
				// ~~~~~~~~~~~~~~~~

				// CRI_IMAGE_BUFFER_CREATE_INFO
				CRI::CRI_IMAGE_BUFFER_CREATE_INFO _criImageBufferCI = {};
				_criImageBufferCI.m_CRIContext = m_renderer->getContext();
				_criImageBufferCI.m_Type = CRI::CRI_IMAGE_BUFFER_CREATE_INFO::TYPE::_2D;
				_criImageBufferCI.m_Attachment = _criImageBufferAttachment;
				_criImageBufferCI.m_Storage = CRI::CRI_IMAGE_BUFFER_CREATE_INFO::STORAGE::DEVICE;
				_criImageBufferCI.m_Width = _textureDesc.m_width;
				_criImageBufferCI.m_Height = _textureDesc.m_height;
				_criImageBufferCI.m_Format = _textureDesc.m_format;
				_criImageBufferCI.m_MipLevels = 1;

				auto _criImageBuffer = m_renderer->getContext()->create(&_criImageBufferCI);

				m_criImageBuffers[_textureDesc.m_bind] = _criImageBuffer;

			} // for (uint32_t ctTexture = 0;

			// ~~~~~~~~~~~~~~~~
			// TechniquePass
			// ~~~~~~~~~~~~~~~~

			// createInfo :: m_passDescs
			for (uint32_t ct_techniquePassDesc = 0; ct_techniquePassDesc < createInfo->m_passDescs.size(); ++ct_techniquePassDesc) {

				const auto& _techniquePassDesc = createInfo->m_passDescs[ct_techniquePassDesc];

				TechniquePass _pass = new CTechniquePass(this);
				
				_pass->create(&_techniquePassDesc);

				m_passes.push_back(_pass);
			}

			m_inputPass = m_passes[0];
			m_outputPass = m_passes[1];
		}
		
		//==============================================================
		//==============================================================
		
		bool CTechnique::checkInputTexture(const TECHNIQUE_TEXTURE *textureDesc) const {

			// m_createInfo :: m_passeDescs
			for (uint32_t ct_techniquePassDec = 0; ct_techniquePassDec < m_createInfo.m_passDescs.size(); ++ct_techniquePassDec) {

				const auto& _techniquePassDesc = m_createInfo.m_passDescs[ct_techniquePassDec];

				// _techniquePassDesc :: m_attachmentDescs
				for (uint32_t ct_attachmentDesc = 0; ct_attachmentDesc < _techniquePassDesc.m_attachmentDescs.size(); ++ct_attachmentDesc) {

					auto _attachmentDesc = _techniquePassDesc.m_attachmentDescs[ct_attachmentDesc];

					if (textureDesc->m_bind == _attachmentDesc.m_bind) return true;

				} // for (uint32_t ct_attachmentDesc = 0;

			} // for (uint32_t ct_techniquePassDec = 0;

			return false;
		}

		//==============================================================
		//==============================================================

	} // namespace RENDERER

} // namespace FE