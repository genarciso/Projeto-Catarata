#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/Filtro.h"


int main(){
	char * caminhoImagem = "../imagens/Catarata.ppm";
	
	Olho * imagem = leituraImagem(caminhoImagem);
	
	
	Olho * escaladoCinza = escalaCinza(imagem);
	
	Olho * filtroGauss = filtroGaussiano(escaladoCinza);

	Olho * filtroSobelImagem = filtroSobel(filtroGauss);

	Olho * binarizacao = binarizacaoImagem(filtroSobelImagem);

	Olho * circuloPupilaCinza = circuloPupila(escaladoCinza,binarizacao, 1);

	Olho * circuloPupilaRGB = circuloPupila(imagem,binarizacao,1);

	salvarImagem(escaladoCinza,"escalaCinza.ppm");
	salvarImagem(filtroGauss,"filtroGauss.ppm");
	salvarImagem(filtroSobelImagem,"filtroSobel.ppm");
	salvarImagem(binarizacao, "binarizada.ppm");
	salvarImagem(circuloPupilaCinza,"circuloPupilaCinza.ppm");
	salvarImagem(circuloPupilaRGB,"circuloPupilaRGB.ppm");

	free(imagem);
	free(escaladoCinza);
	free(filtroGauss);
	free(filtroSobelImagem);
	free(binarizacao);
	free(circuloPupilaCinza);
	free(circuloPupilaRGB);

	return 0;
}

