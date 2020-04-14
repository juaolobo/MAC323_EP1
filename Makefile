CFLAGS = -Wall -g -O0
CC = g++
OBJS = tabeladesimbolos.o util.o unit_test.o vetorDes.o vetorOrd.o listaDes.o listaOrd.o arvoreBin.o treap.o arvore23.o arvoreRN.o
RM = rm


unit_test : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o unit_test -lm
	
%.o : %.cpp tabeladesimbolos.hpp
	$(CC) $(CFLAGS) -c $<

clean :
	$(RM) *.o
