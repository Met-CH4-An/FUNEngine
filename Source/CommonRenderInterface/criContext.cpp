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
#include "Private/Vulkan/vknBatch.h"
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
			auto _vknContext = new VULKAN::CVKContext();

			// create VKContext
			_vknContext->create(createInfo);

			// new CRIContextPrivate
			auto _criContextPrivate = new VULKAN::CCRIContextPrivate(_vknContext);

			return _criContextPrivate;
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		CRIRenderPass CCRIContext::create(const CRI_RENDER_PASS_CI *criCreateInfo) {

			ASSERT_EX(criCreateInfo->isValid(), == , true, "Invalid CRI_RENDER_PASS_CREATE_INFO.", throw e_render_pass_create_failed());

			// ~~~~~~~~~~~~~~~~
			// get VKContext
			// ~~~~~~~~~~~~~~~~

			auto _vknContext = VULKAN::cri2vkn_Context(this);

			// ~~~~~~~~~~~~~~~~
			// get VKRenderPass
			// ~~~~~~~~~~~~~~~~

			uint32_t _idSubpass = 0;

			auto _vknRenderPass = _vknContext->getBatch()->getRenderPass(criCreateInfo, &_idSubpass);

			// ~~~~~~~~~~~~~~~~
			// new CRIRenderPassPrivate
			// ~~~~~~~~~~~~~~~~

			auto _criRenderPassPrivate = new VULKAN::CCRIRenderPassPrivate(_vknRenderPass);

			_criRenderPassPrivate->setIDSubpass(_idSubpass);

			// ~~~~~~~~~~~~~~~~

			return _criRenderPassPrivate;
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		CRIPipeline CCRIContext::create(const CRI_PIPELINE_CI *criCreateInfo) {

			//ASSERT_EX(createInfo, != , nullptr, "Invalid CRI_IMAGE_BUFFER_CREATE_INFO.", throw e_image_buffer_create_failed());
			//ASSERT_EX(createInfo->isValid(), == , true, "Invalid CRI_IMAGE_BUFFER_CREATE_INFO.", throw e_image_buffer_create_failed());

			// ~~~~~~~~~~~~~~~~
			// get VKContext
			// ~~~~~~~~~~~~~~~~

			auto _vknContext = VULKAN::cri2vkn_Context(this);

			// ~~~~~~~~~~~~~~~~
			// get VKPipeline
			// ~~~~~~~~~~~~~~~~

			auto _vknPipeline = _vknContext->getBatch()->getPipeline(criCreateInfo);

			// ~~~~~~~~~~~~~~~~
			// new CRIPipelinePrivate
			// ~~~~~~~~~~~~~~~~

			auto _criPipelinePrivate = new CCRIPipelinePrivate(_vknPipeline);

			return _criPipelinePrivate;
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		CRIProgram CCRIContext::create(const CRI_PROGRAM_CREATE_INFO *criCreateInfo) {

			ASSERT_EX(criCreateInfo->isValid(), == , true, "Invalid CRI_PROGRAM_CREATE_INFO.", throw e_cri_program_create_failed());

			// ~~~~~~~~~~~~~~~~
			// VKContext
			// ~~~~~~~~~~~~~~~~

			auto _vknContext = VULKAN::cri2vkn_Context(this);

			// ~~~~~~~~~~~~~~~~
			// VKProgram
			// ~~~~~~~~~~~~~~~~

			auto _vknProgram = _vknContext->getBatch()->getProgram(criCreateInfo);

			// ~~~~~~~~~~~~~~~~
			// new CRIRenderPassPrivate
			// ~~~~~~~~~~~~~~~~

			auto _criProgramPrivate = new CCRIProgramPrivate(_vknProgram);

			// ~~~~~~~~~~~~~~~~
			// ~~~~~~~~~~~~~~~~

			return _criProgramPrivate;
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		CRIImageBuffer CCRIContext::create(const CRI_IMAGE_BUFFER_CREATE_INFO *criCreateInfo) {

			ASSERT_EX(criCreateInfo, != , nullptr, "Invalid CRI_IMAGE_BUFFER_CREATE_INFO.", throw e_image_buffer_create_failed());
			ASSERT_EX(criCreateInfo->isValid(), == , true, "Invalid CRI_IMAGE_BUFFER_CREATE_INFO.", throw e_image_buffer_create_failed());

			// ~~~~~~~~~~~~~~~~
			// get VKContext
			// ~~~~~~~~~~~~~~~~

			auto _vknContext = VULKAN::cri2vkn_Context(this);

			// ~~~~~~~~~~~~~~~~
			// get VKImageBuffer
			// ~~~~~~~~~~~~~~~~

			auto _vknImageBuffer = _vknContext->getBatch()->getImageBuffer(criCreateInfo);

			// ~~~~~~~~~~~~~~~~
			// new CRIImageBufferPrivate
			// ~~~~~~~~~~~~~~~~

			auto _criImageBufferPrivate = new CCRIImageBufferPrivate(_vknImageBuffer);

			return _criImageBufferPrivate;
		}

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