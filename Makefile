# Compiler
CXX := g++
CXXFLAGS := -I"E:/Program Files/msys2/ucrt64/include" -std=c++17 -Wall -Wextra #-mwindows

# SFML Libraries
LDFLAGS := -L"E:/Program Files/msys2/ucrt64/lib" -lsfml-graphics -lsfml-window -lsfml-system

# Output
TARGET := main.exe

# Source and object files
SRC_DIR := src
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link object files to create final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile each .cpp file into a .o file
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Special rule for main.o (main.cpp có thể không có main.hpp)
$(SRC_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run
run: $(TARGET)
	./$(TARGET)

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)
