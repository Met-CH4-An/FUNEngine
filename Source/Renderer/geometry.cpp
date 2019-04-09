////////////////////////////////////////////////////////////////
// секция PCH
////////////////////////////////////////////////////////////////
#include "pch.renderer.h"
////////////////////////////////////////////////////////////////
// секция заголовочного файла
////////////////////////////////////////////////////////////////
#include "Geometry.h"
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
#include "Renderer.h"
//#include "..\GeometryInfo.h"
//#include "..\..\CRI\CRIDataBuffer.h"
//#include "..\..\CRI\CRIContext.h"

namespace FE {

	namespace RENDERER {

		//==============================================================
		//==============================================================

		/*void CGeometry::get(Renderer renderer, Geometry *geometry) {

			// новый
			Geometry _new = new CGeometry();

			// регистрируем
			renderer->reg(_new);

			// сохраняем
			*geometry = _new;

		}*/

		//==============================================================
		//==============================================================
		
		/*void CGeometry::create(const GEOMETRY_CREATE_INFO *createInfo) {

			auto _criContext = createInfo->m_Renderer->getContext();

			// ~~~~~~~~~~~~~~~~
			// буферы для вертексов
			// ~~~~~~~~~~~~~~~~

			FE::CRI::CRI_DATA_BUFFER_UPDATE_INFO _vertexBufferUI = {};

			_vertexBufferUI.m_Data = createInfo->m_DataVertices;
			_vertexBufferUI.m_Offset = 0;
			_vertexBufferUI.m_Size = createInfo->m_SizeDataVertices;

			FE::CRI::CRI_DATA_BUFFER_CREATE_INFO _vertexBufferCI = {};

			_vertexBufferCI.m_Usage = FE::CRI::CRI_DATA_BUFFER_CREATE_INFO::USAGE::VERTEX;
			_vertexBufferCI.m_Storage = FE::CRI::CRI_DATA_BUFFER_CREATE_INFO::STORAGE::HOST;
			_vertexBufferCI.m_Size = createInfo->m_SizeDataVertices;
			_vertexBufferCI.m_Update = _vertexBufferUI;

			// ~~~~~~~~~~~~~~~~
			// буферы для индексов
			// ~~~~~~~~~~~~~~~~

			FE::CRI::CRI_DATA_BUFFER_UPDATE_INFO _indexBufferUI = {};

			_indexBufferUI.m_Data = createInfo->m_DataIndices;
			_indexBufferUI.m_Offset = 0;
			_indexBufferUI.m_Size = createInfo->m_SizeDataIndices;

			FE::CRI::CRI_DATA_BUFFER_CREATE_INFO _indexBufferCI = {};

			_indexBufferCI.m_Usage = FE::CRI::CRI_DATA_BUFFER_CREATE_INFO::USAGE::INDEX;
			_indexBufferCI.m_Storage = FE::CRI::CRI_DATA_BUFFER_CREATE_INFO::STORAGE::HOST;
			_indexBufferCI.m_Size = createInfo->m_SizeDataIndices;
			_indexBufferCI.m_Update = _indexBufferUI;

			FE::CRI::CRI_DATA_BUFFER_CREATE_INFO_ARR _dataBufferCIs = { _vertexBufferCI, _indexBufferCI };

			FE::CRI::CRIDataBuffer _vertexBuffer;
			FE::CRI::CRIDataBuffer _indexBuffer;
			FE::CRI::CCRIDataBuffer::get(_criContext, &_vertexBuffer);
			FE::CRI::CCRIDataBuffer::get(_criContext, &_indexBuffer);
			_vertexBuffer->create(&_vertexBufferCI);
			_indexBuffer->create(&_indexBufferCI);
			//FE::CRI::OPERATION::createDataBuffer(&_vertexBufferCI, &_vertexBuffer);
			//FE::CRI::OPERATION::createDataBuffer(&_indexBufferCI, &_indexBuffer);

			m_BufferVertices = _vertexBuffer;
			m_BufferIndices = _indexBuffer;

			// ~~~~~~~~~~~~~~~~
			// описываем макет вершин
			// ~~~~~~~~~~~~~~~~

			//FE::CRI::CRI_PIPELINE_VERTEX_LAYOUT_ARR _vertexLayouts;

			//FE::CRI::CRI_PIPELINE_VERTEX_LAYOUT::ATTRIBUTE _positionAttribute = {};
			//_positionAttribute.m_Format = FE::CRI::CRI_FORMAT::R32G32B32_SFLOAT;
			//_positionAttribute.m_Offset = 0;

			//FE::CRI::CRI_PIPELINE_VERTEX_LAYOUT::ATTRIBUTE _colorAttribute = {};
			//_colorAttribute.m_Format = FE::CRI::CRI_FORMAT::R32G32B32_SFLOAT;
			//_colorAttribute.m_Offset = _positionAttribute.m_Offset + FE::CRI::FORMAT_SIZE(_positionAttribute.m_Format);

			//FE::CRI::CRI_PIPELINE_VERTEX_LAYOUT::ATTRIBUTE _normalAttribute = {};
			//_normalAttribute.m_Format = FE::CRI::CRI_FORMAT::R32G32B32_SFLOAT;
			//_normalAttribute.m_Offset = _colorAttribute.m_Offset + FE::CRI::FORMAT_SIZE(_colorAttribute.m_Format);

			///_vertexLayouts = { { _positionAttribute, _colorAttribute, _normalAttribute } };

			//m_VertexLayouts = _vertexLayouts;
		}*/

		//==============================================================
		//==============================================================

	} // namespace RENDERER

} // namespace FE