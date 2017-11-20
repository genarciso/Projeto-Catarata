#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
// Esse método é responsável por fazer a leitura da imagem; retornando um ponteiro do tipo Olho que será, em si, a imagem.
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
		
		leituraComentarios(imagem);
		fscanf(imagem, "%s\n", formato); 						
		
		leituraComentarios(imagem);
		fscanf(imagem, "%i %i\n",&comprimento,&altura);
		
		strcpy(dadosOlho->tipo, formato);
		dadosOlho->altura = altura;
		dadosOlho->largura = comprimento;
		
		leituraComentarios(imagem);		
		fscanf(imagem,"%i\n",&numeroMaximo);

		dadosOlho->numeroMaximo = numeroMaximo;
				
		dadosOlho->imagem =(Pixel**)malloc(sizeof(Pixel*) * altura);
		for(int i = 0; i<altura; i++){
			dadosOlho->imagem[i] =(Pixel*)malloc(sizeof(Pixel) * comprimento);
		} 
		
		for(int i = 0; i < altura; i++){
			for(int j = 0; j < comprimento; j++){
				//leituraComentarios(imagem);
				fscanf(imagem,"%i\n",&dadosOlho->imagem[i][j].r);
				//leituraComentarios(imagem);
				fscanf(imagem,"%i\n",&dadosOlho->imagem[i][j].g);
				//leituraComentarios(imagem);
				fscanf(imagem,"%i\n",&dadosOlho->imagem[i][j].b);
			}
		}	
		fclose(imagem);
		return dadosOlho;	
	}
}


// Esse método recebe um dado do tipo ponteiro para Olho e retorna um outro ponteiro de Olho com o a transformação da imagem do olho recebida no parâmetro para a escala de cinza.
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
	// printf("%s\n", novaImagem->tipo);
	// printf("%d %d\n", novaImagem->largura, novaImagem->altura);
	return novaImagem;
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


