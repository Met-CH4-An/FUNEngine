#ifndef CRI_PROGRAM__HPP
#define CRI_PROGRAM__HPP
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

namespace FE {

	namespace CRI {

		//==============================================================
		//==============================================================

		bool CRI_PROGRAM_CREATE_INFO::isValid(void) const {

			if (m_criContext == nullptr ||
				m_VertexCode == "" ||
				m_FragmentCode == "") return false;

			return true;
		}

		//==============================================================
		//==============================================================

	} // namespace RENDER

} // namespace FE

#endif // CRI_PROGRAM__HPP