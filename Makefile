principal: arquivos/Generico.o arquivos/Filtros.o
	gcc arquivos/Principal.c  arquivos/Generico.o arquivos/Filtros.o -lm  -o arquivos/catarata -ggdb
	
Filtro.o:
	gcc arquivos/Filtros.c -c -o arquivos/Filtros.o -ggdb

Generico.o:
	gcc arquivos/Generico.c -c -o arquivos/Generico.o -ggdb


clean:
	rm arquivos/*.o
	rm arquivos/catarata
