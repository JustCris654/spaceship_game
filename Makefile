CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g 
SFMLFLAGS = -I/opt/homebrew/Cellar/sfml/2.5.1_2/include
LINKEROPTIONS = -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
OBJDIR = build/objs


output: $(OBJDIR)/main.o $(OBJDIR)/game.o $(OBJDIR)/base_entity.o $(OBJDIR)/aircraft.o
	$(CXX) $(CXXFLAGS) $(LINKEROPTIONS) -o build/spaceship_game $(OBJDIR)/main.o  $(OBJDIR)/game.o $(OBJDIR)/base_entity.o $(OBJDIR)/aircraft.o

$(OBJDIR)/aircraft.o: src/Entities/Aircraft/Aircraft.cpp src/Entities/Aircraft/Aircraft.hpp
	$(CXX) $(CXXFLAGS) $(SFMLFLAGS) $(LINKEROPTIONS) -c src/Entities/Aircraft/Aircraft.cpp -o $(OBJDIR)/aircraft.o

$(OBJDIR)/base_entity.o: src/Entities/BaseEntity.cpp src/Entities/BaseEntity.hpp
	$(CXX) $(CXXFLAGS) $(SFMLFLAGS) $(LINKEROPTIONS) -c src/Entities/BaseEntity.cpp -o $(OBJDIR)/base_entity.o

$(OBJDIR)/game.o: src/game/game.cpp src/game/game.hpp
	$(CXX) $(CXXFLAGS) $(SFMLFLAGS) $(LINKEROPTIONS) -c src/game/game.cpp -o $(OBJDIR)/game.o

$(OBJDIR)/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) $(SFMLFLAGS) $(LINKEROPTIONS) -c src/main.cpp -o $(OBJDIR)/main.o


clean:
	rm build/objs/*.o build/spaceship_game

cleanobj:
	rm build/objs/*.o
