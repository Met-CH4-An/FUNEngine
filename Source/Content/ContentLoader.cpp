////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "PCH.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "ContentLoader.h"
////////////////////////////////////////////////////////////////
// секция компиляция файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция форвард-декларации
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция для исключений
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////
#include <fstream>
#include <string>
#include <chrono>
#include <iostream>
#include <clocale>
#include <vector>
#include <map>
#include <unordered_map>

#include "Text.h"

#include "../Core.h"
namespace FE {

	namespace CONTENT {	

		//==============================================================
		//==============================================================

		void CContentLoader::loadDAE(FE::RENDERER::Renderer renderer, std::string name) {

			std::locale::global(std::locale("C"));

			using namespace std::chrono_literals;
			auto _beginCounting = std::chrono::high_resolution_clock::now();

			std::ifstream _fileStream;

			// открываем файловый поток			
			_fileStream.open(name, std::fstream::in);

			// определяем размер файла
			size_t _fileSize;
			_fileStream.seekg(0, std::ios::end);
			_fileSize = _fileStream.tellg();
			_fileStream.seekg(0, std::ios::beg);

			// память под данные файла
			char *_data = new char[_fileSize];
			
			// если поток успешно открыт
			if (_fileStream.is_open()) {			

				_fileStream.read(_data, _fileSize);

				CText _text;
				_text.setData(_data, _fileSize);

				FE::RENDERER::MeshArr _meshes;

				CColladaLoader _loader;
				//_loader.load(renderer, &_text);

			}

			//CORE_OBJECT->create();
		
			//FILE_CREATE_INFO _fileCI = {};
			
			//_fileCI.m_Name = name;
			
			//File _file = OPERATION::createFile(&_fileCI);

			CText _text;
			_text.setData(_data, _fileSize);


			CColladaLoader _loader;
			//_loader.load(renderer, &_text);

			auto _endCounting = std::chrono::high_resolution_clock::now();
			auto _deltaCounting = _endCounting - _beginCounting;
			auto _delta_ms = std::chrono::duration <double, std::milli>(_deltaCounting).count();
			std::cout << "parse ms = " << _delta_ms << "\n";

		}

		//==============================================================
		//==============================================================

		void CContentLoader::loadOBJ(std::string name) {

			//Mesh _newMesh = new CMesh();

			//std::locale::global(std::locale("C"));

			//std::ifstream _fileStream;
			//_fileStream.open(name, std::fstream::in);

			//size_t _fileSize;
			//_fileStream.seekg(0, std::ios::end);
			//_fileSize = _fileStream.tellg();
			//_fileStream.seekg(0, std::ios::beg);

			//char *_data = new char[_fileSize];
			
			//using namespace std::chrono_literals;
			//auto _beginCounting = std::chrono::high_resolution_clock::now();

			/*if (_fileStream.is_open()) {
							
				std::string _dataStr;
				_fileStream.read(_data, _fileSize);
				_dataStr.assign(&_data[0], _fileSize);

				const uint32_t			BLOCK_SIZE = 4096;
				uint32_t				_id = 0;
				char					_word[32];
				//std::vector<float>		_vertices(BLOCK_SIZE);
				//std::vector<float>		_normals(BLOCK_SIZE);
				//std::vector<float>		_texCoords(BLOCK_SIZE);
				vec3_arr				_vertices;
				vec3_arr				_normals;
				vec3_arr				_texCoords;
				uint32_t				_idVertices = 0;
				uint32_t				_idNormals = 0;
				uint32_t				_idTexCoords = 0;
				
				//std::vector<float>		_outData;
				//uint32_t				_idFaces = 0;
				//uint32_t				_offset;
				//uint32_t				_offsetVertex = 0;
				//uint32_t				_offsetTexCoord = _offsetVertex + sizeof(vec3) / sizeof(float);
				//uint32_t				_offsetNormal = _offsetTexCoord + sizeof(vec2) / sizeof(float);
			

				
				/*while (getWord(_data, _fileSize, &_id, _word)) {

					//if (std::strcmp(_word, "f") == 0) {

					//	if (_outData.size() - _idFaces == 0) {

					//		_outData.resize(_outData.size() + BLOCK_SIZE);

					//	}

					//	if (!getWord(_data, _fileSize, &_id, _word)) break;
						
						//_vertices[atoi(_word)]
					//}

					if (std::strcmp(_word, "v") == 0) {
						
						if (_vertices.size() - _idVertices == 0) {

							_vertices.resize(_vertices.size() + BLOCK_SIZE);

						}
						
						vec3 _vertex;

						if (!getWord(_data, _fileSize, &_id, _word)) break;					
						_vertex.x = atof(_word);

						if (!getWord(_data, _fileSize, &_id, _word)) break;
						_vertex.y = atof(_word);

						if (!getWord(_data, _fileSize, &_id, _word)) break;
						_vertex.z = atof(_word);

						_vertices[_idVertices++] = _vertex;

					}

					if (std::strcmp(_word, "vn") == 0) {

						if (_normals.size() - _idNormals == 0) {

							_normals.resize(_normals.size() + BLOCK_SIZE);

						}

						vec3 _normal;

						if (!getWord(_data, _fileSize, &_id, _word)) break;
						_normal.x = atof(_word);

						if (!getWord(_data, _fileSize, &_id, _word)) break;
						_normal.y = atof(_word);
						
						if (!getWord(_data, _fileSize, &_id, _word)) break;
						_normal.z = atof(_word);

						_normals[_idNormals++] = _normal;
						

					}

					if (std::strcmp(_word, "vt") == 0) {

						if (_texCoords.size() - _idTexCoords == 0) {

							_texCoords.resize(_texCoords.size() + BLOCK_SIZE);

						}

						vec3 _texCoord;

						if (!getWord(_data, _fileSize, &_id, _word)) break;
						_texCoord.x = atof(_word);

						if (!getWord(_data, _fileSize, &_id, _word)) break;
						_texCoord.y = atof(_word);

						if (!getWord(_data, _fileSize, &_id, _word)) break;
						_texCoord.z = atof(_word);

						_texCoords[_idTexCoords++] = _texCoord;

					}

				}

				int asdasdasasd = 0;

				++asdasdasasd;

			}*/

			//auto _endCounting = std::chrono::high_resolution_clock::now();
			//auto _deltaCounting = _endCounting - _beginCounting;
			//auto _delta_ms = std::chrono::duration <double, std::milli>(_deltaCounting).count();
			//std::cout << "parse ms = " << _delta_ms << "\n";

		}

		//==============================================================
		//==============================================================

	} // namespace CONTENT

} // namespace FE