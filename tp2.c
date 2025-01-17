#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "Funcoes.h"
#include "ProgramacaoDinamica.h"
#include "Filtros.h"
#include "Grafo.h"

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>


int main(int argc, char *argv[]){
	char stringmagica[3],c;
	int height,width,rgbint,i,j,cont=0;
	Imagem imagem;
	FILE* entrada;
	entrada = fopen(argv[1],"r");
	//entrada = fopen("entrada.ppm","r");
	lerimagem (entrada,&imagem,stringmagica,&height,&width,&rgbint);
	fclose(entrada);

	//Aqui começa o programa mesmo
	int qtd_retirar=atoi(argv[4]);
	if (strcmp(argv[2],"D")==0){
		if(strcmp(argv[3],"-h")==0){
			imagem=transposta(imagem);
			ProgramacaoDinamica(&imagem,qtd_retirar);
			imagem=transposta(imagem);
		}
		else if (strcmp(argv[3],"-w")==0){
			ProgramacaoDinamica(&imagem,qtd_retirar);
		}
		imprimirarquivo(imagem,stringmagica,rgbint);
	}
	else if(strcmp(argv[2],"G")==0){
		if(strcmp(argv[3],"-h")==0){
			imagem=transposta(imagem);
			SolucaoGrafos(&imagem,qtd_retirar);
			imagem=transposta(imagem);
		}
		else if (strcmp(argv[3],"-w")==0){
				double inicio, final;						// função para calcular o tempo de execução. Termina no final do código
				struct timeval tv;
				gettimeofday(&tv,NULL);
				inicio= tv.tv_sec + (tv.tv_usec/1000000.0); 
			SolucaoGrafos(&imagem,qtd_retirar);

				struct rusage ru;
				struct timeval tim;
				getrusage(RUSAGE_SELF, &ru);
				tim=ru.ru_utime;
				double sutime = (double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;
				// exibe na tela informações sobre o tempo de execução do programa
				printf("               - TEMPO REAL -                 \n");
				printf(" _______________________________________________\n");
				printf("| Tempo de Usuario: %.3f segundos         |\n", sutime);
				//fprintf(arq_out,"Tempo Usuario: %.3f\t",sutime);
				tim=ru.ru_stime;
				double sstime = (double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;
				printf("| Tempo de Sistema: %.3f segundos         |\n", sstime);
				//fprintf(arq_out,"Tempo Sistema: %.3f\t",sstime);
				printf("| Tempo Total de Execucao: %.3f segundos  |\n", sutime+sstime);
				//fprintf(arq_out,"Tempo Execucao: %.3f\t",sutime+sstime);
				gettimeofday(&tv, NULL); // final do marcador de tempo real
				final = tv.tv_sec + (tv.tv_usec)/1000000.0;
				// a diferença entre os marcador de tempo real final e inicial
				// é o tempo real de execução
				printf("| Tempo Real de Execucao: %.3f segundos   |\n", final-inicio);
		}
		imprimirarquivo(imagem,stringmagica,rgbint);
	}
	else{
		printf("Estratégia desconhecida\n");
	}
}
