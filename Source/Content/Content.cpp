////////////////////////////////////////////////////////////////
// ������ PCH
////////////////////////////////////////////////////////////////
#include "PCH.h"
////////////////////////////////////////////////////////////////
// ������ ������������� �����
////////////////////////////////////////////////////////////////
#include "Content.h"
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
#include "File.h"
#include "Text.h"
#include "ColladaLoader.h"
#include "ContentObject.h"
#include <chrono>
#include "..\Scene\SceneObject.h"
#include "..\Renderer\Renderer.h"
#include <variant>
#include "..\Common\Blob.h"
#include "../Maths/maths.h"

namespace FE {

	namespace CONTENT {

		//==============================================================
		//==============================================================

		void CContent::create(const CONTENT_CREATE_INFO *createInfo) {


		}

		//==============================================================
		//==============================================================

		File CContent::getFile(std::string fileName) {

			// ��������, ����� ���� ����� ���� ��� ��������
			for (auto &it : m_Files) {

				if (it->getCreateInfo().m_Name == fileName) return it;
			}

			// ���������
			FILE_CREATE_INFO _fileCI = {};
			_fileCI.m_Name = fileName;

			// ����� ����
			File _newFile = new CFile();

			_newFile->create(&_fileCI);

			m_Files.push_back(_newFile);

			return _newFile;
		}

		//==============================================================
		//==============================================================
		
		File CContent::get(std::string fileName) {

			auto _beginFrame = std::chrono::high_resolution_clock::now();
			using namespace std::chrono_literals;
			

			// ��������, ����� ���� ����� ���� ��� ��������
			for (auto &it : m_Files) {

				if(it->getCreateInfo().m_Name == fileName) return it;
			}

			// ���������
			FILE_CREATE_INFO _fileCI = {};

			_fileCI.m_Name = fileName;

			// � ������ ����� ����
			File _newFile = new CFile();

			_newFile->create(&_fileCI);

			// ���� �� ���������� ������������ ����� ���� � ���������� ���
			//if (_newFile->isValid()) {

				m_Files.push_back(_newFile);

				CText _new;

				_new.setData((char*)_newFile->getData().c_str(), _newFile->getData().size());

				CColladaLoader _loader;

				ContentObject _newContentObject = new CContentObject();

				_loader.load(_newContentObject, &_new);

				//return _newFile;
			//}

			auto _endFrame = std::chrono::high_resolution_clock::now();
			auto _deltaFrame = _endFrame - _beginFrame;
			auto _frame_ms = std::chrono::duration <double, std::milli>(_deltaFrame).count();
			std::cout << "=================================\nload ms\n=================================\n" << _frame_ms << "\n" << "=================================\n\n";

			return nullptr;
		}

		//==============================================================
		//==============================================================
		
