CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lm

main: main.c
	$(CC) $^ -o $@ $(CFLAGS) $(LIBS)

reverter: reverter.c
	$(CC) $^ -o $@ $(CFLAGS) $(LIBS)

clean:
	rm main reverter *~ 
