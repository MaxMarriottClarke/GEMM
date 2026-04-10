TARGET = main
CXX = g++
CXXFLAGS = -std=c++14 -O2 -Wall -Wextra -m64 -mavx -I. -I../include
SOURCES = main.cpp c2_int_add.cpp

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
