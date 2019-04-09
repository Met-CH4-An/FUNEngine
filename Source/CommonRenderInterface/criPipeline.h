#ifndef CRI_PIPELINE__H
#define CRI_PIPELINE__H
////////////////////////////////////////////////////////////////
// секция компиляция файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция родительского класса
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция форвард-декларации
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////
#include "../Common/Format.h"

namespace FE {

	namespace CRI {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Описание примитивов.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CRI_PIPELINE_INPUT_PRIMITIVE {

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Топология примитивов.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			enum class TOPOLOGY {

				UNKNOWN = -1,
				TRIANGLE_LIST = 0

			}; // enum class TOPOLOGY 

			TOPOLOGY	m_Topology = TOPOLOGY::UNKNOWN;

		}; // struct CRI_PIPELINE_INPUT_PRIMITIVE



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Описание растеризации.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CRI_PIPELINE_RASTERIZATION {

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Отображения полигона.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			enum class POLYGON {

				UNKNOWN = -1,
				FILL = 0,
				LINE = 1,
				POINT = 2

			}; // enum class POLYGON

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Режим отсечения.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			enum class CULL {

				UNKNOWN = -1,
				NONE = 0,
				FRONT = 1,
				BACK = 2,
				FRONT_AND_BACK = 3

			}; // enum class CULL

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Определение передних граней.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			enum class FRONT_FACE {

				UNKNOWN = -1,
				COUNTER_CLOCKWISE = 0,
				CLOCKWISE = 1

			}; // enum class FRONT_FACE

			POLYGON			m_Polygon = POLYGON::UNKNOWN;
			CULL			m_Cull = CULL::UNKNOWN;
			FRONT_FACE		m_FrontFace = FRONT_FACE::UNKNOWN;
			float			m_LineWidth = 1.0f;

		}; // struct PIPELINE_RASTERIZATION



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Описание шейдеров.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CRI_PIPELINE_SHADER {

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Стадия шейдера.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			enum class STAGE {

				UNKNOWN = -1,
				VERTEX = 0,
				TES_CONTROL = 1,
				TES_EVALUATION = 2,
				GEOMETRY = 3,
				FRAGMENT = 4

			}; // enum class STAGE

			STAGE			m_Stage = STAGE::UNKNOWN;
			std::string		m_Code;

		}; // struct PIPELINE_SHADER
		using CRI_PIPELINE_SHADER_ARR = std::vector<CRI_PIPELINE_SHADER>;



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Описание макета юниформ.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CRI_PIPELINE_UNIFORM_LAYOUT {

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Описание биндингов внутри макета.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			struct BINDING {

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Тип биндинга.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				enum class TYPE {

					UNKNOWN = -1,
					UNIFORM = 0,
					INPUT = 1

				}; // enum class TYPE

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				/*!	\brief Тип стадии.
				*/
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				enum class STAGE {

					UNKNOWN = -1,
					VERTEX = 0,
					TES_CONTROL = 1,
					TES_EVALUATION = 2,
					GEOMETRY = 3,
					FRAGMENT = 4

				}; // enum class STAGE

				TYPE	m_Type = TYPE::UNKNOWN;
				STAGE	m_Stage = STAGE::UNKNOWN;

			}; // struct BINDING

		}; // struct PIPELINE_UNIFORM_LAYOUT
		using CRI_PIPELINE_UNIFORM_BINDING_ARR = std::vector<CRI_PIPELINE_UNIFORM_LAYOUT::BINDING>;
		using CRI_PIPELINE_UNIFORM_LAYOUT_ARR = std::vector<CRI_PIPELINE_UNIFORM_BINDING_ARR>;



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Описание макета вершин.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CRI_PIPELINE_VERTEX_LAYOUT {

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Описание атрибута внутри макета.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			struct ATTRIBUTE {

				COMMON::FORMAT::DATA		m_Format = COMMON::FORMAT::DATA::UNKNOWN;
				uint32_t					m_Offset = 0;

			}; // struct ATTRIBUTE

		}; // struct PIPELINE_VERTEX_LAYOUT
		using CRI_PIPELINE_VERTEX_LAYOUT_ATTRIBUTE_ARR = std::vector<CRI_PIPELINE_VERTEX_LAYOUT::ATTRIBUTE>;
		using CRI_PIPELINE_VERTEX_LAYOUT_ARR = std::vector<CRI_PIPELINE_VERTEX_LAYOUT_ATTRIBUTE_ARR>;



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Информация для создания CRIPipeline.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CRI_PIPELINE_CI {

			CRIContext							m_criContext = nullptr;
			CRIRenderPass						m_RenderPass = nullptr;
			CRIProgram							m_criProgram = nullptr;
			CRI_PIPELINE_INPUT_PRIMITIVE		m_InputAssembly;
			CRI_PIPELINE_RASTERIZATION			m_Rasterization;
			CRI_PIPELINE_SHADER_ARR				m_Shader;
			CRI_PIPELINE_UNIFORM_LAYOUT_ARR		m_Uniformlayout;
			CRI_PIPELINE_VERTEX_LAYOUT_ARR		m_VertexLayout;

		}; // struct CRI_PIPELINE_CI



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CCRIPipeline {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Создание.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			static CRIPipeline create(const CRI_PIPELINE_CI *criCreateInfo);

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Конструктор.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			CCRIPipeline();
			
		}; // CCRIPipeline

	} // namespace RENDER

} // namespace FE

#include "CRIPipeline.hpp"

#endif // CRI_PIPELINE__H