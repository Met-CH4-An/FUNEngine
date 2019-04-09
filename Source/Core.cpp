////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "PCH.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "Core.h"
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
#include "CommonRenderInterface\criCoreInfo.h"
#include "CommonRenderInterface\criContext.h"
#include "Renderer/Renderer.h"
#include "Scene\ScriptWriter.h"
#include "Input\Keyboard.h"
#include "Input\Mouse.h"
#include "Content\Content.h"
#include "Procedural/Procedural.h"
#include "Scene/Scene.h"
#include "Scene/Script.h"
#include "main.h"

namespace FE {

	namespace CORE {

		//==============================================================
		//==============================================================

		void CCore::create(HWND hwnd) {

			try {

				HWND _hwnd = 0;

				if (hwnd == NULL) {

					

					m_Window = new CWindow;

					m_Window->create();

					m_Keyboard = new INPUT::CKeyboard();
					m_Keyboard->create();
					m_Window->m_Keyboard.connect_member(m_Keyboard, &FE::INPUT::CKeyboard::connactableKeymap);

					m_Mouse = new INPUT::CMouse();
					m_Mouse->create();
					m_Window->m_S_MouseMove.connect_member(m_Mouse, &FE::INPUT::CMouse::connectableMove);

					_hwnd = m_Window->m_Hwnd;

				}

				// ~~~~~~~~~~~~~~~~
				// подготовка общего рендер интерфейса
				// ~~~~~~~~~~~~~~~~

				//FE::CRI::CRI_CORE_CREATE_INFO _criCI = {};
				//_criCI.m_Flags |= FE::CRI::CRI_CORE_CREATE_FLAGS::DEBUG;

				//FE::CRI::CRICore _core;
				//FE::CRI::OPERATION::createCRICore(&_core, &_criCI);

				// ~~~~~~~~~~~~~~~~
				// ~~~~~~~~~~~~~~~~

				FE::RENDERER::RENDERER_CREATE_INFO _rendererCI = {};
				_rendererCI.m_HWnd = _hwnd;
				_rendererCI.m_Technique = RENDERER::RENDERER_CREATE_INFO::TECHNIQUE::DEFFERED;

				m_Renderrer = new FE::RENDERER::CRenderer(this);
				m_Renderrer->create(&_rendererCI);

				//MessageBoxA(nullptr, "renderer create", "debug", 0);

				// ~~~~~~~~~~~~~~~~
				// ~~~~~~~~~~~~~~~~

				FE::CONTENT::CONTENT_CREATE_INFO _contentCI = {};

				m_Content = new FE::CONTENT::CContent();

				m_Content->create(&_contentCI);

				//m_Content->get("D:\\Laboratory\\FUNEngine\\Data\\Models\\sponza.dae");

				// ~~~~~~~~~~~~~~~~
				// 
				// ~~~~~~~~~~~~~~~~

				m_Procedural = new PROCEDURAL::CProcedural();

				// ~~~~~~~~~~~~~~~~
				// создаём сценариста
				// ~~~~~~~~~~~~~~~~

				FE::SCENE::CScriptWriter::get(&m_ScriptWriter);

				FE::SCENE::SCRIPTWRITER_CREATE_INFO _scriptWriterCI = {};

				_scriptWriterCI.m_Core = this;
				_scriptWriterCI.m_Renderer = m_Renderrer;
				_scriptWriterCI.m_Procedural = m_Procedural;

				m_ScriptWriter->create(&_scriptWriterCI);

				FE::SCENE::Scene _scene;
				FE::SCENE::CScene::get(m_ScriptWriter, &_scene);

				_scene->load();

				FE::SCENE::Script _script;
				FE::SCENE::CScript::get(_scene, &_script);

				_script->create(nullptr);

			}

			catch (std::exception &e){

				return;
			}

			/*auto _beginPeriod = std::chrono::high_resolution_clock::now();
			uint32_t _frame_count = 0;

			int loops = 0;

			while (true) {

				auto _beginFrame = std::chrono::high_resolution_clock::now();

				const int TICKS_PER_SECOND = 25;
				const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
				const int MAX_FRAMESKIP = 5;

				m_Window->update();

				m_Keyboard->update();

				m_Mouse->update();

				m_ScriptWriter->update();

				m_Renderrer->update();
				m_Renderrer->execute();

				using namespace std::chrono_literals;

				auto _endFrame = std::chrono::high_resolution_clock::now();
				auto _deltaFrame = _endFrame - _beginFrame;
				auto _frame_ms = std::chrono::duration <double, std::milli>(_deltaFrame).count();
				++_frame_count;

				auto _endPeriod = std::chrono::high_resolution_clock::now();
				auto _deltaPeriod = _endPeriod - _beginPeriod;
				auto _deltaPeriod_ms = std::chrono::duration <double, std::milli>(_deltaPeriod).count();

				if (_deltaPeriod_ms > 1000.0f) {

					std::cout << "frame ms = " << _frame_ms << "\n";
					std::cout << "fps = " << _frame_count << "\n";

					_beginPeriod = _endPeriod;

					_frame_count = 0;
				}
			}*/

		}

