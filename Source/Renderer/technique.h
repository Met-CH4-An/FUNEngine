#ifndef TECHNIQUE__H
#define TECHNIQUE__H
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
#include "Mesh.h"

#include <vector>

namespace FE {

	namespace RENDERER {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*! \brief
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct TECHNIQUE_SHADER {

			MESH_ATTRIBUTE_DECLARATION			m_attributeDeclaration;
		};
		using TECHNIQUE_SHADER_ARR = std::vector<TECHNIQUE_SHADER>;



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*! \brief
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct TECHNIQUE_TEXTURE {

			uint32_t					m_bind;
			uint32_t					m_width;
			uint32_t					m_height;
			COMMON::FORMAT::TEXTURE		m_format;
		};
		using TECHNIQUE_TEXTURE_ARR = std::vector<TECHNIQUE_TEXTURE>;



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*! \brief
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct TECHNIQUE_PASS {

			struct ATTACHMENT {

				enum class TYPE {

					INPUT,
					OUTPUT
				};

				uint32_t		m_bind;
				TYPE			m_type;
			};

			std::vector<ATTACHMENT>		m_attachmentDescs;
			std::vector<uint32_t>		m_inputTextureBinds;
			std::vector<uint32_t>		m_outputTextureBinds;
		};
		using TECHNIQUE_PASS_ARR = std::vector<TECHNIQUE_PASS>;



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*! \brief
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct TECHNIQUE_CREATE_INFO {

			TECHNIQUE_TEXTURE_ARR		m_textureDescs;
			TECHNIQUE_PASS_ARR			m_passDescs;
		};



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*! \brief
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CTechnique {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*! \brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			CTechnique(CRenderer* renderer);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*! \brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void create(const TECHNIQUE_CREATE_INFO *createInfo);

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*! \brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline Renderer getRenderer(void) const { return m_renderer; }

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*! \brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline const CRI::CRIImageBufferArr& getCRIImageBuffers(void) const { return m_criImageBuffers; }

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*! \brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline const TechniquePass getInputTechniquePass(void) { return m_inputPass; }

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*! \brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline const TechniquePass getOutputTechniquePass(void) { return m_outputPass; }

		private:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*! \brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			bool checkInputTexture(const TECHNIQUE_TEXTURE *textureDesc) const;
			
		private:

			CRenderer*						m_renderer;
			TECHNIQUE_CREATE_INFO			m_createInfo;
			TechniquePass					m_inputPass;
			TechniquePass					m_outputPass;
			TechniquePassArr				m_passes;

			CRI::CRIImageBufferArr			m_criImageBuffers;

		}; // class CTechnique

	} // namespace RENDERER

} // namespace FE

#endif // TECHNIQUE__H

