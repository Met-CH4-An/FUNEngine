////////////////////////////////////////////////////////////////
// ������ PCH
////////////////////////////////////////////////////////////////
#include "PCH.h"
////////////////////////////////////////////////////////////////
// ������ ������������� �����
////////////////////////////////////////////////////////////////
#include "Procedural.h"
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
#include "..\Common\Blob.h"
#include "..\Renderer\Renderer.h"
#include "..\Renderer\Mesh.h"
#include "../Maths/maths.h"

namespace FE {

	namespace PROCEDURAL {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		void CProcedural::buildSphere(const PROCEDURE_SPHERE_CREATE_INFO *createInfo, RENDERER::Mesh *mesh, COMMON::Blob *vertices, COMMON::Blob *indices, SCENE::SceneObject sceneObject) {

			COMMON::Blob _blobVertices = std::make_shared<COMMON::CBlob>();
			COMMON::Blob _blobIndices = std::make_shared<COMMON::CBlob>();

			*vertices = _blobVertices;
			*indices = _blobIndices;

			std::vector<COMMON::Blob>		_vertices;

			// ~~~~~~~~~~~~~~~~
			// ���������� ���������� �������� ��� ������� �������
			// ~~~~~~~~~~~~~~~~

			if (createInfo->m_Geometry.m_Placement == PROCEDURAL::PROCEDURAL_GEOMETRY::PLACEMENT::AOS) {

				// ������ _vertices = 1
				// �.�. ��� �������� ������� ����� � ����� �������
				_vertices.resize(1);

			}

			else {

				// ������ _vertices = ���������� ���� ���������
				// �.�. ������ ������� ������� ����� � ��������� �������
				_vertices.resize(createInfo->m_Geometry.m_Attributes.size());

			}

			// ~~~~~~~~~~~~~~~~
			// stride ��� _vertices
			// ~~~~~~~~~~~~~~~~

			size_t _strideVertices = 0;

			if (createInfo->m_Geometry.m_Placement == PROCEDURAL::PROCEDURAL_GEOMETRY::PLACEMENT::AOS) {

				// stride ������� = ���������� ���������
				for (const auto &itGeometryAttribute : createInfo->m_Geometry.m_Attributes) {

					_strideVertices += 3;

				}
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

			if (createInfo->m_Geometry.m_Placement == PROCEDURAL::PROCEDURAL_GEOMETRY::PLACEMENT::AOS) {

				_vertices[0] = std::make_shared<COMMON::CBlob>();
				_vertices[0]->resize(createInfo->m_Meridians * createInfo->m_Parallels * _strideVertices * sizeof(float));
			}

			else {

				// ������ ������ �� _vertices
				for (auto &itArrayAttribute : _vertices) {

					// ������ ������� �� createInfo->m_Mesh.m_Attributes
					for (auto &itAttribute : createInfo->m_Geometry.m_Attributes) {

						itArrayAttribute = std::make_shared<COMMON::CBlob>();

						// ������ ������� ��� �������� = �������� * �������� * ����������� ��������
						itArrayAttribute->resize(createInfo->m_Meridians * createInfo->m_Parallels * 3);
					}

				}
			}
			
			_blobIndices->resize((createInfo->m_Meridians - 1) * (createInfo->m_Parallels - 1) * 6 * sizeof(uint32_t));

			// ~~~~~~~~~~~~~~~~
			// ~~~~~~~~~~~~~~~~

			uint32_t _index = 0;

			// ��������
			for (size_t i = 0; i < createInfo->m_Parallels; ++i) {

				//
				float AngleXZ = float(math_pi * i) / (createInfo->m_Meridians - 1);

				// ���������
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

					// ~~~~~~~~~~~~~~~~
					// ��������� ������ � ��������
					// �������, ����, ������� � �.�.
					// ~~~~~~~~~~~~~~~~

					uint32_t _offsetAttribute = 0;

					// ���������� ��������
					for(size_t ctAttribute = 0; ctAttribute < createInfo->m_Geometry.m_Attributes.size(); ++ctAttribute) {
			
						const auto &itAttribute = createInfo->m_Geometry.m_Attributes[ctAttribute];
					
						// ���� ��������� �������� - POSITION
						if (itAttribute.m_Semantic == PROCEDURAL_GEOMETRY_ATTRIBUTE::SEMANTIC::POSITION) {

							// ���� ������������ - array of structures
							if (createInfo->m_Geometry.m_Placement == PROCEDURAL::PROCEDURAL_GEOMETRY::PLACEMENT::AOS) {
								
								// ���������� �����������
								for (size_t ctDimension = 0; ctDimension < itAttribute.m_Dimension; ++ctDimension) {

									// ��������� � �������
									_position[ctDimension];
									_vertices[0]->get<float>(_ctVertices * _strideVertices + _offsetAttribute + ctDimension) = _position[ctDimension];
								}
								
							}
							
							// ���� ������������ - struture of arrays
							else {

								// ���������� �����������
								for (size_t ctDimension = 0; ctDimension < itAttribute.m_Dimension; ++ctDimension) {

									// ��������� � �������
									_vertices[ctAttribute]->get<float>(_ctVertices + _offsetAttribute + ctDimension) = _position[ctDimension];
								}

							}
						}

						// ���� ��������� �������� == NORMAL
						if (itAttribute.m_Semantic == PROCEDURAL_GEOMETRY_ATTRIBUTE::SEMANTIC::NORMAL) {

							// ����������� ������� � �������� �������
							_position.normalize();

							// ���� ������������ - array of structures
							if (createInfo->m_Geometry.m_Placement == PROCEDURAL::PROCEDURAL_GEOMETRY::PLACEMENT::AOS) {

								// ���������� �����������
								for (size_t ctDimension = 0; ctDimension < itAttribute.m_Dimension; ++ctDimension) {

									// ��������� � �������
									_vertices[0]->get<float>(_ctVertices * _strideVertices + _offsetAttribute + ctDimension) = _position[ctDimension];
								}

							}

							// ���� ������������ - struture of arrays
							else {

								// ���������� �����������
								for (size_t ctDimension = 0; ctDimension < itAttribute.m_Dimension; ++ctDimension) {

									// ��������� � �������
									_vertices[ctAttribute]->get<float>(_ctVertices + _offsetAttribute + ctDimension) = _position[ctDimension];
								}
					
							}

						}

						_offsetAttribute += itAttribute.m_Dimension;

					}

					++_ctVertices;

					// ~~~~~~~~~~~~~~~~
					// ��������� ������� ��� ������ 
					// � ���������
					// ~~~~~~~~~~~~~~~~

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

							_blobIndices->get<uint32_t>(_ctIndices++) = _index0;
							_blobIndices->get<uint32_t>(_ctIndices++) = _index1;
							_blobIndices->get<uint32_t>(_ctIndices++) = _index2;

							_blobIndices->get<uint32_t>(_ctIndices++) = _index3;
							_blobIndices->get<uint32_t>(_ctIndices++) = _index4;
							_blobIndices->get<uint32_t>(_ctIndices++) = _index5;

						}
					}

				} // for (size_t j = 0; j < createInfo->m_Meridians; ++j) {

			} // for (size_t i = 0; i < createInfo->m_Parallels; ++i)

