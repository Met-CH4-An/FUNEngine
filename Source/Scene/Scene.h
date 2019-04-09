#ifndef SCENE__H
#define SCENE__H
////////////////////////////////////////////////////////////////
// ������ ���������� �����
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ ������������� ������
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ �������-����������
////////////////////////////////////////////////////////////////
#include "FScene.h"
#include "..\Procedural\FProcedural.h"
////////////////////////////////////////////////////////////////
// ������ ��� ����������
////////////////////////////////////////////////////////////////
#include "..\main.h"
#include "..\Content\Content.h"
#include "..\Procedural\Procedural.h"
//#include "..\..\Renderer.h"
//struct CRenderer;
namespace FE {

	namespace SCENE {

		

		////////////////////////////////////////////////////////////////
		/// \brief �������� ��������� ��� tga �������
		////////////////////////////////////////////////////////////////
		struct TGAHeader {

			uint8_t		_idLeight_ = 0;		///< ����� ��������� ���������� ����� ������� 18 - �� ��������� �����. ����� ���� ������������ ��� �������� �����
			uint8_t		_colorMap_ = 0;		///< ������������� ������� �������� �����, ����� �� ������ - �������
			uint8_t		_dataType_ = 0;		///< ��� ������ - ������������ ��� ���
			uint8_t		_colorMapInfo_[5];	///< ���������� � �������� ����� - ����� ���������� ��� 5 ����
			uint16_t	_x_Origin_ = 0;		///< ������ ����������� �� ��� X
			uint16_t	_y_Origin_ = 0;		///< ������ ����������� �� ��� Y
			uint16_t	_width_ = 0;   		///< ������ �����������
			uint16_t	_height_ = 0;   	///< ������ �����������
			uint8_t		_bitPerPel_ = 0; 	///< ��� - �� ��� �� ������� - ����� ������ 24 ��� 32
			uint8_t		_description_ = 0;	///< �������� - �����������

											//size = IdLeight 	unknown     	unknown   	���������� IdLeight ���� � ���(IdLeight - ����� ������ ����)

			TGAHeader() {

				_colorMapInfo_[0] = 0;
				_colorMapInfo_[1] = 0;
				_colorMapInfo_[2] = 0;
				_colorMapInfo_[3] = 0;
				_colorMapInfo_[4] = 0;

			}
		};

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct Geometry {

			FE::CRI::CRIDataBuffer						m_Vertex;
			FE::CRI::CRIDataBuffer						m_Index;
			//FE::CRI::CRI_PIPELINE_VERTEX_LAYOUT_ARR		m_VertexLayout;
		};

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct Effect {

			FE::CRI::CRIImageBuffer		m_ColorMap;
			bool							m_ColorAttribute;

			FE::CRI::CRIImageBuffer		m_NormalMap;
			bool							m_NormalAttribute;
		};

		struct Technique {

			std::string		m_VertexShader;
			std::string		m_FragmentShader;
		};
		

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CAMERA_CREATE_INFO1 {

			uint32_t		m_Width;
			uint32_t		m_Height;
			float			m_FOV;
			float			m_ZNear;
			float			m_ZFar;
			vec3			m_Position;
		};

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		struct Camera1 {

			void create(const CAMERA_CREATE_INFO1 *createInfo);
			inline const mat4& getViewProjectionMatrix(void) const { return m_ViewProjection; }

			mat4 m_Projection;
			mat4 m_View;
			mat4 m_ViewProjection;

		};

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief ���������� ��� �������� Scene.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct SCENE_CREATE_INFO {

			ScriptWriter		m_ScriptWriter;
			Scene				m_Scene = nullptr;
			CRI::CRIContext		m_Context = nullptr;
			FE::RENDERER::Renderer						m_Renderer;
			CONTENT::Content		m_Content;
			PROCEDURAL::Procedural m_Procedural;

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �������� ������������ ��������.

			\return true - ���� �������� ���������. false - ���� �������� �� ����������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline bool isValid(void) const {

				if (m_Context == nullptr) return false;

				return true;

			}

		}; // struct SCENE_CREATE_INFO

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CScene {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief ������� ������.

			\param[in] scene ������� ��������.
			\param[out] sceneObject ���������� ������.
			\param[in] createInfo ���������� ��� ��������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			static void create(Scene scene, SceneObject *sceneObject, const SCENE_OBJECT_CREATE_INFO *createInfo);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �������� ������.

			\param[in] scriptWriter ScriptWriter, ������� ������� ��������.
			\param[out] scene ���������� ������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			static void get(ScriptWriter scriptWriter, Scene* scene);

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �����������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			CScene();

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief ������� ������.

			\param[in] createInfo ���������� ��� ��������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void create(const SCENE_CREATE_INFO *createInfo);

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief ���������������� ������.

			\param[in] script ������ ��� �����������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void reg(Script script);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief ���������������� ������.

			\param[in] sceneObject ������ ��� �����������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void reg(SceneObject sceneObject);

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �������� ScriptWriter.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline ScriptWriter getScriptWriter(void) const;

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �������� Camera.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline Camera getCamera(void) const;

			inline CRI::CRIContext getContext(void) { return m_Context; }


			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief ��������� ��������� Scene.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void load(void);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �������� ��������� Scene.

			\param scenes ����� ��� ����������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			static void update(SceneArr *scenes);

			void update();

			void create(SCENE_CREATE_INFO *createInfo);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief ���������������� ������.

			\param camera ������ ��� �����������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void regCamera(Camera camera);

		private:

			ScriptWriter				m_ScriptWriter;
			FE::CRI::CRIContext			m_Context;

			Camera						m_Camera;
			ScriptArr					m_Scripts;
			SceneObjectArr				m_SceneObjects;
			CameraArr					m_Cameras;
			CONTENT::Content			m_Content;
			PROCEDURAL::Procedural		m_Procedural;

			//void update(void);
		};

	} // namespace SCENE

} // namespace FE

#include "Scene.hpp"

#endif // SCENE__H