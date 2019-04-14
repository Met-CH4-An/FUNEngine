#ifndef VK_CONTEXT__H
#define VK_CONTEXT__H
////////////////////////////////////////////////////////////////
// секция компиляция файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция родительского класса
////////////////////////////////////////////////////////////////
#include "../CRIContext.h"
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
			/*!	\brief Ошибки контекста.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			enum class VK_CONTEXT_ERROR_CODE {

				INVALID_INDEX_MEMORY = -1

			}; // enum class VK_CONTEXT_ERROR_CODE



			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*! \brief Невозможно создать CVKContext.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			class e_vulkan_common_context_create_fail : public e_vulkan_common {};


			

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*! \brief Контекст вулкана.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			class CVKContext {

			public:

				// VkSwapchainKHR
				PFN_vkCreateSwapchainKHR							vkCreateSwapchainKHR;
				PFN_vkDestroySwapchainKHR							vkDestroySwapchainKHR;
				PFN_vkGetSwapchainImagesKHR							vkGetSwapchainImagesKHR;

				// VkDeviceMemory
				PFN_vkAllocateMemory								vkAllocateMemory;
				PFN_vkFreeMemory									vkFreeMemory;
				PFN_vkMapMemory										vkMapMemory;
				PFN_vkUnmapMemory									vkUnmapMemory;

				// VkRenderPass и VkFramebuffer
				PFN_vkCreateRenderPass								vkCreateRenderPass;
				PFN_vkDestroyRenderPass								vkDestroyRenderPass;
				PFN_vkCreateFramebuffer								vkCreateFramebuffer;
				PFN_vkDestroyFramebuffer							vkDestroyFramebuffer;

				// VkPipeline
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

				//
				PFN_vkCreateFence									vkCreateFence;
				PFN_vkWaitForFences									vkWaitForFences;
				PFN_vkResetFences									vkResetFences;

				// VkSemaphore
				PFN_vkCreateSemaphore								vkCreateSemaphore;
				PFN_vkDestroySemaphore								vkDestroySemaphore;

				// остальное					
				PFN_vkCreateDescriptorPool							vkCreateDescriptorPool;
				PFN_vkAllocateDescriptorSets						vkAllocateDescriptorSets;
				PFN_vkUpdateDescriptorSets							vkUpdateDescriptorSets;
				PFN_vkGetDeviceQueue								vkGetDeviceQueue;
				PFN_vkQueueSubmit									vkQueueSubmit;
				PFN_vkDeviceWaitIdle								vkDeviceWaitIdle;
				PFN_vkCreateCommandPool								vkCreateCommandPool;
				PFN_vkAcquireNextImageKHR							vkAcquireNextImageKHR;
				PFN_vkQueuePresentKHR								vkQueuePresentKHR;
				PFN_vkCmdExecuteCommands							vkCmdExecuteCommands;

			public:

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Конструктор.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				CVKContext();

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Деструктор.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				~CVKContext();

			public:

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Создание множества VKContext.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void create(const CRI_CONTEXT_CREATE_INFO *createInfo);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Обновление контекста.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void update(void);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Выполнение контекста.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void execute(void);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				//void execute(void);

			public:

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить CRIRenderPass.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				CRIRenderPass createRenderPass(const CRI_RENDER_PASS_CI *criCreateInfo);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить CRIPipeline.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void getPipeline(const CRI_PIPELINE_CI *criCreateInfo, CRIPipeline *criPipeline);
			
			public:

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить логическое устройство вулкана.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				VkDevice getDevice(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить формат свопчайна
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				VkFormat getFormat(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить массив VkImageView свопчайна.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				const VkImageViewArr& getImageViews(void) const;
				
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить VkQueue.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				VkQueue getQueue(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить VkSwapchainKHR.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				VkSwapchainKHR getSwapchain(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				int32_t getIndexFamilyQueue(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить индекст памяти.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				int32_t getIndexMemory(VkMemoryPropertyFlags memoryType) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить индекст памяти.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				VkCommandPool getVkCommandPool(void) const { return m_VkCmdPool; }

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить пул ресурсов.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				VKResourcePool getResourcePool(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Получить батч
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				VKBatch getBatch(void) const;

			private:

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

			// данные
			private:

				CRI_CONTEXT_CREATE_INFO					m_CRICreateInfo;

				VKDevice								m_VKDevice;
				VKInstance								m_VKInstance;
				VKResourcePool							m_VKResourcePool;
				VKBatch									m_VKBatch;
				CVKExtensionArr							m_VKSupportExtensions;
				CVKLayerArr								m_VKSupportLayers;

				VkQueue									m_VkQueue;
				int32_t									m_IdFamilyQueue;

				VkDevice								m_VkDevice;

				VkSurfaceKHR							m_VkSurface;
				VkSurfaceCapabilitiesKHR				m_VkSurfaceCaps;
				VkPresentModeArr						m_VkSurfacePresentModes;
				VkSurfaceFormatArr						m_VkSurfaceFormats;

				VkSwapchainCreateInfoKHR				m_VkSwapchainCI;
				VkSwapchainKHR							m_VkSwapchain;
				VkFormat								m_VkFormat;
				VkImageArr								m_VkImages;
				VkImageViewArr							m_VkImageViews;

				VkCommandPool							m_VkCmdPool;

				VkSemaphore								m_PresentCompleteSemaphore;
				VkSemaphore								m_RenderCompleteSemaphore;

			}; // class CVKContext

			using CCRIContextPrivate = VulkanRenderInterfaceImpl<CVKContext, CCRIContext>;

			inline VKContext cri2vkn_Context(CRIContext criContext) { return static_cast<CCRIContextPrivate*>(criContext)->getImpl(); }

		} // namespace VULKAN		

	} // namespace RENDER

} // namespace FE

#include "vknContext.hpp"

#endif // VK_CONTEXT__H