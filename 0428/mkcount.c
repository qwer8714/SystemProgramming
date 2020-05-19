#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BLOCK_SIZE 16
int main() {
    int fd;
    int i;
    char buf[BLOCK_SIZE];
    if ((fd = open("b_counter", O_CREAT|O_WRONLY)) == -1)
    {
        perror("file open error : ");
        exit(0);
    }
    for(i = 1; i < 4; i++)
    {
        memset(buf, 0x00, BLOCK_SIZE);
        sprintf(buf,"%d", i);
        write(fd, buf, BLOCK_SIZE);
    }    
    close(fd);
}
