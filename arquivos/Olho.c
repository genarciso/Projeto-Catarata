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

// Esse método recebe um dado do tipo ponteiro para Olho e retorna um outro ponteiro de Olho com o a transformação da imagem do olho recebida no parâmetro para a escala de cinza.
Olho * escalaCinza(Olho * imagemOlho){
	int vermelho = 0;
	int azul = 0;
	int verde = 0;

	Olho * novaImagem;
	novaImagem = malloc(sizeof(Olho));
	novaImagem = criarImagem(imagemOlho);

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

Olho * filtroGaussiano(Olho * imagemOlho){
	int novoPixel;
	Pixel * pixel;
	int soma,divisao;

	int mascara[5][5] = {{ 2,  4,  5,  4, 2 },
                        { 4,  9, 12,  9, 4 },
                        { 5, 12, 15, 12, 5 },
                        { 4,  9, 12,  9, 4 },
                        { 2,  4,  5,  4, 2 }};

    Olho * novaImagem;
    novaImagem = malloc(sizeof(Olho));
    novaImagem = criarImagem(imagemOlho);

    for (int linha = 0; linha < imagemOlho->altura; ++linha){
    	for (int coluna = 0; coluna < imagemOlho->largura; ++coluna){
    		soma = 0;
    		divisao = 0;
    		for (int i = 0; i < 5; ++i){
    			for (int j = 0; j < 5; ++j){
    			 	pixel = leituraPixel(imagemOlho, coluna + (j-2), linha + (i-2));
    				soma += ( pixel->r *  mascara[i][j] );
                    divisao += mascara[i][j];
    			}
    		}
    		novoPixel = soma/divisao;
    		//printf("%i\n",novaImagem->imagem[linha][coluna].r);
    		novaImagem->imagem[linha][coluna].r = novoPixel;
    		novaImagem->imagem[linha][coluna].g = novoPixel;
    		novaImagem->imagem[linha][coluna].b = novoPixel;
    	}
    }
    return novaImagem;
}

Olho * filtroSobel(Olho * imagemOlho){
	// int mascaraVertical[3][3] = {{ 1, 0, (-1)},
	// 							{ 2, 0, (-2) },
	// 							{ 1, 0, (-1) }};

	// int mascaraVertical[3][3] = {{ 1, 2, 1 },
	// 							{ 0, 0, 0 },
	// 							{ -1, -2, -1 }};

	Olho * novaImagem;
	novaImagem = malloc(sizeof(Olho));
	novaImagem = criarImagem(imagemOlho);

	int novoPixel;
	Pixel ** pixelsVerticais;
	Pixel ** pixelsHorizontais;

	pixelsVerticais = (Pixel**) malloc(sizeof(Pixel*) * imagemOlho->altura);
	pixelsHorizontais = (Pixel**) malloc(sizeof(Pixel*) * imagemOlho->altura);
	for(int i = 0; i< imagemOlho->largura; i++){
		pixelsVerticais[i] = (Pixel*) malloc(sizeof(Pixel) * imagemOlho->largura);
		pixelsHorizontais[i] = (Pixel*) malloc(sizeof(Pixel) * imagemOlho->largura);
	}

	for (int i = 1; i < imagemOlho->altura-1; ++i){
		for (int j = 1; j < imagemOlho->largura-1; ++j){
			pixelsVerticais[i][j].r = (1)*imagemOlho->imagem[i-1][j-1].r + (2)*imagemOlho->imagem[i-1][j].r + (1)*imagemOlho->imagem[i-1][j+1].r +
									(0)*imagemOlho->imagem[i][j-1].r + (0)*imagemOlho->imagem[i][j].r + (0)*imagemOlho->imagem[i][j+1].r +
									(-1)*imagemOlho->imagem[i+1][j-1].r + (-2)*imagemOlho->imagem[i+1][j].r + (-1)*imagemOlho->imagem[i+1][j+1].r;

			pixelsHorizontais[i][j].r = (-1)*imagemOlho->imagem[i-1][j-1].r + 0*imagemOlho->imagem[i-1][j].r + (1)*imagemOlho->imagem[i-1][j+1].r +
									(-2)*imagemOlho->imagem[i][j-1].r + 0*imagemOlho->imagem[i][j].r + (2)*imagemOlho->imagem[i][j+1].r +
									(-1)*imagemOlho->imagem[i+1][j-1].r + (0)*imagemOlho->imagem[i+1][j].r + (1)*imagemOlho->imagem[i+1][j+1].r;
			
		}
	}

	for (int i = 0; i < imagemOlho->altura; ++i){
		for (int j = 0; j < imagemOlho->largura; ++j){
		novoPixel = pixelsVerticais[i][j].r;
		novaImagem->imagem[i][j].r = novoPixel;
		novaImagem->imagem[i][j].g = novoPixel;
		novaImagem->imagem[i][j].b = novoPixel;
		}
	}

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


