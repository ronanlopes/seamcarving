#include "Grafo.h"
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

void CriaGrafo(TipoGrafo *grafo, Imagem imagem,int alocar){		//passa o grafo, a imagem correspondente e se deve alocar o grafo ou não.
	//calcula numero de vertices
	(*grafo).numvertices=imagem.w*imagem.h;

	//aloca a lista de adjacencia
	if (alocar==1){
		(*grafo).InicioLista=(PonteiroLista) malloc(((*grafo).numvertices+2)*sizeof(TipoLista));
	}

	//declarando contadores
	int contvertice=1;
	int i;
	int j;
	int k;

	//percorrendo a matriz com os pixels
	Ponteiro aux;
	for (i=0;i<imagem.h;i++){
		for (j=0;j<imagem.w;j++){

			//se já existe o grafo, desaloca as listas existentes para alocar de novo.
			if (alocar!=1){
				while ((*grafo).InicioLista[contvertice].inicio!=NULL){
					aux=(*grafo).InicioLista[contvertice].inicio;
					(*grafo).InicioLista[contvertice].inicio=(*grafo).InicioLista[contvertice].inicio->prox;
					free(aux);
				}
			}

			//Inicializa a lista
			(*grafo).InicioLista[contvertice].inicio=(Ponteiro) malloc(sizeof(Celula));
			(*grafo).InicioLista[contvertice].fim=(*grafo).InicioLista[contvertice].inicio;

			//se não for a ultima linha(esta não tem arestas)
			if (i!=(imagem.h-1)){
				for (k=j-1;k<=j+1;k++){			//percorre os 3 vertices adjacentes do vertice em analise e os aloca na lista.
					if ((k!=-1) && (k!=imagem.w)){
						(*grafo).InicioLista[contvertice].fim->prox=(Ponteiro) malloc(sizeof(Celula));		//Cria nova celula
						(*grafo).InicioLista[contvertice].fim=(*grafo).InicioLista[contvertice].fim->prox;	//aponta o fim para a nova celula
						(*grafo).InicioLista[contvertice].fim->vertice=((i+1)*imagem.w)+k+1;			//calcula o vertice adjacente a partir do vertice em análise
						(*grafo).InicioLista[contvertice].fim->peso=CalculaEnergiaPixel(imagem,i+1,k);		//calcula o peso da aresta(energia do pixel adjacente)
						(*grafo).InicioLista[contvertice].fim->prox=NULL;					//aponta o proximo do fim para NULL
					}
				}
			}
			//grava dados do pixel em questão.
			(*grafo).InicioLista[contvertice].antecessor=-1;
			(*grafo).InicioLista[contvertice].x=i;
			(*grafo).InicioLista[contvertice].y=j;
			(*grafo).InicioLista[contvertice].flag=0;
			contvertice++;
		}
	}
}

void ConstruirHeap(TipoGrafo grafo, Heap heap, int *pos,Imagem imagem){
	int i;
	int n=grafo.numvertices;
	for (i=1;i<=grafo.numvertices;i++){
		if (i<=imagem.w){
			heap[i].peso=CalculaEnergiaPixel(imagem,0,i-1);
		}
		else{
			heap[i].peso=infinito;
		}
		heap[i].vertice=i;
		pos[i]=i;
	}
	construir(heap,n,pos);
}

void ProxAdj(int vertice, TipoGrafo grafo, int *verticeadj, float *peso, Ponteiro *aux, int *FimListaAdj){		//a partir de um adjacente
	if ((*aux)!=NULL){												//ele captura o próximo adjacente na lista de adjacencia
		(*verticeadj)=(*aux)->vertice;		//pega o vertice
		(*peso)=(*aux)->peso;			//pega o peso também
		(*aux)=(*aux)->prox;			//aponta para o proximo
		if ((*aux)==NULL){			//se for NULL FimListaAdj volta como NULL.
			*FimListaAdj=1;
		}
		else{
			*FimListaAdj=0;
		}
	}
}

Ponteiro PrimeiroListaAdj(int vertice, TipoGrafo grafo){	//pega o lista.inicio de um dado vertice
	return(grafo.InicioLista[vertice].inicio->prox);
}

int ListaAdjVazia(int vertice, TipoGrafo grafo){					//vê se o vertice não tem adjacentes.
	return(grafo.InicioLista[vertice].inicio==grafo.InicioLista[vertice].fim);
}

void ImprimeGrafo(TipoGrafo grafo){
	int i=0;
	Ponteiro aux;
	for (i=1;i<=9;i++){
		if (grafo.InicioLista[i].flag!=1){
			printf("i:%d\nx:%d,y:%d\n",i,grafo.InicioLista[i].x,grafo.InicioLista[i].y);
			aux=grafo.InicioLista[i].inicio->prox;
			printf("VERTICE: %d\n",i);
			while (aux!=NULL){
				printf("ADJ: %d PESO: %f\n",aux->vertice,aux->peso);
				aux=aux->prox;
			}
			printf("\n-----------------------------------\n");
		}
	}
}

void LiberaGrafo(TipoGrafo *grafo){
	int i;
	Ponteiro aux;
	for (i=1;i<=(*grafo).numvertices;i++){
		while ((*grafo).InicioLista[i].inicio!=NULL){
			aux=(*grafo).InicioLista[i].inicio;
			(*grafo).InicioLista[i].inicio=(*grafo).InicioLista[i].inicio->prox;
			free(aux);
		}
	}
	free((*grafo).InicioLista);
}

