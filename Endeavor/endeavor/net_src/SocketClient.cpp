#include "SocketClient.h"
#include "WriteFile.h"
#include "ReadFile.h"
#include "String_.h"
#include "Zip.h"
#include "EndeavorGame.h"

#include <iostream>

void SocketClient::run()
{
	char* buffer = new char[8];
	
	connection->receiveBytes(&buffer[0], 8); //player_ID received
	player_ID = atoi(buffer);
	delete[] buffer;
	
	std::string color; //path set for file transfers
	switch (player_ID) {
		case 1: color += "red"; break;
		case 2: color += "purple"; break;
		case 3: color += "orange"; break;
		case 4: color += "blue"; break;
		case 5: color += "green"; break;
	}
	
	std::string title = "Endeavor Client: " + color + "";
	color = "resources/" + color;
	std::string zipp = color;
	color+= "/endeavor_game.xml";
	zipp += "/endeavorzipped";
	
	int len=color.length();
	file_name = new char[len];
	std::strcpy(this->file_name, color.c_str());
	
	len=zipp.length();
	zipped = new char[len];
	std::strcpy(this->zipped, zipp.c_str()); //path for zipped files set too
	
	std::cout << "you are player " << player_ID << std::endl;
	
	//receives game state from server and updates game state
	receiveGameState();
	
	//set title for client
	game->setTitle(title);
	//and boot it
	game->showGUI();

	while(!game->isGameOver())
	{
		if (player_ID == game->getPlayerID())
		{
			std::cout << "your turn!" << std::endl;
			while (player_ID == game->getPlayerID()) {}
			zipItSendIt();
		}
		else
		{
			game->disableGame();
			receiveGameState();
		}
	} 
}

void SocketClient::zipItSendIt()
{
	CSC1310::String str = game->getGameState();
	CSC1310::WriteFile::entireFile(file_name, str.get_c_str(), str.length());
	
	CSC1310::Zip* zip = CSC1310::Zip::getZip();
	zip->zipit(file_name, zipped);
	
	int tcp_text_length = 0;
	char* tcp_text = CSC1310::ReadFile::entireFile(zipped, &tcp_text_length);
	connection->sendBytes(std::to_string(tcp_text_length).c_str(), 8);
	int num_bytes_sent = connection->sendBytes(tcp_text, tcp_text_length);
	std::cout << num_bytes_sent << " bytes sent to server" << std::endl;
}

void SocketClient::receiveGameState()
{
	char* buffer = new char[8];
	connection->receiveBytes(&buffer[0], 8); //get size of file
	int buffer_size = atoi(buffer);
	
	buffer = new char[buffer_size];
	int num_bytes_received = 0;
	int buffer_index = 0;

	num_bytes_received += connection->receiveBytes(&buffer[buffer_index], 1);
	buffer_index = num_bytes_received - 1;
	while (num_bytes_received != buffer_size)  
	{  
		num_bytes_received += connection->receiveBytes(&buffer[buffer_index+1], buffer_size-buffer_index-1);
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
	game->repaint();
	
	delete[] buffer;
}

SocketClient::SocketClient(std::string ip_address, int port_num, EndeavorGame* game)
{
	Poco::Net::initializeNetwork();

	Poco::Net::SocketAddress socket_addr(ip_address, port_num);
	connection = new Poco::Net::StreamSocket(socket_addr);

	this->game = game;
	
	client_thread = new Poco::Thread();
    client_thread->start(*this);
}

SocketClient::~SocketClient()
{
	std::cout << "destructor called" << std::endl;
	delete connection;
}
