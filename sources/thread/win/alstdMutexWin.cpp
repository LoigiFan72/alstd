//! @file alstdMutexWin.cpp
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
    mMutexInner()
{
    ALSTD_UNUSED(isLocked)
}

Mutex::~Mutex()
{
}

bool Mutex::tryLock()
{
    return mMutexInner.try_lock();
}

void Mutex::lock()
{
    mMutexInner.lock();
}

void Mutex::unlock()
{
    mMutexInner.unlock();
}
}