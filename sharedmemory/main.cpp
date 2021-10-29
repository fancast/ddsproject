#include <sys/shm.h> //shared memory operations
#include <sys/ipc.h> //system call operations
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>
#include <iostream>
#include "emc.cpp"
//#include "rts.cpp"

using namespace std;

int main()
{
	int size = 128;
	float arr[size] = {127.234, 23.06, 26, 24.97, 0, 0};
	printf("\nSize 128 constructor:\n");
	Smio rtds_smio(size);
	rtds_smio.write_Signals(arr, size);
	rtds_smio.print_Results();
	float *p = rtds_smio.get_Base_Address();

	EmcStandIn emc(10);
	RtsStandIn rts(3);
}