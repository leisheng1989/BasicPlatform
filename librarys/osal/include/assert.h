#ifndef __ASSERT__H__
#define __ASSERT__H__

#ifdef __cplusplus
extern "C" {
#endif

#undef assert
#undef ASSERT

#ifdef NDEBUG
#define ASSERT(expr) ((void) 0)
#else
#define ASSERT(expr) \
    do { \
        if (!(expr)) { \
            SysFatalTrace("!!ASSERTION FAILED: \"" #expr "\""); \
            abort(); \
        } \
    } while(0)
#endif

#define assert ASSERT

#define ASSERT_RETURN(expr, retval) \
    do { \
        if (!(expr)) { \
            SysFatalTrace("!!ASSERTION FAILED: \"" #expr "\""); \
            return retval; \
        } \
    } while(0)

#ifdef __cplusplus
}
#endif

#endif /* __ASSERT__H__ */
