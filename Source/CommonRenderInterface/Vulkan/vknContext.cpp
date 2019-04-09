////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "vknContext.h"
#include "../CRIContext.h"
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
#include "vknInstance.h"
#include "vknDevice.h"
#include "../Private\Vulkan\vknResourcePool.h"
#include "../Private\Vulkan\vknBatch.h"

#include "../Private\CRICore.h"
#include "../CRIContext.h"
#include "vknDataBuffer.h"

//==============================================================
//==============================================================

#define VK_ASSERT_CONTEXT(function) {\
	ASSERT_EX((function),==,VK_SUCCESS, \
		"Failed to execute function Vulkan", \
		throw e_vulkan_common_context_create_fail());\
}

//==============================================================
//==============================================================

namespace FE {

	namespace CRI {

		//==============================================================
		//==============================================================

		namespace VULKAN {

			//==============================================================
			//==============================================================

			CVKContext::CVKContext() {

				m_CRICreateInfo = {};

				m_VKDevice = nullptr;
				m_VKInstance = nullptr;
				m_VKResourcePool = nullptr;
				m_VKBatch = nullptr;
				m_VKSupportExtensions;
				m_VKSupportLayers;

				m_VkQueue = VK_NULL_HANDLE;
				m_IdFamilyQueue = -1;

				m_VkDevice = VK_NULL_HANDLE;

				m_VkSurface = VK_NULL_HANDLE;
				m_VkSurfaceCaps = {};
				m_VkSurfacePresentModes = {};
				m_VkSurfaceFormats = {};

				m_VkSwapchainCI = {};
				m_VkSwapchain = VK_NULL_HANDLE;
				m_VkFormat = VK_FORMAT_UNDEFINED;
				m_VkImages = {};
				m_VkImageViews = {};

				m_VkCmdPool = VK_NULL_HANDLE;

				m_PresentCompleteSemaphore = VK_NULL_HANDLE;
				m_RenderCompleteSemaphore = VK_NULL_HANDLE;
			}

			//==============================================================
			//==============================================================

			CVKContext::~CVKContext() {

				m_CRICreateInfo = {};

				m_VKDevice = nullptr;
				m_VKInstance = nullptr;
				m_VKResourcePool = nullptr;
				m_VKBatch = nullptr;
				m_VKSupportExtensions.clear();
				m_VKSupportLayers.clear();

				m_VkQueue = VK_NULL_HANDLE;
				m_IdFamilyQueue = -1;

				m_VkDevice = VK_NULL_HANDLE;

				m_VkSurface = VK_NULL_HANDLE;
				m_VkSurfaceCaps = {};
				m_VkSurfacePresentModes.clear();
				m_VkSurfaceFormats.clear();

				m_VkSwapchainCI = {};
				m_VkSwapchain = VK_NULL_HANDLE;
				m_VkFormat = VK_FORMAT_UNDEFINED;
				m_VkImages.clear();
				m_VkImageViews.clear();

				m_VkCmdPool = VK_NULL_HANDLE;

				m_PresentCompleteSemaphore = VK_NULL_HANDLE;
				m_RenderCompleteSemaphore = VK_NULL_HANDLE;
			}

			//==============================================================
			//==============================================================

