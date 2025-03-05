# Compiler
CXX := g++
CXXFLAGS := -I"E:/Program Files/msys2/ucrt64/include" # -mwindows

# SFML Libraries
LDFLAGS := -L"E:/Program Files/msys2/ucrt64/lib" -lsfml-graphics -lsfml-window -lsfml-system

# Output
TARGET := main.exe

# Source files
SRCS := src/*.cpp

# Compile
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

# Run
run: $(TARGET)
	./$(TARGET)

# Clean build files
clean:
	rm -f $(TARGET)
