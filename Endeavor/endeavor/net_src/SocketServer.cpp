#include "SocketServer.h"
#include "ReadFile.h"
#include "WriteFile.h"
#include "Zip.h"

#include <iostream>
#include <string>
#include <cstring>

void SocketServer::run()
{
	//take any AI turns and send game state to every player for initialization
	game->checkForAITurn();
	zipItSendIt(); 
	
	while (!game->isGameOver())
	{
			std::cout << "waiting on player " << game->getPlayerID() << "..." << std::endl;
			receiveGameState(game->getPlayerID()); //waits for player to take their turn 
			std::cout<<"AI on the move..."<<std::endl;
			game->checkForAITurn();
			zipItSendIt();
	}
}

void SocketServer::zipItSendIt()
{
	CSC1310::String str = game->getGameState();
	CSC1310::WriteFile::entireFile(file_name, str.get_c_str(), str.length());
	
	CSC1310::Zip* zip = CSC1310::Zip::getZip();
	zip->zipit(file_name, zipped);
	
	tcp_text_length = 0;
	tcp_text = CSC1310::ReadFile::entireFile(zipped, &tcp_text_length);
	
	for(int i=num_players-1; i>=0; i--)
	{
		client_connections[i].sendBytes(std::to_string(tcp_text_length).c_str(), 8);
		int num_bytes_sent = client_connections[i].sendBytes(tcp_text, tcp_text_length);
		std::cout << "\n" <<num_bytes_sent << " bytes sent to player " << std::to_string(i+1) << std::endl;
	}
}

void SocketServer::receiveGameState(int pid)
{
	pid--;
	
	char* buffer = new char[8];
	client_connections[pid].receiveBytes(&buffer[0], 8); //get size of file
	int buffer_size = atoi(buffer);
	
	buffer = new char[buffer_size];
	int num_bytes_received = 0;
	int buffer_index = 0;

	num_bytes_received += client_connections[pid].receiveBytes(&buffer[buffer_index], 1);
	buffer_index = num_bytes_received - 1;
	while (num_bytes_received != buffer_size)  
	{  
		num_bytes_received += client_connections[pid].receiveBytes(&buffer[buffer_index+1], buffer_size-buffer_index-1);
		std::cout << "num bytes received: " <<  num_bytes_received;
		buffer_index = num_bytes_received - 1;
	}

	CSC1310::Zip* zip = CSC1310::Zip::getZip();
	CSC1310::WriteFile::entireFile(zipped, buffer, num_bytes_received-1);
	zip->unzipit(zipped, file_name);
	int length=0;
	
	CSC1310::String str(CSC1310::ReadFile::entireFile(file_name, &length));
	game->setGameState(str);
	std::cout << ", game state updated" << std::endl;
	
	delete[] buffer;
}


SocketServer::SocketServer(std::string ip_address, int port_num, int num_p, EndeavorGame* game) 
{
	Poco::Net::initializeNetwork();
	
	this->game = game;
	this->num_players = num_p;
	this->tcp_text_length = 0;
	
	Poco::Net::SocketAddress socket_addr(ip_address, port_num);
	server_socket = new Poco::Net::ServerSocket(socket_addr);
	std::cout << "server started!" << std::endl;
}

void SocketServer::startServer()
{
	int conn_num=0;
	while(conn_num<num_players)
	{
		client_connections[conn_num] = server_socket->acceptConnection();
		client_connections[conn_num].sendBytes(std::to_string(conn_num+1).c_str(), 8);
		conn_num++;
		std::cout<<"player "<<conn_num<<" connected"<<std::endl;	
	}
	server_thread = new Poco::Thread();
	server_thread->start(*this); 
}

SocketServer::~SocketServer()
{
	std::cout << "destructor called" << std::endl;
	delete server_socket;
}
