init: calam.cpp
	g++ calam.cpp -c -o calam.o -I/usr/include/SDL2 -D_REENTRANT -lSDL2 -Wall -Wextra

example: calam.o example.cpp
	g++ example.cpp calam.o -o main -I/usr/include/SDL2 -D_REENTRANT -lSDL2 -Wall -Wextra

temp: temp.c
	g++ temp.c calam.c -o temp -I/usr/include/SDL2 -D_REENTRANT -lSDL2 -Wall -Wextra

clean:
	rm main calam.o temp grid output.ppm
