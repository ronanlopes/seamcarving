#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Funcoes.h"

#ifndef FILTROS_H
#define FILTROS_H

//------------------------------------------------------------------------------

float CalculaIntensidade(Pixel matriz[3][3],int i, int j);

//------------------------------------------------------------------------------

float CalculaEnergiaPixel(Imagem imagem,int x, int y);

#endif
