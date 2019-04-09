////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "../../CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция компиляция файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция форвард-декларации
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция для исключений
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция для остального
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
			// новые объекты
			// ~~~~~~~~~~~~~~~~

			//CRICore _newCRICore = new CCRICore();
			//VULKAN::VKInstance _newVLKInstance = new VULKAN::CVKInstance();

			// ~~~~~~~~~~~~~~~~
			// вставка ссылок друг на друга
			// ~~~~~~~~~~~~~~~~

			//_newCRICore->setImpl(_newVLKInstance);
			//_newVLKInstance->setCRI(_newCRICore);

			// ~~~~~~~~~~~~~~~~
			// создание
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