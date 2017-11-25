#ifndef GENERICO_H
#define GENERICO_H

#include "Structs.h"

void leituraComentarios(FILE * imagem);
Olho * criarImagem(Olho * imagemOlho);
Pixel * leituraPixel( Olho * imagem, int coluna, int linha );
void salvarImagem(Olho * imagemOlho, char * nome);

#endif