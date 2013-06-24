class MPIApplication
{
public:
	MPIApplication(int &argc, char** &argv);
	~MPIApplication();

	// Gibt den Rang bezüglich aller MPI Knoten an
	int GetGlobalRank();

	// Gibt den Rang bezüglich naderer MPI Threads auf diesem Knoten an
	int GetLocalRank();
};
