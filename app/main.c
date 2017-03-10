#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "config.h"
#include "iniparser.h"
#include "SysLogPublic.h"
#include "osal.h"

#define LOGCFG_NAME_DEFAULT     "/opt/basic-platform/configs/log.conf"

static char *pLogCfgName = LOGCFG_NAME_DEFAULT; /* log config file name */


/**
 * @val short_opts
 * This is short option string, and the : after d
 * means option d should have value like d=xxx.
 */
static const char short_opts[] = "Vvhl:";

/**
 * @val lng_opts
 * This is for long options, and the last one
 * in the array must be all ZERO.
 */
static const struct option lng_opts[] = {
    {"Version", no_argument, NULL, 'V'},
    {"version", no_argument, NULL, 'v'},
    {"help", no_argument, NULL, 'h'},
    {"log", required_argument, NULL, 'l'},
    {NULL, 0, NULL, 0}
};
extern char *optarg;

void PrintVersion(const char *program_name)
{
    printf("%s Version %d.%d.%d Build on %s %s\n",
            program_name, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH,
            __DATE__, __TIME__);
}

void PrintUsage(const char *program_name) {  
    PrintVersion(program_name);  
    printf("This is a program\n");
    printf("    --version             show program's version number and exit\n");  
    printf("    -h, --help            show this help message and exit\n");
    printf("    -l, --log             the log config file name\n"); 
}

/**
 * @func int GetUsrOpt(int argc, char *argv[])
 * get user setted options from command line.
 * @param argc number of user options, the same as main.
 * @param argv user input string, the sameas main.
 * @return
 * 0 set as user option.
 * -1 argv is NULL.
 * -2 no user options at all.
 * -3 unknown user option.
 */
int UsrOptHdl(int argc, char *argv[])
{
     int idx = 0;
     int opt = 0;
    if (NULL == argv)
        return -1;
#if 0
    if (argc < 2) {
        /* no user option, give default */
        PrintUsage(APP_NAME);
        return -2;
    }
#endif
    while (1) {
        opt = getopt_long(argc, argv, short_opts, lng_opts, &idx);
        /* get the last */
        if (-1 == opt) {
            break;
        }

        switch (opt) {
        case 'V':
        case 'v':
            PrintVersion(APP_NAME); 
            exit(0);
            break;

        case 'l':
            pLogCfgName = malloc(strlen(optarg) + 1);
            strcpy(pLogCfgName, optarg);
            *(pLogCfgName + strlen(optarg) + 1) = '\0';
            break;

        case 'h':
        default:
            PrintUsage(APP_NAME);
            exit(0);
            break;
        }
    }

    return 0;
}

static unsigned int glob = 0;
static osal_thread_mutex_t *lock;

static void *thread(void *arg)
{
    unsigned int loops = 10000000;
    unsigned int loc;
    unsigned int j;
    int ret;
    
    for (j = 0; j < loops; j++) {
        ret = osal_thread_mutex_lock(lock);
        if (ret != 0) {
            SysErrorTrace("osal_thread_mutex_lock failed %d", ret);
        }
        
        loc = glob;
        loc++;
        glob = loc;
        
        ret = osal_thread_mutex_unlock(lock);
        if (ret != 0) {
            SysErrorTrace("osal_thread_mutex_unlock failed %d", ret);
        }
    }

    SysDebugTrace("Thread %d: glob=%d", (int)arg, glob);

    return  NULL;
}

int main(int argc, char *argv[])
{
    int ret;
    int cnt;
    
    UsrOptHdl(argc, argv);

    if (pLogCfgName) {
        SysLogInit(pLogCfgName);
    }

    lock = osal_thread_mutex_create();
    if ( lock == NULL) {
        SysErrorTrace("osal_thread_mutex_create fail");
    }

    for(cnt = 0; cnt < 10; cnt++) {
        ret = osal_thread_create(OSAL_SCHED_OTHER, 0, 0, thread, (void *)(cnt + 1));
        if (ret == 0) {
            SysFatalTrace("osal_thread_create %d successfully", cnt);
        }
    }

    while (1) {
        osal_thread_sleep(15);
        SysDebugTrace("******** main thread *********");
    }

    return 0;
}

