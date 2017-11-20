#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/Olho.h"


int main(){
	char * caminhoImagem = "../imagens/Normal.ppm";

	Olho * imagem = leituraImagem(caminhoImagem);

	Olho * escaladoCinza = escalaCinza(imagem);

	Olho * filtroGauss = filtroGaussiano(escaladoCinza);

	salvarImagem(escaladoCinza,"escalaCinza.ppm");
	salvarImagem(filtroGauss,"filtroGauss.ppm");

	free(imagem);
	free(escaladoCinza);
	free(filtroGauss);

	return 0;
}

