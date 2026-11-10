TARGET = jogo_rpg

CC = gcc
CFLAGS = -Wall -Wextra -I./include
LIBS = -lm

SRCS = src/main.c src/personagem.c src/mapa.c src/combate.c src/terminal.c

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)