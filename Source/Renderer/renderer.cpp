////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "pch.renderer.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "Renderer.h"
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
#include "Mesh.h"
#include "Effect.h"
#include "DrawPackage.h"
#include "Technique.h"
#include "techniquePass.h"

#include "../CommonRenderInterface/criCoreInfo.h"
#include "../CommonRenderInterface/criContext.h"
#include "../CommonRenderInterface/criDrawBufferInfo.h"
#include "../CommonRenderInterface/criRenderPass.h"
#include "../CommonRenderInterface/criProgram.h"
#include "../CommonRenderInterface/criPipeline.h"
#include "../CommonRenderInterface/criDataBuffer.h"
#include "../CommonRenderInterface/criImageBuffer.h"

#include "..\Scene\SceneObject.h"
#include "..\Particles\Particles.h"
#include <vector>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


namespace FE {

	namespace RENDERER {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		CRenderer::CRenderer(CORE::Core core)
			: m_Core(core),
			m_CreateInfo({}) {

		}

		//==============================================================
		//==============================================================

		CORE::Core CRenderer::getCore(void) const {

			return m_Core;
		}

		//==============================================================
		//==============================================================

		void CRenderer::reg(DrawPackage drawPackage) {

			// проверяем наличие в списке
			for (size_t ctDrawPackage = 0; ctDrawPackage < m_Meshes.size(); ++ctDrawPackage) {

				auto itDrawPackage = m_DrawPackages[ctDrawPackage];

				// если есть - уходим
				if (itDrawPackage == drawPackage) return;

			}

			// если нет - добавляем
			m_DrawPackages.push_back(drawPackage);
		}

		//==============================================================
		//==============================================================

		void CRenderer::create(Renderer renderer, Mesh *mesh, const MESH_CREATE_INFO *createInfo) {

			// новый
			auto _new = std::make_shared<CMesh>(renderer);

			// регистрируем
			renderer->m_Meshes.push_back(_new);

			_new->create(createInfo);

			// сохраняем
			*mesh = _new;
			
		}

		//==============================================================
		//==============================================================

		void CRenderer::create(Renderer renderer, DrawPackage *drawPackage, const DRAW_PACKAGE_CREATE_INFO *createInfo) {

			// новый
			auto _new = std::make_shared<CDrawPackage>(renderer);

			// регистрируем
			renderer->m_DrawPackages.push_back(_new);

			_new->create(createInfo);

			// сохраняем
			*drawPackage = _new;
		}

		//==============================================================
		//==============================================================

