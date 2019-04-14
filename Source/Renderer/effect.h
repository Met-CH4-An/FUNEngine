#ifndef EFFECT__H
#define EFFECT__H
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
#include "..\Common\FCommon.h"
#include "../CommonRenderInterface/CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////
#include "Mesh.h"

namespace FE {

	namespace RENDERER {

		struct MATERIAL_CREATE_INFO {


		};


		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Информация для создания эффекта.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct EFFECT_CREATE_INFO {

			enum class TYPE0 {

				DEFAULT = 0,
				TRANSFER,
				QUAD

			};

			enum class TYPE1 {

				DEFAULT				= 0,
				BILLBOARD			= 1
				
			};

			enum class TYPE2 {

				DEFAULT				= 0,
				TESSELATION			= 1

			};

			enum class TYPE3 {

				DEFAULT				= 0,
				MRT,			
				LAMBERT,
				WRAP_ARROUBND
			};

			TYPE0		m_Type0;
			TYPE1		m_Type1;
			TYPE2		m_Type2;
			TYPE3		m_Type3;
			VERTEX_ATTRIBUTE_LAYOUTS		m_VertexAttributeLayouts;

		}; // struct EFFECT_CREATE_INFO
		


		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CEffect {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//!	\brief 
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			static Effect create(const EFFECT_CREATE_INFO *createInfo);

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//!	\brief Конструктор.
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			CEffect(void);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//!	\brief Деструктор.
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			~CEffect(void);

		private:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void create(void);

		//данные
		private:

			Renderer					m_Renderer;
			EFFECT_CREATE_INFO			m_CreateInfo;
			CRI::CRIPipeline			m_Pipeline;

		}; // class CEffect

	} // namespace RENDERER

} // namespace FE

#endif //EFFECT__H