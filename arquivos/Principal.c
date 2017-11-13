#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/Olho.h"


int main(){
	char * caminhoImagem = "../imagens/Normal.ppm";
	Olho * imagem = leituraImagem(caminhoImagem);
	
	Olho * escaladoCinza = escalaCinza(imagem);
	
	salvarImagem(escaladoCinza,"escalaCinza.ppm");
	
	return 0;
}

