/* functions for communicating with one or more pololu sscs over a serial port */
typedef struct ssc {
	int connected;		// if not true, connect() must be run 
	int fd;				// File descriptor for the port 
	// char idstring[26];	// Some kind of now useless? identifier
} ssc;

extern int connect(ssc *s);
extern void disconnect(ssc *s);



