//! @file alstdCriticalSection.h
//!
//! @author Stephen A

#ifndef ALSTD_CRITICALSECTION_H
#define ALSTD_CRITICALSECTION_H

#ifdef ALSTD_PLATFORM_WINDOWS
#include <basis/win/alstdWindows.h>
#elif ALSTD_PLATFORM_CTR
#include <nn/os.h>
#endif
#include <prim/alstdHeapUtil.h>
#include <prim/alstdScopedUtil.h>

namespace alstd
{
class CriticalSection : public IDisposer
{
public:
	class ScopedLock;

	CriticalSection();
	CriticalSection(IAllocator* heap);

	virtual ~CriticalSection();

	void initialize();
	void finalize();

	void enter();
	bool tryEnter();

	void leave();
private:
#ifdef ALSTD_PLATFORM_WINDOWS
	CRITICAL_SECTION mCriticalSectionInner;
#elif ALSTD_PLATFORM_CTR
	nn::os::CriticalSection mCriticalSectionInner;
#endif
};

ALSTD_DEFINE_SCOPED_LOCK(CriticalSection, enter(), leave());

}

#endif // ALSTD_CRITICALSECTION_H
