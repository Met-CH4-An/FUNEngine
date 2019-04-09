#ifndef PCH__H
#define PCH__H
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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "maths/maths.h"
#include <fstream>
#include <memory>

using floatArr = std::vector<float>;
using floatArrs = std::vector<floatArr>;

using uint32Arr = std::vector<uint32_t>;
using uint32Arrs = std::vector<uint32Arr>;

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
	<< __FILE__ << " (" << __LINE__ << ").\n"\
	<< #left << "=" /*<< (left)*/ << "; " << #right << "=" /*<< (right)*/ << "\n"\
	<< "NOTE: "<< #message << "\n\n" << std::endl;\
	}\
}

#define ASSERT_EX(left,operator,right,message,action) { \
if(!((left) operator (right))) {\
	std::cerr << "ASSERT FAILED: " << #left << " " << #operator << " " << #right << "\n"\
	<< __FILE__ << " (" << __LINE__ << ").\n"\
	<< #left << "=" /*<< (left)*/ << "; " << #right << "=" /*<< (right)*/ << "\n"\
	<< "NOTE: "<< #message << "\n\n" << std::endl;\
	action;\
	}\
}

#define DEBUG_INFO

/*template <class t_class>
class Singleton {

public:

	static t_class& instance() {

		static t_class _instance;
		return _instance;
	}

protected:

	Singleton() {};
	~Singleton() {};

	Singleton(Singleton const&) = delete;
	Singleton& operator= (Singleton const&) = delete;

}; // class Singleton

#define DECLARE_SINGLETON(className) private: friend class Singleton<className>;

#include <Windows.h>
inline size_t align(size_t x, size_t a) { return ((x - 1) | (a - 1)) + 1; }
//#define align(x, a) ((((x)-1) | ((a)-1)) + 1)

template<size_t PageSize = 65536>
class PagePool
{
public:
	void* GetPage() {
		void* page = VirtualAlloc(NULL, PageSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		pages.push_back(page);
		return page;
	}

	~PagePool() {
		for (std::vector<void*>::iterator i = pages.begin(); i != pages.end(); ++i) {
			VirtualFree(*i, 0, MEM_RELEASE);
		}
	}
private:
	std::vector<void*> pages;
};

//template<class T, size_t PageSize = 65536, size_t Alignment = 8 * sizeof(void*) >
template<class T, size_t PageSize = 65536, size_t Alignment = 8>
class BlockPool : PagePool<PageSize>
{
public:
	BlockPool() : head(NULL) {
		BlockSize = align(sizeof(T), Alignment);
		count = PageSize / BlockSize;
	}

	void* AllocBlock() {
		// todo: lock(this)
		if (!head) FormatNewPage();
		void* tmp = head;
		head = *(void**)head;
		return tmp;
	}

	void FreeBlock(void* tmp) {
		// todo: lock(this)
		*(void**)tmp = head;
		head = tmp;
	}
private:
	void* head;
	size_t BlockSize;
	size_t count;

	void FormatNewPage() {
		void* tmp = GetPage();
		head = tmp;
		for (size_t i = 0; i < count - 1; i++) {
			void* next = (char*)tmp + BlockSize;
			*(void**)tmp = next;
			tmp = next;
		}
		*(void**)tmp = NULL;
	}
};

template<class T>
class BlockAlloc
{
public:
	static void* operator new(size_t s) {
		if (s != sizeof(T)) {
			return ::operator new(s);
		}
		return pool.AllocBlock();
	}

	static void operator delete(void* m, size_t s) {
		if (s != sizeof(T)) {
			::operator delete(m);
		}
		else if (m != NULL) {
			pool.FreeBlock(m);
		}
	}

	// todo: implement nothrow_t overloads, according to borisko' comment
	// http://habrahabr.ru/post/148657/#comment_5020297

	// Avoid hiding placement new that's needed by the stl containers...
	static void* operator new(size_t, void* m) {
		return m;
	}
	// ...and the warning about missing placement delete...
	static void operator delete(void*, void*) {
	}

private:
	static BlockPool<T> pool;
};
template<class T> BlockPool<T> BlockAlloc<T>::pool;*/

#endif // PCH__H