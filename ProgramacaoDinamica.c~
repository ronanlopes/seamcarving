#include "ProgramacaoDinamica.h"


//------------FUNÇÕES DA PROGRAMAÇÃO DINÂMICA------------------------------------------------------------------

/*
* Aloca a tabela que será usada para os cálculos da programação Dinâmica
*/
void CriaTabela(CelulaDinamica ***Tabela, int w,int h,Imagem imagem){
	int i,j;
	(*Tabela)=(CelulaDinamica**) malloc(h*(sizeof(CelulaDinamica*)));		//alocando dinamicamente
	for (i=0;i<h;i++){
		(*Tabela)[i]=(CelulaDinamica*) malloc(w*sizeof(CelulaDinamica));
	}

	for (i=0;i<h;i++){								//inserindo a energia dos pixels na tabela.
		for (j=0;j<w;j++){
			(*Tabela)[i][j].energia=CalculaEnergiaPixel(imagem,i,j);
			(*Tabela)[i][j].coluna=j;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------

/*
* Calcula o menor dos valores dos três pixels acima para ser somado com o valor 
* atual na tabela
*/
void minimo(CelulaDinamica **Tabela,int i,int j,int width,float *min, int *coluna){
	
	int cont;
	*min=123123123;		//a energia minima recebe um valor gigantesco.

	for (cont=j-1;cont<=j+1;cont++){				//o loop percorre os 3 valores da posição em questão da tabela para escolher o menor.
		if ((cont>=0)&&(cont<=(width-1))){			//verifica se ultrapassou as bordas da tabela.
			if (Tabela[i-1][cont].energia<*min){
				*min=Tabela[i-1][cont].energia;
				*coluna=cont;
			}
		}
	}
	/*if (j==0){
		if (Tabela[i-1][j].energia<Tabela[i-1][j+1].energia){
			*min=Tabela[i-1][j].energia;
			*coluna=j;
		}
		else{
			*min=Tabela[i-1][j+1].energia;
			*coluna=j+1;
		}
	}
	else if (j==width-1){
		if (Tabela[i-1][j-1].energia<Tabela[i-1][j].energia){
			*min=Tabela[i-1][j-1].energia;
			*coluna=j-1;
		}
		else{
			*min=Tabela[i-1][j].energia;
			*coluna=j;
		}
	}
	else{
		if ((Tabela[i-1][j-1].energia<Tabela[i-1][j].energia) && (Tabela[i-1][j-1].energia<Tabela[i-1][j+1].energia)){
			*min=Tabela[i-1][j-1].energia;
			*coluna=j-1;
		}
		else if (Tabela[i-1][j].energia<Tabela[i-1][j+1].energia){
			*min=Tabela[i-1][j-1].energia;
			*coluna=j;
		}
		else{
			*min=Tabela[i-1][j+1].energia;
			*coluna=j+1;
		}
	}*/
}

//-------------------------------------------------------------------------------------------------------------
/*
* Função que trás a solução por Programação Dinâmica.
*/
void ProgramacaoDinamica(Imagem *imagem, int qtd){
	CelulaDinamica **Tabela;			//tabela auxiliar p/ a programacao dinâmica
	CriaTabela(&Tabela,(*imagem).w,(*imagem).h,(*imagem));			//funcao para criar a tabela
	Imagem imagemaux;
	int i,j,width,height,aux,k,l;

	float min;
	width = (*imagem).w;
	height = (*imagem).h;

	while (qtd>0){
		printf("%d\n",qtd);

		//com esses 2 for, calculamos a energia dinamicamente.
		aux=0;
		for (i=1;i<(*imagem).h;i++){			//começa de 1, pois a primeira não é necessário verificar
			for (j=0;j<(*imagem).w;j++){
				minimo(Tabela,i,j,(*imagem).w,&min,&Tabela[i][j].coluna);
				Tabela[i][j].energia+=min;
				if (i==((*imagem).h-1)){
					if (Tabela[i][j].energia<Tabela[i][aux].energia){
						aux=j;
					}
				}
			}
		}

		//pega a menor das energias calculadas dinamicamente. Ou seja, pega o fim do caminho com menos energia.
		i=height-1;

		//volta marcando as células a serem removidas.
		j=aux;
		while (i>=0){
			k=j;
			j=Tabela[i][j].coluna;		//pego a coluna da linha anterior
			for (l=k;l<width-1;l++){
				Tabela[i][l]=Tabela[i][l+1];
				(*imagem).matriz[i][l]=(*imagem).matriz[i][l+1];
			}
			i--;				//pego a linha anterior.
		}
		width--;
		(*imagem).w--;


		for (i=0;i<height;i++){
			for (j=0;j<width;j++){
				Tabela[i][j].energia=CalculaEnergiaPixel((*imagem),i,j);
				Tabela[i][j].coluna=j;
			}
		}

		qtd--;
	}
}

//-------------------------------------------------------------------------------------------------------------
