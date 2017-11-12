#ifndef STRUCTS_H
#define STRUCTS_H
typedef struct{
	int r;
	int g;
	int b;

} Imagem;

typedef struct{
	int altura;
	int largura;
	Imagem ** imagem;
	char * tipo;
} Olho;

#endif
