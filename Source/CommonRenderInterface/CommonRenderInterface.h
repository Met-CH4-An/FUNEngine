#ifndef COMMON_RENDER_INTERFACE__H
#define COMMON_RENDER_INTERFACE__H
////////////////////////////////////////////////////////////////
// секция компиляция файла
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция родительского класса
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция форвард-декларации
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// секция для остального
////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <memory>

#define DECLARE_ENUM_OPERATIONS(ENUM_NAME)									\
	inline ENUM_NAME                                                        \
	operator|(ENUM_NAME left, ENUM_NAME right) {                              \
	 return ENUM_NAME(static_cast<int>(left) | static_cast<int>(right)); } \
	\
	inline ENUM_NAME                                                        \
	operator&(ENUM_NAME left, ENUM_NAME right) {                              \
	 return ENUM_NAME(static_cast<int>(left) & static_cast<int>(right)); }	\
	\
	inline ENUM_NAME                                                        \
	operator^(ENUM_NAME left, ENUM_NAME right) {                              \
	 return ENUM_NAME(static_cast<int>(left) ^ static_cast<int>(right)); } \
	\
	inline ENUM_NAME                                                        \
	operator~(ENUM_NAME left) {                                               \
	 return ENUM_NAME(~static_cast<int>(left)); }                          \
	\
	inline const ENUM_NAME&                                                 \
	operator|=(ENUM_NAME& left, ENUM_NAME right) {                            \
	 return left = left | right; }                                         \
	\
	inline const ENUM_NAME&                                                 \
	operator&=(ENUM_NAME& left, ENUM_NAME right) {                            \
	 return left = left & right; }                                         \
	\
	inline const ENUM_NAME&                                                 \
	operator^=(ENUM_NAME& left, ENUM_NAME right) {                            \
	 return left = left ^ right; }

#define ASSERT(left,operator,right, message) { \
if(!((left) operator (right))) {\
	std::cerr << "ASSERT FAILED: " << #left << " " << #operator << " " << #right << "\n"\
	<< __FILE__ << " (" << __LINE__ << ")./n"\
	<< #left << "=" /*<< (left)*/ << "; " << #right << "=" /*<< (right)*/ << "\n"\
	<< "NOTE: "<< #message << "\n\n" << std::endl;\
	}\
}

#define ASSERT_EX(left,operator,right,message,action) { \
if(!((left) operator (right))) {\
	std::cerr << "ASSERT FAILED: " << #left << " " << #operator << " " << #right << "\n"\
	<< __FILE__ << " (" << __LINE__ << ")./n"\
	<< #left << "=" /*<< (left)*/ << "; " << #right << "=" /*<< (right)*/ << "\n"\
	<< "NOTE: "<< #message << "\n\n" << std::endl;\
	action;\
	}\
}

namespace FE {

	namespace CRI {
		
		class e_cri_common : public std::exception {};

		using Hardware = std::shared_ptr<void>;


