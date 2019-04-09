#ifndef CRI_TOOLS__H
#define CRI_TOOLS__H
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
#include "../CommonRenderInterface.h"

namespace FE {

	namespace CRI {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief ����� ����� ��� ���������� �������������.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CCRIImpl {

		// CRITools.hpp
		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �������� ������������.

			\return void* ��������� �� �������������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline void* getImpl(void) const;

		// ������
		protected:

			void		*m_pImpl;		///< �������������.


		}; // class CCRIImpl

	} // namespace RENDER

} // namespace FE

#include "CRITools.hpp"

#endif // CRI_TOOLS__H