		void CRenderer::create(const RENDERER_CREATE_INFO *createInfo) {

			ASSERT_EX(static_cast<int>(createInfo->m_Technique), !=, static_cast<int>(RENDERER_CREATE_INFO::TYPE::UNKNOWN), "RENDERER_CREATE_INFO is incorrect.", throw e_renderer_create_failed());
			
			// ~~~~~~~~~~~~~~~~
			// загрузка шейдеров
			// ~~~~~~~~~~~~~~~~

			// ~~~~~~~~~~~~~~~~
			// создаём контекст
			// ~~~~~~~~~~~~~~~~

			FE::CRI::CRI_CONTEXT_CREATE_INFO _criContextCI = {};

			_criContextCI.m_Width = 800;
			_criContextCI.m_Height = 600;
			_criContextCI.m_Sync = CRI::CRI_CONTEXT_CREATE_INFO::SYNC::NOT_VSYNC;
			_criContextCI.m_Type = CRI::CRI_CONTEXT_CREATE_INFO::TYPE::DEBUG;
			_criContextCI.m_Bufferization = CRI::CRI_CONTEXT_CREATE_INFO::BUFFERIZATION::TRIPLE;
			_criContextCI.m_PlatformInfo.m_Handle = GetModuleHandle(NULL);
			_criContextCI.m_PlatformInfo.m_HWnd = createInfo->m_HWnd;

			auto _criContext = CRI::CCRIContext::create(&_criContextCI);
			

			m_Context = _criContext;
			//FE::CRI::CRIContext _newCRIContext = new FE::CRI::CCRIContext();
			//_newCRIContext->create(&_criContextCI);

			
			createDefferedTechnique();
	
			
			//createForwardTechnique();

			// ~~~~~~~~~~~~~~~~
			// геометрия квада для вывода gbuffer
			// ~~~~~~~~~~~~~~~~

			std::vector<uint32_t> _cubeIndices = {
				0, 3, 1,  1, 3, 2, // front
			};

			float s = 0.7f; // половина размера куба
			std::vector<float> _cubeVertices = {
				//-s, s, s,	1.0f, 1.0f, 1.0f,	0.0f, 0.0f, 1.0f,	s, s, s,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 1.0f,	s,-s, s,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 1.0f,	-s,-s, s,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 1.0f // front
				//-s, s, -0.000001f,		s, s,-0.000001f,			s,-s, -0.000001f,			-s,-s, -0.000001f	// front
				-s, s, 0.0f,		s, s, 0.0f,			s,-s, 0.0f,			-s,-s, 0.0f		// front
				//-s, s, 1.0f,		s, s, 1.0f,		s,-s, 1.0f,		-s,-s, 1.0f	// front
			};

			// буферы для вертексов

			FE::CRI::CRI_DATA_BUFFER_UPDATE_INFO _vertexBufferUI = {};

			_vertexBufferUI.m_Data = _cubeVertices.data();
			_vertexBufferUI.m_Offset = 0;
			_vertexBufferUI.m_Size = _cubeVertices.size() * sizeof(float);

			FE::CRI::CRI_DATA_BUFFER_CREATE_INFO _vertexBufferCI = {};

			_vertexBufferCI.m_Usage = FE::CRI::CRI_DATA_BUFFER_CREATE_INFO::USAGE::VERTEX;
			_vertexBufferCI.m_Storage = FE::CRI::CRI_DATA_BUFFER_CREATE_INFO::STORAGE::HOST;
			_vertexBufferCI.m_Size = _cubeVertices.size() * sizeof(float);;
			_vertexBufferCI.m_Update = _vertexBufferUI;

			// буферы для индексов

			FE::CRI::CRI_DATA_BUFFER_UPDATE_INFO _indexBufferUI = {};

			_indexBufferUI.m_Data = _cubeIndices.data();
			_indexBufferUI.m_Offset = 0;
			_indexBufferUI.m_Size = _cubeIndices.size() * sizeof(uint32_t);;

			FE::CRI::CRI_DATA_BUFFER_CREATE_INFO _indexBufferCI = {};

			_indexBufferCI.m_Usage = FE::CRI::CRI_DATA_BUFFER_CREATE_INFO::USAGE::INDEX;
			_indexBufferCI.m_Storage = FE::CRI::CRI_DATA_BUFFER_CREATE_INFO::STORAGE::HOST;
			_indexBufferCI.m_Size = _cubeIndices.size() * sizeof(uint32_t);
			_indexBufferCI.m_Update = _indexBufferUI;

			// буфер для юниформ

			mat4 _uniformData[4];

			mat4 &_model = _uniformData[0];
			_model = Translation(vec3(0.0f, 0.0f, 0.0f));
			_model = transpose(_model);

			mat4 &_view = _uniformData[1];
			_view = transpose(_view);

			mat4 &_projection = _uniformData[2];
			_projection = transpose(_projection);

			mat4 &_mvp = _uniformData[3];
			_mvp = _model * _view * _projection;
			_mvp = transpose(_mvp);

			FE::CRI::CRI_DATA_BUFFER_UPDATE_INFO _uniformBufferUI = {};

			_uniformBufferUI.m_Data = &_uniformData[0].m[0];
			_uniformBufferUI.m_Offset = 0;
			_uniformBufferUI.m_Size = sizeof(mat4) * 4;

			FE::CRI::CRI_DATA_BUFFER_CREATE_INFO _uniformBufferCI = {};

			_uniformBufferCI.m_Usage = FE::CRI::CRI_DATA_BUFFER_CREATE_INFO::USAGE::UNIFORM;
			_uniformBufferCI.m_Storage = FE::CRI::CRI_DATA_BUFFER_CREATE_INFO::STORAGE::HOST;
			_uniformBufferCI.m_Size = sizeof(mat4) * 4;
			//_uniformBufferCI.m_Data = _uniformBufferUI;

			//FE::CRI::CRIDataBuffer _vertexBuffer = {}, _indexBuffer = {}, _uniformBuffer = {};
			CRI::CCRIContext::create(m_Context, &m_VB, &_vertexBufferCI);
			CRI::CCRIContext::create(m_Context, &m_IB, &_indexBufferCI);
			CRI::CCRIContext::create(m_Context, &m_UB, &_uniformBufferCI);

			

			// ~~~~~~~~~~~~~~~~
			// drawbuffer
			// ~~~~~~~~~~~~~~~~

			FE::CRI::CRI_DRAW_OBJECT_UNIFORM_IMAGE_BUFFER_INFO _uniformSamplePositionCI = {};
			_uniformSamplePositionCI.m_Buffer = m_ImageBuffers[0];
			_uniformSamplePositionCI.m_Type = FE::CRI::CRI_DRAW_OBJECT_UNIFORM_IMAGE_BUFFER_INFO::TYPE::INPUT;

			FE::CRI::CRI_DRAW_OBJECT_UNIFORM_IMAGE_BUFFER_INFO _uniformSampleColorCI = {};
			_uniformSampleColorCI.m_Buffer = m_ImageBuffers[1];
			_uniformSampleColorCI.m_Type = FE::CRI::CRI_DRAW_OBJECT_UNIFORM_IMAGE_BUFFER_INFO::TYPE::INPUT;

			FE::CRI::CRI_DRAW_OBJECT_UNIFORM_IMAGE_BUFFER_INFO _uniformSampleNormalCI = {};
			_uniformSampleNormalCI.m_Buffer = m_ImageBuffers[2];
			_uniformSampleNormalCI.m_Type = FE::CRI::CRI_DRAW_OBJECT_UNIFORM_IMAGE_BUFFER_INFO::TYPE::INPUT;
			

			FE::CRI::CRI_DRAW_BUFFER_CREATE_INFO _drawBufferCI = {};
			_drawBufferCI.m_Context = m_Context;
			_drawBufferCI.m_RenderPass = m_R1;
			_drawBufferCI.m_NumberSubpass = 1;
			_drawBufferCI.m_Pipeline = m_P1;
			_drawBufferCI.m_Vertices = m_VB;
			_drawBufferCI.m_Indices = m_IB;
			_drawBufferCI.m_UniformDBs = { };
			_drawBufferCI.m_UniformIBs = { _uniformSamplePositionCI, _uniformSampleColorCI, _uniformSampleNormalCI };

			FE::CRI::CRIDrawBuffer _drawBuffer;
			FE::CRI::OPERATION::createDrawBuffer(&_drawBuffer, &_drawBufferCI);

			FE::CRI::CRIDrawBufferArr _drawBuffers = { _drawBuffer };

			FE::CRI::OPERATION::drawBuffer(m_Context, &_drawBuffers);

		}

		//==============================================================
		//==============================================================

		const RENDERER_CREATE_INFO& CRenderer::getCreateInfo(void) const {

			return m_CreateInfo;
		}

