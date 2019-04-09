////////////////////////////////////////////////////////////////
// ������ PCH
////////////////////////////////////////////////////////////////
#include "PCH.h"
////////////////////////////////////////////////////////////////
// ������ ������������� �����
////////////////////////////////////////////////////////////////
#include "File.h"
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

	namespace CONTENT {

		//==============================================================
		//==============================================================

		CFile::CFile(void) {

			//m_Valid = false;
			m_FileStream;

		}

		//==============================================================
		//==============================================================

		void CFile::create(const FILE_CREATE_INFO *createInfo) {
			
			m_CreateInfo = *createInfo;

			// ~~~~~~~~~~~~~~~~
			// ���������
			// ~~~~~~~~~~~~~~~~
			
			m_FileStream.open(createInfo->m_Name, std::ios::binary);

			ASSERT_EX(m_FileStream.is_open(), ==, true, 
				"�� ������� ������� std::ifstream.",
				throw e_content_file_create_fail());
			
			// ~~~~~~~~~~~~~~~~
			// ������
			// ~~~~~~~~~~~~~~~~
			
			m_FileStream.seekg(0, std::ios::end);
			size_t _size = m_FileStream.tellg();
			m_FileStream.seekg(0, std::ios::beg);

			// ��������
			m_Data.resize(_size, ' ');

			// ~~~~~~~~~~~~~~~~
			// ������ 
			// ~~~~~~~~~~~~~~~~

			m_FileStream.read(&m_Data[0], _size);

			//m_Valid = true;
		
		}

		//==============================================================
		//==============================================================

	} // namespace CONTENT

} // namespace FE