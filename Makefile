CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g 
SFMLFLAGS = -I/opt/homebrew/Cellar/sfml/2.5.1_2/include
LINKEROPTIONS = -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
OBJDIR = build/objs


output: $(OBJDIR)/main.o $(OBJDIR)/game.o $(OBJDIR)/texture_holder.o
	$(CXX) $(CXXFLAGS) $(LINKEROPTIONS) -o build/spaceship_game $(OBJDIR)/main.o $(OBJDIR)/texture_holder.o $(OBJDIR)/game.o

$(OBJDIR)/game.o: src/game/game.cpp src/game/game.hpp
	$(CXX) $(CXXFLAGS) $(SFMLFLAGS) $(LINKEROPTIONS) -c src/game/game.cpp -o $(OBJDIR)/game.o

$(OBJDIR)/texture_holder.o: src/Textures/texture_holder.cpp src/Textures/texture_holder.hpp
	$(CXX) $(CXXFLAGS) $(SFMLFLAGS) $(LINKEROPTIONS) -c src/Textures/texture_holder.cpp -o $(OBJDIR)/texture_holder.o

$(OBJDIR)/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) $(SFMLFLAGS) $(LINKEROPTIONS) -c src/main.cpp -o $(OBJDIR)/main.o


clean:
	rm build/objs/*.o build/spaceship_game

cleanobj:
	rm build/objs/*.o
