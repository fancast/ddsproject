#include <sys/shm.h> //shared memory operations
#include <sys/ipc.h> //system call operations
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>
#include <iostream>
#include "sharedmemory.cpp"
//#include "emc.cpp"
//#include "rts.cpp"

using namespace std;

int main()
{
	int size = 128;

	printf("\nEmpty constructor:\n");
	Smio rtds_smio_empty;
	rtds_smio_empty.print_results();
	printf("\nSize 128 constructor:\n");
	Smio rtds_smio(size);
	rtds_smio.print_results();

	float signals_array[size];



}