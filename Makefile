principal: arquivos/Olho.o 
	gcc arquivos/Principal.c arquivos/Olho.o -lm  -o arquivos/catarata -ggdb
	
Olho.o: arquivos/Olho.c
	gcc arquivos/Olho.c -c -lm -o arquivos/Olho.o -ggdb
	
clean:
	rm arquivos/*.o
	rm arquivos/catarata
