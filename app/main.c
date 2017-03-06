#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "config.h"
#include "iniparser.h"
#include "SysLogPublic.h"

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
    printf("    -l, --log            the log config file name,\n"); 
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
            break;

        case 'l':
            pLogCfgName = malloc(strlen(optarg) + 1);
            strcpy(pLogCfgName, optarg);
            *(pLogCfgName + strlen(optarg) + 1) = '\0';
            break;

        case 'h':
        default:
            PrintUsage(APP_NAME);
            break;
        }
    }

    return 0;
}


int main(int argc, char *argv[])
{
    unsigned cnt;
    
    UsrOptHdl(argc, argv);

    if (pLogCfgName) {
        SysLogInit(pLogCfgName);
    }

    SysFatalTrace("%s initialize successfully", APP_NAME);
    while (1) {
        cnt ++;
        usleep(1000);
        SysDebugTrace("*********  %d **********", cnt);
    }

    return 0;
}

