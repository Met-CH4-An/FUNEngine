////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "pch.renderer.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "ShaderCollection.h"
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
#include "../Core.h"
#include "../Content/Content.h"
#include "../CommonRenderInterface/criProgram.h"

namespace FE {

	namespace RENDERER {

		const static std::string PATH_SHADER = "D:/Laboratory/FUNEngine/Data/Shaders/sprv";

		//==============================================================
		//==============================================================

		void CShaderCollection::create(const SHADER_COLLECTION_CREATE_INFO* createInfo) {
			
			m_renderer = createInfo->m_renderer;

			
		}

		//==============================================================
		//==============================================================

		void CShaderCollection::getShader(const SHADER_EFFECT_DESCRIPTION shaderEffectDescription) {

			auto _criContext = m_renderer->getContext();
			auto _content = m_renderer->getCore()->getContent();

			if (shaderEffectDescription.m_vertex == SHADER_EFFECT_DESCRIPTION::VERTEX::DEFAULT &&
				shaderEffectDescription.m_teselation == SHADER_EFFECT_DESCRIPTION::TESSELATION::DEFAULT &&
				shaderEffectDescription.m_geometry == SHADER_EFFECT_DESCRIPTION::GEOMETRY::DEFAULT &&
				shaderEffectDescription.m_fragment == SHADER_EFFECT_DESCRIPTION::FRAGMENT::GBUFFER) {

				// ~~~~~~~~~~~~~~~~
				// ~~~~~~~~~~~~~~~~

				_content->getFile(PATH_SHADER + "default@default@default@gBuffer.frag.spv");
				_content->getFile(PATH_SHADER + "default@default@default@gBuffer.vert.spv");

			}
			
			if (shaderEffectDescription.m_vertex == SHADER_EFFECT_DESCRIPTION::VERTEX::DEFAULT &&
				shaderEffectDescription.m_teselation == SHADER_EFFECT_DESCRIPTION::TESSELATION::DEFAULT &&
				shaderEffectDescription.m_geometry == SHADER_EFFECT_DESCRIPTION::GEOMETRY::DEFAULT &&
				shaderEffectDescription.m_fragment == SHADER_EFFECT_DESCRIPTION::FRAGMENT::LIGHTING_GBUFFER) {

				// ~~~~~~~~~~~~~~~~
				// ~~~~~~~~~~~~~~~~

				_content->getFile(PATH_SHADER + "default@default@default@lighting_gBuffer.frag.spv");
				_content->getFile(PATH_SHADER + "default@default@default@lighting_gBuffer.vert.spv");

			}

			CRI::CRI_PROGRAM_CREATE_INFO _criProgramCI = {};
			_criProgramCI.m_criContext = _criContext;

			//CRI::CRIProgram _criProgram = CRI::CCRIProgram::create();
		}

		//==============================================================
		//==============================================================

	} // namespace RENDERER

} // namespace FE