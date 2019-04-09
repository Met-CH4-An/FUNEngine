#ifndef FCONTENT__H
#define FCONTENT__H
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
#include <vector>

namespace FE {

	namespace CONTENT {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		class e_content_common : public std::exception {};

		class CContent;
		using Content = CContent*;

		class CContentManager;
		using ContentManager = CContentManager*;

		class CContentObject;
		using ContentObject = CContentObject*;

		class CFile;
		using File = CFile*;
		using FileArr = std::vector<File>;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	} // namespace CONTENT

} // namespace FE

#endif // FCONTENT__H