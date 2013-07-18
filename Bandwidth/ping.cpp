/*
 * Listens on port 1423 and sends all packets back
 */

#include <malloc.h>
#include <stdio.h>

#include <cstdlib>
using std::atoi;
#include <vector>
using namespace std;

#include "net.h"
#include "../Timer/Timer.hpp"

void run(Client *cl, int N, size_t bytes, char *data, char *buffer);

int main(int argc, char *argv[])
{
	if(argc != 3) {
		printf("Usage: %s %s %s", argv[0], "hostname", "port");
		return 0;
	}

	// read options
	const char *hostname = argv[1];
	int port = atoi(argv[2]);

	// allocate required memory
	char *data = (char *)malloc(0x100000*10);
	char *buffer = (char *)malloc(0x100000*10);
	// TODO: fill with random data

	// connect
	Client *cl = new Client();
	cl->connect(hostname, port);

	// Benchmark
	int N = 10;
	// 1 byte seems special, do it one time in advance
	run(cl, N, 1, data, buffer);
	// 1B-1KB in B-steps
	for(unsigned int i = 1; i <= 0x400; i++) {
		run(cl, N, i, data, buffer);
	}
	// 1KB-1MB in KB-steps
	for(unsigned int i = 1; i <= 0x400; i++) {
		run(cl, N, 0x400*i, data, buffer);
	}
	// 1MB-10MB in MB-steps
	for(unsigned int i = 1; i <= 10; i++) {
		run(cl, N, 0x100000*i, data, buffer);
	}
	// doing 1 Byte again just to be sure
	run(cl, N, 1, data, buffer);

	// Close connection
	delete cl;

	// free memory
	free(buffer),
	free(data);

	return 0;
}

void run(Client *cl, int N, size_t bytes, char *data, char *buffer)
{
	// Timer
	Timer timer;

	vector<uint32_t> times(N);
	for(int i = 0; i < N; i++)
	{
		// send size
		cl->synchronous_send((char *)&bytes, sizeof(bytes));

		// send and receive the data
		timer.start();
		cl->synchronous_send(data, bytes);
		cl->synchronous_recv(buffer, bytes);
		timer.stop();

		// store time
		times[i] = timer.milliseconds();
	}

	// find lowest time
	uint32_t min_time = times[0];
	for(int i = 1; i < N; i++)
		if(times[i] < min_time)
			min_time = times[i];

	printf("Sending and Receiving %uB(%ukB; %uMB) took at minimum %ums\n", bytes, bytes/0x400, bytes/0x100000, min_time);
	// simple output for automatic parsing
	//printf("%u;%u\n", bytes, min_time);
}
