#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../bibliotecas/Structs.h"

void leituraComentarios(FILE * imagem){
	
	char caractere = fgetc(imagem);
	
	while(caractere == '#'){
		if(caractere == '#'){
			while(caractere != '\n'){
				caractere = fgetc(imagem);
			}
		}
		else{
			ungetc(caractere, imagem);
			caractere = fgetc(imagem);
		}
	}
	ungetc(caractere, imagem);
}

Olho * criarImagem(Olho * imagemOlho){
	Olho * novaImagem;
    novaImagem = malloc(sizeof(Olho));
	
    novaImagem->largura = imagemOlho->largura;
	novaImagem->altura = imagemOlho->altura;
	novaImagem->numeroMaximo = imagemOlho->numeroMaximo;
	strcpy(novaImagem->tipo, imagemOlho->tipo);
	
	novaImagem->imagem = (Pixel**) malloc(sizeof(Pixel*) * imagemOlho->altura);
	
	for(int i = 0; i< imagemOlho->largura; i++){
		novaImagem->imagem[i] = (Pixel*) malloc(sizeof(Pixel) * imagemOlho->largura);
	}

	return novaImagem;
}

Pixel * leituraPixel( Olho * imagem, int coluna, int linha ){
    if( coluna >= imagem->largura ) {
    	coluna = imagem->largura - 1;
    }
    if( linha >= imagem->altura ) {
    	linha = imagem->altura - 1;
    }
    if( coluna <= 0 ) {
    	coluna = 0;
    }
    if( linha <= 0 ) {
    	linha = 0;
    }
    return &imagem->imagem[linha][coluna];
}

// Esse método recebe um dado do tipo olho e um char que represente um nome e salva essa imagem de olho em um arquivo ppm nomeado pelo nome dado.
void salvarImagem(Olho * imagemOlho, char * nome){

	FILE * imagem;
	char * caminho;

	caminho = malloc(sizeof(char) * 50);
	strcpy(caminho, "../imagens/");
	strcat(caminho, nome );
	
	imagem = fopen(caminho, "w");
	
	if (imagem == NULL){
		printf("Falha ao abrir o arquivo!\n");
	}
	else{
		fprintf(imagem, "%s\n", imagemOlho->tipo);
		fprintf(imagem, "%d %d\n",imagemOlho->largura,imagemOlho->altura);
		fprintf(imagem, "%d\n", imagemOlho->numeroMaximo);
	
		for(int i = 0; i < imagemOlho->altura; i++){
			for(int j = 0; j < imagemOlho->largura; j++){
				fprintf(imagem,"%d\n",imagemOlho->imagem[i][j].r);
				fprintf(imagem,"%d\n",imagemOlho->imagem[i][j].g);
				fprintf(imagem,"%d\n",imagemOlho->imagem[i][j].b);
		
			}
		}
	}
	fclose(imagem);
}