		//==============================================================
		//==============================================================

		void CRenderer::addObjects(SCENE::SceneObjectArr *sceneObjects) {

			for (size_t ctSceneObject = 0; ctSceneObject < sceneObjects->size(); ++ctSceneObject) {

				if (ctSceneObject == 10) {

					int a = 0;
					++a;
				}
				auto _itSceneObject = (*sceneObjects)[ctSceneObject];

				const auto _mesh = _itSceneObject->getDrawPackage()->getMesh();

				const auto _meshAttributeDeclaration = _mesh->getAttributeDeclaration();

				//for (size_t ctCRIPipeline = 0; ctCRIPipeline < m_RendererPassDescriptions[0].m_RendererSubpassDescriptions[0].m_CRIPipelines.size(); ++ctCRIPipeline) {

				//	const auto _itCRIPipeline = m_RendererPassDescriptions[0].m_RendererSubpassDescriptions[0].m_CRIPipelines[ctCRIPipeline];

					//_itCRIPipeline->
				//}

				//_itSceneObject->getDrawPackage()->getMesh()->

				// ~~~~~~~~~~~~~~~~
				// объект отрисовки
				// ~~~~~~~~~~~~~~~~

				FE::CRI::CRI_DRAW_OBJECT_UNIFORM_DATA_BUFFER_INFO _uniformMatricxCI = {};
				FE::CRI::CRI_DRAW_BUFFER_CREATE_INFO _drawBufferCI = {};
				FE::CRI::CRIDrawBuffer _drawBuffer;
				FE::CRI::CRIDrawBufferArr _drawBuffers = { };

				_uniformMatricxCI = {};

				_uniformMatricxCI.m_Buffer = _itSceneObject->m_Uniforms;
				_uniformMatricxCI.m_Type = FE::CRI::CRI_DRAW_OBJECT_UNIFORM_DATA_BUFFER_INFO::TYPE::UNIFORM;
				_uniformMatricxCI.m_Binding = 0;

				_drawBufferCI = {};

				_drawBufferCI.m_Context = m_Context;
				//_drawBufferCI.m_RenderPass = m_Techniques[0]->m_RenderPass;
				//_drawBufferCI.m_RenderPass = m_RenderPass;
				_drawBufferCI.m_RenderPass = m_R0;
				_drawBufferCI.m_RenderPass = m_Techniques[0]->getInputTechniquePass()->getCRIRenderPass();
				//_drawBufferCI.m_NumberSubpass = 0;
				_drawBufferCI.m_Pipeline = m_P0;
				_drawBufferCI.m_Vertices = _itSceneObject->getDrawPackage()->getMesh()->getVertices()[0];
				_drawBufferCI.m_Indices = _itSceneObject->getDrawPackage()->getMesh()->getIndices();
				_drawBufferCI.m_UniformDBs = { _uniformMatricxCI };

				FE::CRI::OPERATION::createDrawBuffer(&_drawBuffer, &_drawBufferCI);

				_drawBuffers = { _drawBuffer };
				FE::CRI::OPERATION::drawBuffer(m_Context, &_drawBuffers);

			}
						
		}

		//==============================================================
		//==============================================================

		void CRenderer::destroy(void) {

			
		}

		//==============================================================
		//==============================================================

		CRenderer::~CRenderer() {


		}

		//==============================================================
		//==============================================================

		void CRenderer::update(void) {

			m_Context->update();

		}

		//==============================================================
		//==============================================================

		void CRenderer::execute(void) {

			m_Context->execute();

		}

		//==============================================================
		//==============================================================

		CRI::CRIRenderPass CRenderer::getInputRenderPass(void) const {

			return m_R0;
		}

