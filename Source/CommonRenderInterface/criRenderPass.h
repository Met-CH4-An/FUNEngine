#ifndef CRI_RENDER_PASS__H
#define CRI_RENDER_PASS__H
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
#include "../Maths/maths.h"
#include <vector>

namespace FE {

	namespace CRI {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class e_render_pass_create_failed : public std::exception {};



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief �������� ���������.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CRI_RENDER_PASS_ATTACHMENT_CI {

			enum class TYPE {

				UNKNOWN,
				INPUT,
				OUTPUT
			};

			CRIImageBuffer			m_Texture = nullptr;
			TYPE					m_Type = TYPE::UNKNOWN;

		}; // struct CRI_RENDER_PASS_ATTACHMENT_CI
		using CRI_RENDER_PASS_ATTACHMENT_CI_ARR = std::vector<CRI_RENDER_PASS_ATTACHMENT_CI>;



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief ���������� ��� �������� CRIRenderPass.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CRI_RENDER_PASS_CI {

			CRIContext										m_CRIContext = nullptr;
			int32_t											m_Width = -1;
			int32_t											m_Height = -1;
			vec4											m_ClearValue = vec4(-1.0f, -1.0f, -1.0f, -1.0f);
			CRI_RENDER_PASS_ATTACHMENT_CI_ARR				m_Attachments;
			bool											m_Present = false;

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �������� ������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			bool isValid(void) const;

		}; // struct CRI_RENDER_PASS_CI



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief ������ ���������.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CCRIRenderPass {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �������� ������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			static CRIRenderPass create(CRIContext criContext, const CRI_RENDER_PASS_CI *createInfo);

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �����������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			CCRIRenderPass();

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief ����������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			~CCRIRenderPass();

			inline uint32_t getIDSubpass(void) { return m_IDSubpass; }

		public:

			void setIDSubpass(uint32_t idSubpass) {	m_IDSubpass = idSubpass	; }

		private:
			
			CRIContext		m_CRIContext;
			uint32_t		m_IDSubpass;

		}; // CCRIRenderPass

	} // namespace RENDER

} // namespace FE

#include "CRIRenderPass.hpp"

#endif // CRI_RENDER_PASS__H