//! @file alstdCriticalSectionCtr.cpp
//!
//! @author Stephen A
//!
//! @brief Critical Section implmentation for 3DS (CTR).

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
	mCriticalSectionInner.Initialize();
}

void CriticalSection::finalize()
{
	mCriticalSectionInner.Finalize();
}

void CriticalSection::enter()
{
	mCriticalSectionInner.Enter();
}

bool CriticalSection::tryEnter()
{
	return mCriticalSectionInner.TryEnter();
}

void CriticalSection::leave()
{
	mCriticalSectionInner.Leave();
}
}