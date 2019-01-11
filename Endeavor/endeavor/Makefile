AutomatedMakefile = am
CC = g++ -std=c++11

WXGUI_PATH = $(COMPILER_PATH)/wxWidgets-3.1.0
TINYXML_PATH = $(COMPILER_PATH)/tinyxml-2.6.2
GUI_PATH = $(GAME_PATH)/gui
GAME_NETWORK_PATH = $(GAME_PATH)/game_network
ZLIB_PATH = $(COMPILER_PATH)/zlib-1.2.11
ZIP_PATH = $(GAME_PATH)/zip
CSC1310_PATH = $(GAME_PATH)/CSC1310
ENDEAVOR_PATH = $(GAME_PATH)/endeavor

SRC_DIR=./src
NET_DIR=./net_src
BUILD_DIR=./build
HEADER_DIR=./include

GAME_FILES=build/AIXML.o build/CompareBuildingsForPayment.o build/CompareCardsByLevel.o build/CompareShippingByToken.o build/CompareCitiesByToken.o build/EndeavorAI.o build/BasicEndeavorAI.o build/EndeavorGame.o build/GameOverState.o build/EndeavorState.o build/PaymentActionState.o build/DrawAndDrawState.o build/ShipAndShipState.o build/ShipAndOccupyState.o build/OccupyOrAttackState.o build/DiscardState.o build/OccupyOrDrawState.o build/ShipOrDrawState.o build/Cards.o build/Cities.o build/Region.o build/ShipState.o build/ShippingLane.o build/Ship.o build/AttackState.o build/PlayerCardManager.o build/DrawCardState.o build/OccupyState.o build/PaymentState.o build/ActionState.o build/BuildState.o build/Board.o build/Mediterranean.o build/City.o build/Card.o build/Players.o build/Player.o build/Buildings.o build/Building.o build/Token.o build/Connections.o build/Connection.o resources/resource.o
SERVER_FILES=build/SocketServer.o build/AIXML.o build/CompareBuildingsForPayment.o build/CompareCardsByLevel.o build/CompareShippingByToken.o build/CompareCitiesByToken.o build/EndeavorAI.o build/BasicEndeavorAI.o build/EndeavorGame.o build/GameOverState.o build/EndeavorState.o build/PaymentActionState.o build/DrawAndDrawState.o build/ShipAndShipState.o build/ShipAndOccupyState.o build/OccupyOrAttackState.o build/DiscardState.o build/OccupyOrDrawState.o build/ShipOrDrawState.o build/Cards.o build/Cities.o build/Region.o build/ShipState.o build/ShippingLane.o build/Ship.o build/AttackState.o build/PlayerCardManager.o build/DrawCardState.o build/OccupyState.o build/PaymentState.o build/ActionState.o build/BuildState.o build/Board.o build/Mediterranean.o build/City.o build/Card.o build/Players.o build/Player.o build/Buildings.o build/Building.o build/Token.o build/Connections.o build/Connection.o resources/resource.o
CLIENT_FILES=build/SocketClient.o build/AIXML.o build/CompareBuildingsForPayment.o build/CompareCardsByLevel.o build/CompareShippingByToken.o build/CompareCitiesByToken.o build/EndeavorAI.o build/BasicEndeavorAI.o build/EndeavorGame.o build/GameOverState.o build/EndeavorState.o build/PaymentActionState.o build/DrawAndDrawState.o build/ShipAndShipState.o build/ShipAndOccupyState.o build/OccupyOrAttackState.o build/DiscardState.o build/OccupyOrDrawState.o build/ShipOrDrawState.o build/Cards.o build/Cities.o build/Region.o build/ShipState.o build/ShippingLane.o build/Ship.o build/AttackState.o build/PlayerCardManager.o build/DrawCardState.o build/OccupyState.o build/PaymentState.o build/ActionState.o build/BuildState.o build/Board.o build/Mediterranean.o build/City.o build/Card.o build/Players.o build/Player.o build/Buildings.o build/Building.o build/Token.o build/Connections.o build/Connection.o resources/resource.o

INC_DIRS=-I$(ENDEAVOR_PATH)/include -I$(ZIP_PATH)/include -I$(CSC1310_PATH)/include -I$(GUI_PATH)/include -I$(COMPILER_PATH)/wxWidgets-3.1.0/lib/wx/include/msw-unicode-3.1 -I$(COMPILER_PATH)/wxWidgets-3.1.0/include -I$(COMPILER_PATH)/tinyxml-2.6.2/include -I$(GAME_PATH)/random -I$(COMPILER_PATH)/poco-1.7.6/Net/include -I$(COMPILER_PATH)/poco-1.7.6/Foundation/include -I$(COMPILER_PATH)/poco-1.7.6/Util/include
LIB_DIRS= -L$(ZIP_PATH)/lib -L$(ZLIB_PATH)/lib -L$(CSC1310_PATH) -L$(GUI_PATH) -L$(COMPILER_PATH)/wxWidgets-3.1.0/lib -L$(COMPILER_PATH)/tinyxml-2.6.2/lib -L$(GAME_PATH)/random -L$(COMPILER_PATH)/poco-1.7.6/lib/MinGW/i686
LIBS= -lCSC1310 -lrandom -lgui -ltinyxml -lwx_baseu-3.1 -lwx_mswu_core-3.1 -lgdi32
NET_LIBS= -lzlib -lzipp -lPocoNet -lPocoFoundation -lCSC1310 -lrandom -lgui -ltinyxml -lwx_baseu-3.1 -lwx_mswu_core-3.1 -lgdi32 -lWS2_32

COMPILE=$(CC) $(INC_DIRS) -Wno-deprecated-declarations -c 
LINK=$(CC) $(LIB_DIRS) -o 

all: EndeavorServer EndeavorClient 

EndeavorServer: 			$(BUILD_DIR)/EndeavorServerApp.o  $(SERVER_FILES)
					$(LINK) EndeavorServer.exe build/EndeavorServerApp.o $(SERVER_FILES) $(NET_LIBS)

EndeavorClient: 			$(BUILD_DIR)/EndeavorClientApp.o $(CLIENT_FILES)
					$(LINK) EndeavorClient.exe build/EndeavorClientApp.o $(CLIENT_FILES) $(NET_LIBS)

Endeavor:				$(BUILD_DIR)/EndeavorApp.o $(GAME_FILES)
					$(LINK) Endeavor.exe build/EndeavorApp.o $(GAME_FILES) $(LIBS)

$(BUILD_DIR)/EndeavorApp.o:				$(SRC_DIR)/EndeavorApp.cpp
							$(COMPILE) $< -o $@

$(BUILD_DIR)/EndeavorServerApp.o:			$(NET_DIR)/EndeavorServerApp.cpp
							$(COMPILE) $< -o $@

$(BUILD_DIR)/EndeavorClientApp.o:			$(NET_DIR)/EndeavorClientApp.cpp
							$(COMPILE) $< -o $@
							
$(BUILD_DIR)/%.o:					$(SRC_DIR)/%.cpp $(HEADER_DIR)/%.h
							$(COMPILE) $< -o $@
							
$(BUILD_DIR)/%.o:					$(NET_DIR)/%.cpp $(NET_DIR)/%.h
							$(COMPILE) $< -o $@

