#ifndef CONTENT__H
#define CONTENT__H
////////////////////////////////////////////////////////////////
// секци€ компил€ци€ файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секци€ родительского класса
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секци€ форвард-декларации
////////////////////////////////////////////////////////////////
#include "FContent.h"
#include "..\Scene\FScene.h"
////////////////////////////////////////////////////////////////
// секци€ дл€ остального
////////////////////////////////////////////////////////////////
#include "..\Renderer\Mesh.h"

namespace FE {

	namespace CONTENT {

		//struct CONTENT {


		//};

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CONTENT_PROCEDURE_MESH_ATTRIBUTE {

			enum class TYPE {

				POSITION,
				COLOR,
				NORMAL,
				USER
			};

			TYPE		m_Type;
			uint32_t	m_Capacity;
		};
		using CONTENT_PROCEDURE_MESH_ATTRIBUTE_ARR = std::vector<CONTENT_PROCEDURE_MESH_ATTRIBUTE>;



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CONTENT_PROCEDURE_MESH {

			enum class FACE {

				CLOCKWISE,
				COUNTER_CLOCKWISE
			};

			RENDERER::Renderer							m_Renderer;
			FACE										m_Face;
			CONTENT_PROCEDURE_MESH_ATTRIBUTE_ARR		m_Attributes;
		};



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CONTENT_CREATE_INFO {

			SCENE::ScriptWriter					m_ScriptWriter;

		}; // struct CONTENT_CREATE_INFO



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CONTENT_PROCEDURE_SPHERE {

			CONTENT_CREATE_INFO						m_ContentCreateInfo;
			CONTENT_PROCEDURE_MESH					m_Mesh;
			RENDERER::Renderer						m_Renderer;
						uint32_t								m_Meridians;
			uint32_t								m_Parallels;
			float									m_Radius;
			uint32_t								m_PatchSize;

		};



		



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CContent {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void create(const CONTENT_CREATE_INFO *createInfo);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			File getFile(std::string fileName);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			File get(std::string fileName);

			void getProcedure(const CONTENT_PROCEDURE_SPHERE *createInfo, COMMON::Blob *vertices, COMMON::Blob *indices);

		private:

			FileArr		m_Files;

		}; // class CContent

	} // namespace CONTENT

} // namespace FE

#endif // CONTENT__H