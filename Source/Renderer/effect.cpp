////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "pch.renderer.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "Effect.h"
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
#define _CRT_SECURE_NO_WARNINGS
#include "Renderer.h"
#include "../Content/Content.h"
#include "../Content/File.h"
#include "../Common/Blob.h"
#include "../CommonRenderInterface/criContext.h"
#include "../CommonRenderInterface/criProgram.h"
#include "../CommonRenderInterface/criPipeline.h"
#include "../CommonRenderInterface/criDataBuffer.h"

namespace FE {

	namespace RENDERER {

		const std::string PATH_SHADERS = "D:/Laboratory/FUNEngine/Data/Shaders/Cache/";

		std::string load(std::string name) {

			FILE *_fp = nullptr;
			size_t _fileSize = 0;

			// открываем файл
			_fp = fopen(name.c_str(), "rb");

			// размер файла
			fseek(_fp, 0L, SEEK_END);
			_fileSize = ftell(_fp);
			fseek(_fp, 0L, SEEK_SET);

			// копируем данные
			char *_pcnVertCode = new char[_fileSize];
			fread(_pcnVertCode, _fileSize, 1, _fp);
			std::string _code = std::string(_pcnVertCode, _fileSize);

			// закрываем файл
			fclose(_fp);

			return _code;

		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		Effect CEffect::create(const EFFECT_CREATE_INFO *createInfo) {

			// новый
			auto _effect = std::make_shared<CEffect>();

			//
			_effect->m_CreateInfo = *createInfo;

			return _effect;
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		CEffect::CEffect(void) {
			
			m_Renderer = nullptr;
			m_CreateInfo = {};

		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		CEffect::~CEffect(void) {

		}

		//==============================================================
		//==============================================================

		void CEffect::create(void) {

			// ~~~~~~~~~~~~~~~~
			// ~~~~~~~~~~~~~~~~


			auto _core = m_Renderer->getCore();
			auto _criContext = m_Renderer->getContext();
			auto _content = _core->getContent();
			const auto &_rendererCreateInfo = m_Renderer->getCreateInfo();

			// ~~~~~~~~~~~~~~~~
			// ~~~~~~~~~~~~~~~~

			CONTENT::File _fileVertexSrc = nullptr;
			CONTENT::File _fileGeometrySrc = nullptr;
			CONTENT::File _fileTesselationSrc = nullptr;
			CONTENT::File _fileFragmentSrc = nullptr;

			if (m_CreateInfo.m_Type0 == EFFECT_CREATE_INFO::TYPE0::TRANSFER &&
				m_CreateInfo.m_Type1 == EFFECT_CREATE_INFO::TYPE1::DEFAULT &&
				m_CreateInfo.m_Type2 == EFFECT_CREATE_INFO::TYPE2::DEFAULT &&
				m_CreateInfo.m_Type3 == EFFECT_CREATE_INFO::TYPE3::MRT) {

				_fileVertexSrc = _content->getFile(PATH_SHADERS + "deffered_1pass@transfer@@@mrt@pcn.vert.spv");
				_fileFragmentSrc = _content->getFile(PATH_SHADERS + "deffered_1pass@transfer@@@mrt@pcn.frag.spv");
			}

			if (m_CreateInfo.m_Type0 == EFFECT_CREATE_INFO::TYPE0::QUAD &&
				m_CreateInfo.m_Type1 == EFFECT_CREATE_INFO::TYPE1::DEFAULT &&
				m_CreateInfo.m_Type2 == EFFECT_CREATE_INFO::TYPE2::DEFAULT &&
				m_CreateInfo.m_Type3 == EFFECT_CREATE_INFO::TYPE3::LAMBERT) {

				_fileVertexSrc = _content->getFile(PATH_SHADERS + "deffered_2pass@quad@@@lambert@p.vert.spv");
				_fileFragmentSrc = _content->getFile(PATH_SHADERS + "deffered_2pass@quad@@@lambert@p.frag.spv");
			}
			
			// ~~~~~~~~~~~~~~~~
			// ~~~~~~~~~~~~~~~~
			
			CRI::CRI_PROGRAM_CREATE_INFO _criProgramCI = {};
			_criProgramCI.m_criContext = _criContext;
			_criProgramCI.m_VertexCode = _fileVertexSrc->getData();
			_criProgramCI.m_FragmentCode = _fileFragmentSrc->getData();

			CRI::CRIProgram _criProgram = _criContext->create(&_criProgramCI);
			

			// ~~~~~~~~~~~~~~~~
			// ~~~~~~~~~~~~~~~~

			FE::CRI::CRI_PIPELINE_INPUT_PRIMITIVE _criPipeline_InputPrimitiveCI = {};
			_criPipeline_InputPrimitiveCI.m_Topology = FE::CRI::CRI_PIPELINE_INPUT_PRIMITIVE::TOPOLOGY::TRIANGLE_LIST;

			FE::CRI::CRI_PIPELINE_RASTERIZATION _criPipeline_RasterizationCI = {};
			_criPipeline_RasterizationCI.m_Polygon = FE::CRI::CRI_PIPELINE_RASTERIZATION::POLYGON::FILL;
			_criPipeline_RasterizationCI.m_Cull = FE::CRI::CRI_PIPELINE_RASTERIZATION::CULL::BACK;
			_criPipeline_RasterizationCI.m_FrontFace = FE::CRI::CRI_PIPELINE_RASTERIZATION::FRONT_FACE::CLOCKWISE;
			_criPipeline_RasterizationCI.m_LineWidth = 1.0f;

			//FE::CRI::CRI_PIPELINE_SHADER _criPipeline_ShaderVertexCI = {};
			//_criPipeline_ShaderVertexCI.m_Stage = FE::CRI::CRI_PIPELINE_SHADER::STAGE::VERTEX;
			//_criPipeline_ShaderVertexCI.m_Code = _content->get(PATH_SHADERS + "gbuffer.mrt.base.vert.spv")->;

			//FE::CRI::CRI_PIPELINE_SHADER _criPipeline_ShaderFragmentCI = {};
			//_criPipeline_ShaderFragmentCI.m_Stage = FE::CRI::CRI_PIPELINE_SHADER::STAGE::FRAGMENT;
			//_criPipeline_ShaderFragmentCI.m_Code = load("D:/Laboratory/FUNEngine/Data/Shaders/GBufferUsing.fspv");

			FE::CRI::CRI_PIPELINE_UNIFORM_LAYOUT::BINDING _criPipeline_UniformBinding0CI = {};
			_criPipeline_UniformBinding0CI.m_Type = FE::CRI::CRI_PIPELINE_UNIFORM_LAYOUT::BINDING::TYPE::UNIFORM;
			_criPipeline_UniformBinding0CI.m_Stage = FE::CRI::CRI_PIPELINE_UNIFORM_LAYOUT::BINDING::STAGE::VERTEX;

			FE::CRI::CRI_PIPELINE_VERTEX_LAYOUT::ATTRIBUTE _criPipeline_AttributeBindingPositionCI = {};
			_criPipeline_AttributeBindingPositionCI.m_Format = COMMON::FORMAT::DATA::_32_32_32_SFLOAT;
			_criPipeline_AttributeBindingPositionCI.m_Offset = 0;

			FE::CRI::CRI_PIPELINE_CI _criPipelineCI = {};

			_criPipelineCI.m_criContext = _criContext;
			_criPipelineCI.m_RenderPass = m_Renderer->getInputRenderPass();
			//_criPipelineCI.m_criProgram = _criProgram_gbuffer_1pass;
			_criPipelineCI.m_InputAssembly = _criPipeline_InputPrimitiveCI;
			//_criPipelineCI.m_Rasterization = _criPipeline_RasterizationCI;
			//_criPipelineCI.m_Shader = { _criPipeline_ShaderVertexCI, _criPipeline_ShaderFragmentCI };
			//_criPipelineCI.m_Uniformlayout = { { _criPipeline_UniformBinding0CI, _criPipeline_UniformBinding1CI, _criPipeline_UniformBinding2CI,} };
			//_criPipelineCI.m_VertexLayout = { { _criPipeline_AttributeBindingPositionCI } };
			//_criPipelineCI.m_ColorBlend = 1;

			//CRI::CRIPipeline _criPipeline;
			//CRI::CCRIContext::create(m_Context, &_criPipeline, &_criPipelineCI);*/
		}

		//==============================================================
		//==============================================================

	} // namespace RENDERER

} // namespace FE