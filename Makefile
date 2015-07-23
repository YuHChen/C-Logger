TARGET = LoggerTest

SRC_DIR = src
TEST_DIR = test

SRC_FILES = \
	$(TEST_DIR)/LoggerTest.cpp

OBJ_FILES := $(SRC_FILES:.cpp=.o)

# must include -pthread in compiler and linker to enable multithreading
CPPFLAGS = -g -Wall -pthread -std=c++11

all:	$(TARGET)

$(TARGET):	$(OBJ_FILES)
	g++ $(CPPFLAGS) $^ -o $(TARGET)

# common build for all .o files
%.o:	%.c
	g++ $(CPPFLAGS) -c $^ -o $@

clean:
	rm -f *~ *# *.o *.exe $(TARGET)
	rm -f $(SRC_DIR)/*~ $(SRC_DIR)/*# $(SRC_DIR)/*.o $(SRC_DIR)/*.exe
	rm -f $(TEST_DIR)/*~ $(TEST_DIR)/*# $(TEST_DIR)/*.o $(TEST_DIR)/*.exe
