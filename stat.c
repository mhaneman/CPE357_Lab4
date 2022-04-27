#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>


char* filetype(mode_t m) {
        if (S_ISFIFO(m))
            return "FIFO";
        if (S_ISDIR(m))
            return "Directory";
        if (S_ISLNK(m))
            return "Symbolic Link";
        if (S_ISCHR(m))
            return "Character Device";
        if (S_ISBLK(m))
            return "Block Device";
        if (S_ISREG(m))
            return "Regular File";
        
        return "undefined";    
}

void access(mode_t m) {
    printf("Access: ");

    if (S_ISFIFO(m))
        printf("f");
    if (S_ISDIR(m))
        printf("d");
    if (S_ISLNK(m))
        printf("s");
    if (S_ISCHR(m))
        printf("c");
    if (S_ISBLK(m))
        printf("b");
    if (S_ISREG(m))
        printf("-");


    if (m & S_IRUSR)
        printf("r");
    else 
        printf("-");
    if (m & S_IWUSR)
        printf("w");
    else 
        printf("-");

    if (m & S_ISUID) {
        if (m & S_IXUSR) {
            printf("s");
        } else
            printf("S");
    } else if (m & S_IXUSR)
        printf("x");
    else
        printf("-");

    if (m & S_IRGRP)
        printf("r");
    else 
        printf("-");
    if (m & S_IWGRP)
        printf("w");
    else 
        printf("-");
    
    if (m & S_ISGID) {
        if (m & S_IXGRP) {
            printf("s");
        } else
            printf("S");
    } else if (m & S_IXGRP)
        printf("x");
    else
        printf("-");

    if (m & S_IROTH)
        printf("r");
    else 
        printf("-");
    if (m & S_IWOTH)
        printf("w");
    else 
        printf("-");
    if (m & S_IXOTH)
        printf("x");
    else 
        printf("-");
}

int main(int argc, char *argv[]) {
    struct stat file;
    int i;
    for (i = 1; i < argc; i++) {
        if (stat(argv[i], &file) == -1) {
            exit(-1);
        }

        printf("File: %s\n", argv[i]);
        printf("type: %s\n", filetype(file.st_mode));
        printf("Size: %lld\n", file.st_size);
        printf("Inode: %llu\n", file.st_ino);
        printf("Links %d\n", file.st_nlink);
        access(file.st_mode);

    }
    return 0;
}
