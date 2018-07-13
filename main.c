/*
 * File: main.c
 * Description: The main.c gives the initialization of
 * 		the file system, the creation of files and directories, writing
 * 		and reading to files, removing files and directories, and
 *		persistence.
 *
 * Simplifying Assumptions:
 *
 *	INITIALIZATION:
 *		We have only one disk of a predetermined size DISK_SIZE.
 *		We cover two cases for a disk initialization:
 *			1. Disk does not exists and is created of size
 *				DISK_SIZE*1024 Bytes.
 *			2. Disk already exists and is of size DISK_SIZE*1024
 *				Bytes.
 *
 *	DIRECTORIES
 *		Directories are a dixed size of 1 block (1024 Bytes).
 *		Directories can have at most 48 files contained within
 *		 them (48 sub-directories and "." and "..")
 * Coders: Ashna Jain, Janvi Patel
 */

#include "fileSystem.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 10000
#define CHAR_BUFFER_SIZE 10000
#define INT_BUFFER_SIZE 2500
#define DISK_SIZE 1000

/* Global Static variable */
static int errors;
int fmain;
int fildes;
char data[150],ch;
static int length=0;

/* Function Prototypes */
int stringLength(char *str);
int create_fd(char* test, char* fname, int flag, int filesize,char* oldDir);
int open_fd(char* test, char* fname);
int remove_fd(char* test, char* fname);

// Function to major String Length
int stringLength(char *str)
{
	if(*str!=NULL)
	{
		length++;
		stringLength(++str);
	}
	else
	{
		return length;
	}
}

// Function to create files & directories
int create_fd(char* test, char* fname, int flag, int filesize,char* oldDir)
{
	if (flag==FILE)
	{
		if(fs_create(fname, FILE, filesize,oldDir) == 0 )	//calling fs_create from fileSystem.c file
			fprintf(stdout, "%s Created\n", test);
		else
		{
			fprintf(stderr, "%s Error\n", test);
			++errors;
			return -1;
		}
	}
	else
	{
		if(fs_create(fname, DIRECTORY, filesize,oldDir) == 0 )	//calling fs_create from fileSystem.c file
			fprintf(stdout, "%s Created\n", test);
		else
		{
			fprintf(stderr, "%s Error\n", test);
			++errors;
			return -1;
		}
	}
	return 0;
}

// Function to open files & directories
int open_fd(char* test, char* fname)
{
	int fd;		//declaring variable fd as integer

	fd = fs_open(fname);

	if ( fd != 0 )
		fprintf(stdout, "%s Opened Successfully...\n", test);
	else
	{
		fprintf(stderr, "%s Error in opening...!!!\n", test);
		++errors;
		return -1;
	}
	return fd;
}

// Function to remove files & directories
int remove_fd(char* test, char* fname)
{
	fprintf(stdout, "%s removing file %s\n", test, fname);
	if ( fs_delete(fname) == -1 )
	{
		fprintf(stderr, "%s--\t Error in removing...!!!\n", test);
		++errors;
		return -1;
	} else {
		fprintf(stdout, "%s--\t Removed Successfully...\n", test);
	}
	return 0;
}

