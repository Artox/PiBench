/*
 * Listens on port 1423 and sends all packets back
 */

#include <malloc.h>
#include <stdio.h>

#include <iostream>
using namespace std;

#include "net.h"

#include <fcntl.h>

class PongServer : public Server {
public:
	void onAccept(int cs) {
		// prepare array for receiving data. 200MB Maximum here.
		char *buffer = (char *)malloc(0x100000*200);

		// set non-blocking mode
		// int flags;
		// flags = fcntl(cs, F_GETFD);
		// int x = fcntl(cs, F_SETFD, flags|O_NONBLOCK);

		// while the connection stands, do the pong-ing
		bool run = true;
		while(run) {
			// transmission state variables
			size_t recvcount;
			size_t recvwanted;
			size_t writecount;
			size_t writewanted;

			// receive data size
			// printf("Waiting for data size\n");
			size_t size;
			recvwanted = sizeof(size);
			recvcount = 0;
			while(recvcount < recvwanted) {
				int e = read(cs, (&size)+recvcount, recvwanted-recvcount);
				if(e == 0) {
					// This means EOF, the client has closed
					// get out of endless loop
					run = false;
					break;
				} else if(e < 0) {
					printf("read encountered error %i\n", e);
				}
				recvcount += e;
			}
			if(!run)
				break;

			//cout << "Expected data size is " << size << endl;

			// Now read the actual data
			recvwanted = size;
			recvcount = 0;
			while(recvcount < recvwanted) {
				int e = read(cs, buffer+recvcount, recvwanted-recvcount);
				if(e == 0) {
					// This means EOF, the client has closed
					// get out of endless loop
				  run = false;
					break;
				} else if(e < 0) {
					printf("read encountered error %i\n", e);
				}
				recvcount += e;
			}
			if(!run)
				break;
			//cout << "Data received completely" << endl;

			// send the data back
			writewanted = size;
			writecount = 0;
			while(writecount < writewanted) {
				int e = write(cs, buffer+writecount, writewanted-writecount);
				if(e < 0) {
					printf("write encountered error %i\n", e);
				}
				writecount += e;
			}
			//cout << "Data sent back completely" << endl;
		}

		// Close socket
		close(cs);

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
