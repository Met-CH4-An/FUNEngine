#ifndef VK_RECORD_CMD_BUFFER_TASK__H
#define VK_RECORD_CMD_BUFFER_TASK__H
////////////////////////////////////////////////////////////////
// секция компиляция файла
////////////////////////////////////////////////////////////////
#include "../../../RenderConfig.h"
#if defined(FE_RENDER) && defined(FE_RENDER_VULKAN) && FE_RENDER == FE_RENDER_VULKAN
////////////////////////////////////////////////////////////////
// секция родительского класса
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция форвард-декларации
////////////////////////////////////////////////////////////////
#include "../../Vulkan\Vulkan.h"
#include "../../CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////


namespace FE {

	namespace CRI {

		namespace VULKAN {

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Невозможно создать CVKResourcePool.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			struct VK_RECORD_CMD_BUFFER_TASK_CREATE_INFO {

				VKContext		m_Context;
			};



			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Невозможно создать CVKResourcePool.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			class CVKRecordCmdBufferTask {

			public:

				static void create(VKRecordCmdBufferTaskArr *tasks, VKContext context);

			public:



			private:

				VkCommandPool		m_Pool;
			};

		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE

#endif // #if defined(FE_RENDER) && defined(FE_RENDER_VULKAN) && FE_RENDER == FE_RENDER_VULKAN

#endif // VK_RECORD_CMD_BUFFER_TASK__H