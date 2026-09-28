//! @file alstdSingleton.h
//!
//! @author Stephen A

#ifndef ALSTD_SINGLETON_H
#define ALSTD_SINGLETON_H

#include <prim/alstdHeapUtil.h>
#include <dev/alstdAssert.h>

#define ALSTD_INSTANCE(CLASS) (CLASS::instance())

#define ALSTD_SINGLETON_DISPOSER(CLASS)                                                             \
public:                                                                                            \
    class SingletonDisposer_ : public alstd::IDisposer                                              \
    {                                                                                              \
    public:                                                                                        \
        using alstd::IDisposer::IDisposer;                                                          \
        virtual ~SingletonDisposer_();                                                             \
                                                                                                   \
        static SingletonDisposer_* sStaticDisposer;                                                \
    };                                                                                             \
                                                                                                   \
    static CLASS* instance() { return sInstance; }                                                 \
    static CLASS* createInstance(alstd::IAllocator* heap);                                         \
    static void deleteInstance();                                                                  \
                                                                                                   \
    CLASS(const CLASS&){}                                                                          \
    CLASS& operator=(const CLASS&){};                                                              \
    CLASS(CLASS&&){};                                                                              \
    CLASS& operator=(CLASS&&){};                                                                   \
                                                                                                   \
protected:                                                                                         \
    static CLASS* sInstance;                                                                       \
                                                                                                   \
    friend class SingletonDisposer_;                                                               \
    u32 mSingletonDisposerBuf_[sizeof(SingletonDisposer_) / sizeof(u32)];

#define ALSTD_CREATE_SINGLETON_INSTANCE(CLASS)                                                      \
    CLASS* CLASS::createInstance(alstd::IAllocator* heap)                                          \
    {                                                                                              \
        if (!sInstance)                                                                            \
        {                                                                                          \
            auto* buffer = new (heap, alignof(CLASS)) u8[sizeof(CLASS)];                                               \
			ALSTD_ASSERT_MSG(!SingletonDisposer_::sStaticDisposer, "Create Singleton Twice (%s).",  \
                            #CLASS);                                                               \
            auto* disposer_buffer = buffer + offsetof(CLASS, mSingletonDisposerBuf_);              \
            SingletonDisposer_::sStaticDisposer = new (disposer_buffer) SingletonDisposer_(heap);  \
            sInstance = new (buffer) CLASS;                                                        \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            ALSTD_ASSERT_MSG(false, "Create Singleton Twice (%s) : addr %p", #CLASS, sInstance);    \
        }                                                                                          \
                                                                                                   \
        return CLASS::sInstance;                                                                   \
    }

#define ALSTD_DELETE_SINGLETON_INSTANCE(CLASS)                                                      \
    void CLASS::deleteInstance()                                                                   \
    {                                                                                              \
        SingletonDisposer_* staticDisposer = SingletonDisposer_::sStaticDisposer;                  \
        if (SingletonDisposer_::sStaticDisposer != NULL)                                           \
        {                                                                                          \
            SingletonDisposer_::sStaticDisposer = NULL;                                            \
            staticDisposer->~SingletonDisposer_();                                                 \
                                                                                                   \
            delete sInstance;                                                                      \
                                                                                                   \
            sInstance = NULL;                                                                      \
        }                                                                                          \
    }

#define ALSTD_SINGLETON_DISPOSER_IMPL(CLASS)                                                        \
    CLASS::SingletonDisposer_::~SingletonDisposer_()                                               \
    {                                                                                              \
        if (this == sStaticDisposer)                                                               \
        {                                                                                          \
            sStaticDisposer = nullptr;                                                             \
            CLASS::sInstance->~CLASS();                                                            \
            CLASS::sInstance = nullptr;                                                            \
        }                                                                                          \
    }                                                                                              \
    SEAD_CREATE_SINGLETON_INSTANCE(CLASS)                                                          \
    SEAD_DELETE_SINGLETON_INSTANCE(CLASS)                                                          \
    CLASS* CLASS::sInstance;                                                                       \
    CLASS::SingletonDisposer_* CLASS::SingletonDisposer_::sStaticDisposer;

#endif // ALSTD_SINGLETON_H
