#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int fd_lock(int fd);
int fd_open(int fd);
int fd_isopen(int fd);
int fd_unlock(int fd);

int main()
{
    int fd;
    int n_read;
    char buf[11];
    char wbuf[11];

    fd = open("counter.txt", O_CREAT|O_RDWR); 
    if (fd == -1)
    {
        perror("file open error : ");
        exit(0);
    }
    if (fd_isopen(fd) == -1)
    {
        perror("file is lock "); 
        exit(0);
    }
    printf("I get file lock\n");

    memset(buf, 0x00, 11);
    memset(wbuf, 0x00, 11);
    if ((n_read = read(fd, buf, 11)) > 0)
    {
        printf("%s\n", buf); 
    }

    // 처음위치로 되돌린다. 
    lseek(fd, 0, SEEK_SET);
    sprintf(wbuf, "%d", atoi(buf) + 1);
    write(fd, wbuf, 11);
    
    // 숫자외의 필요없는 부분을 자른다.  
    ftruncate(fd, strlen(wbuf)); 
    // 10 초를 쉰다. 
    sleep(10);

    // 파일잠김을 푼다. 
    if (fd_unlock(fd) == -1)
    {
        perror("file unlock error ");
    }
    printf("file unlock success\n");
    sleep(5);

    close(fd);
}

// 파일이 잠겨있는지 확인하고 잠겨 있지 않으면
// 잠금을 얻고 
// 잠겨 있을경우 잠김이 풀릴때까지 기다린다(F_SETLKW) 
int fd_isopen(int fd)
{
    struct flock lock;

    lock.l_type = F_WRLCK; 
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;

    return fcntl(fd, F_SETLKW, &lock);
}

// 파일 잠금을 얻은후 모든 작업이 끝난다면 
// 파일 잠금을 돌려준다. 
int fd_unlock(int fd)
{
    struct flock lock;

    lock.l_type = F_UNLCK; 
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;

    return fcntl(fd, F_SETLK, &lock);
}
