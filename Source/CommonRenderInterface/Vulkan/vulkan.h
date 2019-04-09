#ifndef VULKAN__H
#define VULKAN__H
////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "../CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция компиляция файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция родительского класса
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция форвард-декларации
////////////////////////////////////////////////////////////////
#include "../CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////
#define VK_USE_PLATFORM_WIN32_KHR
#include "../../../Dependencies/Source/Vulkan/vulkan.h"
#include "../../Common/Format.h"

//==============================================================
//==============================================================
//==============================================================

inline std::string errorString(VkResult errorCode)
{
	switch (errorCode)
	{
#define STR(r) case VK_ ##r: return #r
		STR(NOT_READY);
		STR(TIMEOUT);
		STR(EVENT_SET);
		STR(EVENT_RESET);
		STR(INCOMPLETE);
		STR(ERROR_OUT_OF_HOST_MEMORY);
		STR(ERROR_OUT_OF_DEVICE_MEMORY);
		STR(ERROR_INITIALIZATION_FAILED);
		STR(ERROR_DEVICE_LOST);
		STR(ERROR_MEMORY_MAP_FAILED);
		STR(ERROR_LAYER_NOT_PRESENT);
		STR(ERROR_EXTENSION_NOT_PRESENT);
		STR(ERROR_FEATURE_NOT_PRESENT);
		STR(ERROR_INCOMPATIBLE_DRIVER);
		STR(ERROR_TOO_MANY_OBJECTS);
		STR(ERROR_FORMAT_NOT_SUPPORTED);
		STR(ERROR_SURFACE_LOST_KHR);
		STR(ERROR_NATIVE_WINDOW_IN_USE_KHR);
		STR(SUBOPTIMAL_KHR);
		STR(ERROR_OUT_OF_DATE_KHR);
		STR(ERROR_INCOMPATIBLE_DISPLAY_KHR);
		STR(ERROR_VALIDATION_FAILED_EXT);
		STR(ERROR_INVALID_SHADER_NV);
#undef STR
	default:
		return "UNKNOWN_ERROR";
	}
}

#define VK_ASSERT(function, message) {\
	VkResult res = (function);\
	if (res == VK_SUCCESS) {\
		std::cerr << "vkn_ASSERT FAILED:   " << errorString(res) << "\n\n";\
		ASSERT(res,==,VK_SUCCESS,"message");\
	}\
}

#define VK_ASSERT_LOAD_FUNCTION(function) {\
	ASSERT_EX(function, !=, 0, "Failed to get functions Vulkan.", throw e_vulkan_common());\
}
/*VkResult res = (function);\
if (res != VK_SUCCESS) {\
std::cerr << "vkn_ASSERT FAILED:   " << errorString(res) << "\n\n";\
ASSERT(res,==,VK_SUCCESS,message);\
}\*/


#define VK_ASSERT_EX(function, message, action) {\
VkResult res = (function);\
if (res != VK_SUCCESS) {\
std::cerr << "vkn_ASSERT FAILED:   " << errorString(res) << "\n\n";\
ASSERT_EX(res,==,VK_SUCCESS,message,action);\
}\
}

namespace FE {

	namespace CRI {

		namespace VULKAN {

			enum class VK_FORMAT {

				UNKNOWN = -1,
				R32G32B32_SFLOAT = VK_FORMAT_R32G32B32_SFLOAT
			};

			//==============================================================
			//==============================================================
			//==============================================================

			class	e_vulkan_common : public e_cri_common {};

			class	CVKDevice;
			using	VKDevice = CVKDevice*;
			using	VKDeviceArr = std::vector<VKDevice>;
			
			class	CVKInstance;
			using	VKInstance = CVKInstance*;

			class	CVKContext;
			using	VKContext = std::shared_ptr<CVKContext>;
			using	VKContextArr = std::vector<VKContext>;

			class	CVKResourcePool;
			using	VKResourcePool = CVKResourcePool*;
			using	VKResourcePoolArr = std::vector<VKResourcePool>;

			class	CVKRender;
			using	VKRender = CVKRender*;

			class	CVKBatch;
			using	VKBatch = CVKBatch*;
			using	VKBatchArr = std::vector<VKBatch>;
			struct	VK_BATCH_CREATE_INFO;
			using	VK_BATCH_CREATE_INFO_ARR = std::vector<VK_BATCH_CREATE_INFO>;

			struct	VK_RENDER_OBJECT;
			using	VK_RENDER_OBJECT_ARR = std::vector<VK_RENDER_OBJECT>;

			class	CVKRenderPass;
			using	VKRenderPass = std::shared_ptr<CVKRenderPass>;
			using	VKRenderPassArr = std::vector<VKRenderPass>;
			struct	VK_RENDER_PASS_CREATE_INFO;

