////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "PCH.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "Camera.h"
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
#include "Scene.h"
#include "..\CommonRenderInterface\criContext.h"
#include "..\CommonRenderInterface\criDataBuffer.h"

namespace FE {

	namespace SCENE {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		void CCamera::create(const CAMERA_CREATE_INFO *createInfo) {

			// регистрируем камеру
			//createInfo->m_Scene->regCamera(this);

			m_Position = createInfo->m_Position;

			// нормализованный вектор направления камеры
			//vec3 _direction = normalize(createInfo->m_Position - createInfo->m_Target);

			//vec3 m_Right = normalize(cross(createInfo->m_Up, _direction));

			//vec3 m_Up = cross(_direction, m_Right);

			m_Position = createInfo->m_Position;
			//m_Position = vec3(0.01f, 0.0f, 20.0f);
			m_Target = createInfo->m_Target;
			m_Up = createInfo->m_Up;
			m_Front = vec3(0.0f, 0.0f, -1.0f);
			m_View = LookAt(m_Position, m_Position + m_Front, m_Up);
			


			m_Projection = Perspective(45.0f, 800.0f / 600.0f, 0.1, 512.0f);

		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		void CCamera::update(const INPUT::KEYBOARD_SIGNAL_KEYMAP *keys) {
			
			//std::cout << "HELLO OBSERVER CAMERA\n";
			//std::cout << (int)keyboardEvent->m_Key << "\n";
			//std::cout << "HELLO OBSERVER CAMERA\n";
			
			float _speed = 0.05f;

			
			if (keys->m_Keys.at(static_cast<uint32_t>(INPUT::KEYBOARD_KEY_INFO::ID::A)).m_State == INPUT::KEYBOARD_KEY_INFO::STATE::PRESS) {

				m_Position -= normalize(cross(m_Front, m_Up)) * _speed;

				m_View = LookAt(m_Position, m_Position + m_Front, m_Up);

			}

			if (keys->m_Keys.at(static_cast<uint32_t>(INPUT::KEYBOARD_KEY_INFO::ID::D)).m_State == INPUT::KEYBOARD_KEY_INFO::STATE::PRESS) {

				m_Position += normalize(cross(m_Front, m_Up)) * _speed;

				m_View = LookAt(m_Position, m_Position + m_Front, m_Up);
			}

			if (keys->m_Keys.at(static_cast<uint32_t>(INPUT::KEYBOARD_KEY_INFO::ID::W)).m_State == INPUT::KEYBOARD_KEY_INFO::STATE::PRESS) {

				m_Position += m_Front * _speed;

				m_View = LookAt(m_Position, m_Position + m_Front, m_Up);
			}

			if (keys->m_Keys.at(static_cast<uint32_t>(INPUT::KEYBOARD_KEY_INFO::ID::S)).m_State == INPUT::KEYBOARD_KEY_INFO::STATE::PRESS) {

				m_Position -= m_Front * _speed;

				m_View = LookAt(m_Position, m_Position + m_Front, m_Up);
			}		

		}
#define PI 3.14159265
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
		void CCamera::update(const INPUT::MOUSE_SIGNAL_MOVE *mouseMove) {

			//std::cout << mouseMove->m_Delta.x << "\n";

			float _sesivity = 1.0f;
			int32_t _deltaX = mouseMove->m_Delta.x * _sesivity;
			int32_t _deltaY = mouseMove->m_Delta.y * _sesivity;

			m_Pitch += -_deltaY;
			m_Yaw += -_deltaX;
			//m_Pitch += -mouseMove->m_Delta.y;
			//m_Yaw += -mouseMove->m_Delta.x;


			vec3 front;
			//front.x = cos(m_Pitch) * cos(m_Yaw);
			//front.y = sin(m_Pitch);
			//front.z = cos(m_Pitch) * sin(m_Yaw);

			front.x = cos(m_Pitch * PI / 180.0) * cos(m_Yaw * PI / 180.0);
			front.y = sin(m_Pitch * PI / 180.0);
			front.z = cos(m_Pitch * PI / 180.0) * sin(m_Yaw * PI / 180.0);
			m_Front = normalize(front);

			m_View = LookAt(m_Position, m_Position + m_Front, m_Up);
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	} // namespace  

} // namespace FE