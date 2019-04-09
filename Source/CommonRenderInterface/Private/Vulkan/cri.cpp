////////////////////////////////////////////////////////////////
// ������ PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// ������ ������������� �����
////////////////////////////////////////////////////////////////
#include "../../CommonRenderInterface.h"
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
//#include "vknInstance.h"
#include "../../Vulkan\vknContext.h"
#include "vknResourcePool.h"
#include "vknBatch.h"
#include "../../Vulkan\vknDataBuffer.h"
#include "../../Vulkan/vknImageBuffer.h"
#include "vknDrawBuffer.h"


#include "../CRICore.h"
#include "../../CRIContext.h"
#include "../../CRIRenderPass.h"
#include "../CRIDrawBuffer.h"



namespace FE {

	namespace CRI {

		//==============================================================
		//==============================================================

		void OPERATION::createCRICore(CRICore *core, const CRI_CORE_CREATE_INFO *createInfo) {

			static bool CORE_CREATE = false;

			// ~~~~~~~~~~~~~~~~
			// ����� �������
			// ~~~~~~~~~~~~~~~~

			//CRICore _newCRICore = new CCRICore();
			//VULKAN::VKInstance _newVLKInstance = new VULKAN::CVKInstance();

			// ~~~~~~~~~~~~~~~~
			// ������� ������ ���� �� �����
			// ~~~~~~~~~~~~~~~~

			//_newCRICore->setImpl(_newVLKInstance);
			//_newVLKInstance->setCRI(_newCRICore);

			// ~~~~~~~~~~~~~~~~
			// ��������
			// ~~~~~~~~~~~~~~~~

			//_newCRICore->create(createInfo);
			//_newVLKInstance->create(createInfo);

			//(*core) = _newCRICore;

		}

		//==============================================================
		//==============================================================

		void OPERATION::createDrawBuffer(CRIDrawBuffer *drawBuffer, const CRI_DRAW_BUFFER_CREATE_INFO *createInfo) {

			VULKAN::CVKDrawBuffer::get(createInfo, drawBuffer);
		}

		//==============================================================
		//==============================================================
		
		void OPERATION::drawBuffer(CRIContext context, CRIDrawBufferArr *drawBuffer) {
			VULKAN::cri2vkn_Context(context)->getBatch()->addDrawBuffer(drawBuffer);
			
						
		}

		//==============================================================
		//==============================================================

	} // namespace RENDER

} // namespace FE