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
