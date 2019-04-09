////////////////////////////////////////////////////////////////
// секци€ PCH
////////////////////////////////////////////////////////////////
#include "CommonRenderInterface.h"
////////////////////////////////////////////////////////////////
// секци€ заголовочного файла
////////////////////////////////////////////////////////////////
#include "CRIImageBuffer.h"
////////////////////////////////////////////////////////////////
// секци€ компил€ци€ файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секци€ форвард-декларации
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секци€ дл€ исключений
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секци€ дл€ остального
////////////////////////////////////////////////////////////////
#include "../Common/Format.h"
#include "Vulkan/vknContext.h"
#include "Private/Vulkan/vknBatch.h"
#include "Vulkan/vknImageBuffer.h"

namespace FE {

	namespace CRI {

		//==============================================================
		//==============================================================

		bool CRI_IMAGE_BUFFER_CREATE_INFO::isValid(void) const {

			if (m_CRIContext == nullptr ||
				m_Type == TYPE::UNKNOWN ||
				m_Attachment == ATTACHMENT::UNKNOWN ||
				m_Storage == STORAGE::UNKNOWN ||
				m_Width == 0 ||
				m_Height == 0 ||
				m_Format == COMMON::FORMAT::TEXTURE::UNKNOWN ||
				m_MipLevels == 0) {

				return false;
			}

			return true;
		}

		//==============================================================
		//==============================================================

		CCRIImageBuffer::CCRIImageBuffer() {

			m_CreateInfo = {};
			m_Size = 0;
			m_Mipmaps = {};

		}

		//==============================================================
		//==============================================================

		CCRIImageBuffer::~CCRIImageBuffer() {

			m_CreateInfo = {};
			m_Size = 0;
			m_Mipmaps = {};
		}

		//==============================================================
		//==============================================================

		CRIImageBuffer CCRIImageBuffer::create(const CRI_IMAGE_BUFFER_CREATE_INFO *createInfo) {

			ASSERT_EX(createInfo, != , nullptr, "Invalid CRI_IMAGE_BUFFER_CREATE_INFO.", throw e_image_buffer_create_failed());
			ASSERT_EX(createInfo->isValid(), == , true, "Invalid CRI_IMAGE_BUFFER_CREATE_INFO.", throw e_image_buffer_create_failed());

			// ~~~~~~~~~~~~~~~~
			// get VKContext
			// ~~~~~~~~~~~~~~~~

			auto _vknContext = VULKAN::cri2vkn_Context(createInfo->m_CRIContext);

			// ~~~~~~~~~~~~~~~~
			// get VKImageBuffer
			// ~~~~~~~~~~~~~~~~

			auto _vknImageBuffer = _vknContext->getBatch()->getImageBuffer(createInfo);

			// ~~~~~~~~~~~~~~~~
			// new CRIImageBufferPrivate
			// ~~~~~~~~~~~~~~~~

			auto _criImageBufferPrivate = std::make_shared<CCRIImageBufferPrivate>(_vknImageBuffer);

			// ~~~~~~~~~~~~~~~~
			// описание mip уровней
			// ~~~~~~~~~~~~~~~~

			CRI_IMAGE_BUFFER_MIPMAP_ARR _mipmapArr;
			uint32_t _sumSize = 0;
			uint32_t _width = createInfo->m_Width;
			uint32_t _height = createInfo->m_Height;

			// если нужны мип уровни
			if (createInfo->m_MipLevels > 1) {

				// пока размер не станет 1 по ширине и 1 по высоте
				while (_width > 1 || _height > 1) {

					uint32_t _size = _width * _height * COMMON::FORMAT::dimension(createInfo->m_Format);
					_sumSize += _size;

					// описываем MIPMAP_DESC
					CRI_IMAGE_BUFFER_MIPMAP	_mipmap;

					_mipmap.m_Width = _width;
					_mipmap.m_Height = _height;
					_mipmap.m_Size = _size;

					// добавл€ем описание мип уровн€ в массив
					_mipmapArr.push_back(_mipmap);

					if (_width != 1) _width = _width >> 1;
					if (_height != 1) _height = _height >> 1;

				}; // while(width > 1 || height > 1)

			} // if (createInfo->m_Mipmap)

			uint32_t _size = _width * _height * COMMON::FORMAT::dimension(createInfo->m_Format);
			_sumSize += _size;

			// описываем MIPMAP_DESC
			CRI_IMAGE_BUFFER_MIPMAP	_mipmap;

			_mipmap.m_Width = _width;
			_mipmap.m_Height = _height;
			_mipmap.m_Size = _size;

			// добавл€ем описание мип уровн€ в массив
			_mipmapArr.push_back(_mipmap);

			// ~~~~~~~~~~~~~~~~
			// ~~~~~~~~~~~~~~~~

			_criImageBufferPrivate->m_CreateInfo = *createInfo;
			_criImageBufferPrivate->m_Size = _sumSize;
			_criImageBufferPrivate->m_Mipmaps = _mipmapArr;

			// ~~~~~~~~~~~~~~~~
			// ~~~~~~~~~~~~~~~~

			return _criImageBufferPrivate;

		}

		//==============================================================
		//==============================================================
		bool CCRIImageBuffer::isDepth(void) {

			return COMMON::FORMAT::isDepth(m_CreateInfo.m_Format);
			
		}

		//==============================================================
		//==============================================================

		bool CCRIImageBuffer::isColor(void) {

			return COMMON::FORMAT::isColor(m_CreateInfo.m_Format);
		}

		//==============================================================
		//==============================================================

	} // namespace RENDER

} // namespace FE