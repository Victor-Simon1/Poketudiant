poketudiant : player.o load.o main.o fonctions.o gui.o menu.o serveur.o client.o partie.o
	gcc -o ./bin/poketudiant player.o load.o main.o fonctions.o gui.o menu.o serveur.o client.o partie.o -L/usr/lib/x86_64-linux-gnu -lm -Llib -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf 

main.o : src/main.c
	gcc src/main.c -c -Iinclude  -o main.o

player.o : src/player.c
	gcc src/player.c -c -Iinclude  -o player.o

load.o : src/load.c
	gcc src/load.c -c -Iinclude  -o load.o

fonctions.o : src/fonctions.c
	gcc src/fonctions.c -c -Iinclude  -o fonctions.o

gui.o : src/gui.c
	gcc src/gui.c -c -Iinclude  -o gui.o

menu.o : src/menu.c
	gcc src/menu.c -c -Iinclude  -o menu.o

serveur.o : src/serveur.c
	gcc src/serveur.c -c -Iinclude  -o serveur.o

client.o : src/client.c
	gcc src/client.c -c -Iinclude  -o client.o

partie.o : src/partie.c
	gcc src/partie.c -c -Iinclude  -o partie.o