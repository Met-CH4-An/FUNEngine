#ifndef SHADER_COLLECTION__H
#define SHADER_COLLECTION__H
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
#include "renderer.h"
#include "mesh.h"

namespace FE {

	namespace RENDERER {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct SHADER_EFFECT_DESCRIPTION {

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			enum class VERTEX {

				DEFAULT
			};
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			enum class TESSELATION {

				DEFAULT
			};
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			enum class GEOMETRY {

				DEFAULT
			};
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			enum class FRAGMENT {

				DEFAULT,
				GBUFFER,
				LIGHTING_GBUFFER
			};

			VERTEX				m_vertex = VERTEX::DEFAULT;
			TESSELATION			m_teselation = TESSELATION::DEFAULT;
			GEOMETRY			m_geometry = GEOMETRY::DEFAULT;
			FRAGMENT			m_fragment = FRAGMENT::DEFAULT;

		}; // struct SHADER_DESCRIPTION

		enum class TYPE {

			DEFFERED_MRT,
			DEFFERED_LIGHTING,
			LIGHTING
		};

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CShader {

			MESH_ATTRIBUTE_DECLARATION		m_meshAttributes;
			CRI::CRIProgram					m_criProgram;
		};
		using Shader = CShader*;
		using ShaderArr = std::vector<Shader>;



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct SHADER_COLLECTION_CREATE_INFO {

			Renderer		m_renderer;

		}; // struct SHADER_COLLECTION_CREATE_INFO



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CShaderCollection {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void create(const SHADER_COLLECTION_CREATE_INFO* createInfo);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void getShader(const SHADER_EFFECT_DESCRIPTION shaderEffectDescription);

		private:

			Renderer		m_renderer;
			ShaderArr		m_shaders;

		}; // class CShaderCollection

	} // namespace RENDERER

} // namespace FE

#endif // SHADER_COLLECTION__H