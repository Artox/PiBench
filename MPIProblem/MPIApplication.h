#include <string>
using namespace std;

class MPIApplication
{
public:
	MPIApplication(int &argc, char** &argv);
	~MPIApplication();

	// Gibt den Rang bezüglich aller MPI Knoten an
	int GetGlobalRank();

	// Gibt den Rang bezüglich naderer MPI Threads auf diesem Knoten an
	int GetLocalRank();

	string GetProcessorName();
	
	// gibt die ANzahl MPI Knoten zurück
	int GetGlobalProcesses();
	
	void Recv(void *buffer, size_t count, int source);

	void Send(void *buffer, size_t count, int dest);
};
