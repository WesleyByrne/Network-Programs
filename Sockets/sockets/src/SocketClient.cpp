#include "SocketClient.h"
#include "WriteFile.h"
#include "Zip.h"

#include <iostream>

int main(int argv, char** argc)
{
	std::string ip_address = "127.0.0.1";
	int port_num = 6789;
	
	Poco::Net::initializeNetwork();
	SocketClient* socket_client = new SocketClient(ip_address, port_num);

	//have to keep main from ending until the client's task is complete
	while(!socket_client->isDone())
	{
		Sleep(100);
	}
	
	return 0;
}

void SocketClient::run()
{
	//what should this be set to?
	//if the file size is received first (as ascii characters) as part of the protocol
	//the buffer_size can be set to the exact required size
	char* buffer = new char[8];
	connection->receiveBytes(&buffer[0], 8);
	int buffer_size = atoi(buffer);
	std::cout << "file size to be received: " << buffer_size << std::endl;
	buffer = new char[buffer_size];
	int num_bytes_received = 0;
	int buffer_index = 0;
	
	//get the first byte (which might conceivably be the null terminator)
	//need to use threads as the next statement will block
	num_bytes_received += connection->receiveBytes(&buffer[buffer_index], 1);
	buffer_index = num_bytes_received - 1;
	//check the last byte received on this pass through the loop
	//if it is the null terminator, and the data is ascii, we are done
	//wait for the null terminator (trivial for ascii data, this is a problem for binary data)
	while (num_bytes_received != buffer_size)  
   {  
		//you need to determine if you need more space in your buffer
		if (num_bytes_received == buffer_size)
		{
			//resize the buffer here
			//double the size of the buffer when you run out of room
			std::cout << "you need more buffer space" << std::endl;
		}
		
		//this loop can be tricky as you may have received some, but not all, of the bytes
		//assume there will be enough room in the buffer for all of the bytes
		//TCP will give you all the bytes that it has received that have no errors and are in order
		//only ask for the number of bytes that you have room for in the buffer
		//start filling in the buffer where you left off last time
		num_bytes_received += connection->receiveBytes(&buffer[buffer_index+1], buffer_size-buffer_index-1);
		std::cout << "num bytes received: " <<  num_bytes_received << std::endl;
		//prepare to check the last byte received again for the null terminator
		buffer_index = num_bytes_received - 1;
   }
   
   //std::cout << num_bytes_received << std::endl;
   //std::cout << buffer_index << std::endl;
   //std::cout << buffer << std::endl;
   CSC1310::Zip* zip = CSC1310::Zip::getZip();
   const char* file_name = "endeavor_save_zippedclientside.xml";
   //num_bytes_received includes the null terminator
   //this is not part of the string length needed below
   CSC1310::WriteFile::entireFile(file_name, buffer, num_bytes_received-1);
   zip->unzipit("endeavor_save_zippedclientside.xml", "endeavor_save_unzippedclientside.xml");
   //Sleep(10000);  //keep this client busy for 10 seconds
   
   delete[] buffer;
   done = true;
}

bool SocketClient::isDone()
{
	return done;
}

SocketClient::SocketClient(std::string ip_address, int port_num)
{
	done = false;

	Poco::Net::SocketAddress socket_addr(ip_address, port_num);
	connection = new Poco::Net::StreamSocket(socket_addr);

	client_thread = new Poco::Thread();
    client_thread->start(*this);
}

SocketClient::~SocketClient()
{
	std::cout << "destructor called" << std::endl;
	delete connection;
}
