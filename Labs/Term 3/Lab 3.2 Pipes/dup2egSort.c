/* Title: dup2eg.c
 * Description: ENCE360 Example code - dup2.
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) {

    int fd;

    /* Open my.file */
    if ((fd = open("mySort.file", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1) {
        perror("Couldn't open my.file");
        exit(1);
    }

    /* Redirect stdout to my.file */
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("Could not redirect stdout");
        exit(2);
    }

    /* Replace the current process with "ls -l" */
    // execl("/bin/ls", "ls", "-l", NULL);
    execl("/bin/sort", "sort","-n","+4", NULL);
    /* If we reach this line, execl must have failed */
    perror("Exec failed");
    exit(3);
}
