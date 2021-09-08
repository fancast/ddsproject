#include <sys/types.h>
#include <sys/shm.h> //shared memory operations
#include <sys/ipc.h> //system call operations
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <cstring> // memcpy()

#include <iostream>
#include <type_traits>
using namespace std;

#define BUF_SIZE 2
#define SHM_KEY 0x1234

class ControlSMIO {

private:

	int cnt;
	int complete;
	char buf[BUF_SIZE];

public:

	auto get_reserved_addr()
	{
		shmget(ftok(), 1, IPC_EXCL);
	}



};