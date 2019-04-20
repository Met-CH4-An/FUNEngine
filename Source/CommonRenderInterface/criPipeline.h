#ifndef CRI_PIPELINE__H
#define CRI_PIPELINE__H
////////////////////////////////////////////////////////////////
// ������ ���������� �����
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ ������������� ������
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ �������-����������
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// ������ ��� ����������
////////////////////////////////////////////////////////////////
#include "../Common/Format.h"

namespace FE {

	namespace CRI {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief �������� ����������.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CRI_PIPELINE_INPUT_PRIMITIVE {

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief ��������� ����������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			enum class TOPOLOGY {

				UNKNOWN = -1,
				TRIANGLE_LIST = 0

			}; // enum class TOPOLOGY 

			TOPOLOGY	m_Topology = TOPOLOGY::UNKNOWN;

		}; // struct CRI_PIPELINE_INPUT_PRIMITIVE



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief �������� ������������.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CRI_PIPELINE_RASTERIZATION {

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief ����������� ��������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			enum class POLYGON {

				UNKNOWN = -1,
				FILL = 0,
				LINE = 1,
				POINT = 2

			}; // enum class POLYGON

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief ����� ���������.
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
			/*!	\brief ����������� �������� ������.
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
		/*!	\brief �������� ��������.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CRI_PIPELINE_SHADER {

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief ������ �������.
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
		/*!	\brief �������� ������ �������.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CRI_PIPELINE_UNIFORM_BINDING {

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief ��� ��������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			enum class TYPE {

				UNKNOWN = -1,
				UNIFORM = 0,
				INPUT = 1

			}; // enum class TYPE

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief ��� ������.
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

		}; // struct PIPELINE_UNIFORM_LAYOUT
		using CRI_PIPELINE_UNIFORM_LAYOUT = std::vector<CRI_PIPELINE_UNIFORM_BINDING>;
		using CRI_PIPELINE_UNIFORM_DESCRIPTION = std::vector<CRI_PIPELINE_UNIFORM_LAYOUT>;



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief �������� ������ ������.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CRI_PIPELINE_VERTEX_BINDING {

			COMMON::FORMAT::DATA		m_Format = COMMON::FORMAT::DATA::UNKNOWN;
			uint32_t					m_Offset = 0;

		}; // struct PIPELINE_VERTEX_LAYOUT
		using CRI_PIPELINE_VERTEX_LAYOUT = std::vector<CRI_PIPELINE_VERTEX_BINDING>;
		using CRI_PIPELINE_VERTEX_DESCRIPTION = std::vector<CRI_PIPELINE_VERTEX_LAYOUT>;



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief ���������� ��� �������� CRIPipeline.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CRI_PIPELINE_CI {

			CRIContext									m_criContext = nullptr;
			CRIRenderPass								m_RenderPass = nullptr;
			CRIProgram									m_criProgram = nullptr;
			CRI_PIPELINE_INPUT_PRIMITIVE				m_InputAssembly;
			CRI_PIPELINE_RASTERIZATION					m_Rasterization;
			CRI_PIPELINE_SHADER_ARR						m_Shader;
			CRI_PIPELINE_UNIFORM_DESCRIPTION			m_UniformDescription;
			CRI_PIPELINE_VERTEX_DESCRIPTION				m_VertexLayout;

		}; // struct CRI_PIPELINE_CI



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CCRIPipeline {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �����������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			CCRIPipeline();

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief ��������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void create(const CRI_PIPELINE_CI *criCreateInfo);
			
		}; // CCRIPipeline

	} // namespace RENDER

} // namespace FE

#include "CRIPipeline.hpp"

#endif // CRI_PIPELINE__H