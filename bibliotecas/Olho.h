#ifndef OLHO_H
#define OLHO_H
#include "Structs.h"

Olho * leituraImagem(char * file);
Olho * escalaCinza(Olho * imagemOlho);
void salvarImagem(Olho * imagemOlho, char * nome);
Olho * criarImagem(Olho * imagemOlho);
Pixel * leituraPixel( Olho * imagem, int coluna, int linha );
Olho * filtroGaussiano(Olho * imagem);
Olho * filtroSobel(Olho * imagemOlho);
Olho * binarizacaoImagem(Olho * imagemOlho);
#endif
