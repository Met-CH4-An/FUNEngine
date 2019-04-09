#ifndef GEOMETRY__H
#define GEOMETRY__H
////////////////////////////////////////////////////////////////
// секция компиляция файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция родительского класса
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция форвард-декларации
////////////////////////////////////////////////////////////////
#include "pch.renderer.h"
#include "../CommonRenderInterface/CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////

namespace FE {

	namespace RENDERER {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Информация для создания Geometry.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct GEOMETRY_CREATE_INFO {

			void*			m_DataVertices;
			uint32_t		m_SizeDataVertices;
			void*			m_DataIndices;
			uint32_t		m_SizeDataIndices;

		}; // struct GEOMETRY_CREATE_INFO



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CGeometry {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Получить объект.

			\param[in] renderer Рендерер, который будет владеть объектом.
			\param[out] geometry Полученный объект.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//static void get(Renderer renderer, Geometry *geometry);

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//inline FE::CRI::CRIDataBuffer getVertices(void) { return m_BufferVertices; }
			//inline FE::CRI::CRIDataBuffer getIndices(void) { return m_BufferIndices; }
			//inline FE::CRI::CRI_PIPELINE_VERTEX_LAYOUT_ARR getVertexLayouts(void) { return m_VertexLayouts; }

		private:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//void create(const GEOMETRY_CREATE_INFO *createInfo);			

		private:

			FE::RENDERER::Renderer			m_Renderer;

			FE::CRI::CRIDataBuffer						m_BufferVertices;
			FE::CRI::CRIDataBuffer						m_BufferIndices;
			//FE::CRI::CRI_PIPELINE_VERTEX_LAYOUT_ARR		m_VertexLayouts;
		
		}; // CGeometry

	} // namespace RENDERER

} // namespace FE

#endif // GEOMETRY__H
