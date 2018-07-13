#
# File: Makefile.mk
# Description: This file is for compling the code
# Coders: Ashna Jain,Janvi Patel
#

main: fileSystem.o disk.o main.o
	gcc -g -Wall fileSystem.o disk.o main.o -o main


main.o:main.c
	gcc -c -g -Wall main.c


fileSystem.o: fileSystem.c
	gcc -c -g -Wall fileSystem.c

disk.o: disk.c
	gcc -c -g -Wall disk.c


