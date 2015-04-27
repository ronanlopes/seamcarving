#include "Filtros.h"



//------------FUNÇÕES DE CÁLCULO DOS FILTROS------------------------------------

float CalculaIntensidade(Pixel matriz[3][3],int i, int j){
	return(0.3*matriz[i][j].R + 0.59*matriz[i][j].G + 0.11*matriz[i][j].B);
}

//------------------------------------------------------------------------------

float CalculaEnergiaPixel(Imagem imagem,int x, int y){
	int i,j,k,l,gx,gy;
	Pixel matriz[3][3];
	for (i=x-1,k=0;i<=x+1;i++,k++){
		for(j=y-1,l=0;j<=y+1;j++,l++){
			if (((i<0) && (j<0)) || ((i<0) && (j>=imagem.w)) || ((i>=imagem.h) && (j<0)) || ((i>=imagem.h) && (j>=imagem.w))){		//se a energia resultar em erro(s) olhar essa função, especialmente essa linha
				matriz[k][l]=imagem.matriz[x][y];
			}
			else if ((i<0)||(i>=imagem.h)||(j<0)||(j>=imagem.w)){
				if ((i<0)||(i>=imagem.h)){
					matriz[k][l]=imagem.matriz[x][j];
				}
				else if ((j<0)||(j>=imagem.w)){
					matriz[k][l]=imagem.matriz[i][y];
				}
			}
			else{
				matriz[k][l]=imagem.matriz[i][j];
			}
		}
	}
	gx = (-1*CalculaIntensidade(matriz,0,0))+(CalculaIntensidade(matriz,0,2))+
	     (-2*CalculaIntensidade(matriz,1,0))+(2*CalculaIntensidade(matriz,1,2))+
	     (-1*CalculaIntensidade(matriz,2,0))+(CalculaIntensidade(matriz,2,2));

	gy = (-1*CalculaIntensidade(matriz,0,0))+(-2*CalculaIntensidade(matriz,0,1))+
	     (-1*CalculaIntensidade(matriz,0,2))+(CalculaIntensidade(matriz,2,0))+
	     (2*CalculaIntensidade(matriz,2,1))+(CalculaIntensidade(matriz,2,2));

	return(sqrt((gx*gx)+(gy*gy)));
}

//------------------------------------------------------------------------------
