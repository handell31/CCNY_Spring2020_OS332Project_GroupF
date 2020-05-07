#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main() {
    chdir("Dir0");
    char cwd[PATH_MAX] = {"\0"};
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
    int fd_t2 = open("t2.txt", O_WRONLY);
    if (fd_t2 == -1) {
        printf("\n open() failed with error [%s]\n", strerror(errno));
        return 1;
    } else {
        int i = 0;
        while(*(cwd+i) !='\0') {
            write(fd_t2, (cwd+i), 1);
            i++;
        }
    }
    close(fd_t2);
    if(rename("t2.txt", "path-info.txt") != 0){
        printf("Error in renaming file.\n");
    }
    int fd_tree = open("tree.txt", O_RDONLY);
    int fd_path = open("path-info.txt", O_RDONLY);
    int fd_t3 = open("t3.txt", O_WRONLY);
    if (fd_tree == -1 | fd_path == -1 | fd_t3 == -1) {
        printf("\n open() failed with error [%s]\n", strerror(errno));
        return 1;
    } else {
        // Reads every character of the source files and writes into the destination file
        char content[1];
        while (read(fd_tree, content, 1) != 0) {
            write(fd_t3, content, 1);
        }
        char new_line[1] = {'\n'};
        write(fd_t3, new_line, 1);
        while (read(fd_path, content, 1) != 0) {
            write(fd_t3, content, 1);
        }
    }
    close(fd_tree);
    close(fd_path);
    close(fd_t3);
    if(rename("t3.txt", "log.txt") != 0)
        printf("Error in renaming file.\n");
    if(remove("tree.txt") != 0 | remove("path-info.txt") != 0)
        printf("Error in removing files.\n");

    return 0;
}
