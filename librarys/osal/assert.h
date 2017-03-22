#ifndef __ASSERT__H__
#define __ASSERT__H__

#ifdef __cplusplus
extern "C" {
#endif

#undef assert
#ifdef NDEBUG
#define assert(expr) ((void) 0)
#else
#define assert(expr) \
    ((expr) ? ((void) 0) : (SysFatalTrace("!!ASSERTION FAILED: \"" #expr "\""); abort()))\
#endif

#ifdef __cplusplus
}
#endif

#endif /* __ASSERT__H__ */