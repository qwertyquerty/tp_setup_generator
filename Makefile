CXX      := g++
CXXFLAGS := -O3 -std=c++17 -Wall
LDFLAGS  := -static-libstdc++ -static-libgcc

TARGET := mtps.exe
SRC    := mtps.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
