#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include<sys/sysinfo.h>
#include<sys/utsname.h>
#include<pwd.h>
#include<string.h>

//Colors
#define MAGENTA "\033[1;35m" 
#define CYAN "\033[1;36m"

struct utsname unameinfo;
char *username, *shellname;

static char *name()
{
    username = getlogin();
    printf("%sUser:%s%s\n",MAGENTA,CYAN,username);
    return 0;
}

static char *os()
{
    struct utsname unameinfo;
    if (uname(&unameinfo))
        exit(-1);
    printf("%sOS:%s%s\n", MAGENTA, CYAN, unameinfo.sysname);
    return 0;
}

static char *machine()
{
    struct utsname unameinfo;
    if (uname(&unameinfo))
        exit(-1);
    printf("%sArchitecture:%s%s\n", MAGENTA, CYAN, unameinfo.machine);
    return 0;
}

static char *kernel()
{
    struct utsname unameinfo;
    if (uname(&unameinfo))
        exit(-1);
    printf("%sKernel:%s%s\n", MAGENTA, CYAN, unameinfo.release);
    return 0;
}

static char *shell()
{
    shellname = getpwuid(geteuid())->pw_shell;
    printf("%sShell:%s%s\n", MAGENTA, CYAN, shellname);
    return 0;
}

static void uptime()
{
    double uptime;
    FILE *file = fopen("/proc/uptime", "r");
    if (file == NULL)
        return;

    fscanf(file, "%lf", &uptime);
    fclose(file);

    int days = (int)(uptime / 86400);
    int hours = (int)((uptime - days * 86400) / 3600);
    int mins = (int)((uptime - days * 86400 - hours * 3600)/60);
    if(days <= 1)
    {
        if(hours <= 1)
        {
            if(mins == 1){
            printf("%sUptime:%s %d Day, %d Hour, %d Min\n", MAGENTA, CYAN, days, hours, mins);
            }
            else
            printf("%sUptime:%s %d Day, %d Hour, %d Mins\n", MAGENTA, CYAN, days, hours, mins);
        }
        printf("%sUptime:%s %d Day, %d Hours, %d Mins\n", MAGENTA, CYAN, days, hours, mins);
    }
    else
        printf("%sUptime:%s %d Days, %d Hours, %d Mins\n", MAGENTA, CYAN, days, hours, mins);
}

size_t ramUsage()
{
    struct sysinfo meminfo;

    if (sysinfo(&meminfo))
        exit(-1);

    double totalRam = (double)meminfo.totalram / (1024 * 1024 * 1024);
    double freeRam = (double)meminfo.freeram / (1024 * 1024 * 1024);
    double usedRam = totalRam - freeRam;

    printf("%sRam used:%s %.2f GB / %.2f GB\n", MAGENTA, CYAN, usedRam, totalRam);

    return 0;
}

static char *process()
{
    struct sysinfo meminfo;

    if (sysinfo(&meminfo))
        exit(-1);

    unsigned short processes = meminfo.procs;
    printf("%sProcesses Running:%s%d\n", MAGENTA, CYAN, processes);
    return 0;
}

int main()
{
    name();
    os();
    machine();
    kernel();
    ramUsage();
    process();
    shell();
    uptime();

    return 0;
}