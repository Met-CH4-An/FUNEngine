////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "Vulkan.h"
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

namespace FE {

	namespace CRI {

		namespace VULKAN {

			//CVKInstance &asd = CVKInstance::instance();

			namespace FUNC {

				//
				PFN_vkGetInstanceProcAddr							vkGetInstanceProcAddr = 0;
				PFN_vkGetDeviceProcAddr								vkGetDeviceProcAddr = 0;

				// vkInstance
				PFN_vkCreateInstance								vkCreateInstance = 0;
				PFN_vkDestroyInstance								vkDestroyInstance = 0;
				PFN_vkEnumerateInstanceExtensionProperties			vkEnumerateInstanceExtensionProperties = 0;
				PFN_vkEnumerateInstanceLayerProperties				vkEnumerateInstanceLayerProperties = 0;

				// VkPhysicalDevice
				PFN_vkEnumeratePhysicalDevices						vkEnumeratePhysicalDevices = 0;
				PFN_vkGetPhysicalDeviceProperties					vkGetPhysicalDeviceProperties = 0;
				PFN_vkGetPhysicalDeviceMemoryProperties				vkGetPhysicalDeviceMemoryProperties = 0;
				PFN_vkGetPhysicalDeviceQueueFamilyProperties		vkGetPhysicalDeviceQueueFamilyProperties = 0;

				// VkDevice
				PFN_vkCreateDevice									vkCreateDevice = 0;
				PFN_vkDestroyDevice									vkDestroyDevice = 0;
				PFN_vkEnumerateDeviceExtensionProperties			vkEnumerateDeviceExtensionProperties = 0;
				PFN_vkEnumerateDeviceLayerProperties				vkEnumerateDeviceLayerProperties = 0;

				// VkSurfaceKHR
				PFN_vkCreateWin32SurfaceKHR							vkCreateWin32SurfaceKHR = 0;
				PFN_vkDestroySurfaceKHR								vkDestroySurfaceKHR = 0;
				PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR		vkGetPhysicalDeviceSurfaceCapabilitiesKHR = 0;
				PFN_vkGetPhysicalDeviceSurfacePresentModesKHR		vkGetPhysicalDeviceSurfacePresentModesKHR = 0;
				PFN_vkGetPhysicalDeviceSurfaceFormatsKHR			vkGetPhysicalDeviceSurfaceFormatsKHR = 0;
				PFN_vkGetPhysicalDeviceSurfaceSupportKHR			vkGetPhysicalDeviceSurfaceSupportKHR = 0;
				PFN_vkGetPhysicalDeviceFormatProperties				vkGetPhysicalDeviceFormatProperties = 0;

				// VkSwapchainKHR
				PFN_vkCreateSwapchainKHR							vkCreateSwapchainKHR = 0;
				PFN_vkDestroySwapchainKHR							vkDestroySwapchainKHR = 0;
				PFN_vkGetSwapchainImagesKHR							vkGetSwapchainImagesKHR = 0;

				//
				PFN_vkCreateDebugReportCallbackEXT					vkCreateDebugReportCallbackEXT = 0;
				PFN_vkDestroyDebugReportCallbackEXT					vkDestroyDebugReportCallbackEXT = 0;
				PFN_vkDebugReportMessageEXT							vkDebugReportMessageEXT = 0;

				// VkDeviceMemory
				PFN_vkAllocateMemory								vkAllocateMemory = 0;
				PFN_vkFreeMemory									vkFreeMemory = 0;
				PFN_vkMapMemory										vkMapMemory = 0;
				PFN_vkUnmapMemory									vkUnmapMemory = 0;

				// VkBuffer
				PFN_vkCreateBuffer									vkCreateBuffer = 0;
				PFN_vkDestroyBuffer									vkDestroyBuffer = 0;
				PFN_vkGetBufferMemoryRequirements					vkGetBufferMemoryRequirements = 0;
				PFN_vkBindBufferMemory								vkBindBufferMemory = 0;

