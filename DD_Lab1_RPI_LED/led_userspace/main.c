#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define PROC_FILE "/proc/rpi_gpio"

int main(void)
{
    int fd;
    char value;

    fd = open(PROC_FILE, O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    /* Turn GPIO ON */
    value = '1';
    write(fd, &value, 1);

    sleep(1);

    /* Turn GPIO OFF */
    value = '0';
    write(fd, &value, 1);

    /* Read current state */
    lseek(fd, 0, SEEK_SET);

    if (read(fd, &value, 1) == 1) {
        printf("Current GPIO state: %c\n", value);
    }

    close(fd);
    return 0;
}