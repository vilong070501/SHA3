CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++20 -Wold-style-cast
TARGET = sha3

SRC = main.cpp keccak.cpp sha3.cpp readfile.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
