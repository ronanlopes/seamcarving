#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#ifndef FUNCOES_H
#define FUNCOES_H

typedef struct Pixel{
	int R,G,B;		//codigo rgb da imagem
}Pixel;

typedef struct Imagem{
	Pixel **matriz;		//matriz com os pixels
	int w,h;		//dimensão da imagem.
}Imagem;

//------------------------------------------------------------------------------

void CriaImagem(Imagem *imagem,int w,int h);

//------------------------------------------------------------------------------

void imprimirarquivo(Imagem imagem, char stringmagica[3], int rgbint);

//------------------------------------------------------------------------------

void lernumero(FILE* arquivo, int *num);

//------------------------------------------------------------------------------

void pular(FILE* arquivo);

//------------------------------------------------------------------------------

Imagem transposta(Imagem imagem);

//------------------------------------------------------------------------------
void lerimagem (FILE* arquivo,Imagem *imagem, char *stringmagica, int *height, int *width, int *rgbint);

//------------------------------------------------------------------------------

#endif
