#include <stdio.h>
#include <sys/shm.h> 
#include <sys/stat.h> 

int main()
{
    int segment_id;
    double* shared_memory;
    struct shmid_ds shmbuffer;
    int segment_size;
    const int shared_segment_size = sizeof(double);

    /* Allocate a shared memory segment.  */
    segment_id = shmget(IPC_PRIVATE, shared_segment_size,
        IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

    /* Attach the shared memory segment.  */
    shared_memory = (double*)shmat(segment_id, 0, 0);
    printf("shared memory attached at address %p\n", shared_memory);

    /* Determine the segment's size. */
    shmctl(segment_id, IPC_STAT, &shmbuffer);
    segment_size = shmbuffer.shm_segsz;
    printf("segment size: %d\n", segment_size);

    /* Write a string to the shared memory segment.  */
    shared_memory[0] = 25980123;
    printf("This is the data written in memory: %2f\n", shared_memory[0]);

    /* Detach the shared memory segment.  */
    shmdt(shared_memory);

    /* Reattach the shared memory segment, at a different address.  */
    shared_memory = (double*)shmat(segment_id, (void*)0, 0);
    printf("shared memory reattached at address %p\n", shared_memory);

    /* Print out the string from shared memory.  */
    printf("%2f\n", shared_memory[0]);

    /* Detach the shared memory segment.  */
    shmdt(shared_memory);

    /* Deallocate the shared memory segment.  */
    shmctl(segment_id, IPC_RMID, 0);

    printf("shared memory reattached at address %p\n", shared_memory);
    printf("This is the data written in memory: %2f\n", shared_memory[0]);

    return 0;
}