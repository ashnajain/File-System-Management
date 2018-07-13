/*
 * File: fileSystem.h
 * Description: The File System (FS), fileSystem.c simulates
 *		a file system with a file, i.e. a "fisk", as disk and separate
 *		blocks of the file as "disk files". This file system is based on
 *		the older Unix File System consisting of superblock, inode, data,
 *		boot, and swap spaces. The fileSyste.h API is also used by the test harness
 *		main.c and the interactive shell main.c. For their uses, please
 *		refer to the README file.
 * Simplifying assumptions:
 *		-memory leaks not tested
 *		-boot and swap space not implemented
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

/* defines */
#define OCCUPIED 1
#define FREE 0
#define DIRECTORY 1
#define FILE 0
#define EFFS_ROOT_CHECKSUM 1337
#define INODE_SIZE 18
#define MAX_FILECOUNT 48

// interface functions
int fs_initialize(int numblocks);
int fs_create(char* name, int flag, int filesize,char* oldDir);
int fs_delete(char* filename);
int fs_open(char* filename);
int fs_write(int inode_index, void *file_content, int filesize);
int fs_read(char* filename, void *file_content, int filesize);
int fs_sync(int fildes);
int fs_close(int fildes);

// additional functions 
int create_file(int filesize, char* filename,char* oldDir);
int create_dir(char* dirname);
void print_curr_dir();
void change_dir(char* dirname);
int get_curr_dir();


