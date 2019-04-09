////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "PCH.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "Keyboard.h"
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

namespace FE {

	namespace INPUT {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		void CKeyboard::create(void) {

			m_Keymap.m_Keys.resize(static_cast<uint32_t>(KEYBOARD_KEY_INFO::ID::MAX));
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		void CKeyboard::update() {

			m_S_Keymap.emit(&m_Keymap);
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		void CKeyboard::connactableKeymap(const SIGNAL_WINDOW_KEYBOARD *signal) {

			//
			KEYBOARD_KEY_INFO::STATE _state;
			switch (signal->m_State) {

			case SIGNAL_WINDOW_KEYBOARD::STATE::DOWN:		_state = KEYBOARD_KEY_INFO::STATE::PRESS;		break;
			case SIGNAL_WINDOW_KEYBOARD::STATE::UP:			_state = KEYBOARD_KEY_INFO::STATE::RELEASE;		break;
			};

			// преобразовываем идентификатор клавиши			
			KEYBOARD_KEY_INFO::ID _id = KEYBOARD_KEY_INFO::ID::H;
			switch (signal->m_Key) {

			case SIGNAL_WINDOW_KEYBOARD::KEY::A:		_id = KEYBOARD_KEY_INFO::ID::A;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::B:		_id = KEYBOARD_KEY_INFO::ID::B;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::C:		_id = KEYBOARD_KEY_INFO::ID::C;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::D:		_id = KEYBOARD_KEY_INFO::ID::D;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::E:		_id = KEYBOARD_KEY_INFO::ID::E;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::F:		_id = KEYBOARD_KEY_INFO::ID::F;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::G:		_id = KEYBOARD_KEY_INFO::ID::G;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::H:		_id = KEYBOARD_KEY_INFO::ID::H;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::I:		_id = KEYBOARD_KEY_INFO::ID::I;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::J:		_id = KEYBOARD_KEY_INFO::ID::J;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::K:		_id = KEYBOARD_KEY_INFO::ID::K;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::L:		_id = KEYBOARD_KEY_INFO::ID::L;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::M:		_id = KEYBOARD_KEY_INFO::ID::M;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::N:		_id = KEYBOARD_KEY_INFO::ID::N;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::O:		_id = KEYBOARD_KEY_INFO::ID::O;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::P:		_id = KEYBOARD_KEY_INFO::ID::P;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::Q:		_id = KEYBOARD_KEY_INFO::ID::Q;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::R:		_id = KEYBOARD_KEY_INFO::ID::R;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::S:		_id = KEYBOARD_KEY_INFO::ID::S;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::T:		_id = KEYBOARD_KEY_INFO::ID::T;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::U:		_id = KEYBOARD_KEY_INFO::ID::U;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::V:		_id = KEYBOARD_KEY_INFO::ID::V;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::W:		_id = KEYBOARD_KEY_INFO::ID::W;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::X:		_id = KEYBOARD_KEY_INFO::ID::X;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::Y:		_id = KEYBOARD_KEY_INFO::ID::Y;	break;
			case SIGNAL_WINDOW_KEYBOARD::KEY::Z:		_id = KEYBOARD_KEY_INFO::ID::Z;	break;


			}

			m_Keymap.m_Keys[static_cast<uint32_t>(_id)].m_ID = _id;
			m_Keymap.m_Keys[static_cast<uint32_t>(_id)].m_State = _state;

		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	} // namespace INPUT

} // namespace FE