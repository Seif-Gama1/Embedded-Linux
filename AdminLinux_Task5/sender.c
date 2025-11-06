#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>

#define KEY 0x1234u
#define SIZE 100u

int main(void){
    char* address;
    int access_key = shmget(KEY, SIZE, IPC_CREAT | 0666);

    if (access_key < 0){
        printf("Error, can't allocate shared memory");
        return 1;
    }

    address = (char *)shmat(access_key, NULL, 0);
    if(address != (char *)-1){
        while (1) {
            printf("writer: ");
            fgets(address, SIZE, stdin);

            if (strncmp(address, "exit", 4) == 0){
                break;
            }
            printf("\nwriter: msg written\n");
        }

        shmdt(address);
        return 0;   
    }else{
        printf("Error can't attach");
    }
}