#ifndef RENDERER__H
#define RENDERER__H
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
#include "../CommonRenderInterface/CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////
#include <Windows.h>
#include "..\Core.h"
#include <vector>

namespace FE {

	namespace RENDERER {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*! \brief Исключения.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class e_renderer_create_failed : public e_renderer {};



		



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Информация для создания Renderer.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct RENDERER_CREATE_INFO {

			enum class TYPE {

				UNKNOWN,
				FORWARD,
				DEFFERED
			};

			HWND					m_HWnd;
			FE::CORE::Core			m_Core = nullptr;
			TYPE				m_Technique = TYPE::UNKNOWN;

		}; // struct RENDERER_CREATE_INFO



		struct RendererSubpassDescription {

			CRI::CRIPipelineArr				m_CRIPipelines;
		};
		using RendererSubpassDescriptionArr = std::vector<RendererSubpassDescription>;

		struct RendererPassDescription {

			CRI::CRIRenderPass					m_CRIRenderPass;
			RendererSubpassDescriptionArr		m_RendererSubpassDescriptions;
		};
		using RendererPassDescriptionArr = std::vector<RendererPassDescription>;

		enum SHADER_STAGE {

			VERTEX,
			GEOMETRY,
			FRAGMENT
		};

		struct CShaderDescription {
			enum class TYPE0 {

				DEFAULT = 0,
				TRANSFER,
				QUAD

			};
			enum class TYPE1 {

				DEFAULT = 0,
				BILLBOARD = 1

			};
			enum class TYPE2 {

				DEFAULT = 0,
				TESSELATION = 1

			};
			enum class TYPE3 {

				DEFAULT = 0,
				MRT,
				LAMBERT,
				WRAP_ARROUBND
			};
			enum class TYPE4 {
				POSITION	= 0x00000001,
				COLOR		= 0x00000002,
				NORMAL		= 0x00000004
			};
			TYPE0				m_type0;
			TYPE1				m_type1;
			TYPE2				m_type2;
			TYPE3				m_type3;
			CRI::CRIProgram		m_criProgramm;
		};
		using ShaderDescriptionArr = std::vector<CShaderDescription>;

		enum class EFFECT_TYPE {

			BILLBOARD,
			PN_TRIANGLE
		};

		//struct CPipelineDescription {

		//	CRI::CRIPipeline				m_criPipeline;
		//	VERTEX_ATTRIBUTE_LAYOUTS		m_VertexAttributeLayouts;
		//};
		//using PipelineDescriptionArr = std::vector<CPipelineDescription>;

		//struct CRendererTechniquePass {
		//public:

			// add//

		//	CRI::CRIRenderPass			m_criRenderPass;
		//	PipelineDescriptionArr		m_pipelines;

		//};
		//using RendererTechniquePassArr = std::vector<CRendererTechniquePass>;

		//class CRendererTechniquie {
		//public:
		//	RendererTechniquePassArr		m_TechniquePasses;
		//};
		//using RendererTechniquieArr = std::vector<CRendererTechniquie>;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CRenderer {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Зарегистрировать новый объект.

			\param[in] drawPackage Объект для регистрации.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void reg(DrawPackage drawPackage);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Создать объект.

			\param[in] renderer Владеет объектом.
			\param[out] mesh Полученный объект.
			\param[in] createInfo Информация для создания.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			static void create(Renderer renderer, Mesh *mesh, const MESH_CREATE_INFO *createInfo = nullptr);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Создать объект.

			\param[in] renderer Владеет объектом.
			\param[out] drawPackage Полученный объект.
			\param[in] createInfo Информация для создания.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			static void create(Renderer renderer, DrawPackage *drawPackage, const DRAW_PACKAGE_CREATE_INFO *createInfo = nullptr);

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//!	\brief Конструктор.

			// \param[in] core Владеет объектом.
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			CRenderer(CORE::Core core);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Получить Core.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			CORE::Core getCore(void) const;

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Создать объект.

			\param[in] createInfo Информация для создания.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void create(const RENDERER_CREATE_INFO *createInfo);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Получить CREATE_INFO.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			const RENDERER_CREATE_INFO& getCreateInfo(void) const;

			void addObjects(SCENE::SceneObjectArr *sceneObjects);
			inline FE::CRI::CRIContext getContext(void) { return m_Context; }
		public:

			void destroy(void);

		protected:
			friend class CMesh;
			friend class CEffect;

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			CRI::CRIRenderPass getInputRenderPass(void) const;


		public:

			FE::CRI::CRIContext				m_Context;
			FE::CRI::CRIRenderPassArr		m_RenderPasses;			

			//void add(const FE::SCENE::ObjectArr *object);

			void update(void);

			void execute(void);

			~CRenderer();

		private:

			void createDefferedTechnique(void);

			void createForwardTechnique(void);

		public:

			uint32_t						m_IDInputCRIRenderPass;
			uint32_t						m_IDInputCRIRenderSubpass;
			CRI::CRIRenderPassArr			m_CRIRenderPasses;
			CRI::CRIRenderPass				m_R0;
			CRI::CRIRenderPass				m_R1;
			CRI::CRIDataBuffer				m_VB;
			CRI::CRIDataBuffer				m_IB;
			CRI::CRIDataBuffer				m_UB;
			CRI::CRIImageBufferArr			m_ImageBuffers;
			CRI::CRIPipeline				m_P0;
			CRI::CRIPipeline				m_P1;

		// данные
		private:

			CORE::Core							m_Core;
			RENDERER_CREATE_INFO				m_CreateInfo;

			//RendererPassDescriptionArr		m_RendererPassDescriptions;
			MeshArr								m_Meshes;				
			EffectArr							m_Effects;
			DrawPackageArr						m_DrawPackages;
			GeometryArr							m_Geometrys;		
			PARTICLES::ParticlesArr				m_Particles;
			
			TechniqueArr						m_Techniques;
			ShaderDescriptionArr				m_shaders;
		};

	}

}

#endif // RENDERER__H
