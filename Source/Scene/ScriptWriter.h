#ifndef SCRIPTWRITER__H
#define SCRIPTWRITER__H
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
#include "..\Core.h"		// временно
#include "..\Input\FInput.h"
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////

namespace FE {

	namespace SCENE {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class e_scriptwriter_common : public CORE::e_core_common {};



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct SCRIPTWRITER_CREATE_INFO {

			CORE::Core					m_Core;
			CRI::CRIContext				m_Context = nullptr;
			FE::RENDERER::Renderer		m_Renderer;
			FE::PROCEDURAL::Procedural	m_Procedural;


		}; // struct SCRIPTWRITER_CREATE_INFO



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CScriptWriter {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Получить объект.

			\param[out] scriptWriter Полученный объект.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			static void get(ScriptWriter *scriptWriter);

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Конструктор.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			CScriptWriter();

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Создание.

			\param createInfo Информация для создания.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void create(const SCRIPTWRITER_CREATE_INFO *createInfo);

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Зарегистрировать объект.

			\param[in] scene Объект для регистрации.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void reg(Scene scene);

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Получить Procedural.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline PROCEDURAL::Procedural getProcedural(void) const;


			RENDERER::Renderer getRenderer(void) { return m_Renderer; }
			void update();

			INPUT::Keyboard getKeyboard(void) { return m_Keyboard; }
			INPUT::Mouse getMouse(void) { return m_Mouse; }
		// inline
		public:

		// данные
		private:

			RENDERER::Renderer			m_Renderer;
			INPUT::Keyboard				m_Keyboard;
			INPUT::Mouse				m_Mouse;
			SceneArr					m_Scenes;
			PROCEDURAL::Procedural		m_Procedural;

		}; // class CScriptWriter

	} // namespace SCENE

} // namespace FE

#include "ScriptWriter.hpp"

#endif // SCRIPTWRITER__H