all:
	g++ -I SDL2/include -L SDL2/lib -o sdl sdl.cpp -lmingw32 -lSDL2main -lSDL2