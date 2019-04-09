#ifndef FRENDERER__H
#define FRENDERER__H
#define _CRT_SECURE_NO_WARNINGS
////////////////////////////////////////////////////////////////
// секци€ компил€ци€ файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секци€ родительского класса
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секци€ форвард-декларации
///////////////////////////////////////////////////////////////
#include "..\Particles\FParticles.h"
#include "..\Scene\FScene.h"
////////////////////////////////////////////////////////////////
// секци€ дл€ остального
////////////////////////////////////////////////////////////////
#include "../Common/Format.h"
#include <memory>
#include <vector>

namespace FE {

	namespace RENDERER {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		class e_renderer : public std::exception {};

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		class		CRenderer;
		using		Renderer = CRenderer*;
		using		RendererArr = std::vector<Renderer>;
		struct		RENDERER_CREATE_INFO;
		using		RENDERER_CREATE_INFO_ARR = std::vector<RENDERER_CREATE_INFO*>;

		class		CTechnique;
		using 		Technique = CTechnique*;
		using		TechniqueArr = std::vector<Technique>;

		class		CTechniquePass;
		using 		TechniquePass = CTechniquePass*;
		using		TechniquePassArr = std::vector<TechniquePass>;

		class		CDrawPackage;
		using		DrawPackage = std::shared_ptr<CDrawPackage>;
		using		DrawPackageArr = std::vector<DrawPackage>;
		struct		DRAW_PACKAGE_CREATE_INFO;

		class		CMesh;
		using		Mesh = std::shared_ptr<CMesh>;
		using		MeshArr = std::vector<Mesh>;
		struct		MESH_CREATE_INFO;

		class		CGeometry;
		using		Geometry = CGeometry*;
		using		GeometryArr = std::vector<Geometry>;
		struct		GEOMETRY_CREATE_INFO;
		using		GEOMETRY_CREATE_INFO_ARR = std::vector<GEOMETRY_CREATE_INFO>;

		class		CEffect;
		using		Effect = std::shared_ptr<CEffect>;
		using		EffectArr = std::vector<Effect>;
		struct		EFFECT_CREATE_INFO;
		using		EFFECT_CREATE_INFO_ARR = std::vector<EFFECT_CREATE_INFO>;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct VERTEX_ATTRIBUTE_BINDING {

			COMMON::FORMAT::DATA		m_Format = COMMON::FORMAT::DATA::UNKNOWN;
			int32_t						m_Offset = -1;

		};
		using VERTEX_ATTRIBUTE_LAYOUT = std::vector<VERTEX_ATTRIBUTE_BINDING>;
		using VERTEX_ATTRIBUTE_LAYOUTS = std::vector<VERTEX_ATTRIBUTE_LAYOUT>;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	} // namespace RENDERER

} // namespace FE

#endif // FRENDERER__H