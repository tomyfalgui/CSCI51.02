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
        printf("<textfile> & <shared memory size in bytes>\n");
        exit(1);
    }

    // shmA

    int shmIdA;

    key_t shmKeyA = 7676;
    // 1024
    // 2048
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
        printf("Successfully incremented semaphore!\n");

        // -- Do stuff --

        // reading
        char *source = NULL;
        long bufsize;
        FILE *fp = fopen(argv[1], "r");
        if (fp != NULL)
        {
            /* Go to the end of the file. */
            if (fseek(fp, 0L, SEEK_END) == 0)
            {
                /* Get the size of the file. */
                bufsize = ftell(fp);
                if (bufsize == -1)
                { /* Error */
                }

                /* Allocate our buffer to that size. */
                source = malloc(sizeof(char) * (bufsize + 1));

                /* Go back to the start of the file. */
                if (fseek(fp, 0L, SEEK_SET) != 0)
                { /* Error */
                }

                /* Read the entire file into memory. */
                size_t newLen = fread(source, sizeof(char), bufsize, fp);
                if (ferror(fp) != 0)
                {
                    fputs("Error reading file", stderr);
                }
                else
                {
                    source[newLen++] = '\0'; /* Just to be safe. */
                }
            }
            fclose(fp);
        }
        // end reading

        if (((int *)sharedMemA) == (int *)-1)
        {
            perror("shmop: shmat failed");
        }
        else
        {
            int chunk = atoi(argv[2]);

            long remain = bufsize + 1;

            int pointer = 0;
            while (remain > 0)
            {

                long chunkSize = remain > chunk ? chunk : remain;
                char chunkBuff[chunkSize];
                memcpy(chunkBuff, &source[(pointer * chunk)], chunkSize);
                memcpy(&sharedMemA[(pointer * chunk)], chunkBuff, chunkSize);
                remain -= chunkSize;
                pointer++;
                printf("writing\n");
                usleep(30 * 1000);
            }
        }

        free(source);

        int a;

        a = shmdt(sharedMemA);
        if (a == -1)
        {
            perror("shmop: shmdt failed");
        }
        else
        {
            (void)fprintf(stderr, "shmop: shmdt returned %d\n", a);
        }

        // Do stuff here

        // -- Semaphore Releasing --

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
            printf("Successfully decremented semaphore!\n");
        }
    }
    else
    {
        perror("semop (increment)");
    }

    return 0;
}