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

struct utsname uname_info;
char *username, *shellname;

static char *name()
{
    username = getlogin();
    printf("%sUser:%s%s\n",MAGENTA,CYAN,username);
    return 0;
}

static char *os()
{
    struct utsname uname_info;
    if (uname(&uname_info))
        exit(-1);
    printf("%sOS:%s%s\n", MAGENTA, CYAN, uname_info.sysname);
    return 0;
}

static char *kernel()
{
    struct utsname uname_info;
    if (uname(&uname_info))
        exit(-1);
    printf("%sKernel:%s%s\n", MAGENTA, CYAN, uname_info.release);
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

int main()
{
    name();
    os();
    kernel();
    shell();
    uptime();
    return 0;
}