		void CContent::getProcedure(const CONTENT_PROCEDURE_SPHERE *createInfo, COMMON::Blob *vertices, COMMON::Blob *indices) {

			*vertices = std::make_shared<COMMON::CBlob>();
			*indices = std::make_shared<COMMON::CBlob>();
			//*sceneObject = new SCENE::CSceneObject();
			
			RENDERER::Mesh _newMesh;

			

			//createInfo->m_Renderer->get(&_newMesh);
			//(*sceneObject)->m_Mesh = _newMesh;
			

			// ~~~~~~~~~~~~~~~~
			// stride ��� ������� _vertices
			// ~~~~~~~~~~~~~~~~

			size_t _strideVertices = 0;

			for (const auto &itMeshAttribute : createInfo->m_Mesh.m_Attributes) {

				_strideVertices += itMeshAttribute.m_Capacity;

			}

			// ~~~~~~~~~~~~~~~~
			// stride ��� ������� _indices
			// ~~~~~~~~~~~~~~~~

			size_t _strideIndices = 0;
			if (createInfo->m_PatchSize == 3) _strideIndices = 6;

			// ~~~~~~~~~~~~~~~~
			// ������� ��� ������ � ��������
			// ~~~~~~~~~~~~~~~~

			uint32_t	_ctVertices = 0;
			uint32_t	_ctIndices = 0;

			float		*_vertices = new float[createInfo->m_Meridians * createInfo->m_Parallels * _strideVertices];
			uint32_t	*_indices = new uint32_t[(createInfo->m_Meridians - 1) * (createInfo->m_Parallels - 1) * 6];

			// ~~~~~~~~~~~~~~~~
			// ~~~~~~~~~~~~~~~~
			
			uint32_t _index = 0;

			for (size_t i = 0; i < createInfo->m_Parallels; ++i) {

				//
				float AngleXZ = float(math_pi * i) / (createInfo->m_Meridians - 1);

				for (size_t j = 0; j < createInfo->m_Meridians; ++j) {

					//
					float AngleY = float(2 * math_pi * j) / (createInfo->m_Parallels - 1);	

					// ~~~~~~~~~~~~~~~~
					// ��������� ������� �������, 
					// ��������� ��������������� ��������� �����
					// ~~~~~~~~~~~~~~~~

					vec3 _position;

					// ��������������� ��������� �����
					_position.x = sinf(AngleXZ) * cosf(AngleY) * createInfo->m_Radius;
					_position.y = sinf(AngleXZ) * sinf(AngleY) * createInfo->m_Radius;
					_position.z = cosf(AngleXZ) * createInfo->m_Radius;

					uint32_t _offset = 0;
					for (const auto &itMeshAttribute : createInfo->m_Mesh.m_Attributes) {

						if (itMeshAttribute.m_Type == CONTENT::CONTENT_PROCEDURE_MESH_ATTRIBUTE::TYPE::POSITION) {

							// ��������� ���������� ������� � ������� ������
							_vertices[_ctVertices * _strideVertices + _offset + 0] = _position.x;
							_vertices[_ctVertices * _strideVertices + _offset + 1] = _position.y;
							_vertices[_ctVertices * _strideVertices + _offset + 2] = _position.z;

						}

						if (itMeshAttribute.m_Type == CONTENT::CONTENT_PROCEDURE_MESH_ATTRIBUTE::TYPE::NORMAL) {

							// ����������� ������� � �������� �������
							_position.normalize();

							// ��������� � �������
							_vertices[_ctVertices * _strideVertices + _offset + 0] = _position.x;
							_vertices[_ctVertices * _strideVertices + _offset + 1] = _position.y;
							_vertices[_ctVertices * _strideVertices + _offset + 2] = _position.z;

						}

						_offset += itMeshAttribute.m_Capacity;

					}
					
					++_ctVertices;

					if (i != 0 && j != 0) {
					
						if (createInfo->m_PatchSize == 4) {

							//_cubeIndices.push_back(i*_maxParallels + j);
							//_cubeIndices.push_back(i*_maxParallels + j - 1);
							//_cubeIndices.push_back((i - 1)*_maxParallels + j - 1);
							//_cubeIndices.push_back((i - 1)*_maxParallels + j);
						}

						else if (createInfo->m_PatchSize == 3) {

							uint32_t _index0 = 0, _index1 = 0, _index2 = 0, _index3 = 0, _index4 = 0, _index5 = 0;

							// ������� �������
							_index0 = i * createInfo->m_Parallels + j;
							_index1 = i * createInfo->m_Parallels + j - 1;
							_index2 = (i - 1)*createInfo->m_Parallels + j - 1;

							_index3 = (i - 1)*createInfo->m_Parallels + j - 1;
							_index4 = (i - 1)*createInfo->m_Parallels + j;
							_index5 = i * createInfo->m_Parallels + j;

							_indices[_ctIndices++] = _index0;
							_indices[_ctIndices++] = _index1;
							_indices[_ctIndices++] = _index2;

							_indices[_ctIndices++] = _index3;
							_indices[_ctIndices++] = _index4;
							_indices[_ctIndices++] = _index5;

							

						}
					}
					
				}

			}

			(*vertices)->resize(createInfo->m_Meridians * createInfo->m_Parallels * _strideVertices * sizeof(float));
			(*indices)->resize((createInfo->m_Meridians - 1) * (createInfo->m_Parallels - 1) * _strideIndices * sizeof(uint32_t));
			(*vertices)->insert(0, _vertices, createInfo->m_Meridians * createInfo->m_Parallels * _strideVertices * sizeof(float));
			(*indices)->insert(0, _indices, (createInfo->m_Meridians - 1) * (createInfo->m_Parallels - 1) * _strideIndices * sizeof(uint32_t));
			

			//_newMesh->m_Vertices = _verticesNew.data().;
			//_newMesh->m_Indices = _indices;

			//_newMesh->m_SizeVertices = createInfo->m_Meridians * createInfo->m_Parallels * _strideVertices;
			//_newMesh->m_SizeIndicess = (createInfo->m_Meridians - 1) * (createInfo->m_Parallels - 1) * _strideIndices;
		}

		//==============================================================
		//==============================================================

	} // namespace CONTENT

} // namespace FE