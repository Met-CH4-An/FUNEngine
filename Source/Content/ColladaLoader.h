#ifndef COLLADA_LOADER__H
#define COLLADA_LOADER__H
////////////////////////////////////////////////////////////////
// секция компиляция файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция родительского класса
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция форвард-декларации
////////////////////////////////////////////////////////////////
#include "FContent.h"
#include "../Renderer/pch.renderer.h"
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////
#include "Text.h"
#include <map>

namespace FE {

	namespace CONTENT {
		
		struct ColladaPolylist;
		struct ColladaVertices;
		struct ColladaSource;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Структура описывает тег колады.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ColladaTag {

			std::string m_Name;												///< Название тега
			std::map<std::string, std::string> m_Attributes;				///< Атрибуты тега
		
		}; // struct ColladaTag



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Описывает <float_array>
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ColladaFloatArray {

			std::string		m_ID;			///< Идентификатор тега.
			floatArr		m_Data;			///< Данные float массива.
			uint32_t		m_Stride;		///<

		}; // struct ColladaFloatArray



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Описывает <input>
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ColladaInput {

			uint32_t		m_Offset;		///< Смещение ресурса.
			std::string		m_IDSource;		///< Идентификатор ресурса.

		}; // struct ColladaInput



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Описывает <vcount>
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ColladaVCount {

			uint32Arr		m_Data;			///< Данные uint массива.

		}; // struct ColladaVCount



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Описывает <p>
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ColladaP {

			uint32Arr		m_Data;			///< Данные uint массива.

		}; // struct ColladaP



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Описывает <polylist>
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ColladaPolylist {

			std::vector<ColladaInput>		m_Inputs;		///< Описание массива <input
			ColladaVCount					m_VCount;		///< Описание массива <vcount
			ColladaP						m_P;			///< Описание массива <p

			uint32_t						m_PStride;
			std::vector<uint16_t>			m_Offsets;

		}; // struct ColladaPolylist



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Описывает <vertices>
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ColladaVertices {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ColladaVertices(std::string id) { m_ID = id; }

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline std::string getID(void) { return m_ID; }

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline ColladaInput* newInput() {
				m_Inputs.emplace_back(ColladaInput());
				return &m_Inputs.back();
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline const std::vector<ColladaInput>* getInputs() {
				return &m_Inputs;
			}

		private:

			std::string						m_ID;
			std::vector<ColladaInput>		m_Inputs;

		}; // struct ColladaVertices



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ColladaSource {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ColladaSource(std::string id) { m_ID = id; }

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline std::string getID(void) { return m_ID; }

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline ColladaFloatArray* newFloatArray() {
				m_FloatArrays.resize(m_FloatArrays.size() + 1);
				return &m_FloatArrays.back();
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline const std::vector<ColladaFloatArray>* getFloatArrays() {
				return &m_FloatArrays;
			}

		private:

			std::string							m_ID;
			std::vector<ColladaFloatArray>		m_FloatArrays;
		
		}; // struct ColladaSource



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Описывает <mesh>
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ColladaMesh {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline ColladaVertices& findVertices(std::string id) {

				// перебираем все <polylist>
				for (uint32_t ctVertices = 0; ctVertices < m_Vertices.size(); ++ctVertices) {

					std::string _id = id.substr(1);

					auto &_itVertices = m_Vertices[ctVertices];
					if (_itVertices.getID() == _id) return _itVertices;
				}
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline ColladaSource& findSource(std::string id) {

				// перебираем все <polylist>
				for (uint32_t ctSource = 0; ctSource < m_Sources.size(); ++ctSource) {

					std::string _id = id.substr(1);

					auto &_itSource = m_Sources[ctSource];
					if (_itSource.getID() == _id) return _itSource;
				}
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline ColladaSource* newSource(std::string id) {
				m_Sources.emplace_back(ColladaSource(id));
				return &m_Sources.back();
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline ColladaVertices* newVertices(std::string id) {
				m_Vertices.emplace_back(ColladaVertices(id));
				return &m_Vertices.back();
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline ColladaPolylist* newPolylist() {
				m_Polylists.resize(m_Polylists.size() + 1);
				return &m_Polylists.back();
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline const std::vector<ColladaSource>* getSources(void) { return &m_Sources; }

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline const std::vector<ColladaVertices>* getVertices(void) { return &m_Vertices; }

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline const std::vector<ColladaPolylist>* getPolylists(void) { return &m_Polylists; }

		private:

			std::vector<ColladaSource>				m_Sources;
			std::vector<ColladaVertices>			m_Vertices;
			std::vector<ColladaPolylist>			m_Polylists;

		}; // struct ColladaMesh



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Описывает объект колады.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ColladaObject {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Создать новый ColladaMesh и вернуть ссылку на него.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline ColladaMesh* newMesh(void) { 
				m_Mesh.resize(m_Mesh.size() + 1);
				return &m_Mesh.back();
			}

		// данные
		private:

			std::vector<ColladaMesh>		m_Mesh;
		
		}; // struct ColladaObject



		struct TestObject {

			std::vector<std::vector<float>>		m_Data;
		};



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct COLLADA_LOADER_CREATE_INFO {


		};
		

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief Загрузчик файлов collada
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		class CColladaLoader {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void load(ContentObject object,  CText *text);

		// 
		private:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Получение тега колады.

			\param[out] tag Возвращаемый тег колады.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void getTag(ColladaTag *tag, CText *text);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Загрузка <mesh>

			\param[in] Тег, описывающий <mesh>.
			\param[in] ColladaObject, котрый вызвал загрузку <mesh>
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void loadMesh(ColladaTag *tag, ColladaObject *object, CText *text);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Загрузка <source>

			\param[in] Тег, описывающий <source>.
			\param[in] <mesh>, котрый вызвал загрузку <source>
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void loadSource(ColladaTag *tag, ColladaMesh *mesh, CText *text);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Загрузка <vertices>

			\param[in] Тег, описывающий <vertices>.
			\param[in] <mesh>, котрый вызвал загрузку <vertices>
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void loadVertices(ColladaTag *tag, ColladaMesh *mesh, CText *text);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Загрузка <polylist>

			\param[in] Тег, описывающий <polylist>.
			\param[in] <mesh>, котрый вызвал загрузку <polylist>
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void loadPolylist(ColladaTag *tag, ColladaMesh *mesh, CText *text);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Загрузка <input>

			\param[in] Тег, описывающий <input>.
			\param[in] <polylist>, котрый вызвал загрузку <input>
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void loadInput(ColladaTag *tag, ColladaPolylist *polylist, CText *text);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Загрузка <input>

			\param[in] Тег, описывающий <input>.
			\param[in] <vertices>, котрый вызвал загрузку <input>
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void loadInput(ColladaTag *tag, ColladaVertices *vertices, CText *text);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Загрузка <vcount>

			\param[in] Тег, описывающий <vcount>.
			\param[in] <polylist>, котрый вызвал загрузку <vcount>
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void loadVCount(ColladaTag *tag, ColladaPolylist *polylist, CText *text);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Загрузка <p>

			\param[in] Тег, описывающий <p>.
			\param[in] <polylist>, котрый вызвал загрузку <p>
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void loadP(ColladaTag *tag, ColladaPolylist *polylist, CText *text);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Загрузка <float_array>

			\param[in] Тег, описывающий <float_array>.
			\param[in] <source>, котрый вызвал загрузку <float_array>
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void loadFloatArray(ColladaTag *tag, ColladaSource *source, CText *text);

			

			CText m_text;

		}; // class CColladaLoader

	} // namespace CONTENT

} // namespace FE

#endif // COLLADA_LOADER__H