			class	CVKPipeline;
			using	VKPipeline = std::shared_ptr<CVKPipeline>;
			using	VKPipelineArr = std::vector<VKPipeline>;
			struct	VK_PIPELINE_CREATE_INFO;
			using	VK_PIPELINE_CREATE_INFO_ARR = std::vector<VK_PIPELINE_CREATE_INFO>;

			class	CVKProgram;
			using	VKProgram = std::shared_ptr<CVKProgram>;
			using	VKProgramArr = std::vector<VKProgram>;
			struct	VK_PROGRAM_CREATE_INFO;

			class	CVKDataBuffer;
			using	VKDataBuffer = std::shared_ptr<CVKDataBuffer>;
			using	VKDataBufferArr = std::vector<VKDataBuffer>;
			struct	VK_DATA_BUFFER_CREATE_INFO;
			using	VK_DATA_BUFFER_CREATE_INFO_ARR = std::vector<VK_DATA_BUFFER_CREATE_INFO>;

			class	CVKImageBuffer;
			using	VKImageBuffer = std::shared_ptr<CVKImageBuffer>;
			using	VKImageBufferArr = std::vector<VKImageBuffer>;
			struct	VK_IMAGE_BUFFER_CREATE_INFO;
			using	VK_IMAGE_BUFFER_CREATE_INFO_ARR = std::vector<VK_IMAGE_BUFFER_CREATE_INFO>;

			class	CVKDrawBuffer;
			using	VKDrawBuffer = CVKDrawBuffer*;
			using	VKDrawBufferArr = std::vector<VKDrawBuffer>;
			struct	VK_DRAW_BUFFER_CREATE_INFO;
			using	VK_DRAW_BUFFER_CREATE_INFO_ARR = std::vector<VK_DRAW_BUFFER_CREATE_INFO>;

			class	CVKRecordCmdBufferTask;
			using	VKRecordCmdBufferTask = CVKRecordCmdBufferTask*;
			using	VKRecordCmdBufferTaskArr = std::vector<VKRecordCmdBufferTask>;
			struct	VK_RECORD_CMD_BUFFER_CREATE_INFO;
			using	VK_RECORD_CMD_BUFFER_CREATE_INFO_ARR = std::vector<VK_RECORD_CMD_BUFFER_CREATE_INFO>;

			using	VkFramebufferArr = std::vector<VkFramebuffer>;

			//==============================================================
			//==============================================================
			//==============================================================

			using VkExtensionPropertiesArr = std::vector<VkExtensionProperties>;
			using VkLayerPropertiesArr = std::vector<VkLayerProperties>;
			using VkPhysicalDeviceArr = std::vector<VkPhysicalDevice>;
			using VkQueueFamilyPropertiesArr = std::vector<VkQueueFamilyProperties>;
			using VkPresentModeArr = std::vector<VkPresentModeKHR>;
			using VkSurfaceFormatArr = std::vector<VkSurfaceFormatKHR>;

			using VkImageArr = std::vector<VkImage>;
			using VkImageViewArr = std::vector<VkImageView>;
			using VkImageViewArrs = std::vector<VkImageViewArr>;

			using VkFormatArr = std::vector<VkFormat>;
			using VkCommandBufferArr = std::vector<VkCommandBuffer>;
			using VkDescriptorSetArr = std::vector<VkDescriptorSet>;
			using VkDescriptorSetLayoutArr = std::vector<VkDescriptorSetLayout>;
			using VkDescriptorPoolArr = std::vector<VkDescriptorPool>;
			using VkDescriptorPoolSizeArr = std::vector<VkDescriptorPoolSize>;

			using VkClearValueArr = std::vector<VkClearValue>;
			using VkSubpassDescriptionArr = std::vector<VkSubpassDescription>;
			using VkAttachmentDescriptionArr = std::vector<VkAttachmentDescription>;
			using VkAttachmentReferenceArr = std::vector<VkAttachmentReference>;
			using VkAttachmentReferenceArrs = std::vector<VkAttachmentReferenceArr>;
			using VkSubpassDependencyArr = std::vector<VkSubpassDependency>;
			
			using VkPipelineColorBlendAttachmentStateArr = std::vector<VkPipelineColorBlendAttachmentState>;
			using VkPipelineShaderStageCreateInfoArr = std::vector<VkPipelineShaderStageCreateInfo>;

