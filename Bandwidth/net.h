#include <cstdint>
using std::size_t;

// Fixed Size Packet
class Packet
{
private:
	size_t size;
	char *buffer;
public:
	Packet(size_t size);
	const char *GetBuffer();
	const size_t GetSize();
};

// Basic TCP Server
class Server
{
private:
	int s;
	bool r;

public:
	// Erzeugt einen neuen Server an gegebenem Port
	Server();

	// Server MainLoop. Wartet auf Eingehende Verbindungen
	void run(int port);

	// Wird bei Eingang einer neuen Verbindung ausgeführt.
	virtual void onAccept(int cs) = 0;
	
	// Beendet den Server *irgendwann*
	void shutdown();

	// Closes Socket properly
	~Server();
};

class Client
{
private:
	int s;
public:
	Client();
	void connect(const char *hostname, int port);
	void synchronous_send(char *data, size_t size);
	void synchronous_recv(char *buffer, size_t bytes);
	~Client();
};

// pushes all the data to the socket and returns afterwards
void synchronous_send(int socket, char *data, size_t size);

// reads <length> bytes into <buffer>, then returns
void synchronous_recv(int socket, char *buffer, size_t bytes);
