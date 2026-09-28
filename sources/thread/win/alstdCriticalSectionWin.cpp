//! @file alstdCriticalSectionWin.cpp
//!
//! @author Stephen A
//!
//! @brief Critical Section implmentation for windows.

#include <thread/alstdCriticalSection.h>

namespace alstd
{

CriticalSection::CriticalSection():
	IDisposer()
{
	initialize();
}

CriticalSection::CriticalSection(IAllocator* pAllocator):
	IDisposer(pAllocator, cObjectNonDisposable),
	mCriticalSectionInner()
{
	initialize();
}

CriticalSection::~CriticalSection()
{
	finalize();
}

void CriticalSection::initialize()
{
	InitializeCriticalSection(&mCriticalSectionInner);
}

void CriticalSection::finalize()
{
	DeleteCriticalSection(&mCriticalSectionInner);
}

void CriticalSection::enter()
{
	EnterCriticalSection(&mCriticalSectionInner);
}

bool CriticalSection::tryEnter()
{
	return TryEnterCriticalSection(&mCriticalSectionInner);
}

void CriticalSection::leave()
{
	LeaveCriticalSection(&mCriticalSectionInner);
}
} // namespace alstd