			void CVKContext::create(const CRI_CONTEXT_CREATE_INFO *createInfo) {
				
				ASSERT_EX(createInfo->isValid(), == , true, "Invalid CRI_CONTEXT_CREATE_INFO.", throw e_vulkan_common_context_create_fail());

				m_CRICreateInfo = *createInfo;

				// ~~~~~~~~~~~~~~~~
				// VkInstance
				// ~~~~~~~~~~~~~~~~

				m_VKInstance = new VULKAN::CVKInstance();
				
				VK_INSTANCE_CREATE_INFO _vknInstanceCI = {};
				_vknInstanceCI.m_Type = VK_INSTANCE_CREATE_INFO::TYPE::DEBUG;
				
				m_VKInstance->create(&_vknInstanceCI);

				// ~~~~~~~~~~~~~~~~
				// VKDevice
				// ~~~~~~~~~~~~~~~~

				m_VKDevice = m_VKInstance->getPhysicalDevices()[0];
				
				// ~~~~~~~~~~~~~~~~
				// extensions
				// ~~~~~~~~~~~~~~~~

				// перебираем доступные расширения
				for (const auto& itSupportExtensions : m_VKDevice->getVkExtensions()) {

					CVKExtension _vknExtension = {};

					_vknExtension.m_VkExtension = itSupportExtensions;
					_vknExtension.m_Status = false;

					m_VKSupportExtensions.push_back(_vknExtension);

				} // for (const auto& itExtensionProps

				// ~~~~~~~~~~~~~~~~
				// layers
				// ~~~~~~~~~~~~~~~~
				
				// перебираем слои
				for (const auto& itSupportLayers : m_VKDevice->getVkLayers()) {

					CVKLayer _vknLayer = {};

					_vknLayer.m_VkLayer = itSupportLayers;
					_vknLayer.m_Status = false;

					m_VKSupportLayers.push_back(_vknLayer);

				} // for (const auto& itLayerProps 

				// ~~~~~~~~~~~~~~~~
				// setups
				// ~~~~~~~~~~~~~~~~

				setupExtensionLayer();

				// ~~~~~~~~~~~~~~~~
				// индекс семейства графических очередей
				// ~~~~~~~~~~~~~~~~

				int32_t _idFamilyQueue = m_VKDevice->getIndexGraphicsQueueFamily();
				

				std::vector<float> _queuePriorities = { 0.0f };

				// ~~~~~~~~~~~~~~~~
				// extension names
				// ~~~~~~~~~~~~~~~~

				std::vector<const char*> _extensionNameEnables;
				for (auto& itSupportExtension : m_VKSupportExtensions) {

					if (itSupportExtension.m_Status) {

						_extensionNameEnables.push_back(itSupportExtension.m_VkExtension.extensionName);
					}

				} // for (const auto& itExtension

				// ~~~~~~~~~~~~~~~~
				// layer names
				// ~~~~~~~~~~~~~~~~

				std::vector<const char*> _layerNameEnables;
				for (auto& itSupportLayer : m_VKSupportLayers) {

					if (itSupportLayer.m_Status) {

						_layerNameEnables.push_back(itSupportLayer.m_VkLayer.layerName);
					}

				} // for (const auto& itLayer : _supportLayers)

				// ~~~~~~~~~~~~~~~~
				// создание VkDevice
				// ~~~~~~~~~~~~~~~~

				// описываем VkDeviceQueueCreateInfo
				VkDeviceQueueCreateInfo queueCreateInfo = {};
				queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				queueCreateInfo.pNext = nullptr;
				queueCreateInfo.flags;
				queueCreateInfo.queueFamilyIndex = _idFamilyQueue;
				queueCreateInfo.queueCount = (uint32_t)_queuePriorities.size();
				queueCreateInfo.pQueuePriorities = _queuePriorities.data();

				// описываем создаваемое логическое устройство
				VkDeviceCreateInfo deviceCreateInfo = {};
				deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
				deviceCreateInfo.pNext = NULL;
				deviceCreateInfo.queueCreateInfoCount = 1;
				deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
				deviceCreateInfo.pEnabledFeatures = NULL;
				deviceCreateInfo.enabledLayerCount = (uint32_t)_layerNameEnables.size();
				deviceCreateInfo.ppEnabledLayerNames = _layerNameEnables.data();
				deviceCreateInfo.enabledExtensionCount = (uint32_t)_extensionNameEnables.size();
				deviceCreateInfo.ppEnabledExtensionNames = _extensionNameEnables.data();

				m_VKDevice->createLogicDevice(&deviceCreateInfo, &m_VkDevice);
			
				// ~~~~~~~~~~~~~~~~
				// loads
				// ~~~~~~~~~~~~~~~~

				loadFunction();

				// ~~~~~~~~~~~~~~~~
				// ~~~~~~~~~~~~~~~~

				vkGetDeviceQueue(m_VkDevice, _idFamilyQueue, 0, &m_VkQueue);

				// ~~~~~~~~~~~~~~~~
				// VkSurface
				// ~~~~~~~~~~~~~~~~

				// описываем VkWin32SurfaceCreateInfoKHR
				VkWin32SurfaceCreateInfoKHR _surfaceCreateInfo = {};
				_surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
				_surfaceCreateInfo.pNext = nullptr;
				_surfaceCreateInfo.flags = 0;
				_surfaceCreateInfo.hinstance = createInfo->m_PlatformInfo.m_Handle;
				_surfaceCreateInfo.hwnd = createInfo->m_PlatformInfo.m_HWnd;

				VK_ASSERT_CONTEXT(m_VKInstance->vkCreateWin32SurfaceKHR(m_VKInstance->getInstance(), &_surfaceCreateInfo, nullptr, &m_VkSurface));

				// ~~~~~~~~~~~~~~~~
				// check VkSurface
				// ~~~~~~~~~~~~~~~~

				ASSERT_EX(m_VKDevice->checkSurface(m_VkSurface, _idFamilyQueue), == , VK_TRUE, "", throw e_vulkan_common_context_create_fail());

				// ~~~~~~~~~~~~~~~~
				// check VkSurface
				// ~~~~~~~~~~~~~~~~

				m_VkSurfaceCaps = m_VKDevice->getVkSurfaceCaps(m_VkSurface);
				
				// ~~~~~~~~~~~~~~~~
				// present modes
				// ~~~~~~~~~~~~~~~~

				m_VkSurfacePresentModes = m_VKDevice->getVkPresentModes(m_VkSurface);
			
				// ~~~~~~~~~~~~~~~~
				// formats
				// ~~~~~~~~~~~~~~~~

				m_VkSurfaceFormats = m_VKDevice->getVkSurfaceFormats(m_VkSurface);
				
				//~~~~~~~~~~~~~~~~
				// image Count
				//~~~~~~~~~~~~~~~~

				uint32_t _imageCount;

				switch (createInfo->m_Bufferization) {

				case CRI_CONTEXT_CREATE_INFO::BUFFERIZATION::DOUBLE:			_imageCount = 2;		break;
				case CRI_CONTEXT_CREATE_INFO::BUFFERIZATION::TRIPLE:			_imageCount = 3;		break;
				}

				if(_imageCount < m_VkSurfaceCaps.minImageCount || _imageCount > m_VkSurfaceCaps.maxImageCount) _imageCount = m_VkSurfaceCaps.minImageCount;
				
				//~~~~~~~~~~~~~~~~
				// VkFormat и VkColorSpaceKHR
				//~~~~~~~~~~~~~~~~

				m_VkFormat = VK_FORMAT_UNDEFINED;
				VkColorSpaceKHR _colorSpace;
				for (const auto &itFormat : m_VkSurfaceFormats) {

					if (itFormat.format == VK_FORMAT_B8G8R8A8_UNORM) {

						m_VkFormat = itFormat.format;
						_colorSpace = itFormat.colorSpace;
					}

				} // for (const auto &itFormat : m_SurfaceFormats)

				//~~~~~~~~~~~~~~~~
				// VkExtent
				//~~~~~~~~~~~~~~~~

				VkExtent2D _swapchainExtent = { 0, 0 };

				ASSERT_EX(m_VkSurfaceCaps.currentExtent.width, != , 0, "", throw e_vulkan_common_instance_create_fail());
				ASSERT_EX(m_VkSurfaceCaps.currentExtent.height, != , 0, "", throw e_vulkan_common_instance_create_fail());

				_swapchainExtent = m_VkSurfaceCaps.currentExtent;

				//~~~~~~~~~~~~~~~~
				// Surface Transform
				//~~~~~~~~~~~~~~~~

				VkSurfaceTransformFlagBitsKHR _transform = {};
				if ((m_VkSurfaceCaps.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR) == VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)

					_transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;

				else _transform = m_VkSurfaceCaps.currentTransform;

				//~~~~~~~~~~~~~~~~
				// Composite Alpha
				//~~~~~~~~~~~~~~~~

				VkCompositeAlphaFlagBitsKHR _compositeAlpha = {};
				if ((m_VkSurfaceCaps.supportedCompositeAlpha & VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR) == VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR)

					_compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

				//~~~~~~~~~~~~~~~~
				// Present Mode
				//~~~~~~~~~~~~~~~~

				VkPresentModeKHR _presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
				
				//~~~~~~~~~~~~~~~~
				// 
				//~~~~~~~~~~~~~~~~

				m_VkSwapchainCI.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
				m_VkSwapchainCI.pNext = nullptr;
				m_VkSwapchainCI.flags = 0;
				m_VkSwapchainCI.surface = m_VkSurface;
				m_VkSwapchainCI.minImageCount = _imageCount;
				m_VkSwapchainCI.imageFormat = m_VkFormat;
				m_VkSwapchainCI.imageColorSpace = _colorSpace;
				m_VkSwapchainCI.imageExtent = _swapchainExtent;
				m_VkSwapchainCI.imageArrayLayers = 1;
				m_VkSwapchainCI.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
				m_VkSwapchainCI.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
				m_VkSwapchainCI.queueFamilyIndexCount = 0;
				m_VkSwapchainCI.pQueueFamilyIndices = NULL;
				m_VkSwapchainCI.preTransform = _transform;
				m_VkSwapchainCI.compositeAlpha = _compositeAlpha;
				m_VkSwapchainCI.presentMode = _presentMode;
				m_VkSwapchainCI.clipped = true;
				m_VkSwapchainCI.oldSwapchain = VkSwapchainKHR();

				VK_ASSERT_CONTEXT(m_VKInstance->vkCreateSwapchainKHR(m_VkDevice, &m_VkSwapchainCI, nullptr, &m_VkSwapchain));

				//~~~~~~~~~~~~~~~~
				// VkImage
				//~~~~~~~~~~~~~~~~

				// 
				uint32_t _countImage = 0;
				VK_ASSERT_CONTEXT(m_VKInstance->vkGetSwapchainImagesKHR(m_VkDevice, m_VkSwapchain, &_countImage, nullptr));

				m_VkImages.resize(_countImage);
				VK_ASSERT_CONTEXT(m_VKInstance->vkGetSwapchainImagesKHR(m_VkDevice, m_VkSwapchain, &_countImage, m_VkImages.data()));

				//~~~~~~~~~~~~~~~~
				// VkImageView
				//~~~~~~~~~~~~~~~~

				m_VkImageViews.resize(m_VkImages.size());

				for(uint32_t ctVkImage = 0; ctVkImage < m_VkImages.size(); ++ctVkImage) {

					// описываем VkImageViewCreateInfo
					VkImageViewCreateInfo _imageViewCI = {};

					_imageViewCI.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
					_imageViewCI.pNext;
					_imageViewCI.flags;
					_imageViewCI.image = m_VkImages[ctVkImage];
					_imageViewCI.viewType = VK_IMAGE_VIEW_TYPE_2D;
					_imageViewCI.format = m_VkFormat;
					_imageViewCI.components = {
						VK_COMPONENT_SWIZZLE_R,
						VK_COMPONENT_SWIZZLE_G,
						VK_COMPONENT_SWIZZLE_B,
						VK_COMPONENT_SWIZZLE_A
					};
					_imageViewCI.subresourceRange = {};
					_imageViewCI.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
					_imageViewCI.subresourceRange.baseMipLevel = 0;
					_imageViewCI.subresourceRange.levelCount = 1;
					_imageViewCI.subresourceRange.baseArrayLayer = 0;
					_imageViewCI.subresourceRange.layerCount = 1;

					VK_ASSERT_CONTEXT(m_VKInstance->vkCreateImageView(m_VkDevice, &_imageViewCI, nullptr, &m_VkImageViews[ctVkImage]));

				} // for (const auto itImage : m_Images)

				// ~~~~~~~~~~~~~~~~
				// ~~~~~~~~~~~~~~~~

				VkQueue _queue = {};
				m_VKInstance->vkGetDeviceQueue(m_VkDevice, _idFamilyQueue, 0, &_queue);

				// ~~~~~~~~~~~~~~~~
				// semaphors
				// ~~~~~~~~~~~~~~~~

				// описываем VkSemaphoreCreateInfo
				VkSemaphoreCreateInfo _semaphoreCI = {};
				_semaphoreCI.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
				_semaphoreCI.pNext = nullptr;
				_semaphoreCI.flags;

				VK_ASSERT_CONTEXT(m_VKInstance->vkCreateSemaphore(m_VkDevice, &_semaphoreCI, nullptr, &m_PresentCompleteSemaphore));
				VK_ASSERT_CONTEXT(m_VKInstance->vkCreateSemaphore(m_VkDevice, &_semaphoreCI, nullptr, &m_RenderCompleteSemaphore));

				// ~~~~~~~~~~~~~~~~
				// command pool
				// ~~~~~~~~~~~~~~~~

				// описываем VkCommandPoolCreateInfo
				VkCommandPoolCreateInfo cmdPoolInfo = {};
				cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
				cmdPoolInfo.queueFamilyIndex = _idFamilyQueue;
				cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

				VK_ASSERT_CONTEXT(m_VKInstance->vkCreateCommandPool(m_VkDevice, &cmdPoolInfo, nullptr, &m_VkCmdPool));

				// ~~~~~~~~~~~~~~~~
				// пул ресурсов
				// ~~~~~~~~~~~~~~~~

				// описываем VK_RESOURCE_POOL_CREATE_INFO
				VK_RESOURCE_POOL_CREATE_INFO _vukResourcePoolCI = {};
				_vukResourcePoolCI.m_Context = this;

				VKResourcePool _resourcePool = new CVKResourcePool();
				_resourcePool->create(&_vukResourcePoolCI);

				// ~~~~~~~~~~~~~~~~
				// ~~~~~~~~~~~~~~~~

				VK_BATCH_CREATE_INFO _batchCI = {};
				_batchCI.m_VKNContext = this;

				VKBatch _batch = new CVKBatch();
				_batch->create(&_batchCI);

				this->m_VKResourcePool = _resourcePool;
				this->m_VKBatch = _batch;

			}

