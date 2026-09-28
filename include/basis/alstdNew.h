//! @file alstdNew.h
//!
//! @author Stephen A

#ifndef ALSTD_NEW_H
#define ALSTD_NEW_H

#include <basis/alstdTypes.h>
#include <heap/alstdAllocator.h>
#include <new>

using namespace alstd;

/**
* @param size_t Size of the object.
*
* @param IAllocator Allocator object.
*
* @param tag If the user wants to, they can define a tag name to print.
*
* @param alignment Device heap alignment (DEFAULT: 16)
*
* @details alstd new object.
*/
void* operator new(size_t size, IAllocator* pAllocator, const char* tag = NULL, s32 alignment = IAllocator::DEFAULT_MEMORY_SIZE);

/**
* @param size_t Size of the object.
*
* @param IAllocator Allocator object.
*
* @param tag If the user wants to, they can define a tag name to print.
*
* @param alignment Device heap alignment (DEFAULT: 16)
*
* @details alstd new[] object.
*/
void* operator new[](size_t size, IAllocator* pAllocator, const char* tag = NULL, s32 alignment = IAllocator::DEFAULT_MEMORY_SIZE);

/**
* @param ptr The object being destroyed.
*
* @details alstd delete object.
*/
void operator delete(void* ptr);

/**
* @param ptr The object being destroyed.
*
* @details alstd delete[] object.
*/
void operator delete[](void* ptr);

#endif // ALSTD_ALSTDNEW_H
