#ifndef __ASSERT__H__
#define __ASSERT__H__

#undef assert
#ifdef NDEBUG
#define assert(expr) ((void) 0)
#else
#define assert(expr) \
    ((expr) ? ((void) 0) : SysFatalTrace("!!ASSERTION FAILED: \"" #expr "\""))\
#endif

#endif /* __ASSERT__H__ */