			//==============================================================
			//==============================================================

			CRIRenderPass CVKContext::createRenderPass(const CRI_RENDER_PASS_CI *criCreateInfo) {

				//return m_VKBatch->createRenderPass(criCreateInfo);
				return nullptr;

			}

			//==============================================================
			//==============================================================

			void CVKContext::getPipeline(const CRI_PIPELINE_CI *criCreateInfo, CRIPipeline *criPipeline) {

				m_VKBatch->getPipeline(criCreateInfo);
			}

			//==============================================================
			//==============================================================

			void CVKContext::setupExtensionLayer(void) {

				// ~~~~~~~~~~~~~~~~
				// extensions
				// ~~~~~~~~~~~~~~~~

				for (auto& itSupportExtension : m_VKSupportExtensions) {

					if (std::strcmp(itSupportExtension.m_VkExtension.extensionName, VK_KHR_SWAPCHAIN_EXTENSION_NAME) == 0) {

						itSupportExtension.m_Status = true;

					}

					if (m_CRICreateInfo.m_Type == CRI_CONTEXT_CREATE_INFO::TYPE::DEBUG) {

						/*if (std::strcmp(itSupportExtension.m_VkExtension.extensionName, VK_KHR_SWAPCHAIN_EXTENSION_NAME) == 0) {

							itSupportExtension.m_Status = true;

						}*/
					}

				}

				// ~~~~~~~~~~~~~~~~
				// layers
				// ~~~~~~~~~~~~~~~~

				for (auto& itSupportLayer : m_VKSupportLayers) {

					/*if (std::strcmp(itSupportLayer.m_VkLayer.layerName, VK_KHR_SURFACE_EXTENSION_NAME) == 0 ||
						std::strcmp(itSupportLayer.m_VkLayer.layerName, VK_KHR_WIN32_SURFACE_EXTENSION_NAME) == 0) {

						itSupportLayer.m_Status = true;

					}*/

					if (m_CRICreateInfo.m_Type == CRI_CONTEXT_CREATE_INFO::TYPE::DEBUG) {

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

					}

				} // for (const auto& itLayerProps 

			}

