all: rpg

rpg.o: Player.c Game.c Lab10_main.c
	gcc -c Player.c Game.c Lab10_main.c

rpg: Player.o Game.o Lab10_main.o
	gcc -Wall Player.o Game.o Lab10_main.o -o rpg
	
clean:
	rm *.o rpg
	