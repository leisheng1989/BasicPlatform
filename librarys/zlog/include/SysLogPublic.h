#ifndef __SYSLOGPUBLIC_H__
#define __SYSLOGPUBLIC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zlog.h"

struct sys_log {
    zlog_category_t *pZc;
};

extern  struct sys_log gSysLog;

int SysLogInit(const char *confpath);
void SysLoguninit(void);


#define SysFatalTrace(format, args...) \
    do \
    { \
        if (gSysLog.pZc) { \
            zlog(gSysLog.pZc, __FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__, \
            ZLOG_LEVEL_FATAL, format, ##args); \
        } \
    } while(0) \


#define SysErrorTrace(format, args...) \
    do \
    { \
        if (gSysLog.pZc) { \
            zlog(gSysLog.pZc, __FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__, \
            ZLOG_LEVEL_ERROR, format, ##args); \
        } \
    } while(0) \

#define SysWarnTrace(format, args...) \
        do \
        { \
            if (gSysLog.pZc) { \
                zlog(gSysLog.pZc, __FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__, \
                ZLOG_LEVEL_WARN, format, ##args); \
            } \
        } while(0) \
        
        
#define SysInfoTrace(format, args...) \
        do \
        { \
            if (gSysLog.pZc) { \
                zlog(gSysLog.pZc, __FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__, \
                ZLOG_LEVEL_INFO, format, ##args); \
            } \
        } while(0) \

#define SysDebugTrace(format, args...) \
        do \
        { \
            if (gSysLog.pZc) { \
                zlog(gSysLog.pZc, __FILE__, sizeof(__FILE__)-1, __func__, sizeof(__func__)-1, __LINE__, \
                ZLOG_LEVEL_DEBUG, format, ##args); \
            } \
        } while(0) \


#ifdef __cplusplus
}
#endif

#endif /* __SYSLOGPUBLIC_H__ */