				// VkImage и VkImageView
				PFN_vkCreateImage									vkCreateImage = 0;
				PFN_vkDestroyImage									vkDestroyImage = 0;
				PFN_vkCreateImageView								vkCreateImageView = 0;
				PFN_vkDestroyImageView								vkDestroyImageView = 0;
				PFN_vkGetImageMemoryRequirements					vkGetImageMemoryRequirements = 0;
				PFN_vkBindImageMemory								vkBindImageMemory = 0;

				// VkCommandBuffer
				PFN_vkAllocateCommandBuffers						vkAllocateCommandBuffers = 0;
				PFN_vkFreeCommandBuffers							vkFreeCommandBuffers = 0;
				PFN_vkBeginCommandBuffer							vkBeginCommandBuffer = 0;
				PFN_vkEndCommandBuffer								vkEndCommandBuffer = 0;
				PFN_vkCmdBeginRenderPass							vkCmdBeginRenderPass = 0;
				PFN_vkCmdEndRenderPass								vkCmdEndRenderPass = 0;
				PFN_vkCmdNextSubpass								vkCmdNextSubpass = 0;
				PFN_vkCmdBindPipeline								vkCmdBindPipeline = 0;
				PFN_vkCmdSetViewport								vkCmdSetViewport = 0;
				PFN_vkCmdSetScissor									vkCmdSetScissor = 0;
				PFN_vkCmdBindDescriptorSets							vkCmdBindDescriptorSets = 0;
				PFN_vkCmdBindIndexBuffer							vkCmdBindIndexBuffer = 0;
				PFN_vkCmdBindVertexBuffers							vkCmdBindVertexBuffers = 0;
				PFN_vkCmdDrawIndexed								vkCmdDrawIndexed = 0;
				PFN_vkCmdPipelineBarrier							vkCmdPipelineBarrier = 0;
				PFN_vkCmdCopyBuffer									vkCmdCopyBuffer = 0;

				// Pipeline
				PFN_vkCreateShaderModule							vkCreateShaderModule = 0;
				PFN_vkDestroyShaderModule							vkDestroyShaderModule = 0;
				PFN_vkCreateDescriptorSetLayout						vkCreateDescriptorSetLayout = 0;
				PFN_vkDestroyDescriptorSetLayout					vkDestroyDescriptorSetLayout = 0;
				PFN_vkCreatePipelineLayout							vkCreatePipelineLayout = 0;
				PFN_vkDestroyPipelineLayout							vkDestroyPipelineLayout = 0;
				PFN_vkCreatePipelineCache							vkCreatePipelineCache = 0;
				PFN_vkDestroyPipelineCache							vkDestroyPipelineCache = 0;
				PFN_vkCreateGraphicsPipelines						vkCreateGraphicsPipelines = 0;
				PFN_vkDestroyPipeline								vkDestroyPipeline = 0;

				// остальное		
				PFN_vkCreateRenderPass								vkCreateRenderPass = 0;
				PFN_vkCreateFramebuffer								vkCreateFramebuffer = 0;
				PFN_vkCreateDescriptorPool							vkCreateDescriptorPool = 0;				
				PFN_vkAllocateDescriptorSets						vkAllocateDescriptorSets = 0;
				PFN_vkUpdateDescriptorSets							vkUpdateDescriptorSets = 0;	
				PFN_vkGetDeviceQueue								vkGetDeviceQueue = 0;
				PFN_vkQueueSubmit									vkQueueSubmit = 0;
				PFN_vkDeviceWaitIdle								vkDeviceWaitIdle = 0;
				PFN_vkCreateSemaphore								vkCreateSemaphore = 0;
				PFN_vkCreateCommandPool								vkCreateCommandPool = 0;
				PFN_vkAcquireNextImageKHR							vkAcquireNextImageKHR = 0;
				PFN_vkQueuePresentKHR								vkQueuePresentKHR = 0;
				PFN_vkCmdExecuteCommands							vkCmdExecuteCommands = 0;

			} // namespace FUNC

		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE

