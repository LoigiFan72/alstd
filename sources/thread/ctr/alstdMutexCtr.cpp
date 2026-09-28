//! @file alstdMutexCtr.cpp
//!
//! @author Stephen A
//!
//! @brief Mutex Section implmentation for windows.

#include <thread/alstdMutex.h>
#include <dev/alstdAssert.h>

namespace alstd
{
Mutex::Mutex():
    mMutexInner()
{
}

Mutex::Mutex(bool isLocked):
    mMutexInner(isLocked)
{
}

Mutex::~Mutex()
{
}

bool Mutex::tryLock()
{
    return mMutexInner.TryLock();
}

void Mutex::lock()
{
    mMutexInner.Lock();
}

void Mutex::unlock()
{
    mMutexInner.Unlock();
}
}