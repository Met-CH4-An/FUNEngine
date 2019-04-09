////////////////////////////////////////////////////////////////
// ������ PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// ������ ������������� �����
////////////////////////////////////////////////////////////////
#include "vknRecordCmdBufferTask.h"
////////////////////////////////////////////////////////////////
// ������ ���������� �����
////////////////////////////////////////////////////////////////
#include "../../../RenderConfig.h"
#if defined(FE_RENDER) && defined(FE_RENDER_VULKAN) && FE_RENDER == FE_RENDER_VULKAN
////////////////////////////////////////////////////////////////
// ������ �������-����������
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ ��� ����������
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ ��� ����������
////////////////////////////////////////////////////////////////
#include "../../Vulkan\vknContext.h"

namespace FE {

	namespace CRI {

		namespace VULKAN {

			void CVKRecordCmdBufferTask::create(VKRecordCmdBufferTaskArr *tasks, VKContext context) {

				size_t _maxTask = 8;
				for (size_t ctTask = 0; ctTask < _maxTask; ++ctTask) {
					
					// ~~~~~~~~~~~~~~~~
					// ��������� ���
					// ~~~~~~~~~~~~~~~~

					// ��������� VkCommandPoolCreateInfo
					VkCommandPoolCreateInfo _cmdPoolCI = {};

					_cmdPoolCI.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
					_cmdPoolCI.queueFamilyIndex = context->getIndexFamilyQueue();
					_cmdPoolCI.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

					VkCommandPool _pool;
					VK_ASSERT_EX(context->vkCreateCommandPool(context->getDevice(), &_cmdPoolCI, nullptr, &_pool), "", );

					// ~~~~~~~~~~~~~~~~
					// ����� ������
					// ~~~~~~~~~~~~~~~~

					VKRecordCmdBufferTask _newTask = new CVKRecordCmdBufferTask();
					_newTask->m_Pool = _pool;

					// ~~~~~~~~~~~~~~~~
					// ����� ������
					// ~~~~~~~~~~~~~~~~

					tasks->push_back(_newTask);
				
				} // for (size_t ctTask = 0;

			}

		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE

#endif // #if defined(FE_RENDER) && defined(FE_RENDER_VULKAN) && FE_RENDER == FE_RENDER_VULKAN

