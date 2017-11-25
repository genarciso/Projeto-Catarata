#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/Filtro.h"


int main(){
	char * caminhoImagem = "../imagens/Catarata2.ppm";
	
	Olho * imagem = leituraImagem(caminhoImagem);
	
	
	Olho * escaladoCinza = escalaCinza(imagem);
	
	Olho * filtroGauss = filtroGaussiano(escaladoCinza);

	Olho * filtroSobelImagem = filtroSobel(filtroGauss);

	Olho * binarizacao = binarizacaoImagem(filtroSobelImagem);


	salvarImagem(escaladoCinza,"escalaCinza.ppm");
	salvarImagem(filtroGauss,"filtroGauss.ppm");
	salvarImagem(filtroSobelImagem,"filtroSobel.ppm");
	salvarImagem(binarizacao, "binarizada.ppm");

	free(imagem);
	free(escaladoCinza);
	free(filtroGauss);
	free(filtroSobelImagem);
	free(binarizacao);

	return 0;
}