/*heap indireto

	O heap é indireto, ou seja, a organização do heap será dada pelo peso
dos elementos. Para isso são necessárias 2 vetores. Uma com o tipo abstrato heap
que tem o vértice e o peso. E outro com a posição do vertice no heap para acessar
com apenas um comando a verdadeira posição de um vértice "i" no heap.

*/
void refazer(Heap heap, int esq,int dir,int *pos){			//refazer o heap dado um valor a esquerda e outro a direita.
	int j=2*esq;
	CelulaHeap x = heap[esq];
	while (j<=dir){
		if (j<dir){
			if (heap[j].peso > heap[j+1].peso){
				j++;
			}
		}
		if (x.peso<=heap[j].peso){
			break;
		}
		heap[esq]=heap[j];
		pos[heap[j].vertice]=esq;
		//pos[heap[j].vertice]=esq;
		esq=j; 
		j=2*esq;
	}
	heap[esq]=x;
	pos[x.vertice]=esq;
}

void construir(Heap heap,int n,int *pos){		//constroi o heap segundo a ordem: 
	int esq= n/2+1;					//um elemento na posicao i tem que ser menor que um
	while (esq>1){					//elemento na posicao 2i e nao posicao 2i+1
		esq--;
		refazer(heap,esq,n,pos);
	}
}

CelulaHeap retirarmenor(Heap heap,int *n,int *pos){	//retira o elemento na posicao 1 do heap,
	CelulaHeap minimo;				//o troca com a última posicao, decrementa a qtd e refaz o heap.
	if ((*n)>=1){
		minimo=heap[1];
		heap[1]=heap[(*n)];
		pos[heap[(*n)].vertice]=1;
		heap[(*n)]=minimo;
		pos[minimo.vertice]=(*n);
		(*n)--;
		refazer(heap,1,*n,pos);
	}
	return(minimo);
}

void recalcularposicoes(int vertice, int *pos,Heap heap){	//recalcula a posicao de um elemento cujo peso foi recém editado.
	int i=pos[vertice];
	CelulaHeap x=heap[i];
	while ((i>1)&&(heap[i/2].peso>=x.peso)){	//recalcula e volta nas posições i/2 para manter a ordem no heap.
		heap[i]=heap[i/2];
		pos[heap[i].vertice]=i;
		i/=2;
	}
	heap[i]=x;
	pos[vertice]=i;
}

//fim heap indireto 

//Dijkstra

void Dijkstra(TipoGrafo *grafo, Heap heap, int *pos,int n){		//precisa do grafo e do heap
	int /*n=(*grafo).numvertices,*/FimListaAdj,vertice;		//declarando variáveis.
	float pesoaresta;
	CelulaHeap u;
	Ponteiro aux;
	int i;

	//enquando houverem elementos no heap.
	while (n>=1){
		u=retirarmenor(heap,&n,pos);	//u recebe os dados do menor elemento.
		if ((*grafo).InicioLista[u.vertice].inicio!=(*grafo).InicioLista[u.vertice].fim){
			aux = (*grafo).InicioLista[u.vertice].inicio->prox;

			//para cada adjacente, verifica se o valor que se quer inserir nele(vertice "pai"+pesoaresta) é menor que o peso lá inserido.
			while(aux!=NULL){
				vertice=aux->vertice;
				pesoaresta=aux->peso;
				aux=aux->prox;
				if (heap[pos[vertice]].peso>(u.peso+pesoaresta)){			//se o peso la existente for maior:
					heap[pos[vertice]].peso=u.peso+pesoaresta;			//é substituido.
					(*grafo).InicioLista[vertice].antecessor=u.vertice;		//e o novo antecessor é marcado.
					recalcularposicoes(vertice,pos,heap);				//as posicoes do heap devem ser recalculadas.
				}
			}

		}
		/*printf("Acabei de retirar o vertice: %d\n",u.vertice);
		for (i=1;i<=9;i++){
			printf("%d %f\n",heap[i].vertice,heap[i].peso);
		}*/
	}
}

//fim Dijkstra

void SolucaoGrafos(Imagem *imagem,int qtd){
	//declarando os tipo abstratos necessários
	TipoGrafo grafo;
	Heap heap;
	int *pos;

	//Criando e alocando o grafo.
	CriaGrafo(&grafo,*imagem,1);
	while (qtd>0){
		printf("qtd: %d\n",qtd);
		//declarando contadores de loops e alocando o heap e o pos
		int i,j;
		int n=grafo.numvertices;
		heap=(Heap) malloc((grafo.numvertices+1)*sizeof(CelulaHeap));
		pos=(int*) malloc((grafo.numvertices+1)*sizeof(int));

		//Criando e construindo heap
		ConstruirHeap(grafo,heap,pos,*imagem);

		//Aplicando o Dijkstra
		Dijkstra(&grafo,heap,pos,n);

		//Após aplicar o Dijkstra, pegamos o menor valor na ultima linha da imagem.
		float menorpeso=infinito;
		int menorindice=0;
		for (i=n-(*imagem).w+1;i<=n;i++){
			if (heap[pos[i]].peso<menorpeso){
				menorpeso=heap[pos[i]].peso;
				menorindice=i;
			}
		}

		//Retirando o caminho marcado.
		i=(*imagem).h-1;
		int indice;
		int *coluna_retirar;
		coluna_retirar=(int*) malloc((*imagem).h*sizeof(int));
		while (i>=0){
			j=grafo.InicioLista[menorindice].y;
			for (j=j;j<(*imagem).w-1;j++){
				(*imagem).matriz[i][j]=(*imagem).matriz[i][j+1];
			}
			coluna_retirar[i]=menorindice;
			grafo.InicioLista[menorindice].flag=1;
			indice=grafo.InicioLista[menorindice].antecessor;
			menorindice=indice;
			i--;
		}
		(*imagem).w--;
		qtd--;

		//liberando memória do heap e recriando o grafo.
		free(heap);
		free(pos);
		CriaGrafo(&grafo,*imagem,0);
	}
	//LiberaGrafo(&grafo);
}

