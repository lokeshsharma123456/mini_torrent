// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fstream>
#define PORT 8080
#define SIZE 1024
using namespace std;


void write_file(int server_fd)
{
	FILE * fp;
	char *filename = "file2.txt";
	char data[SIZE] = {0};
	fp = fopen(filename , "w");
	if (fp == NULL)
	{
		perror("[+]Error in reading file\n");
		exit(1);
	}

	int n;
	while (1)
	{
		if ((n = recv(server_fd, data, SIZE, 0)) <= 0)
		{
			break;
			// return;
		}
		fprintf(fp, "%s", data );
		bzero(data, SIZE);
	}
}

int main(int argc, char const* argv[])
{




// #ifndef ONLINE_JUDGE
// 	freopen("input.txt", "r", stdin);
// 	freopen("output.txt", "w", stdout);
// #endif


	char *ip = "127.0.0.1";
	ofstream out("logs.txt");
	int server_fd; // server file descripotr
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket failed");
		out << "server socket failed\n";
		exit(1);
	}
	printf("Server socket created\n");
	out << "Server socket created\n";



	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr(ip);
	// server_addr.sin_addr.s_addr = INADDR_ANY;
	//INADDR_ANY : assing address of m/c ip to server



	if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("bind failed");
		out << "Server socket bind failed\n";
		exit(EXIT_FAILURE);
	}
	printf("Binding successful\n");
	out << "Server socket Binding successful\n";




	// Forcefully attaching socket to the
	if (listen(server_fd, 5) < 0)//5 backlogs
	{	//5 : how many request in the wait queue
		perror("server listen failed");
		out << "Server socket  listen failed\n";

		exit(EXIT_FAILURE);
	}
	printf("Listening...\n");
	out << "Server socket  listening...\n";



	struct sockaddr_in new_addr;
	socklen_t addr_size;
	addr_size = sizeof(new_addr);



	int accept_socket;
	if ((accept_socket
	        = accept(server_fd, (struct sockaddr*)&new_addr,
	                 (socklen_t*)&addr_size))
	        < 0) {
		perror("server accept failed");
		out << "Server socket  accept failed\n";

		exit(EXIT_FAILURE);
	}

	write_file(accept_socket);
	printf("Data written successfully\n");
	out << "Data written successfully\n";




	out.close();
	return 0;
}
