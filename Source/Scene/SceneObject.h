#ifndef SCENE_OBJECT__H
#define SCENE_OBJECT__H
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
#include "../CommonRenderInterface/CommonRenderInterface.h"
#include "../Renderer/pch.renderer.h"
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////

namespace FE {

	namespace SCENE {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Информация для создания SceneObject.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct SCENE_OBJECT_CREATE_INFO {
		}; // struct SCENE_OBJECT_CREATE_INFO



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Object.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CSceneObject  {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Конструктор.

			// \param[in] scene Владеет объектом.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			CSceneObject(Scene scene);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Создать объект.

			\param[in] createInfo Информация для создания.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void create(const SCENE_OBJECT_CREATE_INFO *createInfo);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Установить Mesh.

			\param[in] mesh Меш.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void setMesh(const RENDERER::Mesh mesh);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Установить Effect.

			\param[in] Effect Материал.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void setEffect(const RENDERER::Effect Effect);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Получить DrawPackage.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			const RENDERER::DrawPackage getDrawPackage(void) const;

		public:

			inline void setUniforms(FE::CRI::CRIDataBuffer buffer) { m_Uniforms = buffer; }

			inline FE::CRI::CRIDataBuffer getUniforms(void) { return m_Uniforms; }

		public:

			Scene										m_Scene;
			FE::CRI::CRIDataBuffer						m_Uniforms;
			FE::RENDERER::DrawPackage					m_DrawPackage;

		}; // struct CSceneObject

	} // namespace SCENE

} // namespace FE

#endif // SCENE_OBJECT__H
