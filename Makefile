CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -g


ifeq  ($(uname), "Linux")
SFMLFLAGS =  ""
else
SFMLFLAGS = -I/opt/homebrew/Cellar/sfml/2.5.1_2/include
endif

ifeq ($(uname), "Linux")
LINKEROPTIONS =  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
else
LINKEROPTIONS = -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
endif

OBJDIR = build/objs


output: $(OBJDIR)/main.o $(OBJDIR)/game.o $(OBJDIR)/base_entity.o $(OBJDIR)/aircraft.o $(OBJDIR)/fps_counter.o
	$(CXX) $(CXXFLAGS) $(LINKEROPTIONS) -o build/spaceship_game $(OBJDIR)/main.o  $(OBJDIR)/game.o $(OBJDIR)/base_entity.o $(OBJDIR)/aircraft.o $(OBJDIR)/fps_counter.o

$(OBJDIR)/fps_counter.o: src/Utils/FpsCounter.cpp src/Utils/FpsCounter.hpp
	$(CXX) $(CXXFLAGS) $(SFMLFLAGS) $(LINKEROPTIONS) -c src/Utils/FpsCounter.cpp -o $(OBJDIR)/fps_counter.o

$(OBJDIR)/aircraft.o: src/Entities/Aircraft/Aircraft.cpp src/Entities/Aircraft/Aircraft.hpp
	$(CXX) $(CXXFLAGS) $(SFMLFLAGS) -c src/Entities/Aircraft/Aircraft.cpp -o $(OBJDIR)/aircraft.o

$(OBJDIR)/base_entity.o: src/Entities/BaseEntity.cpp src/Entities/BaseEntity.hpp
	$(CXX) $(CXXFLAGS) $(SFMLFLAGS) -c src/Entities/BaseEntity.cpp -o $(OBJDIR)/base_entity.o

$(OBJDIR)/game.o: src/Game/Game.cpp src/Game/Game.hpp
	$(CXX) $(CXXFLAGS) $(SFMLFLAGS) -c src/Game/Game.cpp -o $(OBJDIR)/game.o

$(OBJDIR)/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) $(SFMLFLAGS) -c src/main.cpp -o $(OBJDIR)/main.o


clean:
	rm build/objs/*.o build/spaceship_game

cleanobj:
	rm build/objs/*.o
