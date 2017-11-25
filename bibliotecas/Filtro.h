#ifndef FILTRO_H
#define FILTRO_H

#include "Generico.h"

Olho * leituraImagem(char * file);
Olho * escalaCinza(Olho * imagemOlho);
Olho * filtroGaussiano(Olho * imagemOlho);
Olho * filtroSobel(Olho * imagemOlho);
Olho * binarizacaoImagem(Olho * imagemOlho);


#endif