////////////////////////////////////////////////////////////////
// секци€ PCH
////////////////////////////////////////////////////////////////
#include "PCH.h"
////////////////////////////////////////////////////////////////
// секци€ заголовочного файла
////////////////////////////////////////////////////////////////
#include "Script.h"
////////////////////////////////////////////////////////////////
// секци€ компил€ци€ файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секци€ форвард-декларации
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секци€ дл€ исключений
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секци€ дл€ остального
////////////////////////////////////////////////////////////////
#include "ScriptWriter.h"
#include "Scene.h"
#include "Camera.h"
#include "SceneObject.h"
#include "../Common/Blob.h"
#include "../CommonRenderInterface/criContext.h"
#include "../CommonRenderInterface/criDataBuffer.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/GeometryInfo.h"
#include "../Renderer/Mesh.h"
#include "../Renderer/Effect.h"
#include "../Particles/Particles.h"


namespace FE {

	namespace SCENE {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		void CScript::createSphere(PROCEDURAL::Procedural procedural, RENDERER::Renderer renderer) {

			// ~~~~~~~~~~~~~~~~
			// генерируем точки сферы
			// ~~~~~~~~~~~~~~~~

			// описываем атрибуты геометрии сферы
			PROCEDURAL::PROCEDURAL_GEOMETRY_ATTRIBUTE_ARR _sphereGeometryAttribute = {
				{ PROCEDURAL::PROCEDURAL_GEOMETRY_ATTRIBUTE::SEMANTIC::POSITION, 3},
				{ PROCEDURAL::PROCEDURAL_GEOMETRY_ATTRIBUTE::SEMANTIC::COLOR, 3 },
				{ PROCEDURAL::PROCEDURAL_GEOMETRY_ATTRIBUTE::SEMANTIC::NORMAL, 3 },
			};

			// описываем геометрию сферы
			PROCEDURAL::PROCEDURAL_GEOMETRY _proceduralSphereGeometry;

			_proceduralSphereGeometry.m_Placement = PROCEDURAL::PROCEDURAL_GEOMETRY::PLACEMENT::AOS;
			_proceduralSphereGeometry.m_Attributes = _sphereGeometryAttribute;

			// описываем сферу
			PROCEDURAL::PROCEDURE_SPHERE_CREATE_INFO _proceduralSphereGeometryCI = {};

			_proceduralSphereGeometryCI.m_Renderer = m_Scene->getScriptWriter()->getRenderer();
			_proceduralSphereGeometryCI.m_Geometry = _proceduralSphereGeometry;
			_proceduralSphereGeometryCI.m_Meridians = 20;
			_proceduralSphereGeometryCI.m_Parallels = 20;
			_proceduralSphereGeometryCI.m_PatchSize = 3;
			_proceduralSphereGeometryCI.m_Radius = 2.0f;

			// создаЄм сферу
			COMMON::Blob _vertices;
			COMMON::Blob _indices;
			m_Scene->getScriptWriter()->getProcedural()->buildSphere(&_proceduralSphereGeometryCI, nullptr, &_vertices, &_indices, nullptr);

			// ~~~~~~~~~~~~~~~~
			// создаЄм меш
			// ~~~~~~~~~~~~~~~~

			// описываем атрибуты
			RENDERER::MESH_ATTRIBUTE_BINDING _meshAttributePosition = {};
			_meshAttributePosition.m_Name = RENDERER::MESH_ATTRIBUTE_BINDING::NAME::POSITION;
			_meshAttributePosition.m_Capacity = 3;
			_meshAttributePosition.m_Format = COMMON::FORMAT::DATA::_32_32_32_SFLOAT;

			RENDERER::MESH_ATTRIBUTE_BINDING  _meshAttributeColor = {};
			_meshAttributeColor.m_Name = RENDERER::MESH_ATTRIBUTE_BINDING::NAME::COLOR;
			_meshAttributeColor.m_Capacity = 3;
			_meshAttributeColor.m_Format = COMMON::FORMAT::DATA::_32_32_32_SFLOAT;

			RENDERER::MESH_ATTRIBUTE_BINDING  _meshAttributeNormal = {};
			_meshAttributeNormal.m_Name = RENDERER::MESH_ATTRIBUTE_BINDING::NAME::NORMAL;
			_meshAttributeNormal.m_Capacity = 3;
			_meshAttributeNormal.m_Format = COMMON::FORMAT::DATA::_32_32_32_SFLOAT;

