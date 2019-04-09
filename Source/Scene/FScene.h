#ifndef FSCENE__H
#define FSCENE__H
////////////////////////////////////////////////////////////////
// секци€ компил€ци€ файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секци€ родительского класса
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секци€ форвард-декларации
////////////////////////////////////////////////////////////////
#include <vector>
#include <memory>

namespace FE {

	namespace SCENE {

		class		CScriptWriter;
		using		ScriptWriter = std::shared_ptr<CScriptWriter>;
		struct		SCRIPTWRITER_CREATE_INFO;

		class		CScene;
		using		Scene = std::shared_ptr<CScene>;
		using		SceneArr = std::vector<Scene>;
		struct		SCENE_CREATE_INFO;

		class		CScript;
		using		Script = std::shared_ptr<CScript>;
		using		ScriptArr = std::vector<Script>;
		struct		SCRIPT_CREATE_INFO;

		class		CSceneObject;
		using		SceneObject = std::shared_ptr<CSceneObject>;
		using		SceneObjectArr = std::vector<SceneObject>;
		struct		SCENE_OBJECT_CREATE_INFO;
		
		class		CCamera;
		using		Camera = CCamera*;
		using		CameraArr = std::vector<Camera>;

	}

}
//#include "..\Renderer\FRenderer.h"
////////////////////////////////////////////////////////////////
// секци€ дл€ остального
////////////////////////////////////////////////////////////////
//#include "..\PCH.h"

namespace FE {

	namespace SCENE {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class OPERATION {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief ќбновить множество Scene.

			\param scenes —цены дл€ обновлени€.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			static void update(SceneArr *scenes);

		}; // class OPERATION

	} // namespace SCENE

} // namespace FE

#endif // FSCENE__H
