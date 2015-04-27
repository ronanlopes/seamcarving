#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Funcoes.h"
#include "Filtros.h"

#ifndef PROGRAMACAODINAMICA_H
#define PROGRAMACAODINAMICA_H

typedef struct CelulaDinamica{
	float energia;		//energia acumulada dos pixels
	int coluna;			//de qual célula veio essa energia
}CelulaDinamica;


//------------------------------------------------------------------------------

void CriaTabela(CelulaDinamica ***Tabela, int w,int h,Imagem imagem);

//------------------------------------------------------------------------------

void minimo(CelulaDinamica **Tabela,int i,int j,int width,float *min, int *coluna);

//------------------------------------------------------------------------------

void ProgramacaoDinamica(Imagem *imagem, int qtd);

#endif
