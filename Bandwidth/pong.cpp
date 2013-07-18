/*
 * Listens on port 1423 and sends all packets back
 */

#include <malloc.h>
#include <stdio.h>

#include <iostream>
using namespace std;

#include "net.h"

#define _FILE_OFFSET_BITS 64
#include <libexplain/read.h>
#include <libexplain/write.h>
#include <fcntl.h>

class PongServer : public Server {
public:
	void onAccept(int cs) {
		// prepare array for receiving data. 200MB Maximum here.
		char *buffer = (char *)malloc(0x100000*200);

		// set non-blocking mode
		int flags;
		flags = fcntl(cs, F_GETFD);
		fcntl(cs, F_SETFD, flags|O_NONBLOCK);
		
		// while the connection stands, do the pong-ing
		while(true) {
			// transmission state variables
			size_t recvcount;
			size_t recvwanted;
			size_t writecount;
			size_t writewanted;
		  
			// receive data size
			printf("Waiting for data size\n");
			size_t size;
			recvwanted = sizeof(size);
			recvcount = 0;
			while(recvcount < recvwanted) {
				int e = explain_read_or_die(cs, (&size)+recvcount, recvwanted-recvcount);
				if(e < 0) {}
				recvcount += e;
			}

			cout << "Expected data size is " << size << endl;
			
			// Now read the actual data
			recvwanted = size;
			recvcount = 0;
			while(recvcount < recvwanted) {
				int e = explain_read_or_die(cs, buffer+recvcount, recvwanted-recvcount);
				if(e < 0) {}
				recvcount += e;
			}
			cout << "Data received completely" << endl;

			// send the data back
			writewanted = size;
			writecount = 0;
			while(writecount < writewanted) {
				int e = explain_write_or_die(cs, buffer+writecount, writewanted-writecount);
				if(e < 0) {}
				writecount += e;
			}
			cout << "Data senbt back completely" << endl;
		}

		free(buffer);
	}
};

int main()
{
	// Start TCP Server
	PongServer srv;
	srv.run(1423);

	// end
	return 0;
}