		//==============================================================
		//==============================================================

		void CCore::update(void) {

			auto _beginPeriod = std::chrono::high_resolution_clock::now();
			uint32_t _frame_count = 0;

			int loops = 0;

			auto _beginFrame = std::chrono::high_resolution_clock::now();

			const int TICKS_PER_SECOND = 25;
			const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
			const int MAX_FRAMESKIP = 5;

			m_Window->update();

			m_Keyboard->update();

			m_Mouse->update();

			m_ScriptWriter->update();

			m_Renderrer->update();
			m_Renderrer->execute();

			using namespace std::chrono_literals;

			auto _endFrame = std::chrono::high_resolution_clock::now();
			auto _deltaFrame = _endFrame - _beginFrame;
			auto _frame_ms = std::chrono::duration <double, std::milli>(_deltaFrame).count();
			++_frame_count;

			auto _endPeriod = std::chrono::high_resolution_clock::now();
			auto _deltaPeriod = _endPeriod - _beginPeriod;
			auto _deltaPeriod_ms = std::chrono::duration <double, std::milli>(_deltaPeriod).count();

			if (_deltaPeriod_ms > 1000.0f) {

				std::cout << "frame ms = " << _frame_ms << "\n";
				std::cout << "fps = " << _frame_count << "\n";

				_beginPeriod = _endPeriod;

				_frame_count = 0;
			}
		}

		//==============================================================
		//==============================================================

		void CCore::execute(void) {

			auto _beginPeriod = std::chrono::high_resolution_clock::now();
			uint32_t _frame_count = 0;

			//auto next_game_tick = std::chrono::high_resolution_clock::now();
			//auto next_game_tick_ms = std::chrono::duration<double, std::milli>(next_game_tick - _beginPeriod);
			//auto _frame_ms = std::chrono::duration <double, std::milli>(_deltaFrame).count();
			int loops = 0;

			while (true) {

				auto _beginFrame = std::chrono::high_resolution_clock::now();





				const int TICKS_PER_SECOND = 25;
				const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
				const int MAX_FRAMESKIP = 5;

				//loops = 0;
				//while (std::chrono::high_resolution_clock::now() > next_game_tick_ms && loops < MAX_FRAMESKIP) {
					
					m_Window->update();

					m_Keyboard->update();

					m_Mouse->update();
				//	std::chrono::duration <double, std::milli>(_deltaPeriod).count();
				//	next_game_tick_ms += SKIP_TICKS;
				//	loops++;
				//}





				

				m_ScriptWriter->update();

				m_Renderrer->update();
				m_Renderrer->execute();

				using namespace std::chrono_literals;
				//std::this_thread::sleep_for(1s);

				auto _endFrame = std::chrono::high_resolution_clock::now();
				auto _deltaFrame = _endFrame - _beginFrame;
				auto _frame_ms = std::chrono::duration <double, std::milli>(_deltaFrame).count();
				++_frame_count;

				auto _endPeriod = std::chrono::high_resolution_clock::now();
				auto _deltaPeriod = _endPeriod - _beginPeriod;
				auto _deltaPeriod_ms = std::chrono::duration <double, std::milli>(_deltaPeriod).count();

				if (_deltaPeriod_ms > 1000.0f) {

					std::cout << "frame ms = " << _frame_ms << "\n";
					std::cout << "fps = " << _frame_count << "\n";

					_beginPeriod = _endPeriod;

					_frame_count = 0;
				}
			}
		}

		//==============================================================
		//==============================================================

	} // namespace CORE

} // namespace FE