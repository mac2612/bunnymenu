CXX      = $(CROSS)g++
CXXFLAGS =  -lSDL -lSDL_image -lSDL_ttf -g -I. -std=c++11 
DEPS = background.h file_menu.h img_menu.h list_select.h input_parser.h
OBJ =  main.o file_menu.o img_menu.o list_select.o background.o input_parser.o

: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

bunnymenu: $(OBJ)
	$(CXX) $^ -o $@ $(CXXFLAGS)

install:
	install -D bunnymenu /usr/bin
	install -D theme/mainfont.ttf /usr/share/bunnymenu/mainfont.ttf
	install -D theme/background.jpg /usr/share/bunnymenu/background.jpg
	install -D theme/snes.png /usr/share/bunnymenu/snes.png
	install -D theme/nes.png /usr/share/bunnymenu/nes.png
	install -D theme/genesis.png /usr/share/bunnymenu/genesis.png
	install -D scripts/startgenesis.sh /usr/bin
	install -D scripts/startnes.sh /usr/bin
	install -D scripts/startsnes.sh /usr/bin
	install -D scripts/respawn_menu.sh /usr/bin

clean:
	rm -f bunnymenu *.o *.gch
