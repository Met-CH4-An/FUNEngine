////////////////////////////////////////////////////////////////
// ������ PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// ������ ������������� �����
////////////////////////////////////////////////////////////////
#include "CRIDrawBuffer.h"
////////////////////////////////////////////////////////////////
// ������ ���������� �����
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ �������-����������
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ ��� ����������
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ ��� ����������
////////////////////////////////////////////////////////////////

namespace FE {

	namespace CRI {

		//==============================================================
		//==============================================================

		CCRIDrawBuffer::CCRIDrawBuffer(const CRI_DRAW_BUFFER_CREATE_INFO *createInfo)
			: m_CI(*createInfo) {
		}

		//==============================================================
		//==============================================================

		void CCRIDrawBuffer::create(void) {

			m_Valid = true;
		}

		//==============================================================
		//==============================================================

	} // namespace RENDER

} // namespace FE