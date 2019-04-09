#ifndef FORMAT__H
#define FORMAT__H
////////////////////////////////////////////////////////////////
// секци€ компил€ци€ файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секци€ родительского класса
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секци€ форвард-декларации
////////////////////////////////////////////////////////////////
#include "FCommon.h"
////////////////////////////////////////////////////////////////
// секци€ дл€ остального
////////////////////////////////////////////////////////////////

namespace FE {

	namespace COMMON {
	
		struct FORMAT {

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			enum class DATA {

				UNKNOWN,

				_8_UNORM,
				_8_SNORM,
				_8_UINT,
				_8_SINT,
				_8_8_UNORM,
				_8_8_SNORM,
				_8_8_UINT,
				_8_8_SINT,
				_8_8_8_UNORM,
				_8_8_8_SNORM,
				_8_8_8_UINT,
				_8_8_8_SINT,
				_8_8_8_8_UNORM,
				_8_8_8_8_SNORM,
				_8_8_8_8_UINT,
				_8_8_8_8_SINT,

				_16_UNORM,
				_16_SNORM,
				_16_UINT,
				_16_SINT,
				_16_SFLOAT,
				_16_16_UNORM,
				_16_16_SNORM,
				_16_16_UINT,
				_16_16_SINT,
				_16_16_SFLOAT,
				_16_16_16_UNORM,
				_16_16_16_SNORM,
				_16_16_16_UINT,
				_16_16_16_SINT,
				_16_16_16_SFLOAT,
				_16_16_16_16_UNORM,
				_16_16_16_16_SNORM,
				_16_16_16_16_UINT,
				_16_16_16_16_SINT,
				_16_16_16_16_SFLOAT,

				_32_UINT,
				_32_SINT,
				_32_SFLOAT,
				_32_32_UINT,
				_32_32_SINT,
				_32_32_SFLOAT,
				_32_32_32_UINT,
				_32_32_32_SINT,
				_32_32_32_SFLOAT,
				_32_32_32_32_UINT,
				_32_32_32_32_SINT,
				_32_32_32_32_SFLOAT,

				_64_UINT,
				_64_SINT,
				_64_SFLOAT,
				_64_64_UINT,
				_64_64_SINT,
				_64_64_SFLOAT,
				_64_64_64_UINT,
				_64_64_64_SINT,
				_64_64_64_SFLOAT,
				_64_64_64_64_UINT,
				_64_64_64_64_SINT,
				_64_64_64_64_SFLOAT,

			}; // enum class FORMAT
			using FORMAT_ARR = std::vector<FORMAT>;



			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief ‘орматы
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			enum class TEXTURE {

				UNKNOWN,

				R8_UNORM = static_cast<uint32_t>(DATA::_8_UNORM),
				R8_SNORM = static_cast<uint32_t>(DATA::_8_SNORM),
				R8_UINT = static_cast<uint32_t>(DATA::_8_UINT),
				R8_SINT = static_cast<uint32_t>(DATA::_8_SINT),
				R8G8_UNORM = static_cast<uint32_t>(DATA::_8_8_UNORM),
				R8G8_SNORM = static_cast<uint32_t>(DATA::_8_8_SNORM),
				R8G8_UINT = static_cast<uint32_t>(DATA::_8_8_UINT),
				R8G8_SINT = static_cast<uint32_t>(DATA::_8_8_SINT),
				R8G8B8_UNORM = static_cast<uint32_t>(DATA::_8_8_8_UNORM),
				R8G8B8_SNORM = static_cast<uint32_t>(DATA::_8_8_8_SNORM),
				R8G8B8_UINT = static_cast<uint32_t>(DATA::_8_8_8_UINT),
				R8G8B8_SINT = static_cast<uint32_t>(DATA::_8_8_8_SINT),
				R8G8B8A8_UNORM = static_cast<uint32_t>(DATA::_8_8_8_8_UNORM),
				R8G8B8A8_SNORM = static_cast<uint32_t>(DATA::_8_8_8_8_SNORM),
				R8G8B8A8_UINT = static_cast<uint32_t>(DATA::_8_8_8_8_UINT),
				R8G8B8A8_SINT = static_cast<uint32_t>(DATA::_8_8_8_8_SINT),

				R16_UNORM = static_cast<uint32_t>(DATA::_16_UNORM),
				R16_SNORM = static_cast<uint32_t>(DATA::_16_SNORM),
				R16_UINT = static_cast<uint32_t>(DATA::_16_UINT),
				R16_SINT = static_cast<uint32_t>(DATA::_16_SINT),
				R16_SFLOAT = static_cast<uint32_t>(DATA::_16_SFLOAT),
				R16G16_UNORM = static_cast<uint32_t>(DATA::_16_16_UNORM),
				R16G16_SNORM = static_cast<uint32_t>(DATA::_16_16_SNORM),
				R16G16_UINT = static_cast<uint32_t>(DATA::_16_16_UINT),
				R16G16_SINT = static_cast<uint32_t>(DATA::_16_16_SINT),
				R16G16_SFLOAT = static_cast<uint32_t>(DATA::_16_16_SFLOAT),
				R16G16B16_UNORM = static_cast<uint32_t>(DATA::_16_16_16_UNORM),
				R16G16B16_SNORM = static_cast<uint32_t>(DATA::_16_16_16_SNORM),
				R16G16B16_UINT = static_cast<uint32_t>(DATA::_16_16_16_UINT),
				R16G16B16_SINT = static_cast<uint32_t>(DATA::_16_16_16_SINT),
				R16G16B16_SFLOAT = static_cast<uint32_t>(DATA::_16_16_16_SFLOAT),
				R16G16B16A16_UNORM = static_cast<uint32_t>(DATA::_16_16_16_16_UNORM),
				R16G16B16A16_SNORM = static_cast<uint32_t>(DATA::_16_16_16_16_SNORM),
				R16G16B16A16_UINT = static_cast<uint32_t>(DATA::_16_16_16_16_UINT),
				R16G16B16A16_SINT = static_cast<uint32_t>(DATA::_16_16_16_16_SINT),
				R16G16B16A16_SFLOAT = static_cast<uint32_t>(DATA::_16_16_16_16_SFLOAT),

				R32_UINT = static_cast<uint32_t>(DATA::_32_UINT),
				R32_SINT = static_cast<uint32_t>(DATA::_32_SINT),
				R32_SFLOAT = static_cast<uint32_t>(DATA::_32_SFLOAT),
				R32G32_UINT = static_cast<uint32_t>(DATA::_32_32_UINT),
				R32G32_SINT = static_cast<uint32_t>(DATA::_32_32_SINT),
				R32G32_SFLOAT = static_cast<uint32_t>(DATA::_32_32_SFLOAT),
				R32G32B32_UINT = static_cast<uint32_t>(DATA::_32_32_32_UINT),
				R32G32B32_SINT = static_cast<uint32_t>(DATA::_32_32_32_SINT),
				R32G32B32_SFLOAT = static_cast<uint32_t>(DATA::_32_32_32_SFLOAT),
				R32G32B32A32_UINT = static_cast<uint32_t>(DATA::_32_32_32_32_UINT),
				R32G32B32A32_SINT = static_cast<uint32_t>(DATA::_32_32_32_32_SINT),
				R32G32B32A32_SFLOAT = static_cast<uint32_t>(DATA::_32_32_32_32_SFLOAT),

				R64_UINT = static_cast<uint32_t>(DATA::_64_UINT),
				R64_SINT = static_cast<uint32_t>(DATA::_64_SINT),
				R64_SFLOAT = static_cast<uint32_t>(DATA::_64_SFLOAT),
				R64G64_UINT = static_cast<uint32_t>(DATA::_64_64_UINT),
				R64G64_SINT = static_cast<uint32_t>(DATA::_64_64_SINT),
				R64G64_SFLOAT = static_cast<uint32_t>(DATA::_64_64_SFLOAT),
				R64G64B64_UINT = static_cast<uint32_t>(DATA::_64_64_64_UINT),
				R64G64B64_SINT = static_cast<uint32_t>(DATA::_64_64_64_SINT),
				R64G64B64_SFLOAT = static_cast<uint32_t>(DATA::_64_64_64_SFLOAT),
				R64G64B64A64_UINT = static_cast<uint32_t>(DATA::_64_64_64_64_UINT),
				R64G64B64A64_SINT = static_cast<uint32_t>(DATA::_64_64_64_64_SINT),
				R64G64B64A64_SFLOAT = static_cast<uint32_t>(DATA::_64_64_64_64_SFLOAT),

				D16_UNORM,
				D32_SFLOAT,
				S8_UINT,
				D16_UNORM_S8_UINT,
				D24_UNORM_S8_UINT,
				D32_SFLOAT_S8_UINT,

				MAX

			}; // enum class TEXTURE

