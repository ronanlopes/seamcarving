CC = gcc
CFLAGS = -g
CFLAGSAFTER= -lm
OBJS = Funcoes.o ProgramacaoDinamica.o Grafo.o Filtros.o tp2.o
TARGET = tp2

all: $(TARGET)

tp2: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o tp2 $(CFLAGSAFTER)

tp2.o: tp2.c Funcoes.h ProgramacaoDinamica.h Grafo.h Filtros.h
	$(CC) $(CFLAGS) -c tp2.c

Funcoes.o: Funcoes.c Funcoes.h
	$(CC) $(CFLAGS) -c Funcoes.c

ProgramacaoDinamica.o: ProgramacaoDinamica.c ProgramacaoDinamica.h Funcoes.c Funcoes.h Filtros.c Filtros.h
	$(CC) $(CFLAGS) -c ProgramacaoDinamica.c

Grafo.o: Grafo.c Grafo.h Funcoes.c Funcoes.h Filtros.c Filtros.h
	$(CC) $(CFLAGS) -c Grafo.c

Filtros.o: Filtros.c Filtros.h Funcoes.c Funcoes.h
	$(CC) $(CFLAGS) -c Filtros.c

clean:
	rm -rf *.o $(TARGET)

run:
	./$(TARGET)
