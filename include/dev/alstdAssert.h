//! @file alstdAssert.h
//!
//! @author Stephen A

#ifndef ALSTD_ASSERT_H
#define ALSTD_ASSERT_H

#include <basis/alstdPrint.h>

namespace alstd
{

void HaltWithDetail(const char* source, s32 lineNo, const char* fmt, ...);

void HaltWithDetailNoFmt(const char* source, s32 lineNo, const char* fmt, ...);

}

#ifdef ALSTD_ENABLE_ASSERT

#define ALSTD_ASSERT_MSG(condition, message, ...)							\
	if(!(condition))														\
	{																		\
		alstd::HaltWithDetail(__FILE__, __LINE__, message, ##__VA_ARGS__);	\
	}

#define ALSTD_ASSERT(condition)												\
	if(!(condition))														\
	{																		\
		alstd::HaltWithDetailNoFmt(__FILE__, __LINE__, #condition);			\
	}

#else

#define ALSTD_ASSERT_MSG(condition, message, ...)
#define ALSTD_ASSERT(condition)

#endif // ALSTD_ENABLE_ASSERT


#endif // ALSTD_ASSERT_H
