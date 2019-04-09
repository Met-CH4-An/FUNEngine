#include "PCH.h"
#include "Scene.h"
#include <thread>
#include <chrono>
#include "SceneObject.h"
#include "SceneObjectInfo.h"

#include "..\Renderer\GeometryInfo.h"

#include "..\CommonRenderInterface\criDataBuffer.h"
//#include "..\..\Renderer\"
#include "..\Renderer\Renderer.h"

#include "..\Content\ContentLoader.h"

#include <fstream>

#include "..\Renderer\Mesh.h"

#include "Camera.h"

#include "..\main.h"

#include "..\CommonRenderInterface\criContext.h"

#include "ScriptWriter.h"

#include "..\Input\Keyboard.h"
#include "..\Input\Mouse.h"

#include "..\Content\Content.h"

#include "..\Procedural\Procedural.h"

#include "..\Renderer\DrawPackage.h"

#include "..\Common\Blob.h"

#include "../CommonRenderInterface/criImageBuffer.h"

namespace FE {

	namespace SCENE {

		struct Object_File {

			std::string		m_Name;

			vec3						m_Position;
			std::vector<uint32_t>		m_CubeIndices;
			std::vector<float>			m_CubeVertices;
		};

		static std::vector<Object_File> G_OBJECT_FILE_ARR;

		struct Temp {

			inline Temp() {

				float s = 1.0f; // половина размера куба

				Object_File _PCN;

				_PCN.m_Name = "PCN";
				_PCN.m_Position = vec3(-5.0f, 0.0f, 0.0f);
				_PCN.m_CubeIndices = {
					0, 3, 1,  1, 3, 2, // front
					4, 7, 5,  5, 7, 6, // back
					8,11, 9,  9,11,10, // top
					12,15,13, 13,15,14, // bottom
					16,19,17, 17,19,18, // left
					20,23,21, 21,23,22  // right
				};
				_PCN.m_CubeVertices = {
					-s, s, s,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 1.0f,	s, s, s,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 1.0f,	s,-s, s,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 1.0f,	-s,-s, s,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 1.0f, // front
					s, s,-s,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,-1.0f,	-s, s,-s,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,-1.0f,	-s,-s,-s,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,-1.0f,	s,-s,-s,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,-1.0f, // back
					-s, s,-s,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,	s, s,-s,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,	s, s, s,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,	-s, s, s,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f, // top
					s,-s,-s,	0.0f, 0.0f, 0.0f,	0.0f,-1.0f, 0.0f,	-s,-s,-s,	0.0f, 0.0f, 0.0f,	0.0f,-1.0f, 0.0f,	-s,-s, s,	0.0f, 0.0f, 0.0f,	0.0f,-1.0f, 0.0f,	s,-s, s,	0.0f, 0.0f, 0.0f,	0.0f,-1.0f, 0.0f, // bottom
					-s, s,-s,	0.0f, 0.0f, 0.0f,	-1.0f, 0.0f, 0.0f,	-s, s, s,	0.0f, 0.0f, 0.0f,	-1.0f, 0.0f, 0.0f,	-s,-s, s,	0.0f, 0.0f, 0.0f,	-1.0f, 0.0f, 0.0f,	-s,-s,-s,	0.0f, 0.0f, 0.0f,	-1.0f, 0.0f, 0.0f, // left
					s, s, s,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,	s, s,-s,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,	s,-s,-s,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,	s,-s, s,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f  // right
				};
				G_OBJECT_FILE_ARR.push_back(_PCN);

				Object_File _PTN;

				_PTN.m_Name = "PTN";
				_PCN.m_Position = vec3(5.0f, 0.0f, 0.0f);
				_PTN.m_CubeIndices = {
					0, 3, 1,  1, 3, 2, // front
					4, 7, 5,  5, 7, 6, // back
					8,11, 9,  9,11,10, // top
					12,15,13, 13,15,14, // bottom
					16,19,17, 17,19,18, // left
					20,23,21, 21,23,22  // right
				};
				_PTN.m_CubeVertices = {
					 -s, s, s,	0.0f, 1.0f,		0.0f, 0.0f, 1.0f,	s, s, s,	1.0f, 1.0f,		0.0f, 0.0f, 1.0f,	s,-s, s,	1.0f, 0.0f,		0.0f, 0.0f, 1.0f,	-s,-s, s,	0.0f, 0.0f,		0.0f, 0.0f, 1.0f , // front
					 s, s,-s,	0.0f, 1.0f,		0.0f, 0.0f,-1.0f,	-s, s,-s,	1.0f, 1.0f,		0.0f, 0.0f,-1.0f,	-s,-s,-s,	1.0f, 0.0f,		0.0f, 0.0f,-1.0f,	s,-s,-s,	0.0f, 0.0f,		0.0f, 0.0f,-1.0f , // back
					 -s, s,-s,	0.0f, 1.0f,		0.0f, 1.0f, 0.0f,	s, s,-s,	1.0f, 1.0f,		0.0f, 1.0f, 0.0f,	s, s, s,	1.0f, 0.0f,		0.0f, 1.0f, 0.0f,	-s, s, s,	0.0f, 0.0f,		0.0f, 1.0f, 0.0f , // top
					 s,-s,-s,	0.0f, 1.0f,		0.0f,-1.0f, 0.0f,	-s,-s,-s,	1.0f, 1.0f,		0.0f,-1.0f, 0.0f,	-s,-s, s,	1.0f, 0.0f,		0.0f,-1.0f, 0.0f,	s,-s, s,	0.0f, 0.0f,		0.0f,-1.0f, 0.0f , // bottom
					 -s, s,-s,	0.0f, 1.0f,		-1.0f, 0.0f, 0.0f,	-s, s, s,	1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,	-s,-s, s,	1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,	-s,-s,-s,	0.0f, 0.0f,		-1.0f, 0.0f, 0.0f , // left
					 s, s, s,	0.0f, 1.0f,		1.0f, 0.0f, 0.0f ,	s, s,-s,	1.0f, 1.0f,		1.0f, 0.0f, 0.0f,	s,-s,-s,	1.0f, 0.0f,		1.0f, 0.0f, 0.0f,	s,-s, s,	0.0f, 0.0f,		1.0f, 0.0f, 0.0f   // right

				};
				G_OBJECT_FILE_ARR.push_back(_PTN);

			}
		};
		static Temp TEMP;

		//==============================================================
		//==============================================================

		void Camera1::create(const CAMERA_CREATE_INFO1 *createInfo) {

			float _aspect = (float)createInfo->m_Width / (float)createInfo->m_Height;

			m_Projection = Perspective(createInfo->m_FOV, 800.0f / 600.0f, createInfo->m_ZNear, createInfo->m_ZFar);
			m_View = Translation(createInfo->m_Position);

			m_ViewProjection = m_Projection * m_View;
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		void CScene::get(ScriptWriter scriptWriter, Scene* scene) {

			auto _new = std::make_shared<CScene>();

			_new->m_ScriptWriter = scriptWriter;

			scriptWriter->reg(_new);

			*scene = _new;

		}

		//==============================================================
		//==============================================================

		void CScene::create(Scene scene, SceneObject *sceneObject, const SCENE_OBJECT_CREATE_INFO *createInfo) {

			// новый
			auto _new = std::make_shared<CSceneObject>(scene);

			// регистрируем
			scene->m_SceneObjects.push_back(_new);

			_new->create(createInfo);

			// сохраняем
			*sceneObject = _new;
		}

		//==============================================================
		//==============================================================

		CScene::CScene() {


		}


		//==============================================================
		//==============================================================

		void CScene::create(const SCENE_CREATE_INFO *createInfo) {

			// ~~~~~~~~~~~~~~~~
			// камера
			// ~~~~~~~~~~~~~~~~

			CAMERA_CREATE_INFO1 _cameraCI = {};

			_cameraCI.m_FOV = 45;
			_cameraCI.m_Width = 800;
			_cameraCI.m_Height = 600;
			_cameraCI.m_ZNear = 0.1f;
			_cameraCI.m_ZFar = 512.0f;
			//_cameraCI.m_Position = vec3(0.0f, 0.0f, -10.0f);

			Camera1 m_Camera;
			m_Camera.create(&_cameraCI);

		}

		//==============================================================
		//==============================================================

		void CScene::reg(Script script) {

			// проверяем наличие в списке
			for (size_t ctScripts = 0; ctScripts < m_Scripts.size(); ++ctScripts) {

				auto itScript = m_Scripts[ctScripts];

				// если есть - уходим
				if (itScript == script) return;

			}

			// если нет - добавляем
			m_Scripts.push_back(script);

		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		void CScene::reg(SceneObject sceneObject) {

			// проверяем наличие в списке
			for (size_t ctSceneObject = 0; ctSceneObject < m_SceneObjects.size(); ++ctSceneObject) {

				auto itSceneObject = m_SceneObjects[ctSceneObject];

				// если есть - уходим
				if (itSceneObject == sceneObject) return;

			}

			// если нет - добавляем
			m_SceneObjects.push_back(sceneObject);
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		void CScene::regCamera(Camera camera) {

			m_Cameras.push_back(camera);

		}

		//==============================================================
		//==============================================================
		void CScene::create(SCENE_CREATE_INFO *createInfo) {

			m_ScriptWriter = createInfo->m_ScriptWriter;
			
			m_Context = createInfo->m_Context;
			m_Content = createInfo->m_Content;
			m_Procedural = createInfo->m_Procedural;
		}

		//==============================================================
		//==============================================================
		
		const uint32_t G_ROW_COUNT = 10;
		const uint32_t G_COL_COUNT = 3;

		struct A {

			void B(const FE::INPUT::MOUSE_SIGNAL_MOVE *){
			
				std::cout << "struct A :: B/n";
			}
			void B(float) {}
		};
		void CScene::load(void) {

			

			// ~~~~~~~~~~~~~~~~
			// описываем и создаём камеру
			// ~~~~~~~~~~~~~~~~

			CAMERA_CREATE_INFO _cameraCI = {};

			_cameraCI.m_Position = vec3(0.0f, 0.0f, 50.0f);
			_cameraCI.m_Target = vec3(0.0f, 0.0f, 0.0f);
			_cameraCI.m_Up = vec3(0.0f, 1.0f, 0.0f);

			m_Camera = new CCamera();

			m_Camera->create(&_cameraCI);

			m_ScriptWriter->getKeyboard()->connectKeymap<CCamera, const FE::INPUT::KEYBOARD_SIGNAL_KEYMAP *>(m_Camera, &FE::SCENE::CCamera::update);
			//m_ScriptWriter->getMouse()->m_S_Move.connect_member(m_Camera, &FE::SCENE::CCamera::update);
			//m_ScriptWriter->getMouse()->connectMove(this, &CScene::load);
			m_ScriptWriter->getMouse()->connectMove<CCamera, const FE::INPUT::MOUSE_SIGNAL_MOVE *>(m_Camera, &FE::SCENE::CCamera::update);
			//A a;
			//m_ScriptWriter->getMouse()->connectMove<A, const FE::INPUT::MOUSE_SIGNAL_MOVE *>(&a, &A::B);

			// ~~~~~~~~~~~~~~~~
			// описываем камеру
			// ~~~~~~~~~~~~~~~~

			FE::RENDERER::MESH_CREATE_INFO _meshCI = {};

			FE::RENDERER::Mesh _newMesh;

			//FE::RENDERER::OPERATION::createMesh(&_meshCI, &_newMesh);

			FE::CONTENT::CContentLoader _testLoader;
			//_testLoader.loadOBJ("D:/Laboratory/FUNEngine/Data//Models/sponza.obj");
			//_testLoader.loadDAE(m_Renderer, "D:/Laboratory/FUNEngine/Data//Models/sponza.dae");

			// ~~~~~~~~~~~~~~~~
			// текстуры
			// ~~~~~~~~~~~~~~~~

			std::vector<std::string> _nameTexture = {
				"D:/Laboratory/FUNRender/Data/Texture/girl_0.tga",
				"D:/Laboratory/FUNRender/Data/Texture/girl_1.tga",
				"D:/Laboratory/FUNRender/Data/Texture/girl_2.tga",
				"D:/Laboratory/FUNRender/Data/Texture/girl_3.tga",
				"D:/Laboratory/FUNRender/Data/Texture/girl_4.tga",
				"D:/Laboratory/FUNRender/Data/Texture/girl_5.tga",
				"D:/Laboratory/FUNRender/Data/Texture/girl_6.tga",
				"D:/Laboratory/FUNRender/Data/Texture/girl_7.tga",
				"D:/Laboratory/FUNRender/Data/Texture/girl_8.tga",
				"D:/Laboratory/FUNRender/Data/Texture/girl_9.tga",
				"D:/Laboratory/FUNRender/Data/Texture/girl_10.tga"
			};

			size_t		_rgbSize = 0;
			size_t		_rgbaSize = 0;
			uint32_t	_width = 0;
			uint32_t	_height = 0;

			for (const auto &itName : _nameTexture) {

				std::ifstream _stream(itName, std::ios::in | std::ios::binary);

				TGAHeader _tgaHeader;

				// читаем заголовок tga файла
				_stream.read((char*)(&_tgaHeader), sizeof(TGAHeader));

				// размер
				_rgbSize += _tgaHeader._width_ * _tgaHeader._height_ * 3;
				_rgbaSize += _tgaHeader._width_ * _tgaHeader._height_ * 4;

			}

			char *_rgbData = new char[_rgbSize];
			char *_rgbaData = new char[_rgbaSize];
			uint32_t _rgbOffset = 0;
			uint32_t _rgbaOffset = 0;

			for (const auto &itName : _nameTexture) {

				std::ifstream _stream(itName, std::ios::in | std::ios::binary);

				TGAHeader _tgaHeader;

				// читаем заголовок tga файла
				_stream.read((char*)(&_tgaHeader), sizeof(TGAHeader));

				// размер
				_rgbSize = _tgaHeader._width_ * _tgaHeader._height_ * 3;
				_rgbaSize = _tgaHeader._width_ * _tgaHeader._height_ * 4;

				// читаем
				_stream.read(&_rgbData[_rgbOffset], _rgbSize);

				// форматируем данные (данный код был спизжен с https://github.com/sergeyreznik/et-engine)
				for (size_t i = 0, k = 0; i < _rgbSize; i += 3, k += 4) {

					_rgbData[_rgbOffset + i] ^= _rgbData[_rgbOffset + i + 2];
					_rgbData[_rgbOffset + i + 2] ^= _rgbData[_rgbOffset + i];
					_rgbData[_rgbOffset + i] ^= _rgbData[_rgbOffset + i + 2];

					_rgbaData[_rgbaOffset + k + 0] = _rgbData[_rgbOffset + i + 0];
					_rgbaData[_rgbaOffset + k + 1] = _rgbData[_rgbOffset + i + 1];
					_rgbaData[_rgbaOffset + k + 2] = _rgbData[_rgbOffset + i + 2];
					_rgbaData[_rgbaOffset + k + 3] = 0;
				}

				_rgbOffset += (uint32_t)_rgbSize;
				_rgbaOffset += (uint32_t)_rgbaSize;
			}

			// ~~~~~~~~~~~~~~~~
			// ~~~~~~~~~~~~~~~~

			FE::CRI::CRI_IMAGE_BUFFER_CREATE_INFO _textureCI = {};
			//_textureCI.m_Context = m_Context;
			_textureCI.m_Width = 1024;
			_textureCI.m_Height = 1024;
			_textureCI.m_Format = COMMON::FORMAT::TEXTURE::R8G8B8A8_UINT;
			//_textureCI.m_Props = FE::CRI::CRI_IMAGE_BUFFER_CREATE_INFO::PROPS::_2D | FE::CRI::CRI_IMAGE_BUFFER_CREATE_INFO::PROPS::COLOR | FE::CRI::CRI_IMAGE_BUFFER_CREATE_INFO::PROPS::SAMPLED;

			FE::CRI::CRI_IMAGE_BUFFER_CREATE_INFO_ARR _textureCIs = { _textureCI };

			FE::CRI::CRIImageBufferArr _textures;

			//FE::CRI::OPERATION::createImageBuffers(m_Context, &_textures, &_textureCIs);

			// ~~~~~~~~~~~~~~~~
			// геометрия шара
			// ~~~~~~~~~~~~~~~~

			std::vector<uint32_t> _cubeIndices = {
				0, 3, 1,  1, 3, 2, // front
				4, 7, 5,  5, 7, 6, // back
				8,11, 9,  9,11,10, // top
				12,15,13, 13,15,14, // bottom
				16,19,17, 17,19,18, // left
				20,23,21, 21,23,22  // right
			};

			float s = 1.0f; // половина размера куба
			std::vector<float> _cubeVertices = {
				-s, s, s,	1.0f, 1.0f, 1.0f,	0.0f, 0.0f, 1.0f,	s, s, s,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 1.0f,	s,-s, s,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 1.0f,	-s,-s, s,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 1.0f, // front
				s, s,-s,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,-1.0f,	-s, s,-s,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,-1.0f,	-s,-s,-s,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,-1.0f,	s,-s,-s,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,-1.0f, // back
				-s, s,-s,	0.5f, 0.5f, 0.5f,	0.0f, 1.0f, 0.0f,	s, s,-s,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,	s, s, s,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,	-s, s, s,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f, // top
				s,-s,-s,	0.0f, 0.0f, 0.0f,	0.0f,-1.0f, 0.0f,	-s,-s,-s,	0.0f, 0.0f, 0.0f,	0.0f,-1.0f, 0.0f,	-s,-s, s,	0.0f, 0.0f, 0.0f,	0.0f,-1.0f, 0.0f,	s,-s, s,	0.0f, 0.0f, 0.0f,	0.0f,-1.0f, 0.0f, // bottom
				-s, s,-s,	0.0f, 0.0f, 0.0f,	-1.0f, 0.0f, 0.0f,	-s, s, s,	0.0f, 0.0f, 0.0f,	-1.0f, 0.0f, 0.0f,	-s,-s, s,	0.0f, 0.0f, 0.0f,	-1.0f, 0.0f, 0.0f,	-s,-s,-s,	0.0f, 0.0f, 0.0f,	-1.0f, 0.0f, 0.0f, // left
				s, s, s,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,	s, s,-s,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,	s,-s,-s,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,	s,-s, s,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f  // right
			};

			// ~~~~~~~~~~~~~~~~
			// ~~~~~~~~~~~~~~~~



			//RENDERER::MESH_CREATE_INFO _sphereMeshCI = {};

			//RENDERER::Mesh _sphereMesh;

			//m_Renderer->createMesh(&_sphereMeshCI, &_sphereMesh);


			// ~~~~~~~~~~~~~~~~
			//
			// ~~~~~~~~~~~~~~~~



		
			
		}

		//==============================================================
		//==============================================================

		void CScene::update(SceneArr *scenes) {

			

			static bool init = false;
			size_t _maxScene = scenes->size();
			for (size_t ctScene = 0; ctScene < _maxScene; ++ctScene) {

				auto &_itScene = (*scenes)[ctScene];

				if (!init) {
					
					//_itScene->load();

					init = true;

					//FE::RENDERER::OPERATION::addObjects(&_itScene->m_Objects);
				}

				

			}
			
			

			//}
			//std::cout << "thread start\n";
			//using namespace std::chrono_literals;
			//std::this_thread::sleep_for(0.5s);
			//std::cout << "thread end\n";

		}
		void CScene::update() {

			for (auto &itObject : m_SceneObjects) {

				CRI::CRI_DATA_BUFFER_UPDATE_INFO _bufferUI = {};

				mat4 _mat = m_Camera->getView();
				_mat = transpose(_mat);
				_bufferUI.m_Data = &_mat;
				_bufferUI.m_Offset = sizeof(mat4);
				//_bufferUI.m_Offset = 0;
				_bufferUI.m_Size = sizeof(mat4);

				itObject->m_Uniforms->update(&_bufferUI);

				_mat = m_Camera->getProjection();
				_mat = transpose(_mat);

				_bufferUI.m_Data = &_mat;
				_bufferUI.m_Offset = sizeof(mat4) * 2;
				//_bufferUI.m_Offset = 0;
				_bufferUI.m_Size = sizeof(mat4);

				itObject->m_Uniforms->update(&_bufferUI);
			}

			static int a = 0;

			if (a == 0) {

				m_ScriptWriter->getRenderer()->addObjects(&m_SceneObjects);

				a = 1;
			}
		}
		//==============================================================
		//==============================================================

	}

}