			*vertices = _vertices[0];			
			*indices = _blobIndices;

			// ~~~~~~~~~~~~~~~~
			// ������ ���
			// ~~~~~~~~~~~~~~~~

			// ��������� �������� ����
			/*RENDERER::MESH_ATTRIBUTE _sphereMeshAttributePositionCI = {};
			_sphereMeshAttributePositionCI.m_Name = RENDERER::MESH_ATTRIBUTE::NAME::POSITION;
			_sphereMeshAttributePositionCI.m_Capacity = 3;
			_sphereMeshAttributePositionCI.m_Format = COMMON::FORMAT::_32_32_32_SFLOAT;

			RENDERER::MESH_ATTRIBUTE  _sphereMeshAttributeColorCI = {};
			_sphereMeshAttributeColorCI.m_Name = RENDERER::MESH_ATTRIBUTE::NAME::COLOR;
			_sphereMeshAttributeColorCI.m_Capacity = 3;
			_sphereMeshAttributeColorCI.m_Format = COMMON::FORMAT::_32_32_32_SFLOAT;

			RENDERER::MESH_ATTRIBUTE  _sphereMeshAttributeNormalCI = {};
			_sphereMeshAttributeNormalCI.m_Name = RENDERER::MESH_ATTRIBUTE::NAME::NORMAL;
			_sphereMeshAttributeNormalCI.m_Capacity = 3;
			_sphereMeshAttributeNormalCI.m_Format = COMMON::FORMAT::_32_32_32_SFLOAT;

			// ��������� ������ ���������
			RENDERER::MESH_ATTRIBUTE_BINDING _sphereMeshBindingCI = {};
			_sphereMeshBindingCI.push_back(_sphereMeshAttributePositionCI);
			_sphereMeshBindingCI.push_back(_sphereMeshAttributeColorCI);
			_sphereMeshBindingCI.push_back(_sphereMeshAttributeNormalCI);

			RENDERER::MESH_ATTRIBUTE_LAYOUT _sphereMeshLayoutCI = {};
			_sphereMeshLayoutCI.push_back(_sphereMeshBindingCI);

			RENDERER::MESH_ATTRIBUTE_DECLARATION _sphereMeshDeclaration = {};
			_sphereMeshDeclaration.push_back(_sphereMeshLayoutCI);

			// ��������� �������� ����
			RENDERER::MESH_CREATE_INFO _meshCI = {};
			_meshCI.m_AttributeDeclaration = _sphereMeshDeclaration;

			// ����������� � ��������� ����� ���
			RENDERER::Mesh _mesh;
			RENDERER::CRenderer::create(createInfo->m_Renderer, &_mesh, &_meshCI);*/
			
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		void CProcedural::buildCylindricalHelix(const PROCEDURE_HELIX_CREATE_INFO *createInfo, PROCEDURE_OUTPUT *output) {

			float	_stepA = 1.0f;
			float	_stepB = 1.0f;
			size_t	_countElements = 100;
			float	_countTurns = 10.0f;

			COMMON::Blob	_verticesBlob = std::make_shared<COMMON::CBlob>();

			_verticesBlob->resize(_countElements * 3 * sizeof(float));

			for (size_t ctElement = 0; ctElement < _countElements; ++ctElement) {

				float angleXY = math_pi * ctElement / _countTurns;

				float x = _stepA * cosf(angleXY);
				float y = _stepA * sinf(angleXY);
				float z = _stepB * angleXY;

				_verticesBlob->get<float>(ctElement * 3 + 0) = x;
				_verticesBlob->get<float>(ctElement * 3 + 1) = y;
				_verticesBlob->get<float>(ctElement * 3 + 2) = z;

			}

			output->m_Vertices.push_back(_verticesBlob);
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	} // namespace PROCEDURAL

} // namespace FE