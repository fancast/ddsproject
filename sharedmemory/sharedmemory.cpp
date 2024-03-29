#include <sys/shm.h> //shared memory operations
#include <sys/ipc.h> //system call operations
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class Smio {

    private:

        int segment_id;
        float* shared_memory;
        struct shmid_ds shmbuffer;
        int segment_size;
        int arr_length;

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

        ~Smio()
        {
            /* Detach the shared memory segment.  */
            shmdt(shared_memory);

            /* Deallocate the shared memory segment.  */
            shmctl(segment_id, IPC_RMID, 0);
        }

        auto write_Signals(float *signals, int &size)
        {
            arr_length = size;

            /* Write a string to the shared memory segment. */
            for(int i = 0; i < arr_length; i++)
                shared_memory[i] = signals[i];
        }

        auto get_Base_Address() const
        {
            return shared_memory;
        }

        auto print_Results()
        {
            printf("shared memory attached at address %p\n", shared_memory);
            printf("segment size: %d\n", segment_size);
            printf("Signals from memory:\n");
            for (int i = 0; i < arr_length; i++)
                printf("%d: %2f\n", i, shared_memory[i]);
        }
};