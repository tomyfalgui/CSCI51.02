#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Please provide right number of arguments.\n");
        printf("<textfileCopy> & <shared memory size in bytes>\n");
        exit(1);
    }

    // shmA

    int shmIdA;

    key_t shmKeyA = 7676;

    int shmSizeA = 1000 << 10;
    int shmFlagsA = IPC_CREAT | 0666;

    char *sharedMemA;

    shmIdA = shmget(shmKeyA, shmSizeA, shmFlagsA);

    sharedMemA = (char *)shmat(shmIdA, NULL, 0);

    // end shmA

    int semId;
    key_t semKey = 1234;
    int semFlag = IPC_CREAT | 0666;
    int nSems = 1;
    semId = semget(semKey, nSems, semFlag);
    if (semId == -1)
    {
        perror("semget");
        exit(1);
    }
    int nOperations = 2;
    struct sembuf sema[nOperations];

    sema[0].sem_num = 0;
    sema[0].sem_op = 0;
    sema[0].sem_flg = SEM_UNDO;

    sema[1].sem_num = 0;
    sema[1].sem_op = 1;
    sema[1].sem_flg = SEM_UNDO | IPC_NOWAIT;

    int opResult = semop(semId, sema, nOperations);
    if (opResult != -1)
    {
        printf("Running Consumer!\n");

        // -- Do stuff --
        if (((int *)sharedMemA) == (int *)-1)
        {
            perror("shmop: shmat failed");
        }
        else
        {

            FILE *fptr;
            fptr = fopen(argv[1], "w");

            if (fptr == NULL)
            {
                printf("Error!");
                exit(1);
            }

            size_t length = strlen(sharedMemA);
            int chunk = atoi(argv[2]);
            size_t remain = length + 1;
            size_t pointer = 0;

            while (remain > 0)
            {

                size_t chunkSize = remain > chunk ? chunk : remain;
                char chunkBuff[chunkSize];
                memcpy(chunkBuff, &sharedMemA[(pointer * chunk)], chunkSize);
                fprintf(fptr, "%s", chunkBuff);
                remain -= chunkSize;
                pointer++;
                usleep(30 * 1000);
            }
            fclose(fptr);
            shmctl(shmIdA, IPC_RMID, NULL);

            // end writing

            // Set number of operations to 1
            nOperations = 1;

            // Modify the first operation such that it
            // now decrements the semaphore.
            sema[0].sem_num = 0;
            sema[0].sem_op = -1; // Decrement semaphore by 1
            sema[0].sem_flg = SEM_UNDO | IPC_NOWAIT;

            opResult = semop(semId, sema, nOperations);
            if (opResult == -1)
            {
                perror("semop (decrement)");
            }
            else
            {

                printf("Successfully Released!\n");
            }
        }
    }
    else
    {
        perror("semop (increment)");
    }

    return 0;
}