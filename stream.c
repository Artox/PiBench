#include <Timer.h>
#include <stdio.h>
#include <malloc.h>

// stream operations

void STREAM_copy(uint32_t *__restrict__ src, uint32_t *__restrict__ dest, size_t size)
{
	// STREAM COPY
	// 1 read, 1 write

	// copy the whole buffer once
	for(size_t i = 0; i < size; i++)
		dest[i] = src[i];

	// now <size> copy operations have been done
}

// Main Execution

/*
 * Cache Sizes:
 * Intel i5 3350P
 * L1: 4x64KB
 * L2: 4x256KB
 * L3: 6MB
 * since L3 is biggest, array size should be 4x6MB=24MB=
 * 
 * 
 * Raspberry Pi
 * L1: 64KB (64K for data and 64K for instructions or 64K total?  -- from ARM1176JZF-S datasheet)
 * L2: 128KB (http://www.raspberrypi.org/archives/1040)
 * This cache can be disabled in /boot/config.txt
 * array size should be 4x128KB=512KB
 */


int main()
{
	// create buffers for stream copy
	// 0x400 = 1024 Byte = 1kB
	size_t size = 0x400 * 0x400 * 24; // 24MB
	//size_t size = 0x400 * 512; // 512KB
	//size_t size = 0x400 * 512 * 10; // ~5MB
	//size_t size = 0x400 * 0x400 * 100;
	uint32_t *src = malloc(sizeof(uint32_t)*size);
	uint32_t *dest = malloc(sizeof(uint32_t)*size);

	// declare Timer
	void *timer = Timer_create();

	// run STREAM_copy
	// do it N times
	size_t N = 5;
	uint32_t *times = malloc(sizeof(uint32_t)*N);
	for(uint8_t i = 0; i < 10; i++)
	{
		Timer_start(timer);
		STREAM_copy(src, dest, size);
		Timer_stop(timer);
		times[i] = Timer_milliseconds(timer);
	}

	// generate some statistics
	double avg_msec = 0;
	uint32_t max_msec = 0;
	uint32_t min_msec = -1;
	for(uint8_t i = 0; i < 10; i++)
	{
		uint32_t msec = times[i];
		avg_msec += msec/N;
		if(max_msec < msec) max_msec = msec;
		if(min_msec > msec) min_msec = msec;
	}
	double min_mb_sec = ((double)size) / ((double)1024*1024) * 1000.0f / ((double)max_msec);
	double avg_mb_sec = ((double)size) / ((double)1024*1024) * 1000.0f / ((double)avg_msec);
	double max_mb_sec = ((double)size) / ((double)1024*1024) * 1000.0f / ((double)min_msec);

	// print statistics
	printf("Copying %fMP took beetween %fms and %fms, on average %fms\n", ((double)size) / ((double)1024*1024), min_msec, max_msec, avg_msec);
	printf("Minimum speed: %fMB/s\n", min_mb_sec);
	printf("Maximum speed: %fMB/s\n", max_mb_sec);
	printf("Average speed: %fMB/s\n", avg_mb_sec);


	// clean up
	Timer_delete(timer);
	free(times);
	free(dest);
	free(src);
}
