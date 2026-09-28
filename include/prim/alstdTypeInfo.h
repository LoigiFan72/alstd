//! @file alstdTypeInfo.h
//!
//! @author Stephen A

#ifndef ALSTD_TYPE_INFO_H
#define ALSTD_TYPE_INFO_H

#include <basis/alstdTypes.h>

#define ALSTD_RTTI(ClassName) \
public: \
    virtual std::string_view getRuntimeTypeInfoClassStatic() { return #ClassName; } \
    virtual std::string_view getRuntimeTypeInfoClassName() const { return getRuntimeTypeInfoClassStatic(); }

#endif // ALSTD_TYPE_INFO_H

