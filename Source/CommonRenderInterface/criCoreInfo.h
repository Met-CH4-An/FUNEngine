#ifndef CRI_CORE_INFO__H
#define CRI_CORE_INFO__H
////////////////////////////////////////////////////////////////
// ������ ���������� �����
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ ������������� ������
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ �������-����������
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ ��� ����������
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"

namespace FE {

	namespace CRI {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief ���������� ��������� ���� �������� CCRICore �����������.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class e_common_render_interface_create_fail : std::exception {};



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief ����� �������� CCRICore.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		enum class CRI_CORE_CREATE_FLAGS {

			DEBUG = 0x0000001,		///< ���������� ����� ���������.

		}; // enum class CRI_CORE_CREATE_FLAGS
		DECLARE_ENUM_OPERATIONS(CRI_CORE_CREATE_FLAGS);



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief ���������� ��� �������� CCRICore.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CRI_CORE_CREATE_INFO {

			CRI_CORE_CREATE_FLAGS		m_Flags;		///< �����.

		}; // struct CRI_CORE_CREATE_INFO

	} // namespace RENDER

} // namespace FE

#endif // CRI_CORE_INFO__H