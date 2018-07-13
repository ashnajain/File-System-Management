/*
 * File: disk.c
 * Description: The disk.c API simulates hard disk drivers used by the File System (FS), fielSystem.c.
 * Coders: Ashna Jain, Janvi Patel
*/

#include "disk.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BLOCK_SIZE 1024		//defining the block size 1024

//global variable declaration
static int fd;

/* opens the "disk" for reading/writing */
int openDisk(char *filename, int nbytes)
{	
	// opens the disk; if it does not exist, a new one is created
	fd = open(filename, O_RDWR | O_CREAT, (mode_t)0600);
	if (fd == -1) {
		perror("Error encountered while opening the DISKFILE for writing...!!!");
        return -1;
    	}
	
    	// ensures the file is of size nbytes 
	lseek(fd, nbytes-1, SEEK_SET);
	write(fd, "\0", 1);
	
	// returns the file descriptor
	return fd;
}

/* writes the contents of a single block from the buffer *block into the fisk block disk specified by the blocknr */
int writeBlock(int disk, int blocknr, void *block)
{
	int result;		//declaring variable result as integer
	
	// sets the file pointer to position specified by blocknr
	result = lseek(disk, blocknr*BLOCK_SIZE, SEEK_SET);
	
	if(result == -1){
		perror("Error calling lseek() to set starting position in writing");
	}
	
	// writes the contents of the block buffer into the "disk" block	
	result = write(disk, block, BLOCK_SIZE);
	
	if(result == -1){
		perror("Error encountered while writing to the DISKFILE ....!!!");
	}
	
	return 0;
}

/* reads the block specified by blocknr and places the contents into the buffer block */
int readBlock(int disk, int blocknr, void *block)
{
	int result;		//declaring variable result as integer
	
	// sets the file pointer to position specified by blocknr
	result = lseek(disk, blocknr*BLOCK_SIZE, SEEK_SET);
	
	if(result == -1) {
		perror("Error calling lseek() to set starting position in reading");
	}
	
	// obtains the contents of the block and places it in the block buffer
	result = read(disk, block, BLOCK_SIZE);
	
	if(result == -1) {
		perror("Error encountered while reading from the DISKFILE ....!!!");
	}
	
	return 0;
}

/* closes the "disk" */
int closeDisk()
{
	int result;		//declaring variable result as integer
	result = close(fd);
	
	if (result == -1) {
		perror("Error encountered while closing the DISKFILE ....!!!");
		return -1;
	}
	
	return 0;
}

/* forces any outstanding writes to the "disk" immediately */
void syncDisk()
{
	int result;		//declaring variable result as integer
	
	// syncs the "disk"
	result = fsync(fd);
       
	if(result == -1){
		perror("Error encountered while synchronizing to the DISKFILE ....!!!");
	}
}
