/*
 * @Author: machineplay
 * @Date: 2020-02-05 03:04:30
 * @Description: only for fun
 */
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>
#include <sys/utsname.h>
#include <pwd.h>


int main(int argc, char* argv[]) {

    /* init time. */
    tm sys_time;
    timespec sys_timespec;
    tm *sys_tm_ptr = &sys_time;
    time_t time_now = time(NULL);
    char time_buf[255];
    sys_tm_ptr = localtime(&time_now);
    int ret = strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S %Z", sys_tm_ptr);

    if(!ret) {
        printf("get time error\n");
        return -1;
    }

    /* init sys info. */
    utsname sys_info;
    passwd *sys_pwd = nullptr;
    ret = uname(&sys_info);
    if(ret) {
        printf("get uname error\n");
    }

    /* getuid then getpwuid. */
    sys_pwd = getpwuid(getuid());


    /* display system info. */
    printf("______system_info______\t\n");
    printf("* kernel: %s\t\n* machine: %s\t\n* release: %s\t\n* hostname: %s\t\n* system: %s\t\n"
    , sys_info.version, sys_info.machine, sys_info.release, sys_info.nodename, sys_info.sysname);

    /* get username from pwd. */
    printf("* user: %s\t\n", sys_pwd->pw_name);
    printf("* shell: %s\t\n", sys_pwd->pw_shell);
    printf("* home: %s\t\n", sys_pwd->pw_dir);
    printf("* pwd: %s\t\n", sys_pwd->pw_passwd);

    /* time. */
    printf("* time: %s\t\n", time_buf);
    return 0;
}
