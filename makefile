test: cmdparser.o test.o
	gcc -Wall test.o cmdparser.o -o Grupo2_CMDParser

cmdparser.o: cmdparser.c cmdparser.h
	gcc -c -Wall cmdparser.c

test.o:
	gcc -c -Wall test.c
#####################################
clean:
	rm *.o
clean_all:
	rm *.o
	rm Grupo2_CMDParser