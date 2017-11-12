#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/Olho.h"


int main(){
	char * caminhoImagem = "../imagens/Normal.ppm";

	Olho * teste;
	teste = leituraImagem(caminhoImagem);

	return 0;
}