		/*inline uint32_t FORMAT_SIZE(CRI_FORMAT format) {

			switch (format) {

			case CRI_FORMAT::D16_UNORM: return 1;
			case CRI_FORMAT::D32_SFLOAT: return 1;
			case CRI_FORMAT::S8_UINT: return 1;
			case CRI_FORMAT::D16_UNORM_S8_UINT: return 1;
			case CRI_FORMAT::D24_UNORM_S8_UINT: return 1;
			case CRI_FORMAT::D32_SFLOAT_S8_UINT: return 1;

			case CRI_FORMAT::R8_UNORM: return 1;
			case CRI_FORMAT::R8_SNORM: return 1;
			case CRI_FORMAT::R8_UINT: return 1;
			case CRI_FORMAT::R8_SINT: return 1;
			case CRI_FORMAT::R8G8_UNORM: return 2;
			case CRI_FORMAT::R8G8_SNORM: return 2;
			case CRI_FORMAT::R8G8_UINT: return 2;
			case CRI_FORMAT::R8G8_SINT: return 2;
			case CRI_FORMAT::R8G8B8_UNORM: return 3;
			case CRI_FORMAT::R8G8B8_SNORM: return 3;
			case CRI_FORMAT::R8G8B8_UINT: return 3;
			case CRI_FORMAT::R8G8B8_SINT: return 3;
			case CRI_FORMAT::R8G8B8A8_UNORM: return 4;
			case CRI_FORMAT::R8G8B8A8_SNORM: return 4;
			case CRI_FORMAT::R8G8B8A8_UINT: return 4;
			case CRI_FORMAT::R8G8B8A8_SINT: return 4;

			case CRI_FORMAT::R16_UNORM: return 2;
			case CRI_FORMAT::R16_SNORM: return 2;
			case CRI_FORMAT::R16_UINT: return 2;
			case CRI_FORMAT::R16_SINT: return 2;
			case CRI_FORMAT::R16_SFLOAT: return 2;
			case CRI_FORMAT::R16G16_UNORM: return 4;
			case CRI_FORMAT::R16G16_SNORM: return 4;
			case CRI_FORMAT::R16G16_UINT: return 4;
			case CRI_FORMAT::R16G16_SINT: return 4;
			case CRI_FORMAT::R16G16_SFLOAT: return 4;
			case CRI_FORMAT::R16G16B16_UNORM: return 6;
			case CRI_FORMAT::R16G16B16_SNORM: return 6;
			case CRI_FORMAT::R16G16B16_UINT: return 6;
			case CRI_FORMAT::R16G16B16_SINT: return 6;
			case CRI_FORMAT::R16G16B16_SFLOAT: return 6;
			case CRI_FORMAT::R16G16B16A16_UNORM: return 8;
			case CRI_FORMAT::R16G16B16A16_SNORM: return 8;
			case CRI_FORMAT::R16G16B16A16_UINT: return 8;
			case CRI_FORMAT::R16G16B16A16_SINT: return 8;
			case CRI_FORMAT::R16G16B16A16_SFLOAT: return 8;

			case CRI_FORMAT::R32_UINT: return 4;
			case CRI_FORMAT::R32_SINT: return 4;
			case CRI_FORMAT::R32_SFLOAT: return 4;
			case CRI_FORMAT::R32G32_UINT: return 8;
			case CRI_FORMAT::R32G32_SINT: return 8;
			case CRI_FORMAT::R32G32_SFLOAT: return 8;
			case CRI_FORMAT::R32G32B32_UINT: return 12;
			case CRI_FORMAT::R32G32B32_SINT: return 12;
			case CRI_FORMAT::R32G32B32_SFLOAT: return 12;
			case CRI_FORMAT::R32G32B32A32_UINT: return 16;
			case CRI_FORMAT::R32G32B32A32_SINT: return 16;
			case CRI_FORMAT::R32G32B32A32_SFLOAT: return 16;

			case CRI_FORMAT::R64_UINT: return 8;
			case CRI_FORMAT::R64_SINT: return 8;
			case CRI_FORMAT::R64_SFLOAT: return 8;
			case CRI_FORMAT::R64G64_UINT: return 16;
			case CRI_FORMAT::R64G64_SINT: return 16;
			case CRI_FORMAT::R64G64_SFLOAT: return 16;
			case CRI_FORMAT::R64G64B64_UINT: return 24;
			case CRI_FORMAT::R64G64B64_SINT: return 24;
			case CRI_FORMAT::R64G64B64_SFLOAT: return 24;
			case CRI_FORMAT::R64G64B64A64_UINT: return 32;
			case CRI_FORMAT::R64G64B64A64_SINT: return 32;
			case CRI_FORMAT::R64G64B64A64_SFLOAT: return 32;
			};

			return 0;
		}*/

		class		CCRICore;
		using		CRICore = CCRICore * ;
		struct		CRI_CORE_CREATE_INFO;

		class		CCRIContext;
		using		CRIContext = std::shared_ptr<CCRIContext>;
		using		CRIContextArr = std::vector<CRIContext>;
		struct		CRI_CONTEXT_CREATE_INFO;

		class		CCRIDrawBuffer;
		using		CRIDrawBuffer = CCRIDrawBuffer * ;
		using		CRIDrawBufferArr = std::vector<CRIDrawBuffer>;
		struct		CRI_DRAW_BUFFER_CREATE_INFO;
		using		CRI_DRAW_BUFFER_CREATE_INFO_ARR = std::vector<CRI_DRAW_BUFFER_CREATE_INFO>;

