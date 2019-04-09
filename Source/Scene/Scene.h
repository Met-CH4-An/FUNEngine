#ifndef SCENE__H
#define SCENE__H
////////////////////////////////////////////////////////////////
// секция компиляция файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция родительского класса
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция форвард-декларации
////////////////////////////////////////////////////////////////
#include "FScene.h"
#include "..\Procedural\FProcedural.h"
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////
#include "..\main.h"
#include "..\Content\Content.h"
#include "..\Procedural\Procedural.h"
//#include "..\..\Renderer.h"
//struct CRenderer;
namespace FE {

	namespace SCENE {

		

		////////////////////////////////////////////////////////////////
		/// \brief Описание заголовка для tga формата
		////////////////////////////////////////////////////////////////
		struct TGAHeader {

			uint8_t		_idLeight_ = 0;		///< Длина текстовой информации после первого 18 - ти байтового блока. Может быть использована для описания файла
			uint8_t		_colorMap_ = 0;		///< Идентификатор наличия цветовой карты, здесь не описан - устарел
			uint8_t		_dataType_ = 0;		///< Тип данных - запакованный или нет
			uint8_t		_colorMapInfo_[5];	///< Информация о цветовой карте - нужно пропустить эти 5 байт
			uint16_t	_x_Origin_ = 0;		///< Начало изображения по оси X
			uint16_t	_y_Origin_ = 0;		///< Начало изображения по оси Y
			uint16_t	_width_ = 0;   		///< Ширина изображения
			uint16_t	_height_ = 0;   	///< Высота изображения
			uint8_t		_bitPerPel_ = 0; 	///< Кол - во бит на пиксель - здесь только 24 или 32
			uint8_t		_description_ = 0;	///< Описание - пропускайте

											//size = IdLeight 	unknown     	unknown   	Пропустите IdLeight байт и все(IdLeight - самое первое поле)

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
		/*!	\brief Информация для создания Scene.
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
			/*!	\brief Проверка корректности описания.

			\return true - если описание корректно. false - если описание не коррректно.
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
			/*!	\brief Создать объект.

			\param[in] scene Владеет объектом.
			\param[out] sceneObject Полученный объект.
			\param[in] createInfo Информация для создания.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			static void create(Scene scene, SceneObject *sceneObject, const SCENE_OBJECT_CREATE_INFO *createInfo);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Получить объект.

			\param[in] scriptWriter ScriptWriter, который владеет объектом.
			\param[out] scene Полученный объект.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			static void get(ScriptWriter scriptWriter, Scene* scene);

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Конструктор.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			CScene();

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Создать объект.

			\param[in] createInfo Информация для создания.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void create(const SCENE_CREATE_INFO *createInfo);

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Зарегистрировать объект.

			\param[in] script Объект для регистрации.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void reg(Script script);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Зарегистрировать объект.

			\param[in] sceneObject Объект для регистрации.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void reg(SceneObject sceneObject);

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Получить ScriptWriter.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline ScriptWriter getScriptWriter(void) const;

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Получить Camera.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline Camera getCamera(void) const;

			inline CRI::CRIContext getContext(void) { return m_Context; }


			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Загрузить множество Scene.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void load(void);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Обновить множество Scene.

			\param scenes Сцены для обновления.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			static void update(SceneArr *scenes);

			void update();

			void create(SCENE_CREATE_INFO *createInfo);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Зарегистрировать камеру.

			\param camera Камера для регистрации.
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