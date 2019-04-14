#ifndef TECHNIQUE_PASS__H
#define TECHNIQUE_PASS__H
////////////////////////////////////////////////////////////////
// секци€ компил€ци€ файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секци€ родительского класса
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секци€ форвард-декларации
////////////////////////////////////////////////////////////////
#include "pch.renderer.h"
#include "../CommonRenderInterface/CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секци€ дл€ остального
////////////////////////////////////////////////////////////////
#include "technique.h"

namespace FE {

	namespace RENDERER {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*! \brief
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CTechniquePass {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*! \brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			CTechniquePass(Technique technique);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*! \brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void create(const TECHNIQUE_PASS *createInfo);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*! \brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			bool find(const MESH_CREATE_INFO *meshCreateInfo);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*! \brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void addPipeline(const CRI::CRIPipeline criPipeline);

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*! \brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline const CRI::CRIRenderPass getCRIRenderPass(void) const { return m_criRenderPass; }

		private:

			Technique				m_technique;
			CRI::CRIRenderPass		m_criRenderPass;
			CRI::CRIPipelineArr		m_criPipelines;

		}; // class CTechniquePass
		using TechniquePass = CTechniquePass * ;
		using TechniquePassArr = std::vector<TechniquePass>;

	} // RENDERER

} // FE

#endif // TECHNIQUE_PASS__H