#ifndef PROCEDURAL__H
#define PROCEDURAL__H
////////////////////////////////////////////////////////////////
// секция компиляция файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция родительского класса
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция форвард-декларации
////////////////////////////////////////////////////////////////
#include "FProcedural.h"
#include "..\Common\FCommon.h"
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////
#include "..\Renderer\Mesh.h"

namespace FE {

	namespace PROCEDURAL {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Описание атрибута.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct PROCEDURAL_GEOMETRY_ATTRIBUTE {

			enum class SEMANTIC {

				POSITION,
				COLOR,
				NORMAL,
			};

			SEMANTIC		m_Semantic;
			size_t			m_Dimension;
		};
		using PROCEDURAL_GEOMETRY_ATTRIBUTE_ARR = std::vector<PROCEDURAL_GEOMETRY_ATTRIBUTE>;



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//!	\brief Опиание геометрии.
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct  PROCEDURAL_GEOMETRY {

			enum class PLACEMENT {

				AOS,
				SOA
			};

			PLACEMENT								m_Placement;
			PROCEDURAL_GEOMETRY_ATTRIBUTE_ARR		m_Attributes;
		};
		


		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Описание создания сферы.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct PROCEDURE_SPHERE_CREATE_INFO {
			
			RENDERER::Renderer			m_Renderer;
			PROCEDURAL_GEOMETRY			m_Geometry;
			uint32_t					m_Meridians;
			uint32_t					m_Parallels;
			float						m_Radius;
			uint32_t					m_PatchSize;
		
		};



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Описание создания спирали.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct PROCEDURE_HELIX_CREATE_INFO {

			size_t			m_StepXY;
			size_t			m_StepZ;
			size_t			m_Offset;

		};



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Описание создания спирали.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct PROCEDURE_OUTPUT {

			std::vector<COMMON::Blob>		m_Vertices;
			COMMON::Blob					m_Indices;
		};



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CProcedural {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Создание сферы.

			\param[in] createInfo Инфомрация для создания.
			\param[out] sceneObject Созданный объект.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void buildSphere(const PROCEDURE_SPHERE_CREATE_INFO *createInfo, RENDERER::Mesh *mesh, COMMON::Blob *vertices, COMMON::Blob *indices, SCENE::SceneObject sceneObject);

			void buildCylindricalHelix(const PROCEDURE_HELIX_CREATE_INFO *createInfo, PROCEDURE_OUTPUT *output);

		private:


		}; // class CProcedural		

	} // namespace PROCEDURAL

} // namespace FE

#endif // PROCEDURAL__H