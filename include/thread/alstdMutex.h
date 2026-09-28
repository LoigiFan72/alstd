//! @file alstdMutex.h
//!
//! @author Stephen A

#ifndef ALSTD_MUTEX_H
#define ALSTD_MUTEX_H

#ifdef ALSTD_PLATFORM_WINDOWS
#include <mutex>
#elif ALSTD_PLATFORM_CTR
#include <nn/os.h>
#endif

#include <prim/alstdHeapUtil.h>
#include <prim/alstdScopedUtil.h>

namespace alstd
{
class Mutex
{
public:
    class ScopedLock;
	Mutex();
    explicit Mutex(bool isLocked); /* Compatability with 3DS Device. */

	~Mutex();

	void lock();
	bool tryLock();

	void unlock();

private:

#ifdef ALSTD_PLATFORM_WINDOWS
	std::mutex mMutexInner;
#elif ALSTD_PLATFORM_CTR
    nn::os::Mutex mMutexInner;
#endif
};

ALSTD_DEFINE_SCOPED_LOCK(Mutex, lock(), unlock());

}

#endif // ALSTD_MUTEX_H