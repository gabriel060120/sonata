TARGET=../sonata.out
CXX=g++
DEBUG=-g
OPT=-O0
WARN=-Wall
SFML=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CXXFLAGS=$(DEBUG) $(OPT) $(WARN) $(SFML)
LD=g++
OBJS= main.o player.o enemy.o life_bar.o serie_music.o engine.o finish_page.o
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(CXXFLAGS)
	@rm *.o
	@./$(TARGET)
main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) main.cpp -o main.o
player.o: player.cpp
	$(CXX) -c $(CXXFLAGS) player.cpp -o player.o
enemy.o: enemy.cpp
	$(CXX) -c $(CXXFLAGS) enemy.cpp -o enemy.o
life_bar.o: life_bar.cpp
	$(CXX) -c $(CXXFLAGS) life_bar.cpp -o life_bar.o
serie_music.o: serie_music.cpp
	$(CXX) -c $(CXXFLAGS) serie_music.cpp -o serie_music.o
finish_page.o: finish_page.cpp
	$(CXX) -c $(CXXFLAGS) finish_page.cpp -o finish_page.o
engine.o: engine.cpp
	$(CXX) -c $(CXXFLAGS) engine.cpp -o engine.o

