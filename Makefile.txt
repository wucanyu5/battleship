CXX = g++

main: main.o player.o computer.o shooting.o
	$(CXX) -o main main.o player.o computer.o shooting.o

main.o: main.cpp player.h computer.h shooting.h
	$(CXX) -c main.cpp

player.o: player.cpp player.h
	$(CXX) -c player.cpp

computer.o: computer.cpp computer.h
	$(CXX) -c computer.cpp

shooting.o: shooting.cpp shooting.h
	$(CXX) -c shooting.cpp

.PHONY: clean
clean:
	rm *.o main