			// описываем шаблон атрибутов
			RENDERER::MESH_ATTRIBUTE_LAYOUT _meshAttributeLayout = {};
			_meshAttributeLayout.push_back(_meshAttributePosition);
			_meshAttributeLayout.push_back(_meshAttributeColor);
			_meshAttributeLayout.push_back(_meshAttributeNormal);

			RENDERER::MESH_ATTRIBUTE_DECLARATION _meshAttributeDeclaration = {};
			_meshAttributeDeclaration.push_back(_meshAttributeLayout);		

			// опысваем
			RENDERER::MESH_CREATE_INFO _sphereMeshCI = {};
			_sphereMeshCI.m_AttributeDeclaration = _meshAttributeDeclaration;

			// создаЄм
			RENDERER::Mesh _sphereMesh;
			RENDERER::CRenderer::create(renderer, &_sphereMesh, &_sphereMeshCI);

			_sphereMesh->addVertices(_vertices);
			_sphereMesh->addIndices(_indices);

			// ~~~~~~~~~~~~~~~~
			// эффект
			// ~~~~~~~~~~~~~~~~

			RENDERER::VERTEX_ATTRIBUTE_BINDING _vertexBinding0 = {};
			_vertexBinding0.m_Format = COMMON::FORMAT::DATA::_32_32_32_SFLOAT;

			RENDERER::VERTEX_ATTRIBUTE_BINDING _vertexBinding1 = {};
			_vertexBinding1.m_Format = COMMON::FORMAT::DATA::_32_32_32_SFLOAT;

			RENDERER::VERTEX_ATTRIBUTE_BINDING _vertexBinding2 = {};
			_vertexBinding2.m_Format = COMMON::FORMAT::DATA::_32_32_32_SFLOAT;

			RENDERER::VERTEX_ATTRIBUTE_LAYOUT _vertexLayout = {};
			_vertexLayout.push_back(_vertexBinding0);
			_vertexLayout.push_back(_vertexBinding1);
			_vertexLayout.push_back(_vertexBinding2);

			RENDERER::EFFECT_CREATE_INFO _effectCI = {};

			_effectCI.m_VertexAttributeLayouts.push_back(_vertexLayout);

			// создаЄм
			//RENDERER::Effect _effect;
			//renderer->createEffect(&_effectCI, &_effect);

			// ~~~~~~~~~~~~~~~~
			// материал
			// ~~~~~~~~~~~~~~~~

			RENDERER::EFFECT_CREATE_INFO _EffectCI = {};

			//_EffectCI.m_Lighting = RENDERER::EFFECT_CREATE_INFO::LIGHTING::LAMBERT;

			RENDERER::Effect _sphereEffect;
			//RENDERER::CRenderer::create(renderer, &_sphereEffect, &_EffectCI);


			// ~~~~~~~~~~~~~~~~
			// 
			// ~~~~~~~~~~~~~~~~

			// стартовые параметры юниформ
			float	_offsetX = -20.0f;
			float	_offsetY = -15.0f;

			const uint32_t G_ROW_COUNT = 10;
			const uint32_t G_COL_COUNT = 3;

