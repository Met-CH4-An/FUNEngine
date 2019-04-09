////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "vknInstance.h"
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
#include "vknDevice.h"

//==============================================================
//==============================================================

#define VK_ASSERT_INSTANCE_EXE(function) {\
	ASSERT_EX((function),==,VK_SUCCESS, \
		"Failed to execute function Vulkan", \
		throw e_vulkan_common_instance_create_fail());\
}

//==============================================================
//==============================================================

#define VK_ASSERT_INSTANCE_LOAD_FUNCTION(function) {\
	ASSERT_EX(function, !=, 0, "Failed to get functions Vulkan.", throw e_vulkan_common_instance_create_fail());\
}

//==============================================================
//==============================================================

namespace FE {

	namespace CRI {

		namespace VULKAN {

			//==============================================================
			//==============================================================

			CVKInstance::CVKInstance()
				: m_CreateInfo(),
				m_Devices(),
				m_SupportExtensions(),
				m_SupportLayers(),
				m_VkInstance(nullptr),
				m_VkDebugReportCallback(0) {
			}

			//==============================================================
			//==============================================================

			CVKInstance::~CVKInstance() {

				for (auto &it : m_Devices) {

					delete it;
				}

				vkDestroyDebugReportCallbackEXT(m_VkInstance, m_VkDebugReportCallback, nullptr);

				vkDestroyInstance(m_VkInstance, nullptr);
				
				m_CreateInfo = {};
				m_Devices = {};
				m_SupportExtensions = {};
				m_SupportLayers = {};
				m_VkInstance = nullptr;
				m_VkDebugReportCallback = 0;
				
			}

			//==============================================================
			//==============================================================

