////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "CRIContext.h"
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
#include "CRIContext.h"
#include "CRIDataBuffer.h"
#include "Vulkan/vknContext.h"
#include "Vulkan/vknRenderPass.h"
#include "Vulkan/vknPipeline.h"
#include "Vulkan/vknProgram.h"
#include "Vulkan/vknDataBuffer.h"
#include "Vulkan/vknImageBuffer.h"

namespace FE {

	namespace CRI {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		CRIContext CCRIContext::create(const CRI_CONTEXT_CREATE_INFO *createInfo) {

			// new VKContext
			auto _vknContext = std::make_shared<VULKAN::CVKContext>();

			// create VKContext
			_vknContext->create(createInfo);

			// new CRIContextPrivate
			auto _criContextPrivate = std::make_shared<VULKAN::CCRIContextPrivate>(_vknContext);

			return _criContextPrivate;
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//void CCRIContext::getRenderPass(const CRI_RENDER_PASS_CI *criCreateInfo, CRIRenderPass *criRenderPass) {

			// обращаемся к имплементации Khronos Vulkan
			//static_cast<VULKAN::CVKContext*>(this)->getRenderPass(criCreateInfo, criRenderPass);
		
		//}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		/*void CCRIContext::getPipeline(const CRI_PIPELINE_CI *criCreateInfo, CRIPipeline *criPipeline) {

			auto _vknContext = VULKAN::cri2vkn_Context(criCreateInfo->m_Context);

			auto _criPipelinePrivate = std::make_shared<VULKAN::CCRIPipelineImpl>();

			auto _vknPipeline = std::make_shared<VULKAN::CVKPipeline>(_vknContext);

			_vknPipeline->create(criCreateInfo);

			_criPipelinePrivate->m_VKNPipeline = _vknPipeline;
			

			*criPipeline = _criPipelinePrivate;

			

		}*/

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		void CCRIContext::create(CRIContext criContext, CRIDataBuffer *criDataBuffer, const CRI_DATA_BUFFER_CREATE_INFO *createInfo) {
			auto _vknContext = VULKAN::cri2vkn_Context(criContext);
			auto _new = std::make_shared<VULKAN::CVKDataBuffer>(_vknContext);
			
			*criDataBuffer = _new;

			(*criDataBuffer)->create(createInfo);
		
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//void CCRIContext::create(CRIContext criContext, CRIImageBuffer *criImageBuffer, const CRI_IMAGE_BUFFER_CREATE_INFO *createInfo) {

			//auto _new = std::make_shared<VULKAN::CVKImageBuffer>(static_cast<VULKAN::CVKContext*>(criContext));

			//*criImageBuffer = _new;
//
			//(*criImageBuffer)->create(createInfo);

		//}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		CCRIContext::CCRIContext(void){


		}

		

		//==============================================================
		//==============================================================

		void CCRIContext::update(void) {

			static_cast<VULKAN::CCRIContextPrivate*>(this)->getImpl()->update();
			//static_cast<VULKAN::CVKContext*>(this)->update();
		
		}

		//==============================================================
		//==============================================================

		void CCRIContext::execute(void) {
			static_cast<VULKAN::CCRIContextPrivate*>(this)->getImpl()->execute();
			//static_cast<VULKAN::CVKContext*>(this)->execute();

		}

		//==============================================================
		//==============================================================

	} // namespace RENDER

} // namespace FE