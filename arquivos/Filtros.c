#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../bibliotecas/Generico.h"

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
	
	printf("\n");
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
    		if(novoPixel > 255){
    			novoPixel = 255;
    		}
    		novaImagem->imagem[linha][coluna].r = novoPixel;
    		novaImagem->imagem[linha][coluna].g = novoPixel;
    		novaImagem->imagem[linha][coluna].b = novoPixel;
    	}
    }
    return novaImagem;
}

Olho * filtroSobel(Olho * imagemOlho){
	 int mascaraHorizontal[3][3] = {{ (-1), 0, (1) },
									{ (-2), 0, (2) },
									{ (-1), 0, (1) }};

	 int mascaraVertical[3][3] = {{ (-1), (-2), (-1) },
	 							  { 0, 0, 0 },
								  { (1), (2), (1) }};

	Olho * novaImagem;
	novaImagem = malloc(sizeof(Olho));
	novaImagem = criarImagem(imagemOlho);

	int novoPixel;
	Pixel * pixel;

	int somaV, somaH;
	for (int linha = 0; linha < imagemOlho->altura; ++linha){
    	for (int coluna = 0; coluna < imagemOlho->largura; ++coluna){
    		somaV = 0;
    		somaH = 0;
    		for (int i = 0; i < 3; ++i){
    			for (int j = 0; j < 3; ++j){
    			 	pixel = leituraPixel(imagemOlho, coluna + (j-1), linha + (i-1));
    				somaV += ( pixel->r *  mascaraVertical[i][j] );
    				somaH += ( pixel->r *  mascaraHorizontal[i][j] );
    			}
    		}
    		novoPixel = sqrt(((somaV*somaV)+(somaH*somaH)));

    		if(novoPixel > 255){
    			novoPixel = 255;
    		}
    		novaImagem->imagem[linha][coluna].r = novoPixel;
    		novaImagem->imagem[linha][coluna].g = novoPixel;
    		novaImagem->imagem[linha][coluna].b = novoPixel;
    	}
    }

	return novaImagem;

}

Olho * binarizacaoImagem(Olho * imagemOlho){
	Olho * novaImagem;
	novaImagem = malloc(sizeof(Olho));
	novaImagem = criarImagem(imagemOlho);
	novaImagem->numeroMaximo = 1;

	int limiar = 18;
	for (int i = 0; i < imagemOlho->altura; ++i){
		for (int j = 0; j < imagemOlho->largura; ++j){
			if(imagemOlho->imagem[i][j].r > limiar){
				novaImagem->imagem[i][j].r = 1;
				novaImagem->imagem[i][j].g = 1;
				novaImagem->imagem[i][j].b = 1;
			}
			else{
				novaImagem->imagem[i][j].r = 0;
				novaImagem->imagem[i][j].g = 0;
				novaImagem->imagem[i][j].b = 0;
			}
		}
	}

	return novaImagem;

}

Olho * circuloPupila(Olho * imagemOlho, int * vetorCoordenada){
	int x = vetorCoordenada[0];
	int y = vetorCoordenada[1];
	int raio = vetorCoordenada[2] + vetorCoordenada[3];
	
	Olho * novaImagem;
	novaImagem = malloc(sizeof(Olho));
	novaImagem = criarImagem(imagemOlho);

	for (int i = 0; i < imagemOlho->altura; ++i){
		for (int j = 0; j < imagemOlho->largura; ++j){
			novaImagem->imagem[i][j].r = imagemOlho->imagem[i][j].r;
			novaImagem->imagem[i][j].g = imagemOlho->imagem[i][j].g;
			novaImagem->imagem[i][j].b = imagemOlho->imagem[i][j].b;
		}
	}

	
	float tabelaSin[361];
	float tabelaCos[361];
	for (int i = 0; i <= 360; ++i)
	{
		tabelaCos[i] = cos(i*M_PI/180);
		tabelaSin[i] = sin(i*M_PI/180);
	}
		
	for (int i=0; i <= 360; i++){
        int posicaoX = (int) x - raio*tabelaCos[i];
		int posicaoY = (int) y - raio*tabelaSin[i];
		if(posicaoX >= 0 && posicaoY >= 0){
			novaImagem->imagem[posicaoX][posicaoY].r=255;
        	novaImagem->imagem[posicaoX][posicaoY].g=0;
        	novaImagem->imagem[posicaoX][posicaoY].b=0;	
		}
    }
    //printf("%d\t%d\t%d\t%d\n",vetorCoordenada[0],vetorCoordenada[1],vetorCoordenada[2],vetorCoordenada[3] );
    return novaImagem;
}

Olho * imagemSegmentada(Olho * imagemOlho, int * vetorCoordenada){	
	int raio = vetorCoordenada[2] + vetorCoordenada[3];
	int diametro = raio * raio;

	Olho * novaImagem;
	novaImagem = malloc(sizeof(Olho));
	novaImagem->altura = diametro + 100;
	novaImagem->largura = diametro + 100;
	novaImagem->numeroMaximo = 255;
	strcpy(novaImagem->tipo,"P3");

	




}

