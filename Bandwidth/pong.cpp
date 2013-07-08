/*
 * Listens on port 1423 and sends all packets back
 */

#include <malloc.h>
#include <stdio.h>

#include "net.h"

class PongServer : public Server {
	public void onAccept(int cs) {
		// prepare array for receiving data. 200MB Maximum here.
		char *buffer = (char *)malloc(0x100000*200);

		// receive data size
		printf("Waiting for data size\n");
		size_t size;
		synchronous_recv(_c, (char *)&size, sizeof(size));
		printf("Expected data size: %i\n", size);

		// now read the data
		synchronous_recv(_c, buffer, size);
		printf("Data received completely\n");

		// send the data back
		printf("Sending the data back\n");
		synchronous_send(_c, buffer, size);
		free(buffer);
	}
}

int main()
{
	// Start TCP Server
	PongServer srv;
	srv.run(1423);

	// end
	return 0;
}