			// перебираем объект по лини€ми
			for (uint32_t ctY = 0; ctY < G_ROW_COUNT; ++ctY) {

				// по столбцам
				for (uint32_t ctX = 0; ctX < G_COL_COUNT; ++ctX) {

					mat4 _uniformData[4];

					mat4 &_model = _uniformData[0];
					_model = Translation(vec3(_offsetX, _offsetY, 0.0f));
					_model = transpose(_model);

					mat4 &_view = _uniformData[1];
					_view = m_Scene->getCamera()->getView();
					_view.m[0] = 1.0f;
					_view.m[10] = 1.0f;
					_view = transpose(_view);

					mat4 &_projection = _uniformData[2];
					_projection = m_Scene->getCamera()->getProjection();
					_projection = transpose(_projection);

					mat4 &_mvp = _uniformData[3];
					_mvp = transpose(_mvp);

					FE::CRI::CRI_DATA_BUFFER_UPDATE_INFO _uniformBufferUI = {};

					_uniformBufferUI.m_Data = &_uniformData[0].m[0];
					_uniformBufferUI.m_Offset = 0;
					_uniformBufferUI.m_Size = sizeof(mat4) * 4;

					FE::CRI::CRI_DATA_BUFFER_CREATE_INFO _uniformBufferCI = {};

					_uniformBufferCI.m_Usage = FE::CRI::CRI_DATA_BUFFER_CREATE_INFO::USAGE::UNIFORM;
					_uniformBufferCI.m_Storage = FE::CRI::CRI_DATA_BUFFER_CREATE_INFO::STORAGE::HOST;
					_uniformBufferCI.m_Size = sizeof(mat4) * 4;
					_uniformBufferCI.m_Update = _uniformBufferUI;

					FE::CRI::CRIDataBuffer _uniformBuffer;
					CRI::CCRIContext::create(m_Scene->getScriptWriter()->getRenderer()->getContext(), &_uniformBuffer, &_uniformBufferCI);

					_offsetY += 6.0f;

					// ~~~~~~~~~~~~~~~~
					// готовим
					// ~~~~~~~~~~~~~~~~

					SCENE_OBJECT_CREATE_INFO _sceneCI = {};

					SceneObject _newObject;
					SCENE::CScene::create(m_Scene, &_newObject, &_sceneCI);

					//_newObject->m_Effect = _Effect;
					_newObject->m_Uniforms = _uniformBuffer;
					//_newObject->m_Vertices = _sphereMesh->getVertices()[0];
					//_newObject->m_Indices = _sphereMesh->getIndices();
					_newObject->setMesh(_sphereMesh);
					_newObject->setEffect(_sphereEffect);


				} // for (uint32_t ctX = 0

				  // 
				_offsetY = -15.0f;
				_offsetX += 4.0f;


			} // for (uint32_t ctY = 0

			

		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		void CScript::createHelixParticles(PROCEDURAL::Procedural procedural, RENDERER::Renderer renderer) {

			// ~~~~~~~~~~~~~~~~
			// генерируем точки цилиндрической винтовой линии
			// ~~~~~~~~~~~~~~~~

			// описываем параметры цилиндрической винтовой линии
			PROCEDURAL::PROCEDURE_HELIX_CREATE_INFO _cylindricalHelixPointsCI = {};
			_cylindricalHelixPointsCI.m_StepXY = 1.0f;
			_cylindricalHelixPointsCI.m_StepZ = 1.0f;
			_cylindricalHelixPointsCI.m_Offset = 1.0f;

			PROCEDURAL::PROCEDURE_OUTPUT _outputPoints = {};

			// генерируем данные цилиндрической винтовой линии
			procedural->buildCylindricalHelix(&_cylindricalHelixPointsCI, &_outputPoints);

			// ~~~~~~~~~~~~~~~~
			// создаЄм меш
			// ~~~~~~~~~~~~~~~~

			// описываем атрибуты
			RENDERER::MESH_ATTRIBUTE_BINDING _meshAttributePosition = {};
			_meshAttributePosition.m_Name = RENDERER::MESH_ATTRIBUTE_BINDING::NAME::POSITION;
			_meshAttributePosition.m_Capacity = 3;
			_meshAttributePosition.m_Format = COMMON::FORMAT::DATA::_32_32_32_SFLOAT;

			RENDERER::MESH_ATTRIBUTE_LAYOUT _meshAttributeLayout = {};
			_meshAttributeLayout.push_back(_meshAttributePosition);

			RENDERER::MESH_ATTRIBUTE_DECLARATION _meshAttributeDeclaration = {};
			_meshAttributeDeclaration.push_back(_meshAttributeLayout);
			
			// опысваем
			RENDERER::MESH_CREATE_INFO _meshCI = {};
			_meshCI.m_AttributeDeclaration = _meshAttributeDeclaration;

			// создаЄм
			RENDERER::Mesh _mesh;
			RENDERER::CRenderer::create(renderer, &_mesh, &_meshCI);

			_mesh->addVertices(_outputPoints.m_Vertices[0]);

			// ~~~~~~~~~~~~~~~~
			// материал
			// ~~~~~~~~~~~~~~~~

			RENDERER::EFFECT_CREATE_INFO _EffectCI = {};

			//_EffectCI.m_Lighting = RENDERER::EFFECT_CREATE_INFO::LIGHTING::NONE;

			RENDERER::Effect _Effect;
			//RENDERER::CRenderer::create(renderer, &_Effect);

		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
		void CScript::get(Scene scene, Script *script) {
			
			auto _new = std::make_shared<CScript>();

			_new->m_Scene = scene;

			scene->reg(_new);

			*script = _new;
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		CScript::CScript() {

			m_Scene = nullptr;
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		void CScript::create(const SCRIPT_CREATE_INFO *createInfo) {

			createSphere(m_Scene->getScriptWriter()->getProcedural(), m_Scene->getScriptWriter()->getRenderer());

			createHelixParticles(m_Scene->getScriptWriter()->getProcedural(), m_Scene->getScriptWriter()->getRenderer());			

		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


	} // namespace SCENE {

} // namespace FE {