			//==============================================================
			//==============================================================

			void CVKContext::loadFunction(void) {
				
				// VkSwapchainKHR
				VK_ASSERT_LOAD_FUNCTION(vkCreateSwapchainKHR = (PFN_vkCreateSwapchainKHR)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCreateSwapchainKHR"));
				VK_ASSERT_LOAD_FUNCTION(vkCreateSwapchainKHR = (PFN_vkCreateSwapchainKHR)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCreateSwapchainKHR"));
				VK_ASSERT_LOAD_FUNCTION(vkDestroySwapchainKHR = (PFN_vkDestroySwapchainKHR)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkDestroySwapchainKHR"));
				VK_ASSERT_LOAD_FUNCTION(vkGetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkGetSwapchainImagesKHR"));

				// VkDeviceMemory
				VK_ASSERT_LOAD_FUNCTION(vkAllocateMemory = (PFN_vkAllocateMemory)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkAllocateMemory"));
				VK_ASSERT_LOAD_FUNCTION(vkFreeMemory = (PFN_vkFreeMemory)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkFreeMemory"));
				VK_ASSERT_LOAD_FUNCTION(vkMapMemory = (PFN_vkMapMemory)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkMapMemory"));
				VK_ASSERT_LOAD_FUNCTION(vkUnmapMemory = (PFN_vkUnmapMemory)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkUnmapMemory"));

				// VkRenderPass и VkFramebuffer
				VK_ASSERT_LOAD_FUNCTION(vkCreateRenderPass = (PFN_vkCreateRenderPass)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCreateRenderPass"));
				VK_ASSERT_LOAD_FUNCTION(vkDestroyRenderPass = (PFN_vkDestroyRenderPass)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkDestroyRenderPass"));
				VK_ASSERT_LOAD_FUNCTION(vkCreateFramebuffer = (PFN_vkCreateFramebuffer)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCreateFramebuffer"));
				VK_ASSERT_LOAD_FUNCTION(vkDestroyFramebuffer = (PFN_vkDestroyFramebuffer)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkDestroyFramebuffer"));

				// VkPipeline
				VK_ASSERT_LOAD_FUNCTION(vkCreateShaderModule = (PFN_vkCreateShaderModule)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCreateShaderModule"));
				VK_ASSERT_LOAD_FUNCTION(vkDestroyShaderModule = (PFN_vkDestroyShaderModule)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkDestroyShaderModule"));
				VK_ASSERT_LOAD_FUNCTION(vkCreateDescriptorSetLayout = (PFN_vkCreateDescriptorSetLayout)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCreateDescriptorSetLayout"));
				VK_ASSERT_LOAD_FUNCTION(vkDestroyDescriptorSetLayout = (PFN_vkDestroyDescriptorSetLayout)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkDestroyDescriptorSetLayout"));
				VK_ASSERT_LOAD_FUNCTION(vkCreatePipelineCache = (PFN_vkCreatePipelineCache)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCreatePipelineCache"));
				VK_ASSERT_LOAD_FUNCTION(vkDestroyPipelineCache = (PFN_vkDestroyPipelineCache)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkDestroyPipelineCache"));
				VK_ASSERT_LOAD_FUNCTION(vkCreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCreateGraphicsPipelines"));
				VK_ASSERT_LOAD_FUNCTION(vkDestroyPipeline = (PFN_vkDestroyPipeline)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkDestroyPipeline"));
				VK_ASSERT_LOAD_FUNCTION(vkCreatePipelineLayout = (PFN_vkCreatePipelineLayout)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCreatePipelineLayout"));
				VK_ASSERT_LOAD_FUNCTION(vkDestroyPipelineLayout = (PFN_vkDestroyPipelineLayout)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkDestroyPipelineLayout"));

				// VkBuffer
				VK_ASSERT_LOAD_FUNCTION(vkCreateBuffer = (PFN_vkCreateBuffer)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCreateBuffer"));
				VK_ASSERT_LOAD_FUNCTION(vkDestroyBuffer = (PFN_vkDestroyBuffer)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkDestroyBuffer"));
				VK_ASSERT_LOAD_FUNCTION(vkGetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkGetBufferMemoryRequirements"));
				VK_ASSERT_LOAD_FUNCTION(vkBindBufferMemory = (PFN_vkBindBufferMemory)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkBindBufferMemory"));

				// VkImage и VkImageView
				VK_ASSERT_LOAD_FUNCTION(vkCreateImage = (PFN_vkCreateImage)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCreateImage"));
				VK_ASSERT_LOAD_FUNCTION(vkDestroyImage = (PFN_vkDestroyImage)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkDestroyImage"));
				VK_ASSERT_LOAD_FUNCTION(vkCreateImageView = (PFN_vkCreateImageView)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCreateImageView"));
				VK_ASSERT_LOAD_FUNCTION(vkDestroyImageView = (PFN_vkDestroyImageView)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkDestroyImageView"));
				VK_ASSERT_LOAD_FUNCTION(vkGetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkGetImageMemoryRequirements"));
				VK_ASSERT_LOAD_FUNCTION(vkBindImageMemory = (PFN_vkBindImageMemory)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkBindImageMemory"));

				// VkCommandBuffer
				VK_ASSERT_LOAD_FUNCTION(vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkAllocateCommandBuffers"));
				VK_ASSERT_LOAD_FUNCTION(vkFreeCommandBuffers = (PFN_vkFreeCommandBuffers)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkFreeCommandBuffers"));
				VK_ASSERT_LOAD_FUNCTION(vkBeginCommandBuffer = (PFN_vkBeginCommandBuffer)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkBeginCommandBuffer"));
				VK_ASSERT_LOAD_FUNCTION(vkEndCommandBuffer = (PFN_vkEndCommandBuffer)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkEndCommandBuffer"));
				VK_ASSERT_LOAD_FUNCTION(vkCmdBeginRenderPass = (PFN_vkCmdBeginRenderPass)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCmdBeginRenderPass"));
				VK_ASSERT_LOAD_FUNCTION(vkCmdEndRenderPass = (PFN_vkCmdEndRenderPass)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCmdEndRenderPass"));
				VK_ASSERT_LOAD_FUNCTION(vkCmdNextSubpass = (PFN_vkCmdNextSubpass)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCmdNextSubpass"));
				VK_ASSERT_LOAD_FUNCTION(vkCmdBindPipeline = (PFN_vkCmdBindPipeline)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCmdBindPipeline"));
				VK_ASSERT_LOAD_FUNCTION(vkCmdSetViewport = (PFN_vkCmdSetViewport)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCmdSetViewport"));
				VK_ASSERT_LOAD_FUNCTION(vkCmdSetScissor = (PFN_vkCmdSetScissor)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCmdSetScissor"));
				VK_ASSERT_LOAD_FUNCTION(vkCmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCmdBindDescriptorSets"));
				VK_ASSERT_LOAD_FUNCTION(vkCmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCmdBindIndexBuffer"));
				VK_ASSERT_LOAD_FUNCTION(vkCmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCmdBindVertexBuffers"));
				VK_ASSERT_LOAD_FUNCTION(vkCmdDraw = (PFN_vkCmdDraw)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCmdDraw"));
				VK_ASSERT_LOAD_FUNCTION(vkCmdDrawIndexed = (PFN_vkCmdDrawIndexed)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCmdDrawIndexed"));
				VK_ASSERT_LOAD_FUNCTION(vkCmdPipelineBarrier = (PFN_vkCmdPipelineBarrier)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCmdPipelineBarrier"));
				VK_ASSERT_LOAD_FUNCTION(vkCmdCopyBuffer = (PFN_vkCmdCopyBuffer)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCmdCopyBuffer"));

				//
				VK_ASSERT_LOAD_FUNCTION(vkCreateFence = (PFN_vkCreateFence)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCreateFence"));
				VK_ASSERT_LOAD_FUNCTION(vkWaitForFences = (PFN_vkWaitForFences)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkWaitForFences"));
				VK_ASSERT_LOAD_FUNCTION(vkResetFences = (PFN_vkResetFences)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkResetFences"));

				// VkSemaphore
				VK_ASSERT_LOAD_FUNCTION(vkCreateSemaphore = (PFN_vkCreateSemaphore)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCreateSemaphore"));
				VK_ASSERT_LOAD_FUNCTION(vkDestroySemaphore = (PFN_vkDestroySemaphore)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkDestroySemaphore"));

				// остальное
				VK_ASSERT_LOAD_FUNCTION(vkCreateDescriptorPool = (PFN_vkCreateDescriptorPool)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCreateDescriptorPool"));
				VK_ASSERT_LOAD_FUNCTION(vkAllocateDescriptorSets = (PFN_vkAllocateDescriptorSets)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkAllocateDescriptorSets"));
				VK_ASSERT_LOAD_FUNCTION(vkUpdateDescriptorSets = (PFN_vkUpdateDescriptorSets)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkUpdateDescriptorSets"));
				VK_ASSERT_LOAD_FUNCTION(vkGetDeviceQueue = (PFN_vkGetDeviceQueue)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkGetDeviceQueue"));
				VK_ASSERT_LOAD_FUNCTION(vkQueueSubmit = (PFN_vkQueueSubmit)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkQueueSubmit"));
				VK_ASSERT_LOAD_FUNCTION(vkDeviceWaitIdle = (PFN_vkDeviceWaitIdle)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkDeviceWaitIdle"));
				VK_ASSERT_LOAD_FUNCTION(vkCreateCommandPool = (PFN_vkCreateCommandPool)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCreateCommandPool"));
				VK_ASSERT_LOAD_FUNCTION(vkAcquireNextImageKHR = (PFN_vkAcquireNextImageKHR)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkAcquireNextImageKHR"));
				VK_ASSERT_LOAD_FUNCTION(vkQueuePresentKHR = (PFN_vkQueuePresentKHR)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkQueuePresentKHR"));
				VK_ASSERT_LOAD_FUNCTION(vkCmdExecuteCommands = (PFN_vkCmdExecuteCommands)m_VKInstance->vkGetDeviceProcAddr(m_VkDevice, "vkCmdExecuteCommands"));
			}

			//==============================================================
			//==============================================================
			static bool a = false;
			void CVKContext::update(void) {
				
				///for (auto &it : m_CreateDataBuffer) {

				//	it->createS();
				//}

				//for (auto &it : m_UpdateDataBuffer) {

				//	it->updateS();
				//}

				//m_CreateDataBuffer.clear();
				//m_UpdateDataBuffer.clear();

				m_VKResourcePool->update();

				static bool aa = false;
				if (!aa) {
					m_VKBatch->update();
					aa = true;
				}
				a = true;
								
			}

			//==============================================================
			//==============================================================

			void CVKContext::execute(void) {
				if (!a) return;
				// получаем индекс изображения, в который будет производиться отрисовка
				// индекс изображения это индекс VkImageView который создавался для свопчайна
				uint32_t currentBuffer;
				vkAcquireNextImageKHR(m_VkDevice, m_VkSwapchain, UINT64_MAX, m_PresentCompleteSemaphore, (VkFence)nullptr, &currentBuffer);

				VkCommandBufferArr _drawCmdBuffers;
				m_VKBatch->getCmdBuffers(&_drawCmdBuffers, currentBuffer);

				std::vector<VkFence> _fence;
				m_VKBatch->getFences(&_fence, currentBuffer);

				// Use a fence to wait until the command buffer has finished execution before using it again
				VK_ASSERT_EX(vkWaitForFences(m_VkDevice, 1, &_fence[0], VK_TRUE, UINT64_MAX));
				VK_ASSERT_EX(vkResetFences(m_VkDevice, 1, &_fence[0]));

				//const VkCommandBufferArr &_copyCmdBuffers = m_ResourcePool->getCmdBuffer();

				//vknPipelineStageFlags waitStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

				//vknSubmitInfo submitInfo = {};

				//submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
				//submitInfo.pWaitDstStageMask = &waitStageMask;									// Pointer to the list of pipeline stages that the semaphore waits will occur at
				//submitInfo.pWaitSemaphores = &m_BeginRenderComplete;							// Semaphore(s) to wait upon before the submitted command buffer starts executing
				//submitInfo.waitSemaphoreCount = 1;												// One wait semaphore																				
				//submitInfo.pSignalSemaphores = &m_EndRenderComplete;						// Semaphore(s) to be signaled when command buffers have completed
				//submitInfo.signalSemaphoreCount = 1;											// One signal semaphore
				//submitInfo.pCommandBuffers = _copyCmdBuffers.data();					// Command buffers(s) to execute in this batch (submission)
				//submitInfo.commandBufferCount = _copyCmdBuffers.size();												// One command buffer

																								// Submit to the graphics queue passing a wait fence
				//vkn_ASSERT_EX(vkQueueSubmit(m_Queue, 1, &submitInfo, 0));

				

				//for (auto &itDrawCmdBuffer : _drawCmdBuffers) {

					VkPipelineStageFlags waitStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

					VkSubmitInfo submitInfo = {};
					
					submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
					submitInfo.pWaitDstStageMask = &waitStageMask;									// Pointer to the list of pipeline stages that the semaphore waits will occur at
					submitInfo.pWaitSemaphores = &m_PresentCompleteSemaphore;							// Semaphore(s) to wait upon before the submitted command buffer starts executing
					submitInfo.waitSemaphoreCount = 1;												// One wait semaphore																				
					submitInfo.pSignalSemaphores = &m_RenderCompleteSemaphore;							// Semaphore(s) to be signaled when command buffers have completed
					submitInfo.signalSemaphoreCount = 1;											// One signal semaphore
					submitInfo.pCommandBuffers = &_drawCmdBuffers[0];								// Command buffers(s) to execute in this batch (submission)
					submitInfo.commandBufferCount = 1;												// One command buffer

					// Submit to the graphics queue passing a wait fence
					VK_ASSERT_EX(vkQueueSubmit(m_VkQueue, 1, &submitInfo, _fence[0]));
				//}

				// ~~~~~~~~~~~~~~~~
				// ждём полного завершения очередей
				// ждём сигнала от семафора m_EndRenderComplete
				// ~~~~~~~~~~~~~~~~

				// описываем VkPresentInfoKHR
				VkPresentInfoKHR _presentInfo = {};
				_presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
				_presentInfo.pNext = NULL;
				_presentInfo.waitSemaphoreCount = 1;
				_presentInfo.pWaitSemaphores = &m_RenderCompleteSemaphore;
				_presentInfo.swapchainCount = 1;
				_presentInfo.pSwapchains = &m_VkSwapchain;
				_presentInfo.pImageIndices = &currentBuffer;
				_presentInfo.pResults;

				vkQueuePresentKHR(m_VkQueue, &_presentInfo);

				// ~~~~~~~~~~~~~~~~
				// ждём полного завершения работы устройства
				// ~~~~~~~~~~~~~~~~

				//vknDeviceWaitIdle(m_Device);

			}

			//==============================================================
			//==============================================================

			VkDevice CVKContext::getDevice(void) const {

				return m_VkDevice;
			}

			//==============================================================
			//==============================================================

			VkFormat CVKContext::getFormat(void) const {

				return m_VkFormat;
			}

			//==============================================================
			//==============================================================

			const VkImageViewArr& CVKContext::getImageViews(void) const {

				return m_VkImageViews;
			}

			//==============================================================
			//==============================================================

			VkQueue CVKContext::getQueue(void) const {

				return m_VkQueue;
			}

			//==============================================================
			//==============================================================

			VkSwapchainKHR CVKContext::getSwapchain(void) const {

				return m_VkSwapchain;
			}

			//==============================================================
			//==============================================================

			int32_t CVKContext::getIndexFamilyQueue(void) const {

				return m_IdFamilyQueue;
			}

			//==============================================================
			//==============================================================

			int32_t CVKContext::getIndexMemory(VkMemoryPropertyFlags memoryType) const {

				return m_VKDevice->getIndexMemory(memoryType);

			}

			//==============================================================
			//==============================================================

			VKResourcePool CVKContext::getResourcePool(void) const {

				return m_VKResourcePool;
			}

			//==============================================================
			//==============================================================

			VKBatch CVKContext::getBatch(void) const {

				return m_VKBatch;

			}

			//==============================================================
			//==============================================================

		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE
