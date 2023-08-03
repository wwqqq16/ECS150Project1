#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

/*
kill -l
 1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL       5) SIGTRAP
 6) SIGABRT      7) SIGBUS       8) SIGFPE       9) SIGKILL     10) SIGUSR1
11) SIGSEGV     12) SIGUSR2     13) SIGPIPE     14) SIGALRM     15) SIGTERM
16) SIGSTKFLT   17) SIGCHLD     18) SIGCONT     19) SIGSTOP     20) SIGTSTP
21) SIGTTIN     22) SIGTTOU     23) SIGURG      24) SIGXCPU     25) SIGXFSZ
26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGIO       30) SIGPWR
31) SIGSYS      34) SIGRTMIN    35) SIGRTMIN+1  36) SIGRTMIN+2  37) SIGRTMIN+3
38) SIGRTMIN+4  39) SIGRTMIN+5  40) SIGRTMIN+6  41) SIGRTMIN+7  42) SIGRTMIN+8
43) SIGRTMIN+9  44) SIGRTMIN+10 45) SIGRTMIN+11 46) SIGRTMIN+12 47) SIGRTMIN+13
48) SIGRTMIN+14 49) SIGRTMIN+15 50) SIGRTMAX-14 51) SIGRTMAX-13 52) SIGRTMAX-12
53) SIGRTMAX-11 54) SIGRTMAX-10 55) SIGRTMAX-9  56) SIGRTMAX-8  57) SIGRTMAX-7
58) SIGRTMAX-6  59) SIGRTMAX-5  60) SIGRTMAX-4  61) SIGRTMAX-3  62) SIGRTMAX-2
63) SIGRTMAX-1  64) SIGRTMAX
*/
char *symbol[] =    {   "SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP",
                        "SIGABRT", "SIGBUS", "SIGFPE", "SIGKILL", "SIGUSR1",
                        "SIGSEGV", "SIGUSR2", "SIGPIPE", "SIGALRM", "SIGTERM",
                        "SIGSTKFLT", "SIGCHLD", "SIGCONT", "SIGSTOP", "SIGTSTP",
                        "SIGTTIN", "SIGTTOU", "SIGURG", "SIGXCPU", "SIGXFSZ",
                        "SIGVTALRM", "SIGPROF", "SIGWINCH", "SIGIO", "SIGPWR",
                        "SIGSYS"
                        /*
                        , "UNKNOWN", "UNKNOWN", "SIGRTMIN", "SIGRTMIN+1", "SIGRTMIN+2", "SIGRTMIN+3",
                        "SIGRTMIN+4",  "SIGRTMIN+5", "SIGRTMIN+6", "SIGRTMIN+7", "SIGRTMIN+8",
                        "SIGRTMIN+9", "SIGRTMIN+10", "SIGRTMIN+11", "SIGRTMIN+12", "SIGRTMIN+13",
                        "SIGRTMIN+14", "SIGRTMIN+15", "SIGRTMAX-14", "SIGRTMAX-13", "SIGRTMAX-12",
                        "SIGRTMAX-11", "SIGRTMAX-10", "SIGRTMAX-9", "SIGRTMAX-8", "SIGRTMAX-7",
                        "SIGRTMAX-6", "SIGRTMAX-5", "SIGRTMAX-4", "SIGRTMAX-3", "SIGRTMAX-2",
                        "SIGRTMAX-1", "SIGRTMAX"
                        */
                    };

void signal_action(int sign)
{
    time_t now;
    char *str_time;

    time(&now); // get time    
    str_time = ctime(&now); // time to string
    str_time[24] = 0; // delete '\n'
    printf("%s Received signal %d (%s)\n", str_time, sign, symbol[sign-1]);
}

int main(int argc, char** argv)
{
    pid_t pid;

    for (int i=1; i<=31; i++) {
        if (i != SIGKILL)
            signal(i, signal_action);
    }
    pid = getpid();
    printf("PID is %d\n", pid);
    while (1); // wait for signals
    return 0;
}