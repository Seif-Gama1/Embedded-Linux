#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define CAPS_PATH "/sys/class/leds/input3::capslock/brightness"

int main(int argc, char* argv[]){
	int fd;
	char led_state;

	if(argv[1][0] == '0' || argv[1][0] == '1'){
		led_state = argv[1][0];
	}else{
		printf("Invalid argument value use 0 or 1 only\0");
		return 1;
	}

	fd = open(CAPS_PATH, O_WRONLY); 
	if (fd != -1){
		write(fd, &led_state,1);
		close(fd);
	}else{
		printf("can't open the file\0");
		return 1;
	}
	return 0;
}
