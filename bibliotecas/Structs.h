#ifndef STRUCTS_H
#define STRUCTS_H
// O registro Pixel é responsável por conter os dados de cor de cada pixel da imagem que será lida. Sabendo disso, seus dados são apenas três inteiros que representem os tons do pixel: tons de vermelho, verde e azul da escala RGB.
typedef struct{
	int r;
	int g;
	int b;

} Pixel;
// O registro Olho é responsável por conter os dados da imagem do olho. Seus dados dados são: um inteiro representando a altura da imagem e outro a largura, um ponteiro de ponteiro do tipo Pixel que será o conjunto de pixel da imagem do olho, um vetor de char para indicar o tipo do arquivo e um inteiro que representa a maior escala do arquivo. 
typedef struct{
	int altura;
	int largura;
	Pixel ** imagem;
	char tipo[3];
	int numeroMaximo;
} Olho;

#endif
