/*
 * Listens on port 1423 and sends all packets back
 */

#define _FILE_OFFSET_BITS 64

#include <malloc.h>
#include <stdio.h>

#include <cstdlib>
using std::atoi;

#include "net.h"

int main(int argc, char *argv[])
{
	if(argc != 3) {
		printf("Usage: %s %s %s", argv[0], "hostname", "port");
		return 0;
	}

	// Create a Client
	Client cl;

	// connect to server
	cl.connect(argv[1], atoi(argv[2]));
	printf("Connected.\n");

	// Send Data
	size_t size = 0x100000; // 1MB
	char *data = (char *)malloc(0x100000);

	cl.synchronous_send((char *)&size, sizeof(size));
	cl.synchronous_send(data, size);
	printf("Sent %u bytes.\n", size);

	free(data);

	// prepare array for receiving data.
	char *buffer = (char *)malloc(0x100000);

	// now read the data
	cl.synchronous_recv(buffer, size);

	free(buffer);

	// end
	return 0;
}
