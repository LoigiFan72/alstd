//! @file alstdNew.${EXTENSION}
//!
//! @author Stephen A
//!
//! @brief Operator new implmentation for alstd.

#include <basis/alstdNew.h>

void* operator new(size_t size, IAllocator* pAllocator, const char* tag, s32 alignment)
{
    ALSTD_ASSERT(pAllocator)
    ALSTD_PRINT("[NEW %s]", tag);
    return pAllocator->alloc(size, alignment);
}

/** 
* @example new(size, allocator, "Sound Engine", IAllocator::DEFAULT_MEMORY_SIZE);
*/
void* operator new[](size_t size, IAllocator* pAllocator, const char* tag, s32 alignment)
{
    ALSTD_ASSERT(pAllocator)
    ALSTD_PRINT("[NEW ARRAY %s]", tag);
    return pAllocator->alloc(size, alignment);
}

void operator delete(void* obj)
{
    IAllocator* pAllocator = *reinterpret_cast<IAllocator**>((u32)obj - 4);
    pAllocator->destroy(obj);
}

void operator delete[](void* obj)
{
    IAllocator* pAllocator = *reinterpret_cast<IAllocator**>((u32)obj - 4);
    pAllocator->destroy(obj);
}