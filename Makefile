TARGET=a.out
CXX=g++
DEBUG=-g
OPT=-O0
WARN=-Wall
SFML=-lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS=$(DEBUG) $(OPT) $(WARN) $(SFML)
LD=g++
OBJS= main.o player.o
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(CXXFLAGS)
	@rm *.o
	@./$(TARGET)
main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) main.cpp -o main.o
player.o: player.cpp
	$(CXX) -c $(CXXFLAGS) player.cpp -o player.o