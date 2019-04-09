#ifndef VK_DRAW_BUFFER__H
#define VK_DRAW_BUFFER__H
////////////////////////////////////////////////////////////////
// ������ ���������� �����
////////////////////////////////////////////////////////////////
#include "../../../RenderConfig.h"
#if defined(FE_RENDER) && defined(FE_RENDER_VULKAN) && FE_RENDER == FE_RENDER_VULKAN
////////////////////////////////////////////////////////////////
// ������ ������������� ������
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ �������-����������
////////////////////////////////////////////////////////////////
#include "../../Vulkan\Vulkan.h"
#include "../../CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// ������ ��� ����������
////////////////////////////////////////////////////////////////
#include "../../CRIDrawBufferInfo.h"

namespace FE {

	namespace CRI {

		namespace VULKAN {

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief .
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			class CVKDrawBuffer {

			public:

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief �������� CRIDrawBuffer.

				\param createInfo ���������� ��� ��������.
				\param drawBuffer ���������� CRIDrawBuffer.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				static void get(const CRI_DRAW_BUFFER_CREATE_INFO *createInfo, CRIDrawBuffer *drawBuffer);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief ������� ��������� CRIDrawBuffer.

				\param drawBuffers ��������� CRIDrawBuffer.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				void create();

			public:

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief �����������.

				\param createInfo ���������� ��� ��������.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				CVKDrawBuffer(const CRI_DRAW_BUFFER_CREATE_INFO *createInfo);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief �������� ���������� CRI.

				\return cri ���������� ����� CRI.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline CRIDrawBuffer getCRI(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief ���������� ���������� CRI.

				\param cri ���������� ����� CRI.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline void setCRI(CRIDrawBuffer cri);

			public:

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brie �������� VKRenderPass.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline VKRenderPass getRenderPass(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brie �������� VKPipeline.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline VKPipeline getPipeline(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brie �������� VKDataBuffer ������.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline VKDataBuffer getVertices(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brie �������� VKDataBuffer ��������.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline VKDataBuffer getIndices(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brie �������� ����� ����������.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline uint32_t getSubpass(void) const;

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief �������� VkDescriptorSet.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				inline VkDescriptorSet getDescriptorSet(void) const;

			// ������
			private:

				CRIDrawBuffer						m_CRI;
				CRI_DRAW_BUFFER_CREATE_INFO			m_CI;

				VKContext							m_Context;
				VKRenderPass						m_RenderPass;
				VKPipeline							m_Pipeline;
				VKDataBuffer						m_Vertices;
				VKDataBuffer						m_Indices;
				VkDescriptorSet						m_DescriptorSet;

			}; // class CVKDrawBuffer

		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE

#include "vknDrawBuffer.hpp"

#endif // #if defined(FE_RENDER) && defined(FE_RENDER_VULKAN) && FE_RENDER == FE_RENDER_VULKAN

#endif // VK_DRAW_BUFFER__H