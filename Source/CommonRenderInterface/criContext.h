#ifndef CRI_CONTEXT__H
#define CRI_CONTEXT__H
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
#include "../Renderer/pch.renderer.h"
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////
#include "../Core.h"
#include <Windows.h>

namespace FE {

	namespace CRI {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Информация для создания CRIContext под windows.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CRI_PLATFORM_CONTEXT_CREATE_INFO {

			HINSTANCE		m_Handle = NULL;
			HWND			m_HWnd = NULL;

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			bool isValid(void) const {
				if (m_Handle == NULL ||
					m_HWnd == NULL) return false;
				return true;
			}

		}; // struct CRI_PLATFORM_CONTEXT_CREATE_INFO



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Информация для создания CRIContext.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct CRI_CONTEXT_CREATE_INFO {

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			enum class TYPE {
				UNKNOWN,
				RELEASE,
				DEBUG
			};

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			enum class SYNC {
				UNKNOWN,
				NOT_VSYNC,
				VSYNC
			};

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			enum class BUFFERIZATION {
				UNKNOWN,
				DOUBLE,
				TRIPLE
			};

			size_t								m_Width = 0;
			size_t								m_Height = 0;
			TYPE								m_Type = TYPE::UNKNOWN;
			SYNC								m_Sync = SYNC::UNKNOWN;
			BUFFERIZATION						m_Bufferization = BUFFERIZATION::UNKNOWN;
			CRI_PLATFORM_CONTEXT_CREATE_INFO	m_PlatformInfo = {};

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			bool isValid(void) const {

				if (m_Width == 0 || m_Height == 0 ||
					m_Type == TYPE::UNKNOWN ||
					m_Sync == SYNC::UNKNOWN ||
					m_Bufferization == BUFFERIZATION::UNKNOWN ||
					!m_PlatformInfo.isValid()) return false;
				return true;
			}

		}; // struct CRI_CONTEXT_CREATE_INFO



		struct CRI_DRAW_OBJECT {

			CRIRenderPass		m_RednerPass;
			uint32_t			m_NumberSubPass;

		}; // struct CRI_DRAW_OBJECT



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Контекст рендера.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CCRIContext {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Получить объект.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			static CRIContext create(const CRI_CONTEXT_CREATE_INFO *createInfo);

		public:

			//void getPipeline(const CRI_PIPELINE_CI *criCreateInfo, CRIPipeline *criPipeline);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Создать объект.

			\param[in] criContext Владеет объектом.
			\param[out] criDataBuffer Полученный объект.
			\param[in] createInfo Информация для создания.			
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			static void create(CRIContext criContext, CRIDataBuffer *criDataBuffer, const CRI_DATA_BUFFER_CREATE_INFO *createInfo = nullptr);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Создать объект.

			\param[in] criContext Владеет объектом.
			\param[out] criImageBuffer Полученный объект.
			\param[in] createInfo Информация для создания.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//static void create(CRIContext criContext, CRIImageBuffer *criImageBuffer, const CRI_IMAGE_BUFFER_CREATE_INFO *createInfo = nullptr);

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Конструктор.

			\param[in] renderer Рендерер, который владеет объектом.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			CCRIContext(void);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Обновление контекста.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void update(void);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Выполнение контекста.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void execute(void);
		
		public:
			
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Получить информацию, по которой был создан объект.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline const CRI_CONTEXT_CREATE_INFO& getCreateInfo(void) const { return m_CreateInfo; }

		// данные
		private:

			RENDERER::Renderer			m_Renderer;
			CRI_CONTEXT_CREATE_INFO		m_CreateInfo;
			CRIDataBufferArr			m_DataBuffers;			

		}; // class CCRIContext

	} // namespace RENDER

} // namespace FE

#include "CRIContext.hpp"

#endif // CRI_CONTEXT__H