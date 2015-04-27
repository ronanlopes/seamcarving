#include <stdio.h>
#include <stdlib.h>
#include "Funcoes.h"
#include "Filtros.h"
#define infinito 274886			//maior valor do int, a energia nunca alcançará esse número

#ifndef GRAFOS_H
#define GRAFOS_H

typedef struct Celula *Ponteiro;
typedef struct Celula{
	int vertice;
	float peso;
	Ponteiro prox;
}Celula;
typedef struct TipoLista{
	Ponteiro inicio;
	Ponteiro fim;
	int antecessor;
	int x,y;
	int flag;
}TipoLista;
typedef struct TipoLista *PonteiroLista;
typedef struct TipoGrafo{
	PonteiroLista InicioLista;
	int numvertices;
}TipoGrafo;
typedef struct CelulaHeap *Heap;
typedef struct CelulaHeap{
	int vertice;
	float peso;
}CelulaHeap;



//------------------------------------------------------------------------------

void CriaGrafo(TipoGrafo *grafo, Imagem imagem,int alocar);

//------------------------------------------------------------------------------

void ImprimeGrafo(TipoGrafo grafo);

//------------------------------------------------------------------------------

void LiberaGrafo(TipoGrafo *grafo);

//------------------------------------------------------------------------------

void ProxAdj(int vertice, TipoGrafo grafo, int *adj, float *peso, Ponteiro *prox, int *FimListaAdj); 

//------------------------------------------------------------------------------

CelulaHeap retirarmenor(Heap heap,int *n,int *pos);

//------------------------------------------------------------------------------

//int DiminuiChave(int i, float peso, int *vetor, int *pos, int *p);

//------------------------------------------------------------------------------

void refazer(Heap heap, int esq,int dir,int *pos);

//------------------------------------------------------------------------------

void construir(Heap heap,int n,int *pos);

//------------------------------------------------------------------------------

void Dijkstra(TipoGrafo *grafo, Heap heap, int *pos,int n);

//------------------------------------------------------------------------------

void SolucaoGrafos(Imagem *imagem,int qtd);

//------------------------------------------------------------------------------
#endif
