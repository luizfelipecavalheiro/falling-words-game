CC = gcc
CFLAGS = -lm

ifeq ($(OS),Windows_NT)
    TARGET_EXT = .exe
    RM = del /Q
else
    TARGET_EXT =
    RM = rm -f
endif

all: falling-words$(TARGET_EXT)

falling-words$(TARGET_EXT): falling-words.o funcoes.o tela.o tecla.o
	$(CC) $(CFLAGS) falling-words.o funcoes.o tela.o tecla.o -o falling-words$(TARGET_EXT)

falling-words.o: falling-words.c funcoes.h
	$(CC) $(CFLAGS) -c falling-words.c

funcoes.o: funcoes.c funcoes.h tela.h tecla.h
	$(CC) $(CFLAGS) -c funcoes.c

tela.o: tela.c tela.h
	$(CC) $(CFLAGS) -c tela.c

tecla.o: tecla.c tecla.h
	$(CC) $(CFLAGS) -c tecla.c

run: falling-words$(TARGET_EXT)
	./falling-words$(TARGET_EXT)

clean:
	$(RM) falling-words.o funcoes.o tela.o tecla.o falling-words$(TARGET_EXT)