//Main function
int main(int argc, char* argv[])
{
	// Declaring the variables
	int size=0;
	int u=0;
	int i=0;
	int flag=0;
	int Choice=0;
	int* i_buffer;
	char c;
	char newName[10],username[10],password[10],newName1[10],store[10];
	char result[5] ;
	char delims[] = " ";
	char dirName[10];
	char oldDir[10];
	char* c_buffer;
	char* newName_buffer;
	char* newName_buffer1;
	char* test;
	char *user[] = {"Ashna","Janvi"};
	char *pass[] = {"123","456"};
	void* buffer;
	
	errors = 0;

	//Access control & Login to the particular user
	printf("\n\t***** LOGIN *****\n");
	printf("\n\tUSERNAME:");
	scanf("%s",username);
	printf("\n\tPASSWORD:");
	scanf("%s",password);
	for(i=0;i<2;i++)
	{
		if((strcmp(user[i],username)==0)  && (strcmp(pass[i],password)==0))
		{
			flag=1;
			printf("\n\t*****WELCOME TO THE FILE MANAGEMENT SYSTEM *****\n");
		}
	}
	if(flag==0)
	{
		printf("Invalid username or password....!!!\n");
		return 0;
	}

	// Initialize test buffer used for testing
	buffer = (void*)malloc(BUFFER_SIZE);
	c_buffer = (char*)buffer;
	i_buffer = (int*)buffer;

	for (i = 0; i < CHAR_BUFFER_SIZE; ++i)
		c_buffer[i] = '\0';

	/****************************************************************/
	/** Test Part 1: test initialize disk of size DISK_SIZE blocks **/
	/****************************************************************/
	fprintf(stdout, "\n\tInitialize disk of size %i Bytes\n",DISK_SIZE*1024);

	// Test 1a: Test initialize disk of size 10000 blocks
	size = DISK_SIZE*1024;
	if ( fs_initialize(size) == 0 )
		fprintf(stdout, "\tInitialize disk of size 10000 blocks--\t Successfully done!!!\n");
	else
		fprintf(stderr, "\tInitialize disk of size 10000 blocks--\t **Failed**\n");
	
	while(1)
	    {
	    printf("\n\n\t******* MENU FOR THE FILE SYSTEM *******");
	    printf("\n\n\t1.mkdir \t(Create New Directory)\n\t2.touch \t(Create New file)\n\t3.pwd   \t(Display the current path)\n\t4.vi    \t(Enter the data into file)\n\t5.cat   \t(Display the data from file)\n\t6.Update\t(Update the content of file)\n\t7.ls    \t(List the directories & files)\n\t8.Copy   \t(Create copy of the file)\n\t9.file  \t(Shows the type of file) \n\t10.rename\t(Rename the file & directory) \n\t11.remove \t(Delete the file)\n\t12.Tree   \t(Display the struture of the disk) \n\t0.Exit\n\n");
	    printf("\nEnter Your Choice : ");
	    scanf("%d",&Choice);

	    switch(Choice)
	    {
		case 1: //Creating New directory
			printf("\n*** Format: mkdir 'directory name' ***\n");
	    		scanf("%s \t %s",&result,&dirName);
			if (strcmp(result, "mkdir") == 0) 
			{
					if (fs_create(dirName, DIRECTORY, 0, dirName) == -1 )	//calling fs_create from fileSystem.c file
					{
						printf("\nPlease enter different name of directory...!!!");
						break;
					}	
					else
					{
						printf("\nDirectory %s created successfully...",dirName);
						printf("\nTask Completed!!!");
						++errors;
					}
			}
			else
			{
				printf("Invalid Format !!! Please try again...");
			}
		break;

		case 2:	//Creating New file
			printf("\n*** Format: touch 'File name' ***\n");
		    	scanf("%s \t %s",&result,&newName);
			if (strcmp(result, "touch") == 0) 
			{
				 printf("\nEnter the directory in which you want to create file:");
				 scanf("%s", oldDir);
				 newName_buffer= newName;
				 if (fs_create(newName_buffer, FILE, 0,oldDir) == -1 )		//calling fs_create from fileSystem.c file
				 {
					fprintf(stdout, "%s File already exists\n", test);
					break;
				 }
				 else
				 {
					size = 0;
					printf("\nNew File %s of size %d bytes created successfully \n",newName_buffer,size);
				 }
			 }
			 else
			 {
				 printf("Invalid Format !!! Please try again");
			 }
		break;
		case 3: //giving the path of current directory
			printf("\n*** Format: pwd ***\n");
			scanf("%s",&result);
			if (strcmp(result, "pwd") == 0) 
			{
				fmain = open_fd("test",newName);
				printf("%i",fmain);
				get_curr_dir(newName,fmain);	//calling the function get_curr_dir from fileSystem.c
			}
			else
			{
				printf("Invalid Format !!! Please try again");
			}
		break;
		case 4: //Inserting data to the file
		         printf("\n*** Format: vi 'File name' ***\n");
	    	         scanf("%s \t %s",&result,&newName);
		         if (strcmp(result, "vi") == 0) 
		         {
				   newName_buffer=newName;
				   size = 11;

				   //Entering data
				   printf("ENTER THE DATA:");
				   for (i = 0; i < size; i++){
					scanf("%c",&c);
					c_buffer[i] = c;
				   }
				     
				   fmain = open_fd("test",newName_buffer);
			     	   if (fmain > 0)
				   {

					fprintf(stdout, "Writing to file desc. inode[%i] %i Bytes\n", fmain, size);
					if (fs_write(fmain, buffer, size) == 0 )//calling fs_write from fileSystem.c file				
							fprintf(stdout, "%s Data successfully written in the file\n", test);
					else
					{
							fprintf(stderr, "%s **Failed to write data in the file**!!!\n", test);
							++errors;
							return -1;
					}
				  }
			 }
			 else
			 {
					printf("Invalid Format !!! Please try again");
			 }

	 	break;
		case 5:	//display the content of the file
			printf("\n*** Format: cat 'File name'***\n");
		    	scanf("%s \t %s",&result,&newName);
			if (strcmp(result, "cat") == 0) 
			{
			    	newName_buffer = newName;
			 	fmain = open_fd("test", newName_buffer);
				size=11;
				fprintf(stdout, "Reading from file desc. inode[%i] %i Bytes\n", fmain, size);
	
				if ( fs_read(newName_buffer, buffer, size) == 0 )//calling fs_read from fileSystem.c file
				{
					fprintf(stdout, "%s Data successfully read from the file\n", test);
				}
				else
				{
					fprintf(stderr, "%s **Failed to read data from the file**!!!\n", test);
					++errors;
					return -1;
				}
			}
			else
			{
				printf("Invalid Format !!! Please try again");
			}
		break;
		case 6: //Update the file content
			printf("\n*** Format: update 'File name' ***\n");
			scanf("%s \t %s",&result,&newName);
			if (strcmp(result, "update") == 0) 
			{
				printf("\nEnter the directory:");
			    	scanf("%s", oldDir);
				fmain = open_fd("test",newName);
				if(fmain>0)
					remove_fd(test, newName);
				printf("Input the Data:");
				size = 11;
			   	for (i = 0; i < size; i++)
			  	{
					scanf("%c",&c);
					c_buffer[i] = c;
			   	}
				newName_buffer= newName;
				if (fs_create(newName_buffer, FILE, 0,oldDir) != -1 )
				{
					size = 0;
					printf("Updating file",newName_buffer,size);
				}
				fmain = open_fd("test",newName_buffer);
			     	if (fmain > 0)
				{

					fprintf(stdout, "writing to file desc. inode[%i] %i Bytes\n", fmain, size);
					if (fs_write(fmain, buffer, size) == 0 );
					else
					{
						fprintf(stderr, "%s **Failed**\n", test);
						++errors;
						return -1;
					}
				}
				printf(" Replacement did successfully..!! \n");
				}
			else
			{
				printf("Invalid Format !!! Please try again");
			}
		break;
		case 7:	//ls
			printf("\n*** Format: ls ***\n");
		    	scanf("%s",&result);
			if (strcmp(result, "ls") == 0) 
			{
				print_curr_dir();	//calling the function print_curr_dir from fileSystem.c
			}
			else
			{
				printf("Invalid Format !!! Please try again");
			}
		break;
		case 8: //copy
			printf("\n*** Format: copy 'filename' 'Name of other file'***\n");
			scanf("%s %s %s",&result,&newName,&newName1);
			if (strcmp(result, "copy") == 0) 
			{
				printf("\nEnter the directory:");
			    	scanf("%s", oldDir);
				newName_buffer = newName;
				newName_buffer1 = newName1;
				printf("The content of the file :\n");
				if (fs_read(newName_buffer, buffer, size) == 0 )
				{
					fprintf(stdout, "%s Passed\n", test);
				}
				else
				{
					fprintf(stderr, "%s **Failed**\n", test);
					++errors;
					return -1;
				}
			 	fs_create(newName_buffer1, FILE, 0,oldDir);
				fmain = open_fd("test",newName1);
		     		if (fmain > 0)
				{

					fprintf(stdout, "Test 4b: test writing to file desc. inode[%i] %i Bytes\n", fmain, size);
					if ( fs_write(fmain, buffer, size) == 0 )
						fprintf(stdout, "%s Passed\n", test);
					else
					{
						fprintf(stderr, "%s **Failed**\n", test);
						return -1;
					}
		
				}
			}
			else
			{
				printf("Invalid Format !!! Please try again");
			}
		break;
		case 9: //file
			 printf("\nEnter the name of the file: ");
			 scanf("%s", newName);
			 printf("%s",newName);
			 for(i=0;i<10;i++)
			 {
			    if(newName[i] == '.')
				{
				    break;
				}
			 }
		         strncpy(store, newName+i,10);
		         if(strcmp(store,".sh")==0)
			 {
			    printf(" :ASCII text\n");
			 }
		         else if(strcmp(store,".txt")==0)
			 {
			    printf(" :ASCII text\n");
			 }
		         else if(strcmp(store,".c")==0)
			 {
			    printf(" :C source, ASCII text\n");
			 }
		         else if(strcmp(store,".tex")==0)
			 {
			    printf(" :LaTeX 2e document, ASCII text\n");
			 }
    		break;
		case 10: // rename the file name
			printf("\n***Format: rename 'File name'***\n");
			scanf("%s \t %s",&result,&newName);
			if (strcmp(result, "rename") == 0) 
			{
				printf("\nEnter the directory:");
			    	scanf("%s", oldDir);
				printf("\nEnter the new name for file: ");
			    	scanf("%s", newName1);
				newName_buffer = newName;
				newName_buffer1 = newName1;
				size=11;
				if (fs_read(newName_buffer, buffer, size) == 0 )//calling the function fs_read
				{
					fprintf(stdout, "%s Renamed successfully\n", test);
				}
				else
				{
					fprintf(stderr, "%s **Failed to rename**\n", test);
					++errors;
					return -1;
				}
		
				remove_fd(test, newName);	//calling the function remove_fd
				size=0;
				fs_create(newName_buffer1, FILE, 0,oldDir); //calling the function fs_create
				size=11;
				fmain = open_fd("test", newName_buffer1);
				fs_write(fmain, buffer, size);	//calling the function fs_write
			}
			else
			{
				printf("Invalid Format !!! Please try again");
			}
		break;
			
		case 11: //remove the file
			printf("\n*** Format: remove 'File name'***\n");
		    	scanf("%s \t %s",&result,&newName);
			if (strcmp(result, "remove") == 0) 
			{
				test = "removing file";
				remove_fd(test, newName);
			}
			else
			{
				printf("Invalid Format !!! Please try again");
			}
		break;
		case 12: //Make a tree
			printf("\n*** Format: Tree ***\n");
			scanf("%s ",&result);
			if (strcmp(result,"Tree") == 0) 
			{
				tree();	//calling tree function from file fileSystem.c
			}
			else
			{
				printf("Invalid Format !!! Please try again");
			}
		break;
	case 0:
            return;
     }
}
	return 0;
}
