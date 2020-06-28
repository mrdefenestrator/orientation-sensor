/* functions for communicating with the pololu ssc over a serial port */

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <sys/select.h>
#include "os.h"

#define STX	0x02
#define CR	0x0D
#define NL	0x0A
#define ETX	0x03

struct ssc port;

int main(void) {
	int i;
	
	printf("Program Started...\r\n"); fflush(stdout);
	if(connect(&port)) {
		printf("COM Port Connected\r\n"); fflush(stdout);
	} else {
		printf("COM Port Would Not Connect\r\n"); fflush(stdout);
		return 0;
	}
//////// TEST CODE STARTS HERE ///////////
	

	
//////// TEST CODE ENDS HERE ///////////	
	
	disconnect(&port);
	printf("Program Complete.\r\n"); fflush(stdout);
	
	return 0;
}

int fcSendStr(char *str, int len)
{
	int i;
	
	for(i = 0; i < len; i++) {
		write(port.fd, str + i, 1);
	}
	return 0;
}

int fcGetStr(char *str, int len)
{
	int i;

	for(i = 0; i < len; i++) {	// Get 'len' bytes
		read(port.fd, str + i, 1); 
	}
	return 0;
}



void disconnect(ssc *s) {
  if(!s->connected) return;
  close(s->fd);
}

int connect(ssc *s) {
	struct termios options;
	int count,ret;

	s->connected=0; /* reset in case we fail to connect */

	s->fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
	if (s->fd == -1) {
		//printf("Failed to open COM port\r\n");
		return 0;
	} else {
		//printf("Successfully opened COM port\r\n");
		fcntl(s->fd, F_SETFL, 0);
	}

	tcgetattr(s->fd, &options);

	/* go to 9600 baud */
	//cfsetispeed(&options, B115200);
	//cfsetospeed(&options, B115200);
	cfsetispeed(&options, B128000);
	cfsetospeed(&options, B128000);

	options.c_cflag |= (CLOCAL | CREAD); /* enable */

	options.c_cflag &= ~PARENB; /* 8N1 */
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;

	/* set all of the options */
	tcsetattr(s->fd, TCSANOW, &options);

	s->connected=1;
	return 1;
}

