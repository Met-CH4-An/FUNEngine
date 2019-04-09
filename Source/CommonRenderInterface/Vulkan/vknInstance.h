#ifndef VK_INSTANCE__H
#define VK_INSTANCE__H
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
#include "Vulkan.h"
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////

namespace FE {

	namespace CRI {

		namespace VULKAN {

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Исключение вызываемое при неудачном создании инстанса.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			class e_vulkan_common_instance_create_fail : public e_vulkan_common {};



			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*! \brief Коды ошибок.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			enum VK_INSTANCE_ERROR : int32_t {

			}; // enum VK_INSTANCE_ERROR


			
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief ИНфомрация для создания.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			struct VK_INSTANCE_CREATE_INFO {

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Тип
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				enum class TYPE {
					RELEASE,
					DEBUG
				};

				TYPE			m_Type;

			}; // struct VK_INSTANCE_CREATE_INFO



			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*! \brief Инстанс вулкана.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			class CVKInstance {

			public:

				//
				PFN_vkGetInstanceProcAddr							vkGetInstanceProcAddr;
				PFN_vkGetDeviceProcAddr								vkGetDeviceProcAddr;

				// vkInstance
				PFN_vkCreateInstance								vkCreateInstance;
				PFN_vkDestroyInstance								vkDestroyInstance;
				PFN_vkEnumerateInstanceExtensionProperties			vkEnumerateInstanceExtensionProperties;
				PFN_vkEnumerateInstanceLayerProperties				vkEnumerateInstanceLayerProperties;

				// VkPhysicaldevice
				PFN_vkEnumeratePhysicalDevices						vkEnumeratePhysicalDevices;
				PFN_vkGetPhysicalDeviceProperties					vkGetPhysicalDeviceProperties;
				PFN_vkGetPhysicalDeviceMemoryProperties				vkGetPhysicalDeviceMemoryProperties;
				PFN_vkGetPhysicalDeviceQueueFamilyProperties		vkGetPhysicalDeviceQueueFamilyProperties;

				// VkDevice
				PFN_vkCreateDevice									vkCreateDevice;
				PFN_vkDestroyDevice									vkDestroyDevice;
				PFN_vkEnumerateDeviceExtensionProperties			vkEnumerateDeviceExtensionProperties;
				PFN_vkEnumerateDeviceLayerProperties				vkEnumerateDeviceLayerProperties;

				// VkSurfaceKHR
				PFN_vkCreateWin32SurfaceKHR							vkCreateWin32SurfaceKHR;
				PFN_vkDestroySurfaceKHR								vkDestroySurfaceKHR;
				PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR		vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
				PFN_vkGetPhysicalDeviceSurfacePresentModesKHR		vkGetPhysicalDeviceSurfacePresentModesKHR;
				PFN_vkGetPhysicalDeviceSurfaceFormatsKHR			vkGetPhysicalDeviceSurfaceFormatsKHR;
				PFN_vkGetPhysicalDeviceSurfaceSupportKHR			vkGetPhysicalDeviceSurfaceSupportKHR;
				PFN_vkGetPhysicalDeviceFormatProperties				vkGetPhysicalDeviceFormatProperties;

				// VkSwapchainKHR
				PFN_vkCreateSwapchainKHR							vkCreateSwapchainKHR;
				PFN_vkDestroySwapchainKHR							vkDestroySwapchainKHR;
				PFN_vkGetSwapchainImagesKHR							vkGetSwapchainImagesKHR;

				// VkDeviceMemory
				PFN_vkAllocateMemory								vkAllocateMemory;
				PFN_vkFreeMemory									vkFreeMemory;
				PFN_vkMapMemory										vkMapMemory;
				PFN_vkUnmapMemory									vkUnmapMemory;

				// VkBuffer
				PFN_vkCreateBuffer									vkCreateBuffer;
				PFN_vkDestroyBuffer									vkDestroyBuffer;
				PFN_vkGetBufferMemoryRequirements					vkGetBufferMemoryRequirements;
				PFN_vkBindBufferMemory								vkBindBufferMemory;

				// VkImage и VkImageView
				PFN_vkCreateImage									vkCreateImage;
				PFN_vkDestroyImage									vkDestroyImage;
				PFN_vkCreateImageView								vkCreateImageView;
				PFN_vkDestroyImageView								vkDestroyImageView;
				PFN_vkGetImageMemoryRequirements					vkGetImageMemoryRequirements;
				PFN_vkBindImageMemory								vkBindImageMemory;

				// VkCommandBuffer
				PFN_vkAllocateCommandBuffers						vkAllocateCommandBuffers;
				PFN_vkFreeCommandBuffers							vkFreeCommandBuffers;
				PFN_vkBeginCommandBuffer							vkBeginCommandBuffer;
				PFN_vkEndCommandBuffer								vkEndCommandBuffer;
				PFN_vkCmdBeginRenderPass							vkCmdBeginRenderPass;
				PFN_vkCmdEndRenderPass								vkCmdEndRenderPass;
				PFN_vkCmdNextSubpass								vkCmdNextSubpass;
				PFN_vkCmdBindPipeline								vkCmdBindPipeline;
				PFN_vkCmdSetViewport								vkCmdSetViewport;
				PFN_vkCmdSetScissor									vkCmdSetScissor;
				PFN_vkCmdBindDescriptorSets							vkCmdBindDescriptorSets;
				PFN_vkCmdBindIndexBuffer							vkCmdBindIndexBuffer;
				PFN_vkCmdBindVertexBuffers							vkCmdBindVertexBuffers;
				PFN_vkCmdDraw										vkCmdDraw;
				PFN_vkCmdDrawIndexed								vkCmdDrawIndexed;
				PFN_vkCmdPipelineBarrier							vkCmdPipelineBarrier;
				PFN_vkCmdCopyBuffer									vkCmdCopyBuffer;

				// Pipeline
				PFN_vkCreateShaderModule							vkCreateShaderModule;
				PFN_vkDestroyShaderModule							vkDestroyShaderModule;
				PFN_vkCreateDescriptorSetLayout						vkCreateDescriptorSetLayout;
				PFN_vkDestroyDescriptorSetLayout					vkDestroyDescriptorSetLayout;
				PFN_vkCreatePipelineLayout							vkCreatePipelineLayout;
				PFN_vkDestroyPipelineLayout							vkDestroyPipelineLayout;
				PFN_vkCreatePipelineCache							vkCreatePipelineCache;
				PFN_vkDestroyPipelineCache							vkDestroyPipelineCache;
				PFN_vkCreateGraphicsPipelines						vkCreateGraphicsPipelines;
				PFN_vkDestroyPipeline								vkDestroyPipeline;

				// debug
				PFN_vkCreateDebugReportCallbackEXT					vkCreateDebugReportCallbackEXT;
				PFN_vkDestroyDebugReportCallbackEXT					vkDestroyDebugReportCallbackEXT;
				PFN_vkDebugReportMessageEXT							vkDebugReportMessageEXT;

				// остальное
				PFN_vkCreateRenderPass								vkCreateRenderPass;
				PFN_vkCreateFramebuffer								vkCreateFramebuffer;
				PFN_vkCreateDescriptorPool							vkCreateDescriptorPool;
				PFN_vkAllocateDescriptorSets						vkAllocateDescriptorSets;
				PFN_vkUpdateDescriptorSets							vkUpdateDescriptorSets;
				PFN_vkGetDeviceQueue								vkGetDeviceQueue;
				PFN_vkQueueSubmit									vkQueueSubmit;
				PFN_vkDeviceWaitIdle								vkDeviceWaitIdle;
				PFN_vkCreateSemaphore								vkCreateSemaphore;
				PFN_vkCreateCommandPool								vkCreateCommandPool;
				PFN_vkAcquireNextImageKHR							vkAcquireNextImageKHR;
				PFN_vkQueuePresentKHR								vkQueuePresentKHR;
				PFN_vkCmdExecuteCommands							vkCmdExecuteCommands;

			public:

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Конструктор.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				CVKInstance();

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Деструктор.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				~CVKInstance();

			public:

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Создание.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void create(const VK_INSTANCE_CREATE_INFO *createInfo);

			public:

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*! \brief Получить физические устройства.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				const VKDeviceArr& getPhysicalDevices(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить VkInstance.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				VkInstance getInstance(void) const;				

			// VKLoader.cpp
			private:
				
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void createPlatform(void);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void setupExtensionLayer(void);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void loadFunction(void);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void setupDebug();
				
				static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(
					VkDebugReportFlagsEXT flags,
					VkDebugReportObjectTypeEXT type,
					uint64_t src,
					size_t location,
					int32_t code,
					const char *layer_prefix,
					const char *msg,
					void *data) {
				
					if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT) {

						std::cout << "DEBUG ERROR:\t" << msg << "\n";
					}

					if (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT) {

						std::cout << "DEBUG WARNING:\t" << msg << "\n";
					}

					if (flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT) {

						std::cout << "DEBUG:\t" << msg << "\n";
					}

					return false;
				}
			// данные
			private:

				VK_INSTANCE_CREATE_INFO		m_CreateInfo;	
				VKDeviceArr					m_Devices;
				CVKExtensionArr				m_SupportExtensions;
				CVKLayerArr					m_SupportLayers;

				VkInstance					m_VkInstance;				
				VkDebugReportCallbackEXT	m_VkDebugReportCallback;
				
			}; // class CVKInstance		

		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE

#include "vknInstance.hpp"

#endif // VK_INSTANCE__H