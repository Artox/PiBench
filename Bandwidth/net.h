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
public:
	Server();

	// binds to given port
	void bind(int port);

	// starts listening for incoming connections
	void listen(int backlog = 5);

	// accepts 1 connection
	int accept();

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
