////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "vknDevice.h"
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

//==============================================================
//==============================================================

#define VK_FASSERT_DEVICE_EXE(function) {\
	ASSERT_EX((function),==,VK_SUCCESS, \
		"Failed to execute function Vulkan", \
		throw e_vulkan_common_instance_create_fail());\
}

//==============================================================
//==============================================================

namespace FE {

	namespace CRI {

		namespace VULKAN {

			//==============================================================
			//==============================================================

			CVKDevice::CVKDevice(VKInstance vknInstance)
				: m_VKCreateInfo(),
				m_VKInstance(vknInstance),
				m_VkPhysicalDevice(nullptr),
				m_VkPhysicalDeviceProps(),
				m_VkPhysicalDeviceMemoryProps(),
				m_VkQueueFamilyProps() {

			}

			//==============================================================
			//==============================================================

			CVKDevice::~CVKDevice() {

				m_VKCreateInfo = {};
				m_VKInstance = nullptr;
				m_VkPhysicalDevice = nullptr;
				m_VkPhysicalDeviceProps = {};
				m_VkPhysicalDeviceMemoryProps = {};
				m_VkQueueFamilyProps = {};

			}

			//==============================================================
			//==============================================================
		
			void CVKDevice::create(const VK_DEVICE_CREATE_INFO *createInfo) {

				m_VKCreateInfo = *createInfo;

				ASSERT(createInfo->isValid(), == , true, "Invalid VK_DEVICE_CREATE_INFO.");

				m_VkPhysicalDevice = createInfo->m_VkPhysicalDevice;

				// свойства физического устройства
				m_VKInstance->vkGetPhysicalDeviceProperties(m_VkPhysicalDevice, &m_VkPhysicalDeviceProps);

				// свойства памяти
				m_VKInstance->vkGetPhysicalDeviceMemoryProperties(m_VkPhysicalDevice, &m_VkPhysicalDeviceMemoryProps);

				// свойства семейств очередей
				uint32_t _queuePropertiesCount = 0;
				m_VKInstance->vkGetPhysicalDeviceQueueFamilyProperties(m_VkPhysicalDevice, &_queuePropertiesCount, nullptr);
				
				m_VkQueueFamilyProps.resize(_queuePropertiesCount);
				m_VKInstance->vkGetPhysicalDeviceQueueFamilyProperties(m_VkPhysicalDevice, &_queuePropertiesCount, m_VkQueueFamilyProps.data());

				// ~~~~~~~~~~~~~~~~
				// extensions
				// ~~~~~~~~~~~~~~~~

				// количество расширений
				uint32_t _countExtension = 0;
				VK_FASSERT_DEVICE_EXE(m_VKInstance->vkEnumerateDeviceExtensionProperties(m_VkPhysicalDevice, nullptr, &_countExtension, nullptr));

				// получаем расширения
				m_VkExtensionProps.resize(_countExtension);
				VK_FASSERT_DEVICE_EXE(m_VKInstance->vkEnumerateDeviceExtensionProperties(m_VkPhysicalDevice, nullptr, &_countExtension, m_VkExtensionProps.data()));

				// ~~~~~~~~~~~~~~~~
				// layers
				// ~~~~~~~~~~~~~~~~

				// количество слоёв
				uint32_t _countLayer = 0;
				VK_FASSERT_DEVICE_EXE(m_VKInstance->vkEnumerateDeviceLayerProperties(m_VkPhysicalDevice, &_countLayer, nullptr));

				// получаем расширения
				m_VkLayerProps.resize(_countLayer);
				VK_FASSERT_DEVICE_EXE(m_VKInstance->vkEnumerateDeviceLayerProperties(m_VkPhysicalDevice, &_countLayer, m_VkLayerProps.data()));

			}
			
			//==============================================================
			//==============================================================

			void CVKDevice::createLogicDevice(const VkDeviceCreateInfo *vkCreateInfo, VkDevice *vkDevice) {

				VK_FASSERT_DEVICE_EXE(m_VKInstance->vkCreateDevice(m_VkPhysicalDevice, vkCreateInfo, nullptr, vkDevice));
			}

