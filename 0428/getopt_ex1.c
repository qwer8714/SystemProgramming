#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void help();
void version();
int main(int argc, char **argv) { 
    int opt;
    int port_num;
    int fp;
    int opt_ok;
    char file_name[16];
    char buf[256];

    while((opt = getopt(argc, argv, "hvf:")) != -1) {
        switch(opt) { 
            case 'h':
                help(); 
                break; 
            case 'v':
                version(); 
                break;
            case 'f':
                memcpy(file_name, optarg, 16);
                opt_ok = 1;
                break;
        }
    } 
    if (opt_ok != 1) { 
        help();
        exit(0);
    } 

    if (access(file_name, R_OK) != 0) {
        printf("파일이 존재하지 않습니다");
        exit(0);
    }
    if((fp = open(file_name, O_RDONLY)) == -1) {
        printf("file open error");
        exit(0);
    }

    memset(buf, '\0', 256);
    while(read(fp, buf, 256) > 0) {
        printf("%s", buf);
        memset(buf, '\0', 256);
    }
}

void help() {
    printf("Usage: ./testopt [OPTION] [FILE]\n"
           "  -h                도움말\n"
           "  -f [FILE]         파일출력\n"
           "  -v                버전출력\n");
    exit(0);
}

void version() {
    printf("Version : 1.01\n");
    exit(0);
}