			void CVKInstance::create(const VK_INSTANCE_CREATE_INFO *createInfo) {		

				m_CreateInfo = *createInfo;

				// платформозависимое создание
				createPlatform();

				// 
				vkCreateInstance = (PFN_vkCreateInstance)(vkGetInstanceProcAddr(nullptr, "vkCreateInstance"));
				vkEnumerateInstanceExtensionProperties = (PFN_vkEnumerateInstanceExtensionProperties)(vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceExtensionProperties"));
				vkEnumerateInstanceLayerProperties = (PFN_vkEnumerateInstanceLayerProperties)(vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceLayerProperties"));

				// ~~~~~~~~~~~~~~~~
				// получение данных о доступных расширениях инстанса
				// ~~~~~~~~~~~~~~~~

				// количество доступных расширений инстанса
				uint32_t _extensionCount = 0;
				VK_ASSERT_INSTANCE_EXE(vkEnumerateInstanceExtensionProperties(NULL, &_extensionCount, NULL));

				// данные о доступных расширенияях инстанса
				VkExtensionPropertiesArr _supportExtensions(_extensionCount);
				VK_ASSERT_INSTANCE_EXE(vkEnumerateInstanceExtensionProperties(NULL, &_extensionCount, _supportExtensions.data()));
			
				// перебираем доступные расширения
				for (const auto& itSupportExtensions : _supportExtensions) {
					
					CVKExtension _vknExtension = {};

					_vknExtension.m_VkExtension = itSupportExtensions;
					_vknExtension.m_Status = false;

					m_SupportExtensions.push_back(_vknExtension);

				} // for (const auto& itExtensionProps

				// ~~~~~~~~~~~~~~~~
				// получение данных о доступных слоях инстанса
				// ~~~~~~~~~~~~~~~~

				// количество доступных слоёв инстанса
				uint32_t _layerCount = 0;
				VK_ASSERT_INSTANCE_EXE(vkEnumerateInstanceLayerProperties(&_layerCount, NULL));
												
				// данные о доступных слоях инстанса
				VkLayerPropertiesArr _supportLayers(_layerCount);
				VK_ASSERT_INSTANCE_EXE(vkEnumerateInstanceLayerProperties(&_layerCount, _supportLayers.data()));

				// перебираем слои
				for (const auto& itSupportLayers : _supportLayers) {

					CVKLayer _vknLayer = {};

					_vknLayer.m_VkLayer = itSupportLayers;
					_vknLayer.m_Status = false;

					m_SupportLayers.push_back(_vknLayer);

				} // for (const auto& itLayerProps 

				// ~~~~~~~~~~~~~~~~
				// setup
				// ~~~~~~~~~~~~~~~~

				setupExtensionLayer();

				// ~~~~~~~~~~~~~~~~
				// get extension names
				// ~~~~~~~~~~~~~~~~

				std::vector<const char*> _extensionNameEnables;
				for (auto& itSupportExtension : m_SupportExtensions) {

					if (itSupportExtension.m_Status) {

						_extensionNameEnables.push_back(itSupportExtension.m_VkExtension.extensionName);
					}

				} // for (const auto& itExtension

				// ~~~~~~~~~~~~~~~~
				// get layer names
				// ~~~~~~~~~~~~~~~~

				std::vector<const char*> _layerNameEnables;
				for (auto& itSupportLayer : m_SupportLayers) {

					if (itSupportLayer.m_Status) {
						
						_layerNameEnables.push_back(itSupportLayer.m_VkLayer.layerName);
					}

				} // for (const auto& itLayer : _supportLayers)

				// ~~~~~~~~~~~~~~~~
				// создаём instance
				// ~~~~~~~~~~~~~~~~

				// описываем наше приложение (необязательно, но :) {
				VkApplicationInfo appInfo = {};

				appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
				appInfo.pNext = nullptr;
				appInfo.pApplicationName = "FANRender";
				appInfo.applicationVersion = 1;
				appInfo.pEngineName = "FANRender";
				appInfo.engineVersion = 1;
				appInfo.apiVersion = VK_API_VERSION_1_0;
				
				// описываем создаваемый instance
				VkInstanceCreateInfo instanceCreateInfo = {};

				instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
				instanceCreateInfo.pNext = NULL;
				instanceCreateInfo.flags = 0;
				instanceCreateInfo.pApplicationInfo = &appInfo;
				instanceCreateInfo.enabledLayerCount = (uint32_t)_layerNameEnables.size();
				instanceCreateInfo.ppEnabledLayerNames = _layerNameEnables.data();
				instanceCreateInfo.enabledExtensionCount = (uint32_t)_extensionNameEnables.size();
				instanceCreateInfo.ppEnabledExtensionNames = _extensionNameEnables.data();
				 
				// создаём инстанс
				VK_ASSERT_INSTANCE_EXE(vkCreateInstance(&instanceCreateInfo, nullptr, &m_VkInstance));

				// ~~~~~~~~~~~~~~~~
				// load function
				// ~~~~~~~~~~~~~~~~

				loadFunction();

				// ~~~~~~~~~~~~~~~~
				// ~~~~~~~~~~~~~~~~

				uint32_t				_physDeviceCount = 0;
				VkPhysicalDeviceArr		_physDevices;
				
				// количество физических устройств
				VK_ASSERT_INSTANCE_EXE(vkEnumeratePhysicalDevices(m_VkInstance, &_physDeviceCount, nullptr));
				
				_physDevices.resize(_physDeviceCount);

				// список физических устройств
				VK_ASSERT_INSTANCE_EXE(vkEnumeratePhysicalDevices(m_VkInstance, &_physDeviceCount, _physDevices.data()));
				
				// свойства для всех найденых физических устройств
				for (const auto &itPhysDevice : _physDevices) {

					VKDevice _vknNewDevice = new CVKDevice(this);

					VK_DEVICE_CREATE_INFO _vknNewDeviceCI = {};
					_vknNewDeviceCI.m_VkPhysicalDevice = itPhysDevice;

					_vknNewDevice->create(&_vknNewDeviceCI);

					m_Devices.push_back(_vknNewDevice);

				} // for (const auto &itPhysDevice : _physDevices)

				setupDebug();
												
			}

			//==============================================================
			//==============================================================

			const VKDeviceArr& CVKInstance::getPhysicalDevices(void) const {

				return m_Devices;
				
			}

			//==============================================================
			//==============================================================

			VkInstance CVKInstance::getInstance(void) const {

				return m_VkInstance;
			}

			//==============================================================
			//==============================================================

			void CVKInstance::setupExtensionLayer(void) {

				// ~~~~~~~~~~~~~~~~
				// extensions
				// ~~~~~~~~~~~~~~~~

				for (auto& itSupportExtension : m_SupportExtensions) {

					if (std::strcmp(itSupportExtension.m_VkExtension.extensionName, VK_KHR_SURFACE_EXTENSION_NAME) == 0 ||
						std::strcmp(itSupportExtension.m_VkExtension.extensionName, VK_KHR_WIN32_SURFACE_EXTENSION_NAME) == 0) {

						itSupportExtension.m_Status = true;

					}

					if (m_CreateInfo.m_Type == VK_INSTANCE_CREATE_INFO::TYPE::DEBUG) {

						if (std::strcmp(itSupportExtension.m_VkExtension.extensionName, "vk_LAYER_LUNARG_threading") == 0 ||
							std::strcmp(itSupportExtension.m_VkExtension.extensionName, "vk_LAYER_LUNARG_draw_state") == 0 ||
							std::strcmp(itSupportExtension.m_VkExtension.extensionName, "vk_LAYER_LUNARG_image") == 0 ||
							std::strcmp(itSupportExtension.m_VkExtension.extensionName, "vk_LAYER_LUNARG_mem_tracker") == 0 ||
							std::strcmp(itSupportExtension.m_VkExtension.extensionName, "vk_LAYER_LUNARG_object_tracker") == 0 ||
							std::strcmp(itSupportExtension.m_VkExtension.extensionName, "vk_LAYER_LUNARG_param_checker") == 0 ||
							std::strcmp(itSupportExtension.m_VkExtension.extensionName, "vk_LAYER_LUNARG_swapchain") == 0 ||
							std::strcmp(itSupportExtension.m_VkExtension.extensionName, VK_EXT_DEBUG_REPORT_EXTENSION_NAME) == 0) {

							itSupportExtension.m_Status = true;

						}

						// выводим информацию о расширениях
						std::cout << "\t" << itSupportExtension.m_VkExtension.extensionName << " (" << (itSupportExtension.m_Status ? "enable" : "disable") << ")"
							<< "\n\t\t" << "name:\t\t\t\t\t\t" << itSupportExtension.m_VkExtension.extensionName
							<< "\n\t\t" << "spec version:\t\t\t\t\t" << VK_VERSION_MAJOR(itSupportExtension.m_VkExtension.specVersion) << "." << VK_VERSION_MINOR(itSupportExtension.m_VkExtension.specVersion) << "." << VK_VERSION_PATCH(itSupportExtension.m_VkExtension.specVersion)
							<< std::endl;

					} // if (m_CreateInfo.m_Type == VK_INSTANCE_CREATE_INFO::TYPE::DEBUG)

				} // for (auto& itSupportExtension

				// ~~~~~~~~~~~~~~~~
				// layers
				// ~~~~~~~~~~~~~~~~

				for (auto& itSupportLayer : m_SupportLayers) {

					/*if (std::strcmp(itSupportLayer.m_VkLayer.layerName, VK_KHR_SURFACE_EXTENSION_NAME) == 0 ||
						std::strcmp(itSupportLayer.m_VkLayer.layerName, VK_KHR_WIN32_SURFACE_EXTENSION_NAME) == 0) {

						itSupportLayer.m_Status = true;

					}*/

					if (m_CreateInfo.m_Type == VK_INSTANCE_CREATE_INFO::TYPE::DEBUG) {

						if (std::strcmp(itSupportLayer.m_VkLayer.layerName, "vk_LAYER_LUNARG_threading") == 0 ||
							std::strcmp(itSupportLayer.m_VkLayer.layerName, "vk_LAYER_LUNARG_parameter_validation") == 0 ||
							std::strcmp(itSupportLayer.m_VkLayer.layerName, "vk_LAYER_LUNARG_device_limits") == 0 ||
							std::strcmp(itSupportLayer.m_VkLayer.layerName, "vk_LAYER_LUNARG_core_validation") == 0 ||
							std::strcmp(itSupportLayer.m_VkLayer.layerName, "vk_LAYER_LUNARG_draw_state") == 0 ||
							std::strcmp(itSupportLayer.m_VkLayer.layerName, "vk_LAYER_LUNARG_image") == 0 ||
							std::strcmp(itSupportLayer.m_VkLayer.layerName, "vk_LAYER_LUNARG_mem_tracker") == 0 ||
							std::strcmp(itSupportLayer.m_VkLayer.layerName, "vk_LAYER_LUNARG_object_tracker") == 0 ||
							std::strcmp(itSupportLayer.m_VkLayer.layerName, "vk_LAYER_LUNARG_param_checker") == 0 ||
							std::strcmp(itSupportLayer.m_VkLayer.layerName, "vk_LAYER_LUNARG_swapchain") == 0 ||
							std::strcmp(itSupportLayer.m_VkLayer.layerName, "vk_LAYER_LUNARG_standard_validation") == 0) {

							itSupportLayer.m_Status = true;

						}

						// выводим информацию о расширениях
						std::cout << "\t" << itSupportLayer.m_VkLayer.layerName << " (" << (itSupportLayer.m_Status ? "enable" : "disable") << ")"
							<< "\n\t\t" << "name:\t\t\t\t\t\t" << itSupportLayer.m_VkLayer.layerName
							<< "\n\t\t" << "spec version:\t\t\t\t\t" << VK_VERSION_MAJOR(itSupportLayer.m_VkLayer.specVersion) << "." << VK_VERSION_MINOR(itSupportLayer.m_VkLayer.specVersion) << "." << VK_VERSION_PATCH(itSupportLayer.m_VkLayer.specVersion)
							<< std::endl;

					} // if (m_CreateInfo.m_Type == VK_INSTANCE_CREATE_INFO::TYPE::DEBUG)

				} // for (const auto& itLayerProps 

			}

			//==============================================================
			//==============================================================

			void CVKInstance::loadFunction(void) {
				
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkDestroyInstance = (PFN_vkDestroyInstance)vkGetInstanceProcAddr(m_VkInstance, "vkDestroyInstance"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr)vkGetInstanceProcAddr(m_VkInstance, "vkGetDeviceProcAddr"));

				// VkPhysicalDevice
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkEnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices)vkGetInstanceProcAddr(m_VkInstance, "vkEnumeratePhysicalDevices"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties)vkGetInstanceProcAddr(m_VkInstance, "vkGetPhysicalDeviceProperties"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkGetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties)vkGetInstanceProcAddr(m_VkInstance, "vkGetPhysicalDeviceMemoryProperties"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkGetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties)vkGetInstanceProcAddr(m_VkInstance, "vkGetPhysicalDeviceQueueFamilyProperties"));

