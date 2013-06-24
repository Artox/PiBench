#include "MPIApplication.h"

#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
	MPIApplication app(argc, argv);
	cout << "Anwendung gestartet!" << endl;
	cout << "Globaler Rang ist " << app.GetGlobalRank() << endl;
	cout << "Lokaler Rang ist " << app.GetLocalRank() << endl;
	cout << "Anwendung endet" << endl;
}
