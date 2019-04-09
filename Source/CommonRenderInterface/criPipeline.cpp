////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "CRIPipeline.h"
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
#include "Vulkan/vknContext.h"
#include "Private/Vulkan/vknBatch.h"
#include "Vulkan/vknPipeline.h"

namespace FE {

	namespace CRI {
		
		//==============================================================
		//==============================================================

		CRIPipeline CCRIPipeline::create(const CRI_PIPELINE_CI *criCreateInfo) {

			//ASSERT_EX(createInfo, != , nullptr, "Invalid CRI_IMAGE_BUFFER_CREATE_INFO.", throw e_image_buffer_create_failed());
			//ASSERT_EX(createInfo->isValid(), == , true, "Invalid CRI_IMAGE_BUFFER_CREATE_INFO.", throw e_image_buffer_create_failed());

			// ~~~~~~~~~~~~~~~~
			// get VKContext
			// ~~~~~~~~~~~~~~~~

			auto _vknContext = VULKAN::cri2vkn_Context(criCreateInfo->m_criContext);

			// ~~~~~~~~~~~~~~~~
			// get VKPipeline
			// ~~~~~~~~~~~~~~~~

			auto _vknPipeline = _vknContext->getBatch()->getPipeline(criCreateInfo);

			// ~~~~~~~~~~~~~~~~
			// new CRIPipelinePrivate
			// ~~~~~~~~~~~~~~~~

			auto _criPipelinePrivate = std::make_shared<CCRIPipelinePrivate>(_vknPipeline);

			return _criPipelinePrivate;
		}

		//==============================================================
		//==============================================================

		CCRIPipeline::CCRIPipeline() {


		}

		//==============================================================
		//==============================================================

	} // namespace CRI

} // namespace FE