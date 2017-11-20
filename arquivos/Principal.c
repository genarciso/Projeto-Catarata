#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/Olho.h"


int main(){
	char * caminhoImagem = "../imagens/Normal.ppm";

	Olho * imagem = leituraImagem(caminhoImagem);

	Olho * escaladoCinza = escalaCinza(imagem);

	Olho * filtroGauss = filtroGaussiano(escaladoCinza);

	Olho * filtroSobelImagem = filtroSobel(filtroGauss);

	salvarImagem(escaladoCinza,"escalaCinza.ppm");
	salvarImagem(filtroGauss,"filtroGauss.ppm");
	salvarImagem(filtroSobelImagem,"filtroSobel.ppm");

	free(imagem);
	free(escaladoCinza);
	free(filtroGauss);
	free(filtroSobelImagem);

	return 0;
}

