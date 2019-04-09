#ifndef CAMERA__H
#define CAMERA__H
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
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////

#include "..\Input\Keyboard.h"
#include "..\Input\Mouse.h"

namespace FE {

	namespace SCENE {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CAMERA_CREATE_INFO {

			//Scene		m_Scene;
			vec3		m_Position;
			vec3		m_Target;
			vec3		m_Up;

		}; // struct CAMERA_CREATE_INFO



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CCamera {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Создание камеры.

			\param createInfo Информация для создания.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void create(const CAMERA_CREATE_INFO *createInfo);

			void update(const INPUT::KEYBOARD_SIGNAL_KEYMAP *keyboardEvent);

			void update(const INPUT::MOUSE_SIGNAL_MOVE *mouseMove);

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Получить матрицу вида.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline mat4 getView(void) const;

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Получить матрицу проекции.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline mat4 getProjection(void) const;

		private:

			CRI::CRIDataBuffer			m_DataBuffer;
			vec3						m_Right;
			vec3						m_Up;
			vec3						m_Position;
			vec3						m_Target;
			mat4						m_View;
			mat4						m_Projection;
			mat4						m_ViewProjection;
			vec3						m_Front;
			float						m_Pitch = 0.0f;
			float						m_Yaw = -90.0f;


		}; // class CCamera

	} // namespace SCENE

} // namespace FE

#include "Camera.hpp"

#endif // CAMERA__H