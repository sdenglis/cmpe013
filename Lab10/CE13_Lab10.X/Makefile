HEADERS = Game.h Player.h UNIXBOARD.h

all: rpg


rpg: Player.c Game.c Lab10_main.c $(HEADERS)
	gcc -Wall Player.c Game.c Lab10_main.c -o rpg
	
clean:
	-rm -f rpg.o
	-rm -f rpg
	