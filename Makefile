CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = main

OBJS = main.o player.o computer.o shooting.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp player.h computer.h shooting.h
	$(CXX) $(CXXFLAGS) -c main.cpp

player.o: player.cpp player.h
	$(CXX) $(CXXFLAGS) -c player.cpp

computer.o: computer.cpp computer.h
	$(CXX) $(CXXFLAGS) -c computer.cpp

shooting.o: shooting.cpp shooting.h
	$(CXX) $(CXXFLAGS) -c shooting.cpp

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean
