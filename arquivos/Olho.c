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
		char formato[3];
		int altura = 0, comprimento = 0;
		int numeroMaximo;

		Olho * dadosOlho = malloc(sizeof(Olho));
		fscanf(imagem, "%s\n", formato);
		strcpy(dadosOlho->tipo, formato);
		
		fscanf(imagem, "%i %i\n",&comprimento,&altura);
		
		dadosOlho->altura = altura;
		dadosOlho->largura = comprimento;
		
		fscanf(imagem,"%i\n",&numeroMaximo);
		dadosOlho->numeroMaximo = numeroMaximo;
				
		dadosOlho->imagem =(Pixel**)malloc(sizeof(Pixel*) * altura);
		for(int i = 0; i<altura; i++){
			dadosOlho->imagem[i] =(Pixel*)malloc(sizeof(Pixel) * comprimento);
		} 
		
		for(int i = 0; i < altura; i++){
			for(int j = 0; j < comprimento; j++){
				fscanf(imagem,"%i\n",&dadosOlho->imagem[i][j].r);
				fscanf(imagem,"%i\n",&dadosOlho->imagem[i][j].g);
				fscanf(imagem,"%i\n",&dadosOlho->imagem[i][j].b);
			}
		}
		printf("%s\n", dadosOlho->tipo);
		printf("%d %d\n", dadosOlho->largura, dadosOlho->altura);
			
		fclose(imagem);
		return dadosOlho;	
	}
}

Olho * escalaCinza(Olho * imagemOlho){
	int vermelho = 0;
	int azul = 0;
	int verde = 0;
	Olho * novaImagem;
	
	novaImagem = malloc(sizeof(Olho));
	novaImagem->imagem =(Pixel**)malloc(sizeof(Pixel*) * imagemOlho->altura);
	for(int i = 0; i< imagemOlho->largura; i++){
		novaImagem->imagem[i] =(Pixel*)malloc(sizeof(Pixel) * imagemOlho->largura);
	}
	
	strcpy(novaImagem->tipo, imagemOlho->tipo);
	novaImagem->largura = imagemOlho->largura;
	novaImagem->altura = imagemOlho->altura;
	novaImagem->numeroMaximo = imagemOlho->numeroMaximo;
	
	for(int i = 0; i < imagemOlho->altura; i++){
		for(int j = 0; j < imagemOlho->largura; j++){
			novaImagem->imagem[i][j].r = (imagemOlho->imagem[i][j].r)*0.3 + (imagemOlho->imagem[i][j].g)*0.59 + (imagemOlho->imagem[i][j].b)*0.11;	
			
			if (novaImagem->imagem[i][j].r > 255){
				novaImagem->imagem[i][j].r = 255;
			}
			novaImagem->imagem[i][j].g = novaImagem->imagem[i][j].r;
			novaImagem->imagem[i][j].b = novaImagem->imagem[i][j].r;
		}
	}
	printf("%s\n", novaImagem->tipo);
	printf("%d %d\n", novaImagem->largura, novaImagem->altura);
	return novaImagem;
}

void salvarImagem(Olho * imagemOlho, char * nome){
	int i, j;
	FILE * imagem;
	char *caminho;
	caminho = malloc(sizeof(char) * 50);
	strcpy(caminho, "../imagens/");
	strcat(caminho, nome );
	//printf("%s", nome);
	imagem = fopen(caminho, "w");
	
	if (imagem == NULL){
		printf("Falha ao abrir o arquivo!\n");
	}
	else{
		printf("%s\n", imagemOlho->tipo);
		printf("%d %d\n", imagemOlho->largura, imagemOlho->altura);
		fprintf(imagem, "%s\n", imagemOlho->tipo);
		fprintf(imagem, "%d %d\n",imagemOlho->largura,imagemOlho->altura);
		fprintf(imagem, "%d\n", imagemOlho->numeroMaximo);
	
		for(i = 0; i < imagemOlho->altura; i++){
			for(j = 0; j < imagemOlho->largura; j++){
				fprintf(imagem,"%d\n",imagemOlho->imagem[i][j].r);
				fprintf(imagem,"%d\n",imagemOlho->imagem[i][j].g);
				fprintf(imagem,"%d\n",imagemOlho->imagem[i][j].b);
		
			}
		}
	}
	fclose(imagem);
}

