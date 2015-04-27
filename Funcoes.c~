#include "Funcoes.h"


//-------------FUNÇÕES SOBRE A IMAGEM-------------------------------------------

/*
* Aloca a matriz de pixels.
*/
void CriaImagem(Imagem *imagem,int w,int h){
	int i;
	(*imagem).matriz=(Pixel**) malloc(h*sizeof(Pixel*));		//aloca a altura
	for (i=0;i<h;i++){
		(*imagem).matriz[i]=(Pixel*) malloc(w*sizeof(Pixel));	//aloca a largura
	}
	(*imagem).h=h;		//atribui as dimensões.
	(*imagem).w=w;
}

//------------------------------------------------------------------------------

void imprimirarquivo(Imagem imagem, char stringmagica[3], int rgbint){
	int i,j,cont=1;
	FILE* saida;
	saida = fopen("saida.ppm","w");
	fprintf (saida,"%s\n",stringmagica);
	fprintf (saida,"%d\n",imagem.w);
	fprintf (saida,"%d\n",imagem.h);
	fprintf (saida,"%d\n",rgbint);
	for (i=0;i<imagem.h;i++){
		for(j=0;j<imagem.w;j++){
			fprintf(saida,"%d ",imagem.matriz[i][j].R);
			fprintf(saida,"%d ",imagem.matriz[i][j].G);
			fprintf(saida,"%d ",imagem.matriz[i][j].B);
			cont++;
			if (cont>10){
				fprintf(saida,"\n");
				cont=1;
			}
		}
	}
	fclose(saida);
}

//------------------------------------------------------------------------------

void lernumero(FILE* arquivo, int *num){
	int i;
	char string[20],c;
	for (i=0;i<20;i++){string[i]=' ';}
	c=getc(arquivo);
	for (i=0;isspace(c)==0;i++){
		string[i]=c;
		c=getc(arquivo);
	}
	(*num)=atoi(string);
	pular(arquivo);
}

//------------------------------------------------------------------------------

void pular(FILE* arquivo){ 
char c;
	c = getc(arquivo);
	while (c == '#'|| isspace(c)!=0) {
		if (c=='#'){				
			while (getc(arquivo) != '\n') {
				c = getc(arquivo);
				ungetc(c,arquivo);
			}
		}else{
			c = getc(arquivo);
		}
	}
	ungetc(c,arquivo);
}

//------------------------------------------------------------------------------

Imagem transposta(Imagem imagem){
	int i,j;
	Imagem matriztransposta;
	matriztransposta.w=imagem.h;
	matriztransposta.h=imagem.w;
	matriztransposta.matriz=(Pixel**) malloc(matriztransposta.h*sizeof(Pixel*));
	for (i=0;i<imagem.w;i++){
		matriztransposta.matriz[i]=(Pixel*) malloc(matriztransposta.w*sizeof(Pixel));
	}
	for (i=0;i<matriztransposta.w;i++){
		for (j=0;j<matriztransposta.h;j++){
			matriztransposta.matriz[j][i]=imagem.matriz[i][j];
		}
	}
	return(matriztransposta);
}

void lerimagem (FILE* arquivo,Imagem *imagem, char *stringmagica, int *height, int *width, int *rgbint) {
	int i,j;
	fgets(stringmagica,3,arquivo);
	pular(arquivo);
	lernumero(arquivo,width);
	lernumero(arquivo,height);
	lernumero(arquivo,rgbint);
	CriaImagem(imagem, *width, *height);
	i=0;j=0;
	while (!feof(arquivo)) {
		lernumero(arquivo,&(*imagem).matriz[i][j].R);
		lernumero(arquivo,&(*imagem).matriz[i][j].G);
		lernumero(arquivo,&(*imagem).matriz[i][j].B);
		j++;
		if (i>=(*height)){
			i=0;
			j=0;
		}
		if (j>=(*width)){
			j=0;
			i++;
		}
	}
}
