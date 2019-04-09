////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "vknRecordCmdBufferTask.h"
////////////////////////////////////////////////////////////////
// секция компиляция файла
////////////////////////////////////////////////////////////////
#include "../../../RenderConfig.h"
#if defined(FE_RENDER) && defined(FE_RENDER_VULKAN) && FE_RENDER == FE_RENDER_VULKAN
////////////////////////////////////////////////////////////////
// секция форвард-декларации
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция для исключений
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////
#include "../../Vulkan\vknContext.h"

namespace FE {

	namespace CRI {

		namespace VULKAN {

			void CVKRecordCmdBufferTask::create(VKRecordCmdBufferTaskArr *tasks, VKContext context) {

				size_t _maxTask = 8;
				for (size_t ctTask = 0; ctTask < _maxTask; ++ctTask) {
					
					// ~~~~~~~~~~~~~~~~
					// командный пул
					// ~~~~~~~~~~~~~~~~

					// описываем VkCommandPoolCreateInfo
					VkCommandPoolCreateInfo _cmdPoolCI = {};

					_cmdPoolCI.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
					_cmdPoolCI.queueFamilyIndex = context->getIndexFamilyQueue();
					_cmdPoolCI.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

					VkCommandPool _pool;
					VK_ASSERT_EX(context->vkCreateCommandPool(context->getDevice(), &_cmdPoolCI, nullptr, &_pool), "", );

					// ~~~~~~~~~~~~~~~~
					// новая задача
					// ~~~~~~~~~~~~~~~~

					VKRecordCmdBufferTask _newTask = new CVKRecordCmdBufferTask();
					_newTask->m_Pool = _pool;

					// ~~~~~~~~~~~~~~~~
					// новая задача
					// ~~~~~~~~~~~~~~~~

					tasks->push_back(_newTask);
				
				} // for (size_t ctTask = 0;

			}

		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE

#endif // #if defined(FE_RENDER) && defined(FE_RENDER_VULKAN) && FE_RENDER == FE_RENDER_VULKAN

