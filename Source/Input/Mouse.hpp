#ifndef MOUSE__HPP
#define MOUSE__HPP
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

	namespace INPUT {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		template <typename T, typename ... Args>
		inline void CMouse::connectMove(T *object, void (T::*func)(Args ... args)) {
			
			m_S_Move.connect_member(object, func);

		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
		template <typename T, typename ... Args>
		inline void CMouse::connectMove(T *object, void (T::*func)(Args ... args) const) {
			
			m_S_Move.connect_member(object, func);

		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	} // namespace INPUT

} // namespace FE

#endif // MOUSE__HPP