			//==============================================================
			//==============================================================
			//==============================================================

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			struct CVKExtension {

				VkExtensionProperties		m_VkExtension;
				bool						m_Status;
			};
			using CVKExtensionArr = std::vector<CVKExtension>;



			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			struct CVKLayer {

				VkLayerProperties			m_VkLayer;
				bool						m_Status;
			};
			using CVKLayerArr = std::vector<CVKLayer>;

			//==============================================================
			//==============================================================
			//==============================================================

			inline VkFormat cri2vkn_Format(COMMON::FORMAT::TEXTURE format) {

				switch (format) {

				case COMMON::FORMAT::TEXTURE::D16_UNORM: return VK_FORMAT_D16_UNORM;
				case COMMON::FORMAT::TEXTURE::D32_SFLOAT: return VK_FORMAT_D32_SFLOAT;
				case COMMON::FORMAT::TEXTURE::S8_UINT: return VK_FORMAT_S8_UINT;
				case COMMON::FORMAT::TEXTURE::D16_UNORM_S8_UINT: return VK_FORMAT_D16_UNORM_S8_UINT;
				case COMMON::FORMAT::TEXTURE::D24_UNORM_S8_UINT: return VK_FORMAT_D24_UNORM_S8_UINT;
				case COMMON::FORMAT::TEXTURE::D32_SFLOAT_S8_UINT: return VK_FORMAT_D32_SFLOAT_S8_UINT;

				case COMMON::FORMAT::TEXTURE::R8_UNORM: return VK_FORMAT_R8_UNORM;
				case COMMON::FORMAT::TEXTURE::R8_SNORM: return VK_FORMAT_R8_SNORM;
				case COMMON::FORMAT::TEXTURE::R8_UINT: return VK_FORMAT_R8_UINT;
				case COMMON::FORMAT::TEXTURE::R8_SINT: return VK_FORMAT_R8_SINT;
				case COMMON::FORMAT::TEXTURE::R8G8_UNORM: return VK_FORMAT_R8G8_UNORM;
				case COMMON::FORMAT::TEXTURE::R8G8_SNORM: return VK_FORMAT_R8G8_SNORM;
				case COMMON::FORMAT::TEXTURE::R8G8_UINT: return VK_FORMAT_R8G8_UINT;
				case COMMON::FORMAT::TEXTURE::R8G8_SINT: return VK_FORMAT_R8G8_SINT;
				case COMMON::FORMAT::TEXTURE::R8G8B8_UNORM: return VK_FORMAT_R8G8B8_UNORM;
				case COMMON::FORMAT::TEXTURE::R8G8B8_SNORM: return VK_FORMAT_R8G8B8_SNORM;
				case COMMON::FORMAT::TEXTURE::R8G8B8_UINT: return VK_FORMAT_R8G8B8_UINT;
				case COMMON::FORMAT::TEXTURE::R8G8B8_SINT: return VK_FORMAT_R8G8B8_SINT;
				case COMMON::FORMAT::TEXTURE::R8G8B8A8_UNORM: return VK_FORMAT_R8G8B8A8_UNORM;
				case COMMON::FORMAT::TEXTURE::R8G8B8A8_SNORM: return VK_FORMAT_R8G8B8A8_SNORM;
				case COMMON::FORMAT::TEXTURE::R8G8B8A8_UINT: return VK_FORMAT_R8G8B8A8_UINT;
				case COMMON::FORMAT::TEXTURE::R8G8B8A8_SINT: return VK_FORMAT_R8G8B8A8_SINT;

				case COMMON::FORMAT::TEXTURE::R16_UNORM: return VK_FORMAT_R16_UNORM;
				case COMMON::FORMAT::TEXTURE::R16_SNORM: return VK_FORMAT_R16_SNORM;
				case COMMON::FORMAT::TEXTURE::R16_UINT: return VK_FORMAT_R16_UINT;
				case COMMON::FORMAT::TEXTURE::R16_SINT: return VK_FORMAT_R16_SINT;
				case COMMON::FORMAT::TEXTURE::R16_SFLOAT: return VK_FORMAT_R16_SFLOAT;
				case COMMON::FORMAT::TEXTURE::R16G16_UNORM: return VK_FORMAT_R16G16_UNORM;
				case COMMON::FORMAT::TEXTURE::R16G16_SNORM: return VK_FORMAT_R16G16_SNORM;
				case COMMON::FORMAT::TEXTURE::R16G16_UINT: return VK_FORMAT_R16G16_UINT;
				case COMMON::FORMAT::TEXTURE::R16G16_SINT: return VK_FORMAT_R16G16_SINT;
				case COMMON::FORMAT::TEXTURE::R16G16_SFLOAT: return VK_FORMAT_R16G16_SFLOAT;
				case COMMON::FORMAT::TEXTURE::R16G16B16_UNORM: return VK_FORMAT_R16G16B16_UNORM;
				case COMMON::FORMAT::TEXTURE::R16G16B16_SNORM: return VK_FORMAT_R16G16B16_SNORM;
				case COMMON::FORMAT::TEXTURE::R16G16B16_UINT: return VK_FORMAT_R16G16B16_UINT;
				case COMMON::FORMAT::TEXTURE::R16G16B16_SINT: return VK_FORMAT_R16G16B16_SINT;
				case COMMON::FORMAT::TEXTURE::R16G16B16_SFLOAT: return VK_FORMAT_R16G16B16_SFLOAT;
				case COMMON::FORMAT::TEXTURE::R16G16B16A16_UNORM: return VK_FORMAT_R16G16B16A16_UNORM;
				case COMMON::FORMAT::TEXTURE::R16G16B16A16_SNORM: return VK_FORMAT_R16G16B16A16_SNORM;
				case COMMON::FORMAT::TEXTURE::R16G16B16A16_UINT: return VK_FORMAT_R16G16B16A16_UINT;
				case COMMON::FORMAT::TEXTURE::R16G16B16A16_SINT: return VK_FORMAT_R16G16B16A16_SINT;
				case COMMON::FORMAT::TEXTURE::R16G16B16A16_SFLOAT: return VK_FORMAT_R16G16B16A16_SFLOAT;

				case COMMON::FORMAT::TEXTURE::R32_UINT: return VK_FORMAT_R32_UINT;
				case COMMON::FORMAT::TEXTURE::R32_SINT: return VK_FORMAT_R32_SINT;
				case COMMON::FORMAT::TEXTURE::R32_SFLOAT: return VK_FORMAT_R32_SFLOAT;
				case COMMON::FORMAT::TEXTURE::R32G32_UINT: return VK_FORMAT_R32G32_UINT;
				case COMMON::FORMAT::TEXTURE::R32G32_SINT: return VK_FORMAT_R32G32_SINT;
				case COMMON::FORMAT::TEXTURE::R32G32_SFLOAT: return VK_FORMAT_R32G32_SFLOAT;
				case COMMON::FORMAT::TEXTURE::R32G32B32_UINT: return VK_FORMAT_R32G32B32_UINT;
				case COMMON::FORMAT::TEXTURE::R32G32B32_SINT: return VK_FORMAT_R32G32B32_SINT;
				case COMMON::FORMAT::TEXTURE::R32G32B32_SFLOAT: return VK_FORMAT_R32G32B32_SFLOAT;
				case COMMON::FORMAT::TEXTURE::R32G32B32A32_UINT: return VK_FORMAT_R32G32B32A32_UINT;
				case COMMON::FORMAT::TEXTURE::R32G32B32A32_SINT: return VK_FORMAT_R32G32B32A32_SINT;
				case COMMON::FORMAT::TEXTURE::R32G32B32A32_SFLOAT: return VK_FORMAT_R32G32B32A32_SFLOAT;

				case COMMON::FORMAT::TEXTURE::R64_UINT: return VK_FORMAT_R64_UINT;
				case COMMON::FORMAT::TEXTURE::R64_SINT: return VK_FORMAT_R64_SINT;
				case COMMON::FORMAT::TEXTURE::R64_SFLOAT: return VK_FORMAT_R64_SFLOAT;
				case COMMON::FORMAT::TEXTURE::R64G64_UINT: return VK_FORMAT_R64G64_UINT;
				case COMMON::FORMAT::TEXTURE::R64G64_SINT: return VK_FORMAT_R64G64_SINT;
				case COMMON::FORMAT::TEXTURE::R64G64_SFLOAT: return VK_FORMAT_R64G64_SFLOAT;
				case COMMON::FORMAT::TEXTURE::R64G64B64_UINT: return VK_FORMAT_R64G64B64_UINT;
				case COMMON::FORMAT::TEXTURE::R64G64B64_SINT: return VK_FORMAT_R64G64B64_SINT;
				case COMMON::FORMAT::TEXTURE::R64G64B64_SFLOAT: return VK_FORMAT_R64G64B64_SFLOAT;
				case COMMON::FORMAT::TEXTURE::R64G64B64A64_UINT: return VK_FORMAT_R64G64B64A64_UINT;
				case COMMON::FORMAT::TEXTURE::R64G64B64A64_SINT: return VK_FORMAT_R64G64B64A64_SINT;
				case COMMON::FORMAT::TEXTURE::R64G64B64A64_SFLOAT: return VK_FORMAT_R64G64B64A64_SFLOAT;
				};


			}

			


		} // namespace VULKAN

		
	} // namespace RENDER

} // namespace FE

#endif // VULKAN__H


