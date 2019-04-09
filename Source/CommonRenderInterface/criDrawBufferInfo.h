#ifndef CRI_DRAW_BUFFER_INFO__H
#define CRI_DRAW_BUFFER_INFO__H
////////////////////////////////////////////////////////////////
// секци€ компил€ци€ файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секци€ родительского класса
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секци€ форвард-декларации
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секци€ дл€ остального
////////////////////////////////////////////////////////////////

namespace FE {

	namespace CRI {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CRI_DRAW_OBJECT_UNIFORM_DATA_BUFFER_INFO {

			enum class TYPE {

				UNIFORM = 0
			};

			CRIDataBuffer		m_Buffer;
			TYPE				m_Type;
			uint32_t			m_Binding;
		};
		using CRI_DRAW_OBJECT_UNIFORM_DATA_BUFFER_ARR = std::vector<CRI_DRAW_OBJECT_UNIFORM_DATA_BUFFER_INFO>;



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CRI_DRAW_OBJECT_UNIFORM_IMAGE_BUFFER_INFO {

			enum class TYPE {

				INPUT		= 0,
				SAMPLE		= 1
			};

			CRIImageBuffer		m_Buffer;
			TYPE				m_Type;
			//uint32_t			m_Binding;
		};
		using CRI_DRAW_OBJECT_UNIFORM_IMAGE_BUFFER_ARR = std::vector<CRI_DRAW_OBJECT_UNIFORM_IMAGE_BUFFER_INFO>;



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CRI_DRAW_BUFFER_CREATE_INFO {

			CRIContext									m_Context;
			CRIRenderPass								m_RenderPass;
			uint32_t									m_NumberSubpass;
			CRIPipeline									m_Pipeline;
			CRIDataBuffer								m_Vertices;
			CRIDataBuffer								m_Indices;
			CRI_DRAW_OBJECT_UNIFORM_DATA_BUFFER_ARR		m_UniformDBs;
			CRI_DRAW_OBJECT_UNIFORM_IMAGE_BUFFER_ARR	m_UniformIBs;

		}; // struct CRI_DRAW_BUFFER_CREATE_INFO

	} // namespace RENDER

} // namespace FE

#endif // CRI_DRAW_BUFFER_INFO__H