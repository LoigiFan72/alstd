//! @file alstdAllocator.h
//!
//! @author Stephen A

#ifndef ALSTD_SCOPED_UTIL_H
#define ALSTD_SCOPED_UTIL_H

#include "basis/alstdTypes.h"

namespace alstd
{

#define ALSTD_DEFINE_SCOPED_OBJECT(CLASS, name, enter, destroy)  \
    class CLASS::name  \
    { \
    private: \
        CLASS& mReference; \
    public: \
        name(CLASS& reference): mReference(reference){ mReference.enter; } \
        ~name(){ mReference.destroy; } \
    };

#define ALSTD_DEFINE_SCOPED_LOCK(CLASS, enter, destroy)  \
    class CLASS::ScopedLock  \
    { \
    private: \
        CLASS& mReference; \
    public: \
        ScopedLock(CLASS& reference): mReference(reference){ mReference.enter; } \
        ~ScopedLock(){ mReference.destroy; } \
    };

}

#endif // ALSTD_SCOPED_UTIL_H