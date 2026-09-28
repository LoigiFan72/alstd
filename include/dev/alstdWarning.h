//! @file alstdWARNING.h
//!
//! @author Stephen A

#ifndef ALSTD_WARNING_H
#define ALSTD_WARNING_H

#include <basis/alstdPrint.h>

namespace alstd
{
void WarnWithDetail(const char* source, s32 lineNo, const char* fmt, ...);
}

#ifdef ALSTD_ENABLE_WARNING

#define ALSTD_WARNING(message, ...)							                \
	alstd::WarnWithDetail(__FILE__, __LINE__, message, ##__VA_ARGS__);

#else

#define ALSTD_WARNING(message, ...)

#endif // ALSTD_ENABLE_WARNING


#endif // ALSTD_WARNING_H