		class		CCRIRenderPass;
		using		CRIRenderPass = std::shared_ptr<CCRIRenderPass>;
		using		CRIRenderPassArr = std::vector<CRIRenderPass>;
		struct		CRI_RENDER_PASS_CI;
		using		CRI_RENDER_PASS_CI_ARR = std::vector<CRI_RENDER_PASS_CI>;

		class		CCRIPipeline;
		using		CRIPipeline = std::shared_ptr<CCRIPipeline>;
		using		CRIPipelineArr = std::vector<CRIPipeline>;
		struct		CRI_PIPELINE_CI;
		using		CRI_PIPELINE_CI_ARR = std::vector<CRI_PIPELINE_CI*>;
		struct		CRI_PIPELINE_INFO;

		class		CCRIProgram;
		using		CRIProgram = std::shared_ptr<CCRIProgram>;
		using		CRIProgramArr = std::vector<CRIProgram>;
		struct		CRI_PROGRAM_CREATE_INFO;

		class		CCRIDataBuffer;
		using		CRIDataBuffer = std::shared_ptr<CCRIDataBuffer>;
		using		CRIDataBufferArr = std::vector<CRIDataBuffer>;
		struct		CRI_DATA_BUFFER_CREATE_INFO;
		using		CRI_DATA_BUFFER_CREATE_INFO_ARR = std::vector<CRI_DATA_BUFFER_CREATE_INFO>;
		struct		CRI_DATA_BUFFER_UPDATE_INFO;
		using		CRI_DATA_BUFFER_UPDATE_INFO_ARR = std::vector<CRI_DATA_BUFFER_UPDATE_INFO>;

		class		CCRIImageBuffer;
		using		CRIImageBuffer = std::shared_ptr<CCRIImageBuffer>;
		using		CRIImageBufferArr = std::vector<CRIImageBuffer>;
		struct		CRI_IMAGE_BUFFER_CREATE_INFO;
		using		CRI_IMAGE_BUFFER_CREATE_INFO_ARR = std::vector<CRI_IMAGE_BUFFER_CREATE_INFO>;

		class		CCRIImageBuffer;
		using		ImageBuffer = CCRIImageBuffer * ;





		class OPERATION {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Создать CRICore.

			\exception e_common_render_interface_create_fail Если создание не успешно.
			\param[out] core Указатель, где будет созданный CRICore.
			\param[in] createInfo Информация для создания.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			static void createCRICore(CRICore *core, const CRI_CORE_CREATE_INFO *createInfo);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Создать CRIPipeline.

			\param[in] createInfo Информация для создания.
			\param[out] pipeline Созданный CRIPipeline.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//static void createPipeline(CRI_PIPELINE_CI *createInfo, CRIPipeline *pipeline);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief Создать множество CRIDrawBuffer.

			\param[in] context Контекст для которого создаётся множество CRIDrawBuffer.
			\param[out] drawBuffer Созданное множество CRIDrawBuffer.
			\param[in] createInfo Информация для создания множества CRIDrawBuffer.
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			static void createDrawBuffer(CRIDrawBuffer *drawBuffer, const CRI_DRAW_BUFFER_CREATE_INFO *createInfo);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			static void drawBuffer(CRIContext context, CRIDrawBufferArr *drawBuffer);

		}; // class CRI

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/*!	\brief
		*/
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		template<class Impl, class Parent>
		class VulkanRenderInterfaceImpl : public Parent {

		public:

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			VulkanRenderInterfaceImpl(std::shared_ptr<Impl> impl) { m_Impl = impl; }

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			std::shared_ptr<Impl> getImpl(void) const { return m_Impl; }

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			/*!	\brief
			*/
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			const std::shared_ptr<Impl> getImplConst(void) const { return m_Impl; }

		private:

			std::shared_ptr<Impl>		m_Impl;

		}; // class VulkanRenderInterfaceImpl

	} // namespace CRI

} // namespace FE

#endif // COMMON_RENDER_INTERFACE__H
