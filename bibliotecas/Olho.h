#ifndef OLHO_H
#define OLHO_H
#include "Structs.h"

Olho * leituraImagem(char * file);
Olho * escalaCinza(Olho * imagemOlho);
void salvarImagem(Olho * imagemOlho, char * nome);

#endif
