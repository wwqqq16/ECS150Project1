#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int isAllNum(char *str)
{
    int i=0;
    char c;

    while ((c = str[i]) != '\0') {
        if (c < '0' || c > '9')
            return 0;
        i++;
    }
    return 1;
}
    
int hasSlash(char *str)
{
    int i=0;
    char c;

    while ((c = str[i]) != '\0') {
        if (c == '/')
            return 1;
        i++;
    }
    return 0;
}

void getFullname(char *filename, char *command)
{
    char *path;
    char *token;

    if (hasSlash(filename) == 0) {  // filename without '/'
        path = getenv("PATH");      // get $PATH from env

        token = strtok(path, ":");  // split path with ':'
        while (token != NULL) {
            strcpy(command, token);
            strcat(command, "/");
            strcat(command, filename);
            if (access(command, F_OK) == 0) // filename with full path exist
                return;
            token = strtok(NULL, ":");
        }
    }
    strcpy(command, filename);
    return;
}
    
int main(int argc, char** argv)
{
    pid_t pid;
    int sec;
    char command[1024];
    char **args;
    char *envp[]={NULL};
    int i;
    
    if (argc < 3) {
        printf("Usage: timeout sec command [args ...]\n");
        exit(EXIT_FAILURE);
    }

    if (isAllNum(argv[1]))
        sec = atoi(argv[1]);
    else {
        printf("%s is not a positive integer\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    getFullname(argv[2], command);

    args = (char**)calloc(argc-1, sizeof(char*));
    for (i=2; i<argc; i++) {
        args[i-2] = argv[i];
    }
    args[i-2] = NULL;

    pid = fork();

    if (pid < 0) {
        perror("fork");   
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (execve(command, args, envp) < 0) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else {
        while (waitpid(pid, NULL, WNOHANG) == 0) {
            if (sec > 0) {
                sleep(1);
                sec --;
            } else
                kill(pid, SIGTERM);
        }
    }
    free(args);
    exit(EXIT_SUCCESS);
}