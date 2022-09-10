CXX = g++
CXXFLAGS = -std=c++17 -Wall 
SFMLFLAGS = -I/opt/homebrew/Cellar/sfml/2.5.1_1/include
LINKEROPTIONS = -L/opt/homebrew/Cellar/sfml/2.5.1_1/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
OBJDIR = build/objs

output: $(OBJDIR)/main.o $(OBJDIR)/game.o
	$(CXX) $(CXXFLAGS) $(LINKEROPTIONS) -o build/spaceship_game $(OBJDIR)/main.o $(OBJDIR)/game.o

$(OBJDIR)/game.o: src/game/game.cpp
	$(CXX) $(CXXFLAGS) $(SFMLFLAGS) $(LINKEROPTIONS) -c src/game/game.cpp -o $(OBJDIR)/game.o

$(OBJDIR)/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) $(SFMLFLAGS) $(LINKEROPTIONS) -c src/main.cpp -o $(OBJDIR)/main.o


clean:
	rm *.o spaceship_game

cleanobj:
	rm *.o