			//==============================================================
			//==============================================================

			VkPhysicalDevice CVKDevice::getVkPhysicalDevice(void) const {

				return m_VkPhysicalDevice;
			}

			//==============================================================
			//==============================================================

			VkExtensionPropertiesArr CVKDevice::getVkExtensions(void) const {

				return m_VkExtensionProps;
			}

			//==============================================================
			//==============================================================

			VkLayerPropertiesArr CVKDevice::getVkLayers(void) const {

				return m_VkLayerProps;
			}		

			//==============================================================
			//==============================================================

			VkSurfaceCapabilitiesKHR CVKDevice::getVkSurfaceCaps(const VkSurfaceKHR vkSurface) const {

				VkSurfaceCapabilitiesKHR _surfaceCaps;

				// свойства
				VK_FASSERT_DEVICE_EXE(m_VKInstance->vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_VkPhysicalDevice, vkSurface, &_surfaceCaps));

				return _surfaceCaps;
			}

			//==============================================================
			//==============================================================

			VkPresentModeArr CVKDevice::getVkPresentModes(const VkSurfaceKHR vkSurface) const {

				VkPresentModeArr _presentModes;

				// количество
				uint32_t _countModes = 0;
				VK_FASSERT_DEVICE_EXE(m_VKInstance->vkGetPhysicalDeviceSurfacePresentModesKHR(m_VkPhysicalDevice, vkSurface, &_countModes, NULL));

				// список
				_presentModes.resize(_countModes);
				VK_FASSERT_DEVICE_EXE(m_VKInstance->vkGetPhysicalDeviceSurfacePresentModesKHR(m_VkPhysicalDevice, vkSurface, &_countModes, _presentModes.data()));

				return _presentModes;
			}

			//==============================================================
			//==============================================================

			VkSurfaceFormatArr CVKDevice::getVkSurfaceFormats(const VkSurfaceKHR vkSurface) const {

				VkSurfaceFormatArr _surfaceFormats;

				// количество
				uint32_t _countFormats = 0;
				VK_FASSERT_DEVICE_EXE(m_VKInstance->vkGetPhysicalDeviceSurfaceFormatsKHR(m_VkPhysicalDevice, vkSurface, &_countFormats, NULL));

				// список
				_surfaceFormats.resize(_countFormats);
				VK_FASSERT_DEVICE_EXE(m_VKInstance->vkGetPhysicalDeviceSurfaceFormatsKHR(m_VkPhysicalDevice, vkSurface, &_countFormats, _surfaceFormats.data()));

				return _surfaceFormats;
			}

			//==============================================================
			//==============================================================
			
			int32_t CVKDevice::getIndexGraphicsQueueFamily(void) const {

				// перебираем свойства очередей
				for (int i = 0; i < m_VkQueueFamilyProps.size(); ++i) {

					if ((m_VkQueueFamilyProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == VK_QUEUE_GRAPHICS_BIT) return i;

				}

				return VK_DEVICE_ERROR::INVALID_INDEX_QUEUE_FAMILY;
			}

			//==============================================================
			//==============================================================

			int32_t CVKDevice::getIndexMemory(const VkMemoryPropertyFlags memoryType) const {

				for (int i = 0; i < VK_MAX_MEMORY_TYPES; ++i) {

					if ((m_VkPhysicalDeviceMemoryProps.memoryTypes[i].propertyFlags & memoryType) == memoryType) return i;

				}

				return VK_DEVICE_ERROR::INVALID_INDEX_MEMORY;
			}

			//==============================================================
			//==============================================================
			
			VkBool32 CVKDevice::checkSurface(VkSurfaceKHR vkSurface, uint32_t queueFamilyIndex) const {

				VkBool32 _support = VK_FALSE;

				VK_FASSERT_DEVICE_EXE(m_VKInstance->vkGetPhysicalDeviceSurfaceSupportKHR(m_VkPhysicalDevice, queueFamilyIndex, vkSurface, &_support));

				return _support;

			}

			//==============================================================
			//==============================================================

		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE
