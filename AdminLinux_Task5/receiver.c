#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>

#define KEY 0x1234u
#define SIZE 100u

int main(void){
    char* address;
    char prev_msg[SIZE] = "";

    int access_key = shmget(KEY, SIZE, 0666);

    if (access_key < 0){
        printf("Error, can't allocate shared memory");
        return 1;
    }

    address = (char *)shmat(access_key, NULL, 0);

    if(address != (char *)-1){
        while (1) {
            if (strncmp(address, "exit", 4) == 0){
                break;
            }

            if (strcmp(prev_msg, address) != 0) {
                printf("\nReader: message = %s", address);
                strcpy(prev_msg, address); 
            }
        }
        shmdt(address);
        return 0;   
    }
    else{
        printf("Buffer doesn't exist");
    }
}