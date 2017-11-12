#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/Structs.h"
Olho * leituraImagem(char * file){
	FILE * imagem;

	imagem = fopen(file, "r");


	if (imagem == NULL){
		printf("Falha ao abrir o arquivo!\n");

	}
	else{
		Olho * dadosOlho;
		
		fscanf(imagem, "%s", dadosOlho->tipo);
		printf("%s\n",teste);		
		return dadosOlho;
	
	}




}




