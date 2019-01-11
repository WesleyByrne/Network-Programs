AutomatedMakefile = am
CC = g++

WXGUI_PATH = $(COMPILER_PATH)/wxWidgets-3.1.0
TINYXML_PATH = $(COMPILER_PATH)/tinyxml-2.6.2
GUI_PATH = $(GAME_PATH)/GUI
CSC2110_PATH = $(GAME_PATH)/CSC2110

SRC_DIR=./src
BUILD_DIR=./build
HEADER_DIR=./include

INC_DIRS = -I$(GUI_PATH)/include -I$(TINYXML_PATH)/include -I$(CSC2110_PATH)/include -I$(WXGUI_PATH)/lib/wx/include/msw-unicode-3.1 -I$(WXGUI_PATH)/include
LIB_DIRS = -L$(CSC2110_PATH) -L$(TINYXML_PATH)/lib -L$(WXGUI_PATH)/lib
LIBS = -ltinyxml -lCSC2110 -lwx_baseu-3.1 -lwx_mswu_core-3.1

COMPILE = $(CC) $(INC_DIRS) -Wno-deprecated-declarations -c
LINK = $(CC) $(LIB_DIRS) -o

GUI_FILES = build/DrawFont.o build/PixelXML.o build/DrawImage.o build/HotSpot.o build/PixelDimension.o build/PixelPoint.o build/Color.o build/Line.o build/Circle.o build/Rect.o build/ImageLoader.o build/DrawPanel.o build/BasicGUI.o build/NullDrawable.o

all: GUI_LIB

GUI_LIB: 					$(GUI_FILES)

$(BUILD_DIR)/%.o:	$(SRC_DIR)/%.cpp $(HEADER_DIR)/%.h
								$(COMPILE) $< -o $@

