////////////////////////////////////////////////////////////////
// ������ PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// ������ ������������� �����
////////////////////////////////////////////////////////////////
#include "../../../Vulkan/vknInstance.h"
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
#include <Windows.h>

namespace FE {

	namespace CRI {

		namespace VULKAN {

			//==============================================================
			//==============================================================

			void CVKInstance::createPlatform(void) {

				// ��������� dll �������
				HMODULE _handleDll = LoadLibrary("vulkan-1.dll");

				ASSERT_EX(_handleDll, != , NULL, "�� ������� ��������� vulkan-1.dll.", throw e_vulkan_common_instance_create_fail());

				// �������� ������ �������, ����� ������� ����� ����� �������� ������ ��������� ������� �������
				vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(GetProcAddress(_handleDll, "vkGetInstanceProcAddr"));

			}

			//==============================================================
			//==============================================================

		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE