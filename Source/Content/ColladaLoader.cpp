////////////////////////////////////////////////////////////////
// ������ PCH
////////////////////////////////////////////////////////////////
#include "PCH.h"
////////////////////////////////////////////////////////////////
// ������ ������������� �����
////////////////////////////////////////////////////////////////
#include "ColladaLoader.h"
////////////////////////////////////////////////////////////////
// ������ ���������� �����
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ �������-����������
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ ��� ����������
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// ������ ��� ����������
////////////////////////////////////////////////////////////////
#include "ContentObject.h"

#include "..\Renderer\Mesh.h"

namespace FE {

	namespace CONTENT {
		
		//==============================================================
		//==============================================================

		void CColladaLoader::load(ContentObject object, CText *text) {

			ColladaObject _newColladaObject;

			std::vector<ColladaMesh> _cldMeshes;

			while (text->isValid()) {

				ColladaTag _newTag;

				// �������� ���
				getTag(&_newTag, text);

				// ���� ������ <mesh>
				if (_newTag.m_Name == "mesh") {
					
					loadMesh(&_newTag, &_newColladaObject, text);

				} // if

			} // while (text->isValid())

		}

		//==============================================================
		//==============================================================

		void CColladaLoader::getTag(ColladaTag *tag, CText *text) {

			char _tagText[1024];
			char _word[64];

			// �������� ������ � �����
			size_t _tagSize = text->getInfSup(_tagText, '<', '>');

			// ���� � ���������� ������ ������ ������ '/'
			if (_tagText[0] == '/') {

				tag->m_Name = _tagText;

				return;

			}

			// ����� 
			CText _tagTest;

			_tagTest.setData(_tagText, _tagSize);

			// �������� ������ ������������ � < � ��������������� ��������
			_tagTest.getToSupremum(_word, ' ');

			tag->m_Name = _word;

			// ���������� ������ � �����
			while (_tagTest.isValid()) {

				char _key[64];
				char _value[64];

				_tagTest.getWord(_key);
				_tagTest.getInfSup(_value, '\"', '\"');

				if (std::strcmp(_key, "") != 0) {

					tag->m_Attributes[_key] = _value;

				} // if
			} // while (_tagTest.isValid())
		}

		//==============================================================
		//==============================================================

		void CColladaLoader::loadMesh(ColladaTag *tag, ColladaObject *object, CText *text) {

			ColladaMesh *_newColladaMesh = object->newMesh();
			std::vector<uint32_t> _value;

			while (text->isValid()) {

				// ~~~~~~~~~~~~~~~~
				// ����� ���
				// ~~~~~~~~~~~~~~~~

				ColladaTag _newTag;

				getTag(&_newTag, text);

				// ~~~~~~~~~~~~~~~~
				// ������ </mesh>
				// ~~~~~~~~~~~~~~~~

				if (_newTag.m_Name == "/mesh") {

					std::vector<float> _output;
					
					// ���������� ��� <polylist>
					for (uint32_t ctPolylist = 0; ctPolylist < _newColladaMesh->getPolylists()->size(); ++ctPolylist) {

						//std::vector<std::vector<float>*> _input;
						std::vector<std::vector<const ColladaFloatArray*>> _input;			

						auto _itPolylist = _newColladaMesh->getPolylists()->at(ctPolylist);

						// ���������� <input> �� <polylist>
						for (uint32_t ctInput = 0; ctInput < _itPolylist.m_Inputs.size(); ++ctInput) {

							auto &_itInput = _itPolylist.m_Inputs[ctInput];

							auto & _itVertices = _newColladaMesh->findVertices(_itInput.m_IDSource);

							_input.resize(_input.size() + 1);

							// ���������� <input> �� <vertices>
							for (uint32_t ctInput = 0; ctInput < _itVertices.getInputs()->size(); ++ctInput) {

								auto &_itInput = _itVertices.getInputs()->at(ctInput);

								auto & _itSource = _newColladaMesh->findSource(_itInput.m_IDSource);

								// ���������� 
								for (uint32_t ctFloatArray = 0; ctFloatArray < _itSource.getFloatArrays()->size(); ++ctFloatArray) {

									auto &_itFloatArray = _itSource.getFloatArrays()->at(ctFloatArray);

									_input.back().push_back(&_itFloatArray);

									_output.resize(_output.size() + _itFloatArray.m_Data.size());
								}								
							}							
						}
						
						// ���������� ������������ �������� 
						auto _itMaxOffset = std::max_element(_itPolylist.m_Offsets.begin(), _itPolylist.m_Offsets.end());
						auto _PStride = _itPolylist.m_Offsets[std::distance(_itPolylist.m_Offsets.begin(), _itMaxOffset)] + 1;

						uint32_t _offsetInput = 0;
						uint32_t _offsetOutput = 0;
						uint32_t _maxStride = 8;
						for (uint32_t ctP = 0; ctP < _itPolylist.m_P.m_Data.size(); ctP += _PStride) {

							for (uint32_t ctOffset = 0; ctOffset < _itPolylist.m_Offsets.size(); ++ctOffset) {

								auto _itP = _itPolylist.m_P.m_Data[ctP + _itPolylist.m_Offsets[ctOffset]];

								uint32_t _offset = 0;

								for (uint32_t ctFloatArray = 0; ctFloatArray < _input[ctOffset].size(); ++ctFloatArray) {

									auto _itColladaFloatArray = _input[ctOffset][ctFloatArray];

									for (uint32_t ctStride = 0; ctStride < _itColladaFloatArray->m_Stride; ++ctStride) {
										
										_output[_offset + _maxStride * _itP + ctStride] = _itColladaFloatArray->m_Data[_itP * _itColladaFloatArray->m_Stride + ctStride];
								
									}

									_offset += _itColladaFloatArray->m_Stride;
				
								}
							}							
						}
					}

					return;

				}

				// ~~~~~~~~~~~~~~~~
				// ������ <source>
				// ~~~~~~~~~~~~~~~~

				if (_newTag.m_Name == "source") {

					loadSource(&_newTag, _newColladaMesh, text);

				}

				// ~~~~~~~~~~~~~~~~
				// ������ <vertices>
				// ~~~~~~~~~~~~~~~~

				if (_newTag.m_Name == "vertices") {

					loadVertices(&_newTag, _newColladaMesh, text);

				}

				// ~~~~~~~~~~~~~~~~
				// ������ <polylist>
				// ~~~~~~~~~~~~~~~~

				if (_newTag.m_Name == "polylist") {

					loadPolylist(&_newTag, _newColladaMesh, text);

				} // if 

			} // while (test->isValid())

			//cldMeshes->push_back(_newColladaMesh);

		}

