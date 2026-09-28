//! @file alstdDisposeUtil.h
//!
//! @author Stephen A

#ifndef ALSTD_HEAP_UTIL_H
#define ALSTD_HEAP_UTIL_H

#include <basis/alstdTypes.h>
#include <container/alstdLinkedListImpl.h>

namespace alstd
{

class IAllocator;

class IDisposer
{
public:
    enum DisposeFlag
    {
        cNull = -1,
        cObjectNonDisposable,
        cObjectDispable,
    };
public:
	IDisposer();
	IDisposer(IAllocator* pAllocator, DisposeFlag flag);

	virtual ~IDisposer();
	virtual void dispose();

	IAllocator* getAllocator(){ return mAllocator; }
private:
	IAllocator* mAllocator;
	LinkedListImpl<IDisposer>* mpDisposableList;
};

class IThread
{
public:
	IThread() = default;

	virtual ~IThread() = default;
	virtual void run() = 0;
	virtual void start() = 0;
	virtual void initThreadStack(const void* stackTop, const void* stackBtm) = 0;
	virtual void join() = 0;
	virtual void stop() = 0;
};
}

#endif