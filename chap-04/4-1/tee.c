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
    int fd;
    int opt;
    int flags;
    mode_t file_perms;
    ssize_t num_read, num_written;
    char buf[BUF_SIZE + 1];

    file_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; /* rw-r--r-- */
    flags = O_WRONLY | O_CREAT | O_TRUNC;

    while((opt = getopt(argc, argv, ":a")) != -1)
    {
	switch (opt) {
	    case 'a': 
	    	flags |= O_APPEND;
		flags &= ~O_TRUNC;
	    	break;
	    default:
		usageErr("%s [-a]\n", argv[0]);
	}
    }

    if (optind >= argc) {
	cmdLineErr("Missing filename.\n");
    }

    fd = open(argv[optind], flags, file_perms);
    if (fd == -1)
        errExit("Open file failed.");

    while ((num_read = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
    {
        if (num_read == -1)
            errExit("Read stdin failed.");

        buf[num_read] = '\0';
        
        num_written = write(STDOUT_FILENO, buf, num_read);
        if (num_written == -1)
            errExit("Write stdin failed.");

        num_written = write(fd, buf, num_read);
        if (num_written == -1)
            errExit("Write stdin failed.");
    }

    if (close(fd) == -1)
        errExit("close");

    return 0;
}

