#include "Connections.h"

#include "PixelPoint.h"
#include "PixelDimension.h"

uint8 Connections::computeConnectionsGlory(uint8 player_id)
{
	uint8 connection_glory = 0;
	CSC1310::BinaryTreeIterator<Connection>* conn_iter = connections_by_first_city->iterator();
	conn_iter->setInorder();
	while(conn_iter->hasNext())
	{
		Connection* conn = conn_iter->next();
		if (conn->getControlID() == player_id)
		{
			connection_glory++;
		}
	}
	delete conn_iter;
	return connection_glory;
}
 
Connections::Connections(PixelXML& pixel_xml, CSC1310::Permutation& permute, CSC1310::ListArray<Token>* tokens)
{
	//connections = new CSC1310::ListArray<Connection>();
	connections_by_first_city = new CSC1310::BinarySearchTree<Connection>(&Connection::compareConnectionsByFirstCity, &Connection::compareConnectionsByKeyAndFirstCity);
	connections_by_second_city = new CSC1310::BinarySearchTree<Connection>(&Connection::compareConnectionsBySecondCity, &Connection::compareConnectionsByKeyAndSecondCity);

	CSC1310::ListArray<PixelPoint>* connection_centers = pixel_xml.getPixelCentersList("connections");
	PixelDimension connections_dim = pixel_xml.getPixelDimension("connections");

	CSC1310::ListArrayIterator<PixelPoint>* connection_centers_iter = connection_centers->iterator();
	int connection_count = 1;
	while(connection_centers_iter->hasNext())
	{ 
		PixelPoint* pixel_center = connection_centers_iter->next();

		int token_permute = permute.next();
	
		Token* token = tokens->get(token_permute);
		EndeavorTokenType token_id = token->getTokenType();

		wxBitmap* token_img = token->getTokenImage();

		Connection* conn;

		switch(connection_count)
		{
			case 1: conn = new Connection(27, 29, token_id, token_img, pixel_center, connections_dim); break;
			case 2: conn = new Connection(24, 26, token_id, token_img, pixel_center, connections_dim); break;
			case 3: conn = new Connection(24, 25, token_id, token_img, pixel_center, connections_dim); break;
			case 4: conn = new Connection(2, 25, token_id, token_img, pixel_center, connections_dim); break;
			case 5: conn = new Connection(7, 26, token_id, token_img, pixel_center, connections_dim); break;
			case 6: conn = new Connection(2, 23, token_id, token_img, pixel_center, connections_dim); break;
			case 7: conn = new Connection(22, 23, token_id, token_img, pixel_center, connections_dim); break;
			case 8: conn = new Connection(1, 22, token_id, token_img, pixel_center, connections_dim); break;
			case 9: conn = new Connection(20, 21, token_id, token_img, pixel_center, connections_dim); break;
			case 10: conn = new Connection(1, 21, token_id, token_img, pixel_center, connections_dim); break;
			case 11: conn = new Connection(5, 20, token_id, token_img, pixel_center, connections_dim); break;
			case 12: conn = new Connection(16, 19, token_id, token_img, pixel_center, connections_dim); break;
			case 13: conn = new Connection(8, 19, token_id, token_img, pixel_center, connections_dim); break;
			case 14: conn = new Connection(4, 16, token_id, token_img, pixel_center, connections_dim); break;
			case 15: conn = new Connection(16, 18, token_id, token_img, pixel_center, connections_dim); break;
			case 16: conn = new Connection(3, 18, token_id, token_img, pixel_center, connections_dim); break;
			case 17: conn = new Connection(14, 17, token_id, token_img, pixel_center, connections_dim); break;
			case 18: conn = new Connection(3, 14, token_id, token_img, pixel_center, connections_dim); break;
			case 19: conn = new Connection(4, 15, token_id, token_img, pixel_center, connections_dim); break;
			case 20: conn = new Connection(8, 11, token_id, token_img, pixel_center, connections_dim); break;
			case 21: conn = new Connection(11, 12, token_id, token_img, pixel_center, connections_dim); break;
			case 22: conn = new Connection(10, 12, token_id, token_img, pixel_center, connections_dim); break;
			case 23: conn = new Connection(9, 10, token_id, token_img, pixel_center, connections_dim); break;
			case 24: conn = new Connection(7, 10, token_id, token_img, pixel_center, connections_dim); break;
			case 25: conn = new Connection(6, 7, token_id, token_img, pixel_center, connections_dim); break;
			case 26: conn = new Connection(5, 6, token_id, token_img, pixel_center, connections_dim); break;
		}
		
		delete pixel_center;
		
		connections_by_first_city->insert(conn);
		connections_by_second_city->insert(conn);
		connection_count++;
	}
	
	delete connection_centers_iter;
	delete connection_centers;
}

CSC1310::ListArray<Connection>* Connections::getAllConnectionsContainingCityID(uint8 city_id)
{
	CSC1310::String sk = CSC1310::String::i_to_a(city_id);
	CSC1310::ListArray<Connection>* result_connections_1 = connections_by_first_city->retrieveDuplicates(&sk);
	CSC1310::ListArray<Connection>* result_connections_2 = connections_by_second_city->retrieveDuplicates(&sk);
	
	//merge the results together
	CSC1310::ListArrayIterator<Connection>* conn_iter = result_connections_2->iterator();
	while(conn_iter->hasNext())
	{
		Connection* conn = conn_iter->next();
		result_connections_1->add(conn);
	}
	delete conn_iter;
	delete result_connections_2;
	
	return result_connections_1;
}

Connections::~Connections()
{
//PRINT("Connections Destructor Called.")
	CSC1310::BinaryTreeIterator<Connection>* connections_iter = connections_by_first_city->iterator();
	connections_iter->setInorder();
	while(connections_iter->hasNext())
	{
		Connection* conn = connections_iter->next();
		delete conn;
	}
	delete connections_iter;
	
	delete connections_by_first_city;
	delete connections_by_second_city;
}

void Connections::draw(wxDC&  dc)
{
	CSC1310::BinaryTreeIterator<Connection>* connections_iter = connections_by_first_city->iterator();
	connections_iter->setInorder();
	while(connections_iter->hasNext())
	{
		Connection* conn = connections_iter->next();
		conn->draw(dc);
	}
	delete connections_iter;
}

TiXmlElement* Connections::writeXML()
{
   TiXmlElement* connections_element = new TiXmlElement("Connections");
   
   CSC1310::BinaryTreeIterator<Connection>* connections_iter = connections_by_first_city->iterator();
   connections_iter->setInorder();
   while(connections_iter->hasNext())
   {
	   Connection* conn = connections_iter->next();
	   TiXmlElement* conn_element = conn->writeXML();
	   connections_element->LinkEndChild(conn_element);
   }
   delete connections_iter;

   return connections_element;
}

void Connections::readXML(TiXmlElement* connections_element, wxBitmap** player_images, wxBitmap** token_images)
{
   TiXmlElement* connection_element = connections_element->FirstChildElement();

   CSC1310::BinaryTreeIterator<Connection>* connections_iter = connections_by_first_city->iterator();
   connections_iter->setInorder();
   while(connections_iter->hasNext())
   {
	   Connection* conn = connections_iter->next();
	   conn->readXML(connection_element, player_images, token_images);
	   connection_element = connection_element->NextSiblingElement();
   }
   delete connections_iter;
}
