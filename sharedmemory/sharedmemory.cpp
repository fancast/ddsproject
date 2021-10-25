#include <sys/shm.h> //shared memory operations
#include <sys/ipc.h> //system call operations
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>
#include <iostream>

using namespace std;

//constexpr size_t size = 128*sizeof(double);

class Smio {

    private:

        int segment_id;
        float* shared_memory;
        struct shmid_ds shmbuffer;
        int segment_size;

    public:

        Smio()
        {
            /* Allocate a shared memory segment. */
            segment_id = shmget(IPC_PRIVATE, sizeof(float)*128,
                IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

            /* Attach the shared memory segment. */
            shared_memory = (float*)shmat(segment_id, 0, 0);
            printf("shared memory attached at address %p\n", shared_memory);

            /* Determine the segment's size. */
            shmctl(segment_id, IPC_STAT, &shmbuffer);
            segment_size = shmbuffer.shm_segsz;
            printf("segment size: %d\n", segment_size);

        }

        Smio(size_t size)
        {
            /* Allocate a shared memory segment. */
            segment_id = shmget(IPC_PRIVATE, sizeof(float)*size,
                IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

            /* Attach the shared memory segment. */
            shared_memory = (float*)shmat(segment_id, 0, 0);
            printf("shared memory attached at address %p\n", shared_memory);
        
            /* Determine the segment's size. */
            shmctl(segment_id, IPC_STAT, &shmbuffer);
            segment_size = shmbuffer.shm_segsz;
            printf("segment size: %d\n", segment_size);

        }

        auto write_value(float &signal)
        {
            /* Write a string to the shared memory segment. */
            shared_memory = &signal;

        }

        auto read_value() const
        {
            return shared_memory;
        }

        auto detach_memory_segment()
        {
            /* Detach the shared memory segment.  */
            shmdt(shared_memory);

            /* Deallocate the shared memory segment.  */
            shmctl(segment_id, IPC_RMID, 0);
        }

        auto print_results()
        {

            printf("shared memory attached at address %p\n", shared_memory);
            printf("segment size: %d\n", segment_size);
        }


};