		//==============================================================
		//==============================================================

		void CColladaLoader::loadSource(ColladaTag *tag, ColladaMesh *mesh, CText *text) {

			// ����� <vertices>
			auto _newColladaSource = mesh->newSource(tag->m_Attributes["id"]);

			while (text->isValid()) {

				// ~~~~~~~~~~~~~~~~
				// ����� ���
				// ~~~~~~~~~~~~~~~~

				ColladaTag _newTag;

				getTag(&_newTag, text);

				// ~~~~~~~~~~~~~~~~
				// ������ </source>
				// ~~~~~~~~~~~~~~~~

				if (_newTag.m_Name == "/source") break;

				// ~~~~~~~~~~~~~~~~
				// ������ <float_array>
				// ~~~~~~~~~~~~~~~~

				if (_newTag.m_Name == "float_array") {

					loadFloatArray(&_newTag, _newColladaSource, text);

				} // if (_newTag.m_Name == "float_array")

			} // while (text->isValid())

		}

		//==============================================================
		//==============================================================

		void CColladaLoader::loadVertices(ColladaTag *tag, ColladaMesh *mesh, CText *text) {

			// ����� <vertices>
			auto _newColladaVertices = mesh->newVertices(tag->m_Attributes["id"]);

			while (text->isValid()) {

				ColladaTag _newTag;

				// �������� ���
				getTag(&_newTag, text);
				
				// ~~~~~~~~~~~~~~~~
				// ������ </vertices>
				// ~~~~~~~~~~~~~~~~

				if (_newTag.m_Name == "/vertices") break;

				// ~~~~~~~~~~~~~~~~
				// ������ <input>
				// ~~~~~~~~~~~~~~~~

				if (_newTag.m_Name == "input") {

					// �������� <input>
					loadInput(&_newTag, _newColladaVertices, text);

				} // if (_newTag.m_Name == "input")

			} // while (test->isValid())

		}

		//==============================================================
		//==============================================================
		