				// VkDevice
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCreateDevice = (PFN_vkCreateDevice)vkGetInstanceProcAddr(m_VkInstance, "vkCreateDevice"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkDestroyDevice = (PFN_vkDestroyDevice)vkGetInstanceProcAddr(m_VkInstance, "vkDestroyDevice"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkEnumerateDeviceExtensionProperties = (PFN_vkEnumerateDeviceExtensionProperties)vkGetInstanceProcAddr(m_VkInstance, "vkEnumerateDeviceExtensionProperties"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkEnumerateDeviceLayerProperties = (PFN_vkEnumerateDeviceLayerProperties)vkGetInstanceProcAddr(m_VkInstance, "vkEnumerateDeviceLayerProperties"));

				// VkSurfaceKHR
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(m_VkInstance, "vkCreateWin32SurfaceKHR"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkDestroySurfaceKHR = (PFN_vkDestroySurfaceKHR)vkGetInstanceProcAddr(m_VkInstance, "vkDestroySurfaceKHR"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkGetPhysicalDeviceSurfaceCapabilitiesKHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR)vkGetInstanceProcAddr(m_VkInstance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkGetPhysicalDeviceSurfacePresentModesKHR = (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR)vkGetInstanceProcAddr(m_VkInstance, "vkGetPhysicalDeviceSurfacePresentModesKHR"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkGetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR)vkGetInstanceProcAddr(m_VkInstance, "vkGetPhysicalDeviceSurfaceFormatsKHR"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkGetPhysicalDeviceSurfaceSupportKHR = (PFN_vkGetPhysicalDeviceSurfaceSupportKHR)vkGetInstanceProcAddr(m_VkInstance, "vkGetPhysicalDeviceSurfaceSupportKHR"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkGetPhysicalDeviceFormatProperties = (PFN_vkGetPhysicalDeviceFormatProperties)vkGetInstanceProcAddr(m_VkInstance, "vkGetPhysicalDeviceFormatProperties"));

				// VkSwapchainKHR
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCreateSwapchainKHR = (PFN_vkCreateSwapchainKHR)vkGetInstanceProcAddr(m_VkInstance, "vkCreateSwapchainKHR"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkDestroySwapchainKHR = (PFN_vkDestroySwapchainKHR)vkGetInstanceProcAddr(m_VkInstance, "vkDestroySwapchainKHR"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkGetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR)vkGetInstanceProcAddr(m_VkInstance, "vkGetSwapchainImagesKHR"));

				// VkDeviceMemory
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkAllocateMemory = (PFN_vkAllocateMemory)vkGetInstanceProcAddr(m_VkInstance, "vkAllocateMemory"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkFreeMemory = (PFN_vkFreeMemory)vkGetInstanceProcAddr(m_VkInstance, "vkFreeMemory"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkMapMemory = (PFN_vkMapMemory)vkGetInstanceProcAddr(m_VkInstance, "vkMapMemory"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkUnmapMemory = (PFN_vkUnmapMemory)vkGetInstanceProcAddr(m_VkInstance, "vkUnmapMemory"));

				// VkBuffer
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCreateBuffer = (PFN_vkCreateBuffer)vkGetInstanceProcAddr(m_VkInstance, "vkCreateBuffer"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkDestroyBuffer = (PFN_vkDestroyBuffer)vkGetInstanceProcAddr(m_VkInstance, "vkDestroyBuffer"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkGetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements)vkGetInstanceProcAddr(m_VkInstance, "vkGetBufferMemoryRequirements"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkBindBufferMemory = (PFN_vkBindBufferMemory)vkGetInstanceProcAddr(m_VkInstance, "vkBindBufferMemory"));

				// VkImage и VkImageView
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCreateImage = (PFN_vkCreateImage)vkGetInstanceProcAddr(m_VkInstance, "vkCreateImage"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkDestroyImage = (PFN_vkDestroyImage)vkGetInstanceProcAddr(m_VkInstance, "vkDestroyImage"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCreateImageView = (PFN_vkCreateImageView)vkGetInstanceProcAddr(m_VkInstance, "vkCreateImageView"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkDestroyImageView = (PFN_vkDestroyImageView)vkGetInstanceProcAddr(m_VkInstance, "vkDestroyImageView"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkGetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements)vkGetInstanceProcAddr(m_VkInstance, "vkGetImageMemoryRequirements"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkBindImageMemory = (PFN_vkBindImageMemory)vkGetInstanceProcAddr(m_VkInstance, "vkBindImageMemory"));

				// VkCommandBuffer
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers)vkGetInstanceProcAddr(m_VkInstance, "vkAllocateCommandBuffers"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkFreeCommandBuffers = (PFN_vkFreeCommandBuffers)vkGetInstanceProcAddr(m_VkInstance, "vkFreeCommandBuffers"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer)vkGetInstanceProcAddr(m_VkInstance, "vkBeginCommandBuffer"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkEndCommandBuffer = (PFN_vkEndCommandBuffer)vkGetInstanceProcAddr(m_VkInstance, "vkEndCommandBuffer"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass)vkGetInstanceProcAddr(m_VkInstance, "vkCmdBeginRenderPass"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass)vkGetInstanceProcAddr(m_VkInstance, "vkCmdEndRenderPass"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCmdNextSubpass = (PFN_vkCmdNextSubpass)vkGetInstanceProcAddr(m_VkInstance, "vkCmdNextSubpass"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCmdBindPipeline = (PFN_vkCmdBindPipeline)vkGetInstanceProcAddr(m_VkInstance, "vkCmdBindPipeline"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCmdSetViewport = (PFN_vkCmdSetViewport)vkGetInstanceProcAddr(m_VkInstance, "vkCmdSetViewport"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCmdSetScissor = (PFN_vkCmdSetScissor)vkGetInstanceProcAddr(m_VkInstance, "vkCmdSetScissor"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets)vkGetInstanceProcAddr(m_VkInstance, "vkCmdBindDescriptorSets"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer)vkGetInstanceProcAddr(m_VkInstance, "vkCmdBindIndexBuffer"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers)vkGetInstanceProcAddr(m_VkInstance, "vkCmdBindVertexBuffers"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCmdDraw = (PFN_vkCmdDraw)vkGetInstanceProcAddr(m_VkInstance, "vkCmdDraw"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCmdDrawIndexed = (PFN_vkCmdDrawIndexed)vkGetInstanceProcAddr(m_VkInstance, "vkCmdDrawIndexed"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCmdPipelineBarrier = (PFN_vkCmdPipelineBarrier)vkGetInstanceProcAddr(m_VkInstance, "vkCmdPipelineBarrier"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCmdCopyBuffer = (PFN_vkCmdCopyBuffer)vkGetInstanceProcAddr(m_VkInstance, "vkCmdCopyBuffer"));

				// Pipeline
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCreateShaderModule = (PFN_vkCreateShaderModule)vkGetInstanceProcAddr(m_VkInstance, "vkCreateShaderModule"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkDestroyShaderModule = (PFN_vkDestroyShaderModule)vkGetInstanceProcAddr(m_VkInstance, "vkDestroyShaderModule"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCreateDescriptorSetLayout = (PFN_vkCreateDescriptorSetLayout)vkGetInstanceProcAddr(m_VkInstance, "vkCreateDescriptorSetLayout"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkDestroyDescriptorSetLayout = (PFN_vkDestroyDescriptorSetLayout)vkGetInstanceProcAddr(m_VkInstance, "vkDestroyDescriptorSetLayout"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout)vkGetInstanceProcAddr(m_VkInstance, "vkCreatePipelineLayout"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout)vkGetInstanceProcAddr(m_VkInstance, "vkDestroyPipelineLayout"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCreatePipelineCache = (PFN_vkCreatePipelineCache)vkGetInstanceProcAddr(m_VkInstance, "vkCreatePipelineCache"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkDestroyPipelineCache = (PFN_vkDestroyPipelineCache)vkGetInstanceProcAddr(m_VkInstance, "vkDestroyPipelineCache"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines)vkGetInstanceProcAddr(m_VkInstance, "vkCreateGraphicsPipelines"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkDestroyPipeline = (PFN_vkDestroyPipeline)vkGetInstanceProcAddr(m_VkInstance, "vkDestroyPipeline"));

				// остальное			
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCreateRenderPass = (PFN_vkCreateRenderPass)vkGetInstanceProcAddr(m_VkInstance, "vkCreateRenderPass"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCreateFramebuffer = (PFN_vkCreateFramebuffer)vkGetInstanceProcAddr(m_VkInstance, "vkCreateFramebuffer"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCreateDescriptorPool = (PFN_vkCreateDescriptorPool)vkGetInstanceProcAddr(m_VkInstance, "vkCreateDescriptorPool"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkAllocateDescriptorSets = (PFN_vkAllocateDescriptorSets)vkGetInstanceProcAddr(m_VkInstance, "vkAllocateDescriptorSets"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkUpdateDescriptorSets = (PFN_vkUpdateDescriptorSets)vkGetInstanceProcAddr(m_VkInstance, "vkUpdateDescriptorSets"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkGetDeviceQueue = (PFN_vkGetDeviceQueue)vkGetInstanceProcAddr(m_VkInstance, "vkGetDeviceQueue"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkQueueSubmit = (PFN_vkQueueSubmit)vkGetInstanceProcAddr(m_VkInstance, "vkQueueSubmit"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkDeviceWaitIdle = (PFN_vkDeviceWaitIdle)vkGetInstanceProcAddr(m_VkInstance, "vkDeviceWaitIdle"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCreateSemaphore = (PFN_vkCreateSemaphore)vkGetInstanceProcAddr(m_VkInstance, "vkCreateSemaphore"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCreateCommandPool = (PFN_vkCreateCommandPool)vkGetInstanceProcAddr(m_VkInstance, "vkCreateCommandPool"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkAcquireNextImageKHR = (PFN_vkAcquireNextImageKHR)vkGetInstanceProcAddr(m_VkInstance, "vkAcquireNextImageKHR"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkQueuePresentKHR = (PFN_vkQueuePresentKHR)vkGetInstanceProcAddr(m_VkInstance, "vkQueuePresentKHR"));
				VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCmdExecuteCommands = (PFN_vkCmdExecuteCommands)vkGetInstanceProcAddr(m_VkInstance, "vkCmdExecuteCommands"));

				if (m_CreateInfo.m_Type == VK_INSTANCE_CREATE_INFO::TYPE::DEBUG) {

					VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(m_VkInstance, "vkCreateDebugReportCallbackEXT"));
					VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(m_VkInstance, "vkDestroyDebugReportCallbackEXT"));
					VK_ASSERT_INSTANCE_LOAD_FUNCTION(vkDebugReportMessageEXT = (PFN_vkDebugReportMessageEXT)vkGetInstanceProcAddr(m_VkInstance, "vkDebugReportMessageEXT"));

				}

			}

			//==============================================================
			//==============================================================
			
			void CVKInstance::setupDebug(void) {

				if (m_CreateInfo.m_Type != VK_INSTANCE_CREATE_INFO::TYPE::DEBUG) return;

				// ~~~~~~~~~~~~~~~~
				// info gpu
				// ~~~~~~~~~~~~~~~~

				// ~~~~~~~~~~~~~~~~
				// callback
				// ~~~~~~~~~~~~~~~~

				VkDebugReportCallbackCreateInfoEXT _debugCI = {};
				_debugCI.sType = VkStructureType::VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
				_debugCI.flags = VK_DEBUG_REPORT_INFORMATION_BIT_EXT |
					VK_DEBUG_REPORT_WARNING_BIT_EXT |
					VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
					VK_DEBUG_REPORT_ERROR_BIT_EXT |
					VK_DEBUG_REPORT_DEBUG_BIT_EXT;
				_debugCI.pfnCallback = VulkanDebugCallback;

				vkCreateDebugReportCallbackEXT(m_VkInstance, &_debugCI, nullptr, &m_VkDebugReportCallback);
			}

			//==============================================================
			//==============================================================

			VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(VkDebugReportFlagsEXT flags,
				VkDebugReportObjectTypeEXT type,
				uint64_t src,
				size_t location,
				int32_t code,
				const char *layer_prefix,
				const char *msg,
				void *data)
			{

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

			//==============================================================
			//==============================================================

		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE
