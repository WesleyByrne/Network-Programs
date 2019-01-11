#include "SocketServer.h"
#include "ReadFile.h"
#include "Zip.h"

#include <iostream>
#include <string>
#include <cstring>

int main(int argv, char** argc)
{
	const char* file_name = "endeavor_save_in.xml";
	int length = 0;
	Poco::Net::initializeNetwork();
	
	CSC1310::Zip* zip = CSC1310::Zip::getZip();
	zip->zipit(file_name, "endeavor_save_zipped.xml");
	char* str = CSC1310::ReadFile::entireFile("endeavor_save_zipped.xml", &length);
	
	std::string ip_address = "127.0.0.1";
	int port_num = 6789;
	SocketServer* socket_server = new SocketServer(ip_address, port_num, str, length);
	socket_server->startServer();
	return 0;
}

//the send code is in its own server
//in case this takes a while, the server can wait for new connections
//in parallel (and then start their threads)
void SocketServer::run()
{
	SocketServer* socket_server = this; 
	
	//protocol choices
	//the receiver is going to have a problem with determining
	//when it has received the entire file (unless it is ascii characters)
	//when asked for bytes, TCP can only provide what it has obtained
	//that has no errors and is in order
	
	//1. could send a header with the file size embedded
	//2. could send the file size separately
	//3. if the data is ascii, check for null terminator
	
	//include the null terminator in the byte count
	
	std::cout << "sending file size: " << std::to_string(tcp_text_length).c_str() << std::endl;
	client_connection.sendBytes(std::to_string(tcp_text_length).c_str(), 8);
	std::cout << "sending bytes to client" << std::endl;
	int num_bytes_sent = client_connection.sendBytes(socket_server->tcp_text, socket_server->tcp_text_length);
	std::cout << "num bytes sent: " <<  num_bytes_sent << std::endl;
}

SocketServer::SocketServer(std::string ip_address, int port_num, char* tcp_text, int tcp_text_length) 
{
	this->tcp_text = tcp_text;
	this->tcp_text_length = tcp_text_length;
	
	Poco::Net::SocketAddress socket_addr(ip_address, port_num);
	//creates a TCP welcoming socket
	server_socket = new Poco::Net::ServerSocket(socket_addr);
}

void SocketServer::startServer()
{
	while(true)
	{
		//blocks until connection made (can only handle one at a time)
		//could easily store an array of connections (5 for Endeavor)
		client_connection = server_socket->acceptConnection();

		server_thread = new Poco::Thread();
		server_thread->start(*this);  //the start method accepts a Runnable
	}
}

SocketServer::~SocketServer()
{
	std::cout << "destructor called" << std::endl;
	delete server_socket;
}
