#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

#include "SysLogPublic.h"

struct sys_log gSysLog;


int SysLogInit(const char *confpath)
{
    int ret;
    struct sys_log *pSysLog;

    pSysLog = &gSysLog;
    
    if (confpath == NULL) {
        printf("invalid argument: confpath\n");
        return -1;
    }

    ret = zlog_init(confpath);
    if (ret != 0) {
        printf("zlog_init fail, ret=%d\n", ret);
        return -2;
    }

    pSysLog->pZc = zlog_get_category("sys_trace");
    if (!pSysLog->pZc) {
        printf("get cat fail\n");
        zlog_fini();
        return -3;
    }

    return 0;
}

void SysLoguninit(void)
{
    struct sys_log *pSysLog;

    pSysLog = &gSysLog;

    zlog_fini();
    pSysLog->pZc = NULL;
}

