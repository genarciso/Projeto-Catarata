#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/Structs.h"
Olho * leituraImagem(char * file){
	FILE * imagem;

	imagem = fopen(file, "rw");


	if (imagem == NULL){
		printf("Falha ao abrir o arquivo!\n");

	}
	else{
		char formato[3];
		Olho * dadosOlho = malloc(sizeof(Olho));
		fscanf(imagem, "%s", formato);
		dadosOlho->tipo = formato;
		printf("%s\n",dadosOlho->tipo);	
		return dadosOlho;	
	
	}

}




