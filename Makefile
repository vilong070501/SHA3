CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = sha3

SRC = main.cpp keccak.cpp sha3.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