		//==============================================================
		//==============================================================
		const std::string PATH_SHADERS = "D:/Laboratory/FUNEngine/Data/Shaders/sprv/";
		void CRenderer::createDefferedTechnique() {

			//load("D:/Laboratory/FUNEngine/Data/Shaders/transfer@pcn.vert.spv");
			//load("D:/Laboratory/FUNEngine/Data/Shaders/mrt@pcn.frag.spv");

			//load("D:/Laboratory/FUNEngine/Data/Shaders/quad@p.vert.spv");
			//load("D:/Laboratory/FUNEngine/Data/Shaders/deffered@composite@p.frag.spv");
			
			// ~~~~~~~~~~~~~~~~
			// ~~~~~~~~~~~~~~~~

			{
				std::string _vertexSrc = load(PATH_SHADERS + "default@default@default@gBuffer.vert.spv");
				std::string _fragmentSrc = load(PATH_SHADERS + "default@default@default@gBuffer.frag.spv");

				CRI::CRI_PROGRAM_CREATE_INFO _criProgramCI = {};
				_criProgramCI.m_criContext = m_Context;
				_criProgramCI.m_VertexCode = _vertexSrc;
				_criProgramCI.m_FragmentCode = _fragmentSrc;

				CRI::CRIProgram _criProgram = m_Context->create(&_criProgramCI);

				// ~~~~~~~~~~~~~~~~
				// ~~~~~~~~~~~~~~~~

				CShaderDescription _shaderDescription = {};
				_shaderDescription.m_type0 = CShaderDescription::TYPE0::TRANSFER;
				_shaderDescription.m_type1 = CShaderDescription::TYPE1::DEFAULT;
				_shaderDescription.m_type2 = CShaderDescription::TYPE2::DEFAULT;
				_shaderDescription.m_type3 = CShaderDescription::TYPE3::MRT;
				_shaderDescription.m_criProgramm = _criProgram;

				m_shaders.push_back(_shaderDescription);

			}

			// ~~~~~~~~~~~~~~~~
			// ~~~~~~~~~~~~~~~~

			{
				std::string _vertexSrc = load(PATH_SHADERS + "default@default@default@lighting_gBuffer.vert.spv");
				std::string _fragmentSrc = load(PATH_SHADERS + "default@default@default@lighting_gBuffer.frag.spv");

				CRI::CRI_PROGRAM_CREATE_INFO _criProgramCI = {};
				_criProgramCI.m_criContext = m_Context;
				_criProgramCI.m_VertexCode = _vertexSrc;
				_criProgramCI.m_FragmentCode = _fragmentSrc;

				CRI::CRIProgram _criProgram = m_Context->create(&_criProgramCI);

				// ~~~~~~~~~~~~~~~~
				// ~~~~~~~~~~~~~~~~

				CShaderDescription _shaderDescription = {};
				_shaderDescription.m_type0 = CShaderDescription::TYPE0::QUAD;
				_shaderDescription.m_type1 = CShaderDescription::TYPE1::DEFAULT;
				_shaderDescription.m_type2 = CShaderDescription::TYPE2::DEFAULT;
				_shaderDescription.m_type3 = CShaderDescription::TYPE3::LAMBERT;
				_shaderDescription.m_criProgramm = _criProgram;

				m_shaders.push_back(_shaderDescription);
			}

			// 0 - texture
			// 1 - color
			// 2 - normal
			// 3 - depth

			for (uint32_t ctImageBuffer = 0; ctImageBuffer < 4; ++ctImageBuffer) {

				// CRI_IMAGE_BUFFER_CREATE_INFO
				CRI::CRI_IMAGE_BUFFER_CREATE_INFO _criImageBufferCI = {};
				_criImageBufferCI.m_CRIContext = m_Context;
				_criImageBufferCI.m_Type = CRI::CRI_IMAGE_BUFFER_CREATE_INFO::TYPE::_2D;
				_criImageBufferCI.m_Attachment = CRI::CRI_IMAGE_BUFFER_CREATE_INFO::ATTACHMENT::INPUT;
				_criImageBufferCI.m_Storage = CRI::CRI_IMAGE_BUFFER_CREATE_INFO::STORAGE::DEVICE;
				_criImageBufferCI.m_Width = 800;
				_criImageBufferCI.m_Height = 600;
				_criImageBufferCI.m_Format = COMMON::FORMAT::TEXTURE::R16G16B16A16_SFLOAT;
				_criImageBufferCI.m_MipLevels = 1;

				if (ctImageBuffer == 3) {

					_criImageBufferCI.m_Format = COMMON::FORMAT::TEXTURE::D32_SFLOAT_S8_UINT;
				}

				auto _criImageBuffer = m_Context->create(&_criImageBufferCI);

				m_ImageBuffers.push_back(_criImageBuffer);
			}			

			// ~~~~~~~~~~~~~~~~
			// cri subpass
			// ~~~~~~~~~~~~~~~~
			
			//CRI::CRI_RENDER_SUBPASS_CI_ARR _criRenderSubpassCIs = {};
			
			// подпроход mrt
			{

				// ~~~~~~~~~~~~~~~~
				// cri render pass attachment
				// ~~~~~~~~~~~~~~~~

				CRI::CRI_RENDER_PASS_ATTACHMENT_CI _criRenderPassAttachmentColor0CI = {};
				_criRenderPassAttachmentColor0CI.m_Texture = m_ImageBuffers[0];
				_criRenderPassAttachmentColor0CI.m_Type = CRI::CRI_RENDER_PASS_ATTACHMENT_CI::TYPE::OUTPUT;

				CRI::CRI_RENDER_PASS_ATTACHMENT_CI _criRenderPassAttachmentColor1CI = {};
				_criRenderPassAttachmentColor1CI.m_Texture = m_ImageBuffers[1];
				_criRenderPassAttachmentColor1CI.m_Type = CRI::CRI_RENDER_PASS_ATTACHMENT_CI::TYPE::OUTPUT;

				CRI::CRI_RENDER_PASS_ATTACHMENT_CI _criRenderPassAttachmentColor2CI = {};
				_criRenderPassAttachmentColor2CI.m_Texture = m_ImageBuffers[2];
				_criRenderPassAttachmentColor2CI.m_Type = CRI::CRI_RENDER_PASS_ATTACHMENT_CI::TYPE::OUTPUT;

				CRI::CRI_RENDER_PASS_ATTACHMENT_CI _criRenderPassAttachmentDepthCI = {};
				_criRenderPassAttachmentDepthCI.m_Texture = m_ImageBuffers[3];
				_criRenderPassAttachmentDepthCI.m_Type = CRI::CRI_RENDER_PASS_ATTACHMENT_CI::TYPE::OUTPUT;

				// ~~~~~~~~~~~~~~~~
				// cri pass
				// ~~~~~~~~~~~~~~~~

				CRI::CRI_RENDER_PASS_CI _criRenderPassCI = {};
				
				_criRenderPassCI.m_CRIContext = m_Context;
				_criRenderPassCI.m_Present = true;
				_criRenderPassCI.m_Attachments = { _criRenderPassAttachmentColor0CI, _criRenderPassAttachmentColor1CI, _criRenderPassAttachmentColor2CI, _criRenderPassAttachmentDepthCI };
				_criRenderPassCI.m_ClearValue = vec4(1.0f, 0.0f, 0.0f, 0.0f);
				_criRenderPassCI.m_Width = 800;
				_criRenderPassCI.m_Height = 600;
				
				m_R0 = m_Context->create(&_criRenderPassCI);

				//_renderPass->
				//m_Context->getRenderPass(&_criRenderPassCI, &_renderPass);
				//m_R0 = _renderPass;
				//CRI::CRI_RENDER_SUBPASS_CI _criRenderSubpassCI = {};

				//_criRenderSubpassCI.m_InputAttachments = {};
				//_criRenderSubpassCI.m_OutputAttachments = { 0, 1, 2, 3, 4 };

				//_criRenderSubpassCIs.push_back(_criRenderSubpassCI);
			}

			// подпроход composite
			{
				//CRI::CRI_RENDER_SUBPASS_CI _criRenderSubpassCI = {};

				//_criRenderSubpassCI.m_InputAttachments = { 1, 2, 3 };
				//_criRenderSubpassCI.m_OutputAttachments = { 0, 4 };

				//_criRenderSubpassCIs.push_back(_criRenderSubpassCI);
			}

			// ~~~~~~~~~~~~~~~~
			// cri pass
			// ~~~~~~~~~~~~~~~~

			// ~~~~~~~~~~~~~~~~
			// cri render pass attachment
			// ~~~~~~~~~~~~~~~~

			//CRI::CRI_RENDER_PASS_ATTACHMENT_CI _criRenderPassAttachmentPresentCI = {};
			//_criRenderPassAttachmentPresentCI.m_Texture = nullptr;
			//_criRenderPassAttachmentPresentCI.m_Type = CRI::CRI_RENDER_PASS_ATTACHMENT_CI::TYPE::OUTPUT;

			CRI::CRI_RENDER_PASS_ATTACHMENT_CI _criRenderPassAttachmentColor0CI = {};
			_criRenderPassAttachmentColor0CI.m_Texture = m_ImageBuffers[0];
			_criRenderPassAttachmentColor0CI.m_Type = CRI::CRI_RENDER_PASS_ATTACHMENT_CI::TYPE::INPUT;

			CRI::CRI_RENDER_PASS_ATTACHMENT_CI _criRenderPassAttachmentColor1CI = {};
			_criRenderPassAttachmentColor1CI.m_Texture = m_ImageBuffers[1];
			_criRenderPassAttachmentColor1CI.m_Type = CRI::CRI_RENDER_PASS_ATTACHMENT_CI::TYPE::INPUT;

			CRI::CRI_RENDER_PASS_ATTACHMENT_CI _criRenderPassAttachmentColor2CI = {};
			_criRenderPassAttachmentColor2CI.m_Texture = m_ImageBuffers[2];
			_criRenderPassAttachmentColor2CI.m_Type = CRI::CRI_RENDER_PASS_ATTACHMENT_CI::TYPE::INPUT;

			CRI::CRI_RENDER_PASS_ATTACHMENT_CI _criRenderPassAttachmentDepthCI = {};
			_criRenderPassAttachmentDepthCI.m_Texture = m_ImageBuffers[3];
			_criRenderPassAttachmentDepthCI.m_Type = CRI::CRI_RENDER_PASS_ATTACHMENT_CI::TYPE::OUTPUT;

			CRI::CRI_RENDER_PASS_CI _criRenderPassCI = {};
			_criRenderPassCI.m_CRIContext = m_Context;
			_criRenderPassCI.m_Present = true;
			_criRenderPassCI.m_Attachments = { _criRenderPassAttachmentColor0CI, _criRenderPassAttachmentColor1CI, _criRenderPassAttachmentColor2CI, _criRenderPassAttachmentDepthCI };
			_criRenderPassCI.m_ClearValue = vec4(0.0f, 1.0f, 0.0f, 0.0f);
			_criRenderPassCI.m_Width = 800;
			_criRenderPassCI.m_Height = 600;
			//_criRenderPassCI.m_SubpassDescs = _criRenderSubpassCIs;

			m_R1 = m_Context->create(&_criRenderPassCI);
			//m_Context->getRenderPass(&_criRenderPassCI, &_renderPass);
			//m_R1 = _renderPass;
			//RendererPassDescription _rendererPassDescription = {};
			//_rendererPassDescription.m_CRIRenderPass = _renderPass;
			//_rendererPassDescription.m_RendererSubpassDescriptions.resize(_criRenderSubpassCIs.size());

			//m_RendererPassDescriptions.push_back(_rendererPassDescription);

			m_IDInputCRIRenderPass = 0;
			m_IDInputCRIRenderSubpass = 0;
			//m_CRIRenderPasses.push_back(_renderPass);

			// ~~~~~~~~~~~~~~~~
			// cri program
			// ~~~~~~~~~~~~~~~~

			//CRI::CRIProgram _criProgram_GBuffer;
			//CRI::CRIProgram _criProgram_Composite;

			// mrt
			//{

				//CRI::CRI_PROGRAM_CREATE_INFO _criProgramCI = {};
				//_criProgramCI.m_criContext = m_Context;
				//_criProgramCI.m_VertexCode = load("D:/Laboratory/FUNEngine/Data/Shaders/GBufferFill.vert.spv");
				//_criProgramCI.m_VertexCode = load("D:/Laboratory/FUNEngine/Data/Shaders/Cache/deffered_1pass@transfer@@@mrt@pcn.vert.spv");
				//_criProgramCI.m_FragmentCode = load("D:/Laboratory/FUNEngine/Data/Shaders/Cache/deffered_1pass@transfer@@@mrt@pcn.frag.spv");

				//_criProgram_GBuffer = CRI::CCRIProgram::create(&_criProgramCI);
				

			//}

			// composite
			//{

				//CRI::CRI_PROGRAM_CREATE_INFO _criProgramCI = {};
				//_criProgramCI.m_criContext = m_Context;
				//_criProgramCI.m_VertexCode = load("D:/Laboratory/FUNEngine/Data/Shaders/Cache/deffered_2pass@quad@@@lambert@p.vert.spv");
				//_criProgramCI.m_FragmentCode = load("D:/Laboratory/FUNEngine/Data/Shaders/Cache/deffered_2pass@quad@@@lambert@p.frag.spv");

				//_criProgram_Composite = CRI::CCRIProgram::create(&_criProgramCI);
				

			//}

			// ~~~~~~~~~~~~~~~~
			// cri pipeline
			// ~~~~~~~~~~~~~~~~

			// mrt pipeline
			{
				FE::CRI::CRI_PIPELINE_INPUT_PRIMITIVE _criPipeline_InputPrimitiveCI = {};
				_criPipeline_InputPrimitiveCI.m_Topology = FE::CRI::CRI_PIPELINE_INPUT_PRIMITIVE::TOPOLOGY::TRIANGLE_LIST;

				FE::CRI::CRI_PIPELINE_RASTERIZATION _criPipeline_RasterizationCI = {};
				_criPipeline_RasterizationCI.m_Polygon = FE::CRI::CRI_PIPELINE_RASTERIZATION::POLYGON::FILL;
				_criPipeline_RasterizationCI.m_Cull = FE::CRI::CRI_PIPELINE_RASTERIZATION::CULL::BACK;
				_criPipeline_RasterizationCI.m_FrontFace = FE::CRI::CRI_PIPELINE_RASTERIZATION::FRONT_FACE::CLOCKWISE;
				_criPipeline_RasterizationCI.m_LineWidth = 2.0f;

				//FE::CRI::CRI_PIPELINE_SHADER _criPipeline_ShaderVertexCI = {};
				//_criPipeline_ShaderVertexCI.m_Stage = FE::CRI::CRI_PIPELINE_SHADER::STAGE::VERTEX;
				//_criPipeline_ShaderVertexCI.m_Code = load("D:/Laboratory/FUNEngine/Data/Shaders/GBufferFill.vert.spv");

				//FE::CRI::CRI_PIPELINE_SHADER _criPipeline_ShaderFragmentCI = {};
				//_criPipeline_ShaderFragmentCI.m_Stage = FE::CRI::CRI_PIPELINE_SHADER::STAGE::FRAGMENT;
				//_criPipeline_ShaderFragmentCI.m_Code = load("D:/Laboratory/FUNEngine/Data/Shaders/GBufferFill.frag.spv");

				FE::CRI::CRI_PIPELINE_UNIFORM_LAYOUT::BINDING _criPipeline_UniformBinding0CI = {};
				_criPipeline_UniformBinding0CI.m_Type = FE::CRI::CRI_PIPELINE_UNIFORM_LAYOUT::BINDING::TYPE::UNIFORM;
				_criPipeline_UniformBinding0CI.m_Stage = FE::CRI::CRI_PIPELINE_UNIFORM_LAYOUT::BINDING::STAGE::VERTEX;

				FE::CRI::CRI_PIPELINE_VERTEX_LAYOUT::ATTRIBUTE _criPipeline_AttributeBindingPositionCI = {};
				_criPipeline_AttributeBindingPositionCI.m_Format = COMMON::FORMAT::DATA::_32_32_32_SFLOAT;
				_criPipeline_AttributeBindingPositionCI.m_Offset = 0;

				FE::CRI::CRI_PIPELINE_VERTEX_LAYOUT::ATTRIBUTE _criPipeline_AttributeBindingColorCI = {};
				_criPipeline_AttributeBindingColorCI.m_Format = COMMON::FORMAT::DATA::_32_32_32_SFLOAT;
				_criPipeline_AttributeBindingColorCI.m_Offset = _criPipeline_AttributeBindingPositionCI.m_Offset + 24;

				FE::CRI::CRI_PIPELINE_VERTEX_LAYOUT::ATTRIBUTE _criPipeline_AttributeBindingNormalCI = {};
				_criPipeline_AttributeBindingNormalCI.m_Format = COMMON::FORMAT::DATA::_32_32_32_SFLOAT;
				_criPipeline_AttributeBindingNormalCI.m_Offset = _criPipeline_AttributeBindingColorCI.m_Offset + 24;

				FE::CRI::CRI_PIPELINE_CI _criPipelineCI = {};
				
				_criPipelineCI.m_criContext = m_Context;
				_criPipelineCI.m_RenderPass = m_R0;
				//_criPipelineCI.m_criProgram = _criProgram_GBuffer;
				_criPipelineCI.m_criProgram = m_shaders[0].m_criProgramm;
				_criPipelineCI.m_InputAssembly = _criPipeline_InputPrimitiveCI;
				_criPipelineCI.m_Rasterization = _criPipeline_RasterizationCI;
				//_criPipelineCI.m_Shader = { _criPipeline_ShaderVertexCI, _criPipeline_ShaderFragmentCI };
				_criPipelineCI.m_Uniformlayout = { { _criPipeline_UniformBinding0CI } };
				_criPipelineCI.m_VertexLayout = { { _criPipeline_AttributeBindingPositionCI, _criPipeline_AttributeBindingColorCI, _criPipeline_AttributeBindingNormalCI } };

				m_P0 = m_Context->create(&_criPipelineCI);
			}

			// composite pipeline
			{
				FE::CRI::CRI_PIPELINE_INPUT_PRIMITIVE _criPipeline_InputPrimitiveCI = {};
				_criPipeline_InputPrimitiveCI.m_Topology = FE::CRI::CRI_PIPELINE_INPUT_PRIMITIVE::TOPOLOGY::TRIANGLE_LIST;

				FE::CRI::CRI_PIPELINE_RASTERIZATION _criPipeline_RasterizationCI = {};
				_criPipeline_RasterizationCI.m_Polygon = FE::CRI::CRI_PIPELINE_RASTERIZATION::POLYGON::FILL;
				_criPipeline_RasterizationCI.m_Cull = FE::CRI::CRI_PIPELINE_RASTERIZATION::CULL::BACK;
				_criPipeline_RasterizationCI.m_FrontFace = FE::CRI::CRI_PIPELINE_RASTERIZATION::FRONT_FACE::CLOCKWISE;
				_criPipeline_RasterizationCI.m_LineWidth = 1.0f;

				//FE::CRI::CRI_PIPELINE_SHADER _criPipeline_ShaderVertexCI = {};
				//_criPipeline_ShaderVertexCI.m_Stage = FE::CRI::CRI_PIPELINE_SHADER::STAGE::VERTEX;
				//_criPipeline_ShaderVertexCI.m_Code = load("D:/Laboratory/FUNEngine/Data/Shaders/GBufferUsing.vert.spv");

				//FE::CRI::CRI_PIPELINE_SHADER _criPipeline_ShaderFragmentCI = {};
				//_criPipeline_ShaderFragmentCI.m_Stage = FE::CRI::CRI_PIPELINE_SHADER::STAGE::FRAGMENT;
				//_criPipeline_ShaderFragmentCI.m_Code = load("D:/Laboratory/FUNEngine/Data/Shaders/GBufferUsing.frag.spv");

				FE::CRI::CRI_PIPELINE_UNIFORM_LAYOUT::BINDING _criPipeline_UniformBinding0CI = {};
				_criPipeline_UniformBinding0CI.m_Type = FE::CRI::CRI_PIPELINE_UNIFORM_LAYOUT::BINDING::TYPE::INPUT;
				_criPipeline_UniformBinding0CI.m_Stage = FE::CRI::CRI_PIPELINE_UNIFORM_LAYOUT::BINDING::STAGE::FRAGMENT;

				FE::CRI::CRI_PIPELINE_UNIFORM_LAYOUT::BINDING _criPipeline_UniformBinding1CI = {};
				_criPipeline_UniformBinding1CI.m_Type = FE::CRI::CRI_PIPELINE_UNIFORM_LAYOUT::BINDING::TYPE::INPUT;
				_criPipeline_UniformBinding1CI.m_Stage = FE::CRI::CRI_PIPELINE_UNIFORM_LAYOUT::BINDING::STAGE::FRAGMENT;

				FE::CRI::CRI_PIPELINE_UNIFORM_LAYOUT::BINDING _criPipeline_UniformBinding2CI = {};
				_criPipeline_UniformBinding2CI.m_Type = FE::CRI::CRI_PIPELINE_UNIFORM_LAYOUT::BINDING::TYPE::INPUT;
				_criPipeline_UniformBinding2CI.m_Stage = FE::CRI::CRI_PIPELINE_UNIFORM_LAYOUT::BINDING::STAGE::FRAGMENT;

				FE::CRI::CRI_PIPELINE_VERTEX_LAYOUT::ATTRIBUTE _criPipeline_AttributeBindingPositionCI = {};
				_criPipeline_AttributeBindingPositionCI.m_Format = COMMON::FORMAT::DATA::_32_32_32_SFLOAT;
				_criPipeline_AttributeBindingPositionCI.m_Offset = 0;

				FE::CRI::CRI_PIPELINE_CI _criPipelineCI = {};

				_criPipelineCI.m_criContext = m_Context;
				_criPipelineCI.m_RenderPass = m_R1;
				//_criPipelineCI.m_criProgram = _criProgram_Composite;
				_criPipelineCI.m_criProgram = m_shaders[1].m_criProgramm;
				_criPipelineCI.m_InputAssembly = _criPipeline_InputPrimitiveCI;
				_criPipelineCI.m_Rasterization = _criPipeline_RasterizationCI;
				//_criPipelineCI.m_Shader = { _criPipeline_ShaderVertexCI, _criPipeline_ShaderFragmentCI };
				_criPipelineCI.m_Uniformlayout = { { _criPipeline_UniformBinding0CI, _criPipeline_UniformBinding1CI, _criPipeline_UniformBinding2CI,} };
				_criPipelineCI.m_VertexLayout = { { _criPipeline_AttributeBindingPositionCI } };

				m_P1 = m_Context->create(&_criPipelineCI);
			}

			TECHNIQUE_CREATE_INFO _defferedTechniqueCI = {};

			// ~~~~~~~~~~~~~~~~
			// описание текстур
			// ~~~~~~~~~~~~~~~~

			// position
			TECHNIQUE_TEXTURE _positionTextureDesc = {};
			_positionTextureDesc.m_bind = 0;
			_positionTextureDesc.m_format = COMMON::FORMAT::TEXTURE::R16G16B16A16_SFLOAT;
			_positionTextureDesc.m_width = 800;
			_positionTextureDesc.m_height = 600;

			// color
			TECHNIQUE_TEXTURE _colorTextureDesc = {};
			_colorTextureDesc.m_bind = 1;
			_colorTextureDesc.m_format = COMMON::FORMAT::TEXTURE::R16G16B16A16_SFLOAT;
			_colorTextureDesc.m_width = 800;
			_colorTextureDesc.m_height = 600;

			// normal
			TECHNIQUE_TEXTURE _normalTextureDesc = {};
			_normalTextureDesc.m_bind = 2;
			_normalTextureDesc.m_format = COMMON::FORMAT::TEXTURE::R16G16B16A16_SFLOAT;
			_normalTextureDesc.m_width = 800;
			_normalTextureDesc.m_height = 600;

			// depth
			TECHNIQUE_TEXTURE _depthTextureDesc = {};
			_depthTextureDesc.m_bind = 3;
			_depthTextureDesc.m_format = COMMON::FORMAT::TEXTURE::D32_SFLOAT_S8_UINT;
			_depthTextureDesc.m_width = 800;
			_depthTextureDesc.m_height = 600;

			_defferedTechniqueCI.m_textureDescs = { _positionTextureDesc, _colorTextureDesc, _normalTextureDesc, _depthTextureDesc };

			// ~~~~~~~~~~~~~~~~
			// 1 проход
			// ~~~~~~~~~~~~~~~~
			
			{
				
				TECHNIQUE_PASS::ATTACHMENT _positionAttachmentDesc = {};
				_positionAttachmentDesc.m_bind = _positionTextureDesc.m_bind;
				_positionAttachmentDesc.m_type = TECHNIQUE_PASS::ATTACHMENT::TYPE::OUTPUT;

				TECHNIQUE_PASS::ATTACHMENT _colorAttachmentDesc = {};
				_colorAttachmentDesc.m_bind = _colorTextureDesc.m_bind;
				_colorAttachmentDesc.m_type = TECHNIQUE_PASS::ATTACHMENT::TYPE::OUTPUT;

				TECHNIQUE_PASS::ATTACHMENT _normalAttachmentDesc = {};
				_normalAttachmentDesc.m_bind = _normalTextureDesc.m_bind;
				_normalAttachmentDesc.m_type = TECHNIQUE_PASS::ATTACHMENT::TYPE::OUTPUT;

				TECHNIQUE_PASS::ATTACHMENT _depthAttachmentDesc = {};
				_depthAttachmentDesc.m_bind = _depthTextureDesc.m_bind;
				_depthAttachmentDesc.m_type = TECHNIQUE_PASS::ATTACHMENT::TYPE::OUTPUT;

				TECHNIQUE_PASS _techniquePassDesc = {};
				_techniquePassDesc.m_attachmentDescs = { _positionAttachmentDesc, _colorAttachmentDesc, _normalAttachmentDesc, _depthAttachmentDesc };
				
				_defferedTechniqueCI.m_passDescs.push_back(_techniquePassDesc);
			}
			
			// ~~~~~~~~~~~~~~~~
			// 2 проход
			// ~~~~~~~~~~~~~~~~

			{
				TECHNIQUE_PASS::ATTACHMENT _positionAttachmentDesc = {};
				_positionAttachmentDesc.m_bind = _positionTextureDesc.m_bind;
				_positionAttachmentDesc.m_type = TECHNIQUE_PASS::ATTACHMENT::TYPE::INPUT;

				TECHNIQUE_PASS::ATTACHMENT _colorAttachmentDesc = {};
				_colorAttachmentDesc.m_bind = _colorTextureDesc.m_bind;
				_colorAttachmentDesc.m_type = TECHNIQUE_PASS::ATTACHMENT::TYPE::INPUT;

				TECHNIQUE_PASS::ATTACHMENT _normalAttachmentDesc = {};
				_normalAttachmentDesc.m_bind = _normalTextureDesc.m_bind;
				_normalAttachmentDesc.m_type = TECHNIQUE_PASS::ATTACHMENT::TYPE::INPUT;

				TECHNIQUE_PASS::ATTACHMENT _depthAttachmentDesc = {};
				_depthAttachmentDesc.m_bind = _depthTextureDesc.m_bind;
				_depthAttachmentDesc.m_type = TECHNIQUE_PASS::ATTACHMENT::TYPE::OUTPUT;

				TECHNIQUE_PASS _techniquePassDesc = {};
				_techniquePassDesc.m_attachmentDescs = { _positionAttachmentDesc, _colorAttachmentDesc, _normalAttachmentDesc, _depthAttachmentDesc };

				_defferedTechniqueCI.m_passDescs.push_back(_techniquePassDesc);
			}

			// ~~~~~~~~~~~~~~~~
			// technique
			// ~~~~~~~~~~~~~~~~

			CTechnique* _technique = new CTechnique(this);

			_technique->create(&_defferedTechniqueCI);

			auto _ren = _technique->getInputTechniquePass();

			m_Techniques.push_back(_technique);
		}

