#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char** argv)
{
    int input_fd, output_fd;
    int opt;
    ssize_t num_read, num_written;
    char buf[BUF_SIZE + 1];
    
    if (argc != 3)
        cmdLineErr("Missing filename.");

    input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1)
        errExit("Open input file failed.");
        
    output_fd = open(argv[2],
                     O_WRONLY | O_CREAT | O_TRUNC,
                     S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); /* rw-r--r-- */  
    if (output_fd == -1)
        errExit("Open output file failed.");
                     
    while ((num_read = read(input_fd, buf, BUF_SIZE)) > 0)
    {
        if (num_read == -1)
            errExit("Read file failed.");
            
        buf[num_read] = '\0';
        
        int zero_count = 0;
        int nonzero_count = 0;
        char *p = buf;
        for (int i = 0; i < num_read; i++)
        {
            if (buf[i] == '\0')
            {
            	if (nonzero_count)
            	{
            	    if(write(output_fd, p, nonzero_count) == -1)
                        errExit("Write file failed.");
                    p += nonzero_count;
                }        
            	p++;
            	nonzero_count = 0;
                zero_count++;
            }
            else
            {
            	if (zero_count)
            	    if (lseek(output_fd, zero_count, SEEK_CUR) == -1)
                        errExit("lseek");
                zero_count = 0;        
            	nonzero_count++;
            }
        }
        if (zero_count && lseek(output_fd, zero_count, SEEK_CUR) == -1)
            errExit("lseek");
        if(nonzero_count && write(output_fd, p, nonzero_count) == -1)
            errExit("Write file failed.");   
    }

    if (close(input_fd) == -1)
        errExit("close");
    if (close(output_fd) == -1)
        errExit("close");
    return 0;
}

