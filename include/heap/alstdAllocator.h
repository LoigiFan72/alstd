//! @file alstdAllocator.h
//!
//! @author Stephen A

#ifndef ALSTD_HEAP_H
#define ALSTD_HEAP_H

#include <basis/alstdTypes.h>
#include <container/alstdLinkedListImpl.h>
#include <dev/alstdWarning.h>
#include <prim/alstdScopedUtil.h>
#include <algorithm>

#ifdef ALSTD_PLATFORM_CTR
#include <nn/nstd.h>
#endif

namespace alstd
{
class SafeString;

class IAllocator
{
public:

#ifdef ALSTD_PLATFORM_WINDOWS
    static const int DEFAULT_MEMORY_SIZE = 16; /* 16 bytes for x64 */
#elif ALSTD_PLATFORM_CTR
    static const int DEFAULT_MEMORY_SIZE = 4; /* 4 bytes for 3DS */
#else
    static const int DEFAULT_MEMORY_SIZE = 16; /* 16 bytes for 64 bit systems */
#endif

    IAllocator(){}

    virtual ~IAllocator(){ }
    virtual void* tryAlloc(size_t size, s32 alignment = DEFAULT_MEMORY_SIZE) = 0;
    virtual void* alloc(size_t size, s32 alignment = DEFAULT_MEMORY_SIZE) = 0;

    virtual void* tryCreate(void* obj, const SafeString& name) = 0;

    virtual void tryDestroy(void* obj) = 0;
    virtual void destroy(void* obj) = 0;

    virtual void free() = 0;
    virtual void freeAndDestroy(void* obj) = 0;

    static void* copy(void* dst, const void* src, size_t size)
    {
    #ifdef ALSTD_PLATFORM_WINDOWS
        std::memcpy(dst, src, size);
    #elif ALSTD_PLATFORM_CTR
        nn::nstd::ARMv6::MemCpy(dst, src, size);
    #endif
    }

    void allocAndCopy(void* dst, const void* src, size_t size)
    {
        if(tryAlloc(size))
        {
            std::memcpy(dst, src, size);
        }
        else
        {
            ALSTD_WARNING("IAllocator failed to alloc and copy heap from %p to %p\n", dst, src)
        }
    }
};

class ScopedAllocator
{
private:
    IAllocator* mpReference;
public:
    ScopedAllocator(IAllocator* ref, size_t size, s32 alignment = IAllocator::DEFAULT_MEMORY_SIZE):
        mpReference(ref)
    {
        mpReference->alloc(size, alignment);
    }

    ~ScopedAllocator()
    {
        mpReference->free();
    }
};

class DefaultAllocator : public IAllocator
{
public:
    class ScopedMemoryDump;

    DefaultAllocator();
    DefaultAllocator(IAllocator* ref);

    virtual ~DefaultAllocator();
    virtual void* tryAlloc(size_t size, s32 alignment = DEFAULT_MEMORY_SIZE);
    virtual void* alloc(size_t size, s32 alignment = DEFAULT_MEMORY_SIZE);

    virtual void* tryCreate(void* obj, const SafeString& name);

    virtual void tryDestroy(void* obj);
    virtual void destroy(void* obj);

    virtual void free();
    virtual void freeAndDestroy(void* obj);

    void initializeDump();
    void finalizeDump();

    LinkedListImpl<IAllocator>* mpPreviousHeapNode;
    LinkedListImpl<IAllocator>* mpNextHeapNode;
    size_t mHeapSize;
};

ALSTD_DEFINE_SCOPED_OBJECT(DefaultAllocator, ScopedMemoryDump, initializeDump(), finalizeDump())

}

#endif // ALSTD_HEAP_H