		void CColladaLoader::loadPolylist(ColladaTag *tag, ColladaMesh *mesh, CText *text) {
			
			// ����� <polylist>
			auto _newColladaPolylist = mesh->newPolylist();

			// ��������� <source>
			_newColladaPolylist->m_VCount.m_Data.resize(atoi(tag->m_Attributes["count"].c_str()));

			//
			while (text->isValid()) {

				ColladaTag _newTag;

				// �������� ���
				getTag(&_newTag, text);

				// ~~~~~~~~~~~~~~~~
				// ������ </polylist>
				// ~~~~~~~~~~~~~~~~

				if (_newTag.m_Name == "/polylist") break;

				// ~~~~~~~~~~~~~~~~
				// ������ <input>
				// ~~~~~~~~~~~~~~~~

				if (_newTag.m_Name == "input") {

					// ��������� <input>
					loadInput(&_newTag, _newColladaPolylist, text);

					_newColladaPolylist->m_Offsets.push_back(_newColladaPolylist->m_Inputs.back().m_Offset);
				
				} // if (_newTag.m_Name == "input")

				// ~~~~~~~~~~~~~~~~
				// ������ <vcount>
				// ~~~~~~~~~~~~~~~~

				uint32_t _sumVCount = 0;

				if (_newTag.m_Name == "vcount") {	

					// ��������� <vcount>
					loadVCount(&_newTag, _newColladaPolylist, text);

				} // if (_newTag.m_Name == "vcount")

				// ~~~~~~~~~~~~~~~~
				// ������ <p>
				// ~~~~~~~~~~~~~~~~

				if (_newTag.m_Name == "p") {

					loadP(&_newTag, _newColladaPolylist, text);

				} // if (_newTag.m_Name == "p")

			} // // while (test->isValid())
			
		}

		//==============================================================
		//==============================================================

		void CColladaLoader::loadInput(ColladaTag *tag, ColladaPolylist *polylist, CText *text) {

			// ����� <input>
			polylist->m_Inputs.emplace_back(ColladaInput());
			auto &_newColladaInput = polylist->m_Inputs.back();

			// ���������
			_newColladaInput.m_Offset = atoi(tag->m_Attributes["offset"].c_str());
			_newColladaInput.m_IDSource = tag->m_Attributes["source"];

		}

		//==============================================================
		//==============================================================

		void CColladaLoader::loadInput(ColladaTag *tag, ColladaVertices *vertices, CText *text) {

			// ����� <input>
			auto _newColladaInput = vertices->newInput();

			// ���������
			_newColladaInput->m_Offset = atoi(tag->m_Attributes["offset"].c_str());
			_newColladaInput->m_IDSource = tag->m_Attributes["source"];
		}

		//==============================================================
		//==============================================================

		void CColladaLoader::loadVCount(ColladaTag *tag, ColladaPolylist *polylist, CText *text) {

			uint32_t _sum = 0;

			// ���������� ������
			for (uint32_t ctVCount = 0; ctVCount < polylist->m_VCount.m_Data.size(); ++ctVCount) {

				if (!text->isValid()) break;

				uint32_t _number;

				text->getUint(&_number);

				// ������� �����
				// �� ������ ����� = ������� <p>
				_sum += _number;

				// ���������
				polylist->m_VCount.m_Data[ctVCount] = _number;

			} // for (uint32_t id = 0;

			polylist->m_P.m_Data.resize(_sum);
		}

		//==============================================================
		//==============================================================

		void CColladaLoader::loadP(ColladaTag *tag, ColladaPolylist *polylist, CText *text) {

			for (uint32_t id = 0; id < polylist->m_P.m_Data.size(); ++id) {

				if (!text->isValid()) break;

				uint32_t _number = 0;

				text->getUint(&_number);

				polylist->m_P.m_Data[id] = _number;

			} // for (uint32_t id = 0;
		}

		//==============================================================
		//==============================================================

		void CColladaLoader::loadFloatArray(ColladaTag *tag, ColladaSource *source, CText *text) {

			// ����� <float_array>
			auto _newColladaFloatArray = source->newFloatArray();

			// ��������� <float_array>
			_newColladaFloatArray->m_ID = tag->m_Attributes["id"];
			_newColladaFloatArray->m_Data.resize(atoi(tag->m_Attributes["count"].c_str()));

			// �������� ����� getFloat ��� float ������
			for (uint32_t id = 0; id < _newColladaFloatArray->m_Data.size(); ++id) {

				if (!text->isValid()) break;

				float _number = 0.0f;

				text->getFloat(&_number);
			
				_newColladaFloatArray->m_Data[id] = _number;
			
			} // for (uint32_t id = 0;

			//
			while (text->isValid()) {

				ColladaTag _newTag;

				// �������� ���
				getTag(&_newTag, text);

				// ~~~~~~~~~~~~~~~~
				// ������ </accessor>
				// ~~~~~~~~~~~~~~~~

				if (_newTag.m_Name == "/accessor") break;

				// ~~~~~~~~~~~~~~~~
				// ������ <accessor>
				// ~~~~~~~~~~~~~~~~

				if (_newTag.m_Name == "accessor") {

					_newColladaFloatArray->m_Stride = atoi(_newTag.m_Attributes["stride"].c_str());
				}

			}

		}

		//==============================================================
		//==============================================================

	} // namespace CONTENT

} // namespace FE