#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/Olho.h"


int main(){
	char * caminhoImagem = "../imagens/Normal.ppm";
	Olho * imagem = leituraImagem(caminhoImagem);	
	Olho * escalaDeCinza = escalaCinza(imagem);
	salvarImagem(escalaDeCinza,"escalaCinza.ppm");
	free(imagem);
	free(escalaDeCinza);
	return 0;
}

