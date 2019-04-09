#ifndef VK_DRAW_BUFFER__HPP
#define VK_DRAW_BUFFER__HPP
////////////////////////////////////////////////////////////////
// секци€ компил€ци€ файла
////////////////////////////////////////////////////////////////
#include "../../../RenderConfig.h"
#if defined(FE_RENDER) && defined(FE_RENDER_VULKAN) && FE_RENDER == FE_RENDER_VULKAN
////////////////////////////////////////////////////////////////
// секци€ родительского класса
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секци€ форвард-декларации
////////////////////////////////////////////////////////////////
#include "../../Vulkan\Vulkan.h"
////////////////////////////////////////////////////////////////
// секци€ дл€ остального
////////////////////////////////////////////////////////////////

namespace FE {

	namespace CRI {

		namespace VULKAN {

			//==============================================================
			//==============================================================

			inline CRIDrawBuffer CVKDrawBuffer::getCRI(void) const {

				return m_CRI;
			}

			//==============================================================
			//==============================================================

			inline void CVKDrawBuffer::setCRI(CRIDrawBuffer cri) {

				m_CRI = cri;

			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			inline VKRenderPass CVKDrawBuffer::getRenderPass(void) const { 
				
				return m_RenderPass; 
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			inline VKPipeline CVKDrawBuffer::getPipeline(void) const { 
				
				return m_Pipeline; 
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			inline VKDataBuffer CVKDrawBuffer::getVertices(void) const { 
				
				return m_Vertices;
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			inline VKDataBuffer CVKDrawBuffer::getIndices(void) const { 
				
				return m_Indices;
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			inline uint32_t CVKDrawBuffer::getSubpass(void) const { 
				
				return m_CI.m_NumberSubpass;
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			
			inline VkDescriptorSet CVKDrawBuffer::getDescriptorSet(void) const {

				return m_DescriptorSet;
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		} // namespace VULKAN

	} // namespace RENDER

} // namespace FE

#endif // #if defined(FE_RENDER) && defined(FE_RENDER_VULKAN) && FE_RENDER == FE_RENDER_VULKAN

#endif // VK_DRAW_BUFFER__HPP