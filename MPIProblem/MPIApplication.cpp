#include "MPIApplication.h"

#include "mpi.h"
using namespace MPI;

MPIApplication::MPIApplication(int &argc, char** &argv) {
	Init(argc, argv);
}

MPIApplication::~MPIApplication() {
	Finalize();
}

int MPIApplication::GetGlobalRank() {
	return COMM_WORLD.Get_rank();
}

int MPIApplication::GetLocalRank() {
	return COMM_SELF.Get_rank();
}

int MPIApplication::GetGlobalProcesses()
{
	return COMM_WORLD.Get_size();
}

string MPIApplication::GetProcessorName() {
	char buffer[MPI_MAX_PROCESSOR_NAME];
	int size;
	Get_processor_name(buffer, size);
	return string(buffer, size);
}

void MPIApplication::Recv(void *buffer, size_t count, int source)
{
	size_t recvd = 0;
	do {
		Status status;
		COMM_WORLD.Recv(buffer+recvd, count-recvd, MPI_BYTE, source, MPI_ANY_TAG, status);
		recvd += status.Get_count(MPI_BYTE);
	} while(recvd < count);
}

void MPIApplication::Send(void *buffer, size_t count, int dest)
{
	COMM_WORLD.Send(buffer, count, MPI_BYTE, dest, MPI_ANY_TAG);
}
