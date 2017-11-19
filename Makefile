principal: arquivos/Olho.o 
	gcc arquivos/Principal.c arquivos/Olho.o -o arquivos/catarata
	
Olho.o: arquivos/Olho.c
	gcc arquivos/Olho.c -c -o arquivos/Olho.o
	
clean:
	rm arquivos/*.o
	rm arquivos/catarata
