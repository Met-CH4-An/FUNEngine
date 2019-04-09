#ifndef CORE__H
#define CORE__H
////////////////////////////////////////////////////////////////
// секция компиляция файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция родительского класса
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция форвард-декларации
////////////////////////////////////////////////////////////////
#include "Scene/FScene.h"
#include "CommonRenderInterface/CommonRenderInterface.h"
#include "Renderer/pch.renderer.h"
#include "Input/FInput.h"
#include "Content/FContent.h"
#include "Procedural/FProcedural.h"
#include "ThreadPool.h"
#include <Windows.h>
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////
class CWindow;
using Window = CWindow*;

namespace FE {

	namespace CORE {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class e_core_common : public std::exception {};



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Ядро движка.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CCore {

		public:
			
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Создание.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void create(HWND hwnd = NULL);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Обновление.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void update(void);

			void execute(void);

			INPUT::Keyboard getKeyboard(void) const {	return m_Keyboard;	}
			INPUT::Mouse getMouse(void) const { return m_Mouse; }
			CONTENT::Content getContent() { return m_Content; }

		// данные
		private:

			Window							m_Window;
			INPUT::Keyboard					m_Keyboard;
			INPUT::Mouse					m_Mouse;
			FE::CRI::CRIContext				m_Context;
			FE::RENDERER::Renderer			m_Renderrer;
			FE::SCENE::ScriptWriter			m_ScriptWriter;
			FE::CONTENT::Content			m_Content;
			FE::PROCEDURAL::Procedural		m_Procedural;
			ThreadManager*					m_ThreadManager;

		}; // class CCore

		using Core = CCore*;		

	} // namespace CORE

} // namespace FE

#include "Core.hpp"

#endif // CORE__H