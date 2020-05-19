/***********************************************************************
* ex_filetype.c                                                        *
* example source – about struct FILE                                   *
***********************************************************************/
 
#include <stdio.h>
#include <unistd.h>
 
void print_fileinfo(FILE *fp);
int main()
{
	FILE *fp;
	fp = fopen("./ex_filetype.c", "r");
    getchar();
    print_fileinfo(stdin); 
    getchar();
    print_fileinfo(stdout); 
    getchar();
    print_fileinfo(stderr); 
    getchar();
    print_fileinfo(fp);
	fclose(fp);
    return 0;
}
void print_fileinfo(FILE *fp)
{
    printf("===========================================\n");
    printf("_fileno: %d\n", fp->_fileno);
	//printf("_cnt: %d\n", fp->cnt);
    printf("_flags: %#x\n", fp->_flags);
	int dcnt = (fp->_IO_read_end - fp->_IO_read_ptr);
    printf("data count:%d\n",dcnt);
    printf("_IO_read_base:%s\n", fp->_IO_read_base);
    printf("_IO_read_ptr:%s\n", fp->_IO_read_ptr);
}
