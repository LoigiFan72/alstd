//! @file alstdPrint.h
//!
//! @author Stephen A

#ifndef ALSTD_PRINT_H
#define ALSTD_PRINT_H

#include <basis/alstdTypes.h>
#include <cstdarg> // va_list / arg

namespace alstd
{
//! @brief Print a Thread-Safe message.
void TPrintf(const char* fmt, ...);

//! @brief Print a message using the va list.
void Printf(const char* fmt, std::va_list list);

//! @brief Print a Thread-Safe message, converts it into Printf
void TVPrintf(const char* fmt, ...);

}

#ifndef ALSTD_ENABLE_PRINT

#define ALSTD_TPRINT(message, ...)					\
	alstd::TPrintf(message, ##__VA_ARGS__);

#define ALSTD_PRINT(message, ...)					\
	alstd::TVPrintf(message, ##__VA_ARGS__);

#else

#define ALSTD_TPRINT(message, ...)
#define ALSTD_PRINT(message, ...)

#endif // ALSTD_ENABLE_PRINT


#endif // ALSTD_PRINT_H
