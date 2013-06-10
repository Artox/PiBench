#include "net.h"

#define _FILE_OFFSET_BITS 64

#include <libexplain/accept.h>
#include <libexplain/bind.h>
#include <libexplain/close.h>
#include <libexplain/connect.h>
#include <libexplain/listen.h>
#include <libexplain/read.h>
#include <libexplain/setsockopt.h>
#include <libexplain/socket.h>
#include <libexplain/write.h>
#include <malloc.h>
#include <netdb.h>
#include <netinet/in.h>

#include <cstring>
using std::memset;

Packet::Packet(size_t _size) : size(_size), buffer(0)
{
	buffer = (char *)malloc(size);
}

const char *Packet::GetBuffer()
{
	return buffer;
}

const size_t Packet::GetSize()
{
	return size;
}

Server::Server()
{
	s = explain_socket_or_die(AF_INET, SOCK_STREAM, 0);
}

void Server::bind(int port)
{
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);

	// allow reusing recently closed socket
	int reuse = 1;
	explain_setsockopt_on_error(s, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

	// bind to address
	explain_bind_or_die(s, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
}

void Server::listen(int backlog)
{
	explain_listen_or_die(s, backlog);
}

int Server::accept()
{
	return explain_accept_or_die(s, 0, 0);
}

Server::~Server()
{
	explain_close_or_die(s);
}

Client::Client()
{
	s = explain_socket_or_die(AF_INET, SOCK_STREAM, 0);
}

void Client::connect(const char *hostname, int port)
{
	struct hostent *server;
	server = gethostbyname(hostname);
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
	serv_addr.sin_port = htons(port);

	// connect
	explain_connect_or_die(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
}

void Client::synchronous_send(char *data, const size_t size)
{
	::synchronous_send(s, data, size);
}

void Client::synchronous_recv(char *buffer, size_t bytes)
{
	::synchronous_recv(s, buffer, bytes);
}

Client::~Client()
{
	explain_close_or_die(s);
}

void synchronous_send(int socket, char *data, size_t size)
{
	size_t bytes_left = size;
	char *ptr = data;
	do {
		fprintf(stderr, "Sending %u bytes\n", bytes_left);
		int bytes = explain_write_or_die(socket, ptr, bytes_left);
		ptr += bytes;
		bytes_left -= bytes;
	} while(bytes_left > 0);
}

void synchronous_recv(int socket, char *buffer, size_t bytes)
{
	size_t bytes_left = bytes;
	char *ptr = buffer;
	do {
		fprintf(stderr, "Waiting for %u bytes\n", bytes_left);
		int bytes = explain_read_or_die(socket, ptr, bytes_left);
		ptr += bytes;
		bytes_left -= bytes;
	} while(bytes_left > 0);
}
