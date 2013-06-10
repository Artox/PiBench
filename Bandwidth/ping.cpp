/*
 * Listens on port 1423 and sends all packets back
 */

#define _FILE_OFFSET_BITS 64

#include <malloc.h>
#include <stdio.h>

#include <cstdlib>
using std::atoi;

#include "net.h"
#include "../Timer/Timer.hpp"

void run(const char *hostname, int port, size_t bytes);

int main(int argc, char *argv[])
{
	if(argc != 3) {
		printf("Usage: %s %s %s", argv[0], "hostname", "port");
		return 0;
	}

	const char *hostname = argv[1];
	int port = atoi(argv[2]);
	size_t stepsize = 0x100000; // 1MB
	for(size_t i = 1; i <= 64; i++)
	{
		run(hostname, port, i*stepsize);
	}

	return 0;
}

void run(const char *hostname, int port, size_t bytes)
{
	// Timer
	Timer timer;

	// Create a Client
	Client cl;

	// connect to server
	cl.connect(hostname, port);
	fprintf(stderr, "Connected.\n");

	// Allocate Memory
	size_t size = bytes; // 1MB
	char *data = (char *)malloc(size);
	char *buffer = (char *)malloc(size);

	// send data
	cl.synchronous_send((char *)&size, sizeof(size));
	timer.start();
	cl.synchronous_send(data, size);
	fprintf(stderr, "Sent %u bytes.\n", size);

	// now read the data
	cl.synchronous_recv(buffer, size);
	timer.stop();

	free(buffer);
	free(data);

	//printf("Sending and Receiving %uB(%ukB; %uMB) took %ums\n", size, size/0x400, size/0x100000, timer.milliseconds());
	// simple output for automatic parsing
	printf("%u;%u\n", size, timer.milliseconds());

	// end
	return;
}
