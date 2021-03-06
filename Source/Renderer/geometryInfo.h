#ifndef GEOMETRY_INFO__H
#define GEOMETRY_INFO__H
////////////////////////////////////////////////////////////////
// ������ ���������� �����
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ ������������� ������
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ �������-����������
////////////////////////////////////////////////////////////////
#include "../Renderer/pch.renderer.h"
#include "../CommonRenderInterface/CommonRenderInterface.h"""
////////////////////////////////////////////////////////////////
// ������ ��� ����������
////////////////////////////////////////////////////////////////
#include "..\PCH.h"

namespace FE {

	namespace RENDERER {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief ���������� ��� �������� ���������.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct GEOMETRY_CREATE_INFO {

			Renderer		m_Renderer;
			
			void*			m_DataVertices;
			uint32_t		m_SizeDataVertices;
			void*			m_DataIndices;
			uint32_t		m_SizeDataIndices;

		}; // struct GEOMETRY_CREATE_INFO

	} // namespace RENDERER

} // namespace FE

#endif // GEOMETRY_INFO__H