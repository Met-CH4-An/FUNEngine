////////////////////////////////////////////////////////////////
// ������ PCH
////////////////////////////////////////////////////////////////
#include "pch.renderer.h"
////////////////////////////////////////////////////////////////
// ������ ������������� �����
////////////////////////////////////////////////////////////////
#include "Mesh.h"
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
#include "Renderer.h"
#include "..\Common\Blob.h"
#include "..\CommonRenderInterface/criContext.h"
#include "..\CommonRenderInterface/criDataBuffer.h"

namespace FE {

	namespace RENDERER {

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		CMesh::CMesh(Renderer renderer) 
			: m_Renderer(renderer),
			m_CreateInfo({}),
			m_Vertices({}),
			m_Indices(nullptr) {

		}

		//==============================================================
		//==============================================================

		void CMesh::create(const MESH_CREATE_INFO *createInfo) {

			m_CreateInfo = *createInfo;

			for (size_t ctLayout = 0; ctLayout < createInfo->m_AttributeDeclaration.size(); ++ctLayout) {

				auto _itLayout = createInfo->m_AttributeDeclaration[ctLayout];

				// �������� ���� ����� ������, � ������� ����� ��������� ������ �������
				CRI::CRIDataBuffer _dataBufferVertices;
				CRI::CCRIContext::create(m_Renderer->getContext(), &_dataBufferVertices);

				// ���������
				m_Vertices.push_back(_dataBufferVertices);

				for (size_t ctBinding = 0; ctBinding < _itLayout.size(); ++ctBinding) {

					auto _itBinding = _itLayout[ctBinding];

				} // for (size_t ctBinding = 0;
			} // for (size_t ctLayout = 0;
			
			// �������� ����� ��� ��������
			CRI::CRIDataBuffer _dataBufferIndices;
			CRI::CCRIContext::create(m_Renderer->getContext(), &_dataBufferIndices);
			
			m_Indices = _dataBufferIndices;
		}

		//==============================================================
		//==============================================================

		void CMesh::addVertices(COMMON::Blob blobVertices) {

			// ��������� ���������� DataBuffer
			CRI::CRI_DATA_BUFFER_UPDATE_INFO _dataBufferUI = {};
			_dataBufferUI.m_Data = blobVertices->data();
			_dataBufferUI.m_Offset = 0;
			_dataBufferUI.m_Size = blobVertices->size();

			// ��������� �������� DataBuffer
			CRI::CRI_DATA_BUFFER_CREATE_INFO _dataBufferCI = {};
			_dataBufferCI.m_Usage = CRI::CRI_DATA_BUFFER_CREATE_INFO::USAGE::VERTEX;
			_dataBufferCI.m_Storage = CRI::CRI_DATA_BUFFER_CREATE_INFO::STORAGE::HOST;
			_dataBufferCI.m_Size = blobVertices->size();
			_dataBufferCI.m_Update = _dataBufferUI;

			// ������
			m_Vertices[0]->create(&_dataBufferCI);

		}

		//==============================================================
		//==============================================================
		
		void CMesh::addIndices(COMMON::Blob blobIndices) {

			// ��������� ���������� DataBuffer
			CRI::CRI_DATA_BUFFER_UPDATE_INFO _dataBufferUI = {};

			_dataBufferUI.m_Data = blobIndices->data();
			_dataBufferUI.m_Offset = 0;
			_dataBufferUI.m_Size = blobIndices->size();

			// ��������� �������� DataBuffer
			CRI::CRI_DATA_BUFFER_CREATE_INFO _dataBufferCI = {};

			_dataBufferCI.m_Usage = CRI::CRI_DATA_BUFFER_CREATE_INFO::USAGE::INDEX;
			_dataBufferCI.m_Storage = CRI::CRI_DATA_BUFFER_CREATE_INFO::STORAGE::HOST;
			_dataBufferCI.m_Size = blobIndices->size();
			_dataBufferCI.m_Update = _dataBufferUI;

			// ������
			m_Indices->create(&_dataBufferCI);
		}

		//==============================================================
		//==============================================================

		const MESH_ATTRIBUTE_DECLARATION& CMesh::getAttributeDeclaration(void) const {

			return m_CreateInfo.m_AttributeDeclaration;
		}

		//==============================================================
		//==============================================================
		
		const CRI::CRIDataBufferArr CMesh::getVertices(void) const {

			return m_Vertices;
		}

		//==============================================================
		//==============================================================

		const CRI::CRIDataBuffer CMesh::getIndices(void) const {

			return m_Indices;
		}

		//==============================================================
		//==============================================================

	} // namespace RENDERER

} // namespace FE