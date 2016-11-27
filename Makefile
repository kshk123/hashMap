#define dir for source files
SRC_DIR = ./src

#define dir for target *.o files, etc
OBJ_DIR = ./bin

#define any directories containing header files other than /usr/include
INCLUDES = -I ./inc

#define libraries to be included
LIBS = -lpthread

#define the C compiler to use
CC = g++

#define any compile-time flags
CPPFLAGS = -Wall -Werror -O3 -std=c++14

# define prerequisites (source files)
SOURCES =       $(SRC_DIR)/HastTest.cpp

SRCS = $(notdir $(SOURCES))

# define the executable file 
MAIN = hashMap

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o, $(filter %.cpp, $(SRCS)))

all:    $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CPPFLAGS) $(INCLUDES) $(LIBS) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) $(INCLUDES) -c -o $@ $<

