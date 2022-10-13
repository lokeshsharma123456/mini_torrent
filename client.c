// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fstream>
using namespace std;


#define PORT 8080
#define SIZE 1024


void send_file(FILE * fp , int client_fd)
{
	char data[SIZE] = {0};

	while (fgets(data , SIZE, fp) != NULL)
	{
		if (send(client_fd, data, sizeof(data), 0) == -1)
		{
			perror("Sending data failed");
			exit(1);

		}
		bzero(data, SIZE);
	}
}


int main(int argc, char const* argv[])
{
	ofstream out("log.txt");

	int client_fd; // client file descripotr
	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket failed");
		out << "client socket failed\n";
		exit(1);
	}
	printf("Client socket created\n");
	out << "Client socket created\n";


	char *ip = "127.0.0.1";

	struct sockaddr_in client_addr;
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(PORT);
	client_addr.sin_addr.s_addr = inet_addr(ip);
	// server_addr.sin_addr.s_addr = INADDR_ANY;
	//INADDR_ANY : assing address of m/c ip to server

	int check_connect = 0;
	if ((check_connect = connect(client_fd, (struct sockaddr*)&client_addr,
	                             sizeof(client_addr))) < 0)
	{
		perror("\nError in connecting \n");
		out << "Error in connecting to socket\n";
		return -1;
	}
	printf("Connected to server\n");
	out << "Connecting to socket\n";


	char *filename = "input.txt";
	FILE *fp;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		perror("Error in reading file");
		out << "Error in reading file\n";
		return -1;
	}

	send_file(fp , client_fd);//func
	printf("File data sent successfully\n");
	out << "File data sent successfully\n";




	// valread = read(sock, buffer, 1024);
	// printf("%s\n", buffer);

	// closing the connected socket
	// close(client_fd);
	out.close();

	return 0;
}
