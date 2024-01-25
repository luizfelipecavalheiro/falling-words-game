CC = gcc
CFLAGS = -lm

DEPS = tecla.h tela.h

all: falling-words

falling-words: falling-words.o funcoes.o tela.o tecla.o
	$(CC) $(CFLAGS) falling-words.o funcoes.o tela.o tecla.o -o falling-words

falling-words.o: falling-words.c funcoes.h
	$(CC) $(CFLAGS) -c falling-words.c

funcoes.o: funcoes.c funcoes.h tela.h tecla.h
	$(CC) $(CFLAGS) -c funcoes.c

tela.o: tela.c tela.h
	$(CC) $(CFLAGS) -c tela.c

tecla.o: tecla.c tecla.h
	$(CC) $(CFLAGS) -c tecla.c

clean:
	rm -f falling-words.o funcoes.o tela.o tecla.o falling-words

