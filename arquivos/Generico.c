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

int * transformadaHough(Olho * imagemOlho, int identificadorImagem){
	int raioMin;
	int raioMax;
	if(identificadorImagem == 1){
		raioMin = 82;
		raioMax = 83;	
	}
	else if (identificadorImagem == 2){
		raioMin = 146;
		raioMax = 148;
	}
	else if(identificadorImagem == 3){
		raioMin = 156;
		raioMax = 157;
	}
	else if(identificadorImagem == 4){
		raioMin = 68;
		raioMax = 70;
	}
	

	int *** matrizHough = (int ***) malloc(imagemOlho->altura * sizeof(int**));
	for (int i = 0; i < imagemOlho->altura; ++i){
		matrizHough[i] = (int **) malloc(imagemOlho->largura * sizeof(int*));
		for (int j = 0; j < imagemOlho->largura; ++j){
			matrizHough[i][j] = (int *) malloc((raioMax-raioMin+1) * sizeof(int));
		}	
	}

	for (int i = 0; i < imagemOlho->altura; ++i){
		for (int j = 0; j < imagemOlho->largura; ++j){
			for (int r = 0; r <= raioMax-raioMin; ++r){
				matrizHough[i][j][r] = 0;
			}
		}
	} 
	float tabelaSin[361];
	float tabelaCos[361];
	for (int i = 0; i <= 360; ++i)
	{
		tabelaCos[i] = cos(i*M_PI/180);
		tabelaSin[i] = sin(i*M_PI/180);
	}
	for (int i = 0; i < imagemOlho->altura; ++i){
		for (int j = 0; j < imagemOlho->largura; ++j){
			if (imagemOlho->imagem[i][j].r == 1){
				for (int r = raioMin; r <= raioMax; ++r){
					for (int t = 0; t <= 360; ++t){
						int aAux = (int) i - r*tabelaCos[t];
						int bAux = (int) j - r*tabelaSin[t];

						if( (aAux > 0) && (aAux < imagemOlho->altura) && (bAux > 0) && (bAux < imagemOlho->largura)){
							matrizHough[aAux][bAux][r-raioMin] += 1;

						}
					}
				}
			}	
		}
	}

	int vencedor = 0;
	for (int i = 0; i < imagemOlho->altura; ++i){
		for (int j = 0; j < imagemOlho->largura; ++j){
			for (int r = 0; r <= raioMax-raioMin; ++r){
				if (vencedor < matrizHough[i][j][r]){
					vencedor = matrizHough[i][j][r];
				}	
			}
		}
	}

	int * vetorCoordenadas;
	vetorCoordenadas = malloc(sizeof(int) * 4);
	for (int i = 0; i < imagemOlho->altura; ++i){
		for (int j = 0; j < imagemOlho->largura; ++j){
			for (int r = 0; r <= raioMax-raioMin; ++r){
				if(matrizHough[i][j][r] == vencedor){
					printf("%d\t%d\t%d\n",i,j,r );
					vetorCoordenadas[0] = i;
					vetorCoordenadas[1] = j;
					vetorCoordenadas[2] = r;
					vetorCoordenadas[3] = raioMin;
				}
			}
		}
	}
	printf("%d\n",vencedor );

	free(matrizHough);
	return vetorCoordenadas;

}
