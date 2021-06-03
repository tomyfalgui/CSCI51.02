#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int shmId;

    key_t shmKey = 1234;

    int shmSize = 1 << 10;
    int shmFlags = IPC_CREAT | 0666;

    char *sharedMem;

    shmId = shmget(shmKey, shmSize, shmFlags);

    sharedMem = (char *)shmat(shmId, NULL, 0);

    if (((int *)sharedMem) == (int *)-1)
    {
        perror("shmop: shmat failed");
    }
    else
    {
        const char *buffer = "Hello!";

        // We can now write to shared memory...
        strcpy(sharedMem, buffer);

        char buffer2[50];

        // Or read from shared memory.
        strcpy(buffer2, sharedMem);

        printf("%s\n", buffer2);

        char buffer3[50];

        // We can also use memcpy
        memcpy(buffer3, sharedMem, 3);
        buffer3[3] = '\0';

        printf("%s\n", buffer3);
    }

    return 0;
}
