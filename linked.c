#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char** argv)
{
    struct stat st1, st2;

    if (argc < 3) {
        printf("Usage: %s file1 file2\n", argv[0]);
        return 1;
    }
    if (lstat(argv[1], &st1)) {
        perror(argv[1]);
        return 1;
    }
    if (lstat(argv[2], &st2)) {
        perror(argv[2]);
        return 1;
    }

    if (S_ISLNK(st1.st_mode)) {
        if (stat(argv[1], &st1)) {
            perror(argv[1]);
            return 1;
        }
        if (S_ISLNK(st2.st_mode)) {
            if (stat(argv[2], &st2)) {
                perror(argv[2]);
                return 1;
            }
        } else {
            if (st1.st_ino == st2.st_ino)
                printf("These files are linked.\n");
            else
                printf("The files are not linked.\n");
            return 0;
        }
    } else {
        if (S_ISLNK(st2.st_mode)) {
            if (stat(argv[2], &st2)) {
                perror(argv[2]);
                return 1;
            }
            if (st1.st_ino == st2.st_ino)
                printf("%s is a symbolic link to %s\n",argv[2],argv[1]);
            else
                printf("The files are not linked.\n");
            return 0;
        }
    }
    if (st1.st_ino == st2.st_ino)
        printf("These files are linked.\n");
    else
        printf("The files are not linked.\n");
    return 0;
}