			inline static bool isColor(const FORMAT::TEXTURE format) {

				if (format >= FORMAT::TEXTURE::R8_UNORM &&
					format <= FORMAT::TEXTURE::R64G64B64A64_SFLOAT) return true;

				return false;
			}

			inline static bool isDepth(const FORMAT::TEXTURE format) {

				if (format >= FORMAT::TEXTURE::D16_UNORM &&
					format <= FORMAT::TEXTURE::D32_SFLOAT_S8_UINT) return true;

				return false;
			}

			inline static uint32_t dimension(const FORMAT::TEXTURE format) {
			
				switch (format) {

				case FORMAT::TEXTURE::R8_UNORM: return 1;
				case FORMAT::TEXTURE::R8_SNORM: return 1;
				case FORMAT::TEXTURE::R8_UINT: return 1;
				case FORMAT::TEXTURE::R8_SINT: return 1;
				case FORMAT::TEXTURE::R8G8_UNORM: return 2;
				case FORMAT::TEXTURE::R8G8_SNORM: return 2;
				case FORMAT::TEXTURE::R8G8_UINT: return 2;
				case FORMAT::TEXTURE::R8G8_SINT: return 2;
				case FORMAT::TEXTURE::R8G8B8_UNORM: return 3;
				case FORMAT::TEXTURE::R8G8B8_SNORM: return 3;
				case FORMAT::TEXTURE::R8G8B8_UINT: return 3;
				case FORMAT::TEXTURE::R8G8B8_SINT: return 3;
				case FORMAT::TEXTURE::R8G8B8A8_UNORM: return 4;
				case FORMAT::TEXTURE::R8G8B8A8_SNORM: return 4;
				case FORMAT::TEXTURE::R8G8B8A8_UINT: return 4;
				case FORMAT::TEXTURE::R8G8B8A8_SINT: return 4;

				case FORMAT::TEXTURE::R16_UNORM: return 2;
				case FORMAT::TEXTURE::R16_SNORM: return 2;
				case FORMAT::TEXTURE::R16_UINT: return 2;
				case FORMAT::TEXTURE::R16_SINT: return 2;
				case FORMAT::TEXTURE::R16_SFLOAT: return 2;
				case FORMAT::TEXTURE::R16G16_UNORM: return 4;
				case FORMAT::TEXTURE::R16G16_SNORM: return 4;
				case FORMAT::TEXTURE::R16G16_UINT: return 4;
				case FORMAT::TEXTURE::R16G16_SINT: return 4;
				case FORMAT::TEXTURE::R16G16_SFLOAT: return 4;
				case FORMAT::TEXTURE::R16G16B16_UNORM: return 6;
				case FORMAT::TEXTURE::R16G16B16_SNORM: return 6;
				case FORMAT::TEXTURE::R16G16B16_UINT: return 6;
				case FORMAT::TEXTURE::R16G16B16_SINT: return 6;
				case FORMAT::TEXTURE::R16G16B16_SFLOAT: return 6;
				case FORMAT::TEXTURE::R16G16B16A16_UNORM: return 8;
				case FORMAT::TEXTURE::R16G16B16A16_SNORM: return 8;
				case FORMAT::TEXTURE::R16G16B16A16_UINT: return 8;
				case FORMAT::TEXTURE::R16G16B16A16_SINT: return 8;
				case FORMAT::TEXTURE::R16G16B16A16_SFLOAT: return 8;

				case FORMAT::TEXTURE::R32_UINT: return 4;
				case FORMAT::TEXTURE::R32_SINT: return 4;
				case FORMAT::TEXTURE::R32_SFLOAT: return 4;
				case FORMAT::TEXTURE::R32G32_UINT: return 8;
				case FORMAT::TEXTURE::R32G32_SINT: return 8;
				case FORMAT::TEXTURE::R32G32_SFLOAT: return 8;
				case FORMAT::TEXTURE::R32G32B32_UINT: return 12;
				case FORMAT::TEXTURE::R32G32B32_SINT: return 12;
				case FORMAT::TEXTURE::R32G32B32_SFLOAT: return 12;
				case FORMAT::TEXTURE::R32G32B32A32_UINT: return 16;
				case FORMAT::TEXTURE::R32G32B32A32_SINT: return 16;
				case FORMAT::TEXTURE::R32G32B32A32_SFLOAT: return 16;

				case FORMAT::TEXTURE::R64_UINT: return 8;
				case FORMAT::TEXTURE::R64_SINT: return 8;
				case FORMAT::TEXTURE::R64_SFLOAT: return 8;
				case FORMAT::TEXTURE::R64G64_UINT: return 16;
				case FORMAT::TEXTURE::R64G64_SINT: return 16;
				case FORMAT::TEXTURE::R64G64_SFLOAT: return 16;
				case FORMAT::TEXTURE::R64G64B64_UINT: return 24;
				case FORMAT::TEXTURE::R64G64B64_SINT: return 24;
				case FORMAT::TEXTURE::R64G64B64_SFLOAT: return 24;
				case FORMAT::TEXTURE::R64G64B64A64_UINT: return 32;
				case FORMAT::TEXTURE::R64G64B64A64_SINT: return 32;
				case FORMAT::TEXTURE::R64G64B64A64_SFLOAT: return 32;
				}
			}

		};

		using FORMAT_ARR = std::vector<FORMAT>;

	} // namespace COMMON

} // namespace FE

#endif // FORMAT__H