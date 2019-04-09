#ifndef SCRIPT__H
#define SCRIPT__H
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
#include "../Renderer/pch.renderer.h"
#include "../Procedural/FProcedural.h"
////////////////////////////////////////////////////////////////
// ������ ��� ����������
////////////////////////////////////////////////////////////////

namespace FE {

	namespace SCENE {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief ���������� ��� ��������.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct SCRIPT_CREATE_INFO {
		};



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CScript {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �������� ������.

			\param[in] scene Scene, ������� ������� Script.
			\param[out] script ���������� ������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			static void get(Scene scene, Script *script);

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �����������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			CScript();

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �������.

			\param[in] createInfo ���������� ��� ��������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void create(const SCRIPT_CREATE_INFO *createInfo);

			void createSphere(PROCEDURAL::Procedural procedural, RENDERER::Renderer renderer);

			void createHelixParticles(PROCEDURAL::Procedural procedural, RENDERER::Renderer renderer);

		// ������
		private:

			Scene			m_Scene;

		}; // class CScript

	} // namespace SCENE {

} // namespace FE {

#endif // SCRIPT__H