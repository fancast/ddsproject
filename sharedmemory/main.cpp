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
	float arr[size] = {127, 23, 26, 24, 0, 0};
	//float signals_array[size];
	//printf("\nEmpty constructor:\n");
	//Smio rtds_smio_empty;
	printf("\nSize 128 constructor:\n");
	Smio rtds_smio(size);
	rtds_smio.write_Signals(arr, size);
	rtds_smio.print_Results();
	float* p = rtds_smio.get_Base_Address();
	delete rtds_smio;
	rtds_smio.print_Results();
}