		//==============================================================
		//==============================================================

		void CRenderer::createForwardTechnique() {

			// ~~~~~~~~~~~~~~~~
			// описываем конвееры
			// ~~~~~~~~~~~~~~~~

			// конвеер для форвард
			//RENDERER_TECHNIQUE_PIPELINE_CREATE_INFO _forwardPipelineCI = {};

			//_forwardPipelineCI.m_VertexCode = load("D:/Laboratory/FUNEngine/Data/Shaders/base.vspv");
			//_forwardPipelineCI.m_FragmentCode = load("D:/Laboratory/FUNEngine/Data/Shaders/base.fspv");
			//_forwardPipelineCI.m_Input = { RENDERER_TECHNIQUE_PIPELINE_CREATE_INFO::INPUT::UNIFORM };

			// ~~~~~~~~~~~~~~~~
			// описываем проходы техники
			// ~~~~~~~~~~~~~~~~

			// форвард проход
			//RENDERER_TECHNIQUE_PASS_CREATE_INFO _testGBufferPassI = {};

			///_testGBufferPassI.m_Attachments = {};
			///_testGBufferPassI.m_InputAtachments1;
			//_testGBufferPassI.m_OutputAtachments1;
			//_testGBufferPassI.m_Present = true;
			//_testGBufferPassI.m_Depth = true;

		}

		//==============================================================
		//==============================================================
	}

}