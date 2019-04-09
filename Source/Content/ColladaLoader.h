#ifndef COLLADA_LOADER__H
#define COLLADA_LOADER__H
////////////////////////////////////////////////////////////////
// ������ ���������� �����
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ ������������� ������
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ �������-����������
////////////////////////////////////////////////////////////////
#include "FContent.h"
#include "../Renderer/pch.renderer.h"
////////////////////////////////////////////////////////////////
// ������ ��� ����������
////////////////////////////////////////////////////////////////
#include "Text.h"
#include <map>

namespace FE {

	namespace CONTENT {
		
		struct ColladaPolylist;
		struct ColladaVertices;
		struct ColladaSource;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief ��������� ��������� ��� ������.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ColladaTag {

			std::string m_Name;												///< �������� ����
			std::map<std::string, std::string> m_Attributes;				///< �������� ����
		
		}; // struct ColladaTag



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief ��������� <float_array>
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ColladaFloatArray {

			std::string		m_ID;			///< ������������� ����.
			floatArr		m_Data;			///< ������ float �������.
			uint32_t		m_Stride;		///<

		}; // struct ColladaFloatArray



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief ��������� <input>
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ColladaInput {

			uint32_t		m_Offset;		///< �������� �������.
			std::string		m_IDSource;		///< ������������� �������.

		}; // struct ColladaInput



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief ��������� <vcount>
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ColladaVCount {

			uint32Arr		m_Data;			///< ������ uint �������.

		}; // struct ColladaVCount



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief ��������� <p>
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ColladaP {

			uint32Arr		m_Data;			///< ������ uint �������.

		}; // struct ColladaP



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief ��������� <polylist>
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ColladaPolylist {

			std::vector<ColladaInput>		m_Inputs;		///< �������� ������� <input
			ColladaVCount					m_VCount;		///< �������� ������� <vcount
			ColladaP						m_P;			///< �������� ������� <p

			uint32_t						m_PStride;
			std::vector<uint16_t>			m_Offsets;

		}; // struct ColladaPolylist



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief ��������� <vertices>
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
		/*!	\brief ��������� <mesh>
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ColladaMesh {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline ColladaVertices& findVertices(std::string id) {

				// ���������� ��� <polylist>
				for (uint32_t ctVertices = 0; ctVertices < m_Vertices.size(); ++ctVertices) {

					std::string _id = id.substr(1);

					auto &_itVertices = m_Vertices[ctVertices];
					if (_itVertices.getID() == _id) return _itVertices;
				}
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline ColladaSource& findSource(std::string id) {

				// ���������� ��� <polylist>
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
		/*!	\brief ��������� ������ ������.
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ColladaObject {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief ������� ����� ColladaMesh � ������� ������ �� ����.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			inline ColladaMesh* newMesh(void) { 
				m_Mesh.resize(m_Mesh.size() + 1);
				return &m_Mesh.back();
			}

		// ������
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
		/*!	\brief ��������� ������ collada
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
			/*!	\brief ��������� ���� ������.

			\param[out] tag ������������ ��� ������.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void getTag(ColladaTag *tag, CText *text);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �������� <mesh>

			\param[in] ���, ����������� <mesh>.
			\param[in] ColladaObject, ������ ������ �������� <mesh>
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void loadMesh(ColladaTag *tag, ColladaObject *object, CText *text);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �������� <source>

			\param[in] ���, ����������� <source>.
			\param[in] <mesh>, ������ ������ �������� <source>
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void loadSource(ColladaTag *tag, ColladaMesh *mesh, CText *text);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �������� <vertices>

			\param[in] ���, ����������� <vertices>.
			\param[in] <mesh>, ������ ������ �������� <vertices>
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void loadVertices(ColladaTag *tag, ColladaMesh *mesh, CText *text);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �������� <polylist>

			\param[in] ���, ����������� <polylist>.
			\param[in] <mesh>, ������ ������ �������� <polylist>
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void loadPolylist(ColladaTag *tag, ColladaMesh *mesh, CText *text);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �������� <input>

			\param[in] ���, ����������� <input>.
			\param[in] <polylist>, ������ ������ �������� <input>
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void loadInput(ColladaTag *tag, ColladaPolylist *polylist, CText *text);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �������� <input>

			\param[in] ���, ����������� <input>.
			\param[in] <vertices>, ������ ������ �������� <input>
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void loadInput(ColladaTag *tag, ColladaVertices *vertices, CText *text);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �������� <vcount>

			\param[in] ���, ����������� <vcount>.
			\param[in] <polylist>, ������ ������ �������� <vcount>
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void loadVCount(ColladaTag *tag, ColladaPolylist *polylist, CText *text);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �������� <p>

			\param[in] ���, ����������� <p>.
			\param[in] <polylist>, ������ ������ �������� <p>
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void loadP(ColladaTag *tag, ColladaPolylist *polylist, CText *text);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief �������� <float_array>

			\param[in] ���, ����������� <float_array>.
			\param[in] <source>, ������ ������ �������� <float_array>
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void loadFloatArray(ColladaTag *tag, ColladaSource *source, CText *text);

			

			CText m_text;

		}; // class CColladaLoader

	} // namespace CONTENT

} // namespace FE

#endif // COLLADA_LOADER__H