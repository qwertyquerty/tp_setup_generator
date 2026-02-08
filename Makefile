CXX      := g++
CXXFLAGS := -O3 -std=c++17 -Wall
LDFLAGS  := -static-libstdc++ -static-libgcc -lstdc++ -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive -static

TARGET := mtps.exe
SRC    := mtps.cpp
PYTHON   := py

all: $(TARGET)

gen_moves: generate_moves_h.py
	$(PYTHON) generate_moves_h.py

$(TARGET): gen_moves $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
