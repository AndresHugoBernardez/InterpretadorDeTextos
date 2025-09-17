#ifndef _comafile
#define _comafile

#include "stdio.h"
#include "stdlib.h"

struct bucleinformation
{
	long int inicio, final,posiciony;
	bool sustantivo,verbo,adjetivo,adverbio,pronombre;	
};

void InicializarBucleEnCero(struct bucleinformation *bucle)
{
	bucle->inicio=0;
	bucle->final=0;
	bucle->posiciony=0;
	bucle->adjetivo=false;
	bucle->sustantivo=false;
	bucle->verbo=false;
	bucle->adverbio=false;
	
}



struct buclenodo
{
	struct bucleinformation bucle;
	struct buclenodo *anterior,*posterior;
};

struct bfile
{
	int cursor,tamanio;
	struct buclenodo * inicio,*fin,*cur;
	
};



struct bfile * bfopen()
{
	struct bfile * retorno;
	struct buclenodo * inicio,*nodo,*nodoaux;
	

    
	retorno=(struct bfile*)malloc(sizeof (struct bfile));

	    
	inicio= (struct buclenodo*)malloc(sizeof(struct buclenodo) );
	
	nodo=inicio;
	nodo->anterior=NULL;
	nodo->posterior=NULL;


	retorno->inicio=inicio;
	retorno->cur=inicio;
	retorno->fin=nodo;
	retorno->cursor=0;
	retorno->tamanio=0;
	
	return(retorno);
}


void bfclose(struct bfile * archivo)
{
	long int i,tamanio;
	struct buclenodo * nodo, *nodoaux;
	
	
	
	tamanio= archivo->tamanio;
	
	nodo=archivo->inicio;
	//printf("\ncerrando...");
	for (i=0;i<=tamanio;i++)
	{
		nodoaux=nodo->posterior;
		free(nodo);
		nodo=nodoaux;
	}
	//printf("ok\n");



	free(archivo);
}


int bfseek(struct bfile * archivo, long int offset, int origen)
{
	long int suma,i;
	if(origen == SEEK_SET) 
	{
	    if(offset>=0 && offset<=archivo->tamanio)
			{
				
				//printf("\nSEEK_SET\n{");
				
				archivo->cur=archivo->inicio;
				for(i=0;i<offset;i++) 
				{
					archivo->cur=archivo->cur->posterior;
					//printf("%c",archivo->cur->letra);
				}
				//printf("}\n");
				
				archivo->cursor=offset;
				return(0);
			}
		else return(-1);
	}
	else if (origen == SEEK_CUR)
	{
		suma=archivo->cursor+offset;
		if (suma>=0 && suma<=archivo->tamanio)
		{
				//printf("\nSEEK_CUR\n{");
				if(offset>=0)
				for(i=0;i<offset;i++) 
				{
					archivo->cur=archivo->cur->posterior;
					//printf("%c",archivo->cur->letra);
				}
				if(offset<0)
				for(i=0;i<-offset;i++) 
				{
					archivo->cur=archivo->cur->anterior;
					//printf("%c",archivo->cur->letra);
				}
				//printf("}\n");
			archivo->cursor=suma;
			return(0);
		}
		else return(-1);
	}
	else if (origen=SEEK_END)
	{
		if (offset<=0&& archivo->tamanio>=-offset)
		{
				//printf("\nSEEK_END\n{");
				archivo->cur=archivo->fin;
				for(i=0;i<-offset;i++) 
				{
					archivo->cur=archivo->cur->anterior;
					//printf("%c",archivo->cur->letra);
				}
				//printf("}\n");
			archivo->cursor=archivo->tamanio+offset;
			return(0);
		}
		else
		return (-1);
	}
	
}

long int bftell(struct bfile * archivo)
{
	return(archivo->cursor);
}




void bfread(struct bucleinformation * Bucle ,int Elemento, int cuenta, struct bfile * archivo)
{
	struct bucleinformation buclereturn;
	if(0<=archivo->cursor&& archivo->cursor <archivo->tamanio)
	{
	
	*Bucle=archivo->cur->bucle;
	archivo->cursor=archivo->cursor+1;
	archivo->cur=archivo->cur->posterior;

	}
	else
	{
		archivo->cursor=archivo->tamanio;
		archivo->cur=archivo->fin;
		buclereturn.inicio=-1;
		buclereturn.final=-1;
		*Bucle=buclereturn;
	}
}




void bfput(struct bucleinformation  Bucle, struct bfile * archivo )
{
	struct buclenodo *anterior,*nodo;
	if(0<archivo->cursor&& archivo->cursor <=archivo->tamanio)
	{
	//	printf("\n agregando\n");
	anterior=archivo->cur->anterior;
	anterior->posterior=(struct buclenodo*)malloc(sizeof(struct buclenodo) );
	
	nodo=anterior->posterior;
	nodo->bucle=Bucle;
	nodo->anterior=anterior;
	nodo->posterior=archivo->cur;
	
	archivo->cur->anterior=nodo;
	
	archivo->cursor=archivo->cursor+1;
	archivo->tamanio=archivo->tamanio+1;

	}
	else if (archivo->cursor==0)
	{
	nodo=(struct buclenodo*)malloc(sizeof(struct buclenodo) );
	
	nodo->bucle=Bucle;
	nodo->anterior=NULL;
	nodo->posterior=archivo->cur;
	
	archivo->cur->anterior=nodo;
	
	archivo->cursor=archivo->cursor+1;
	archivo->tamanio=archivo->tamanio+1;
	archivo->inicio=nodo;
	}
	else printf("FUera de rango");
	
}
void bfsuprimir( struct bfile * archivo )
{
	struct buclenodo *anterior,*posterior;
	if(0<archivo->cursor&& archivo->cursor <archivo->tamanio&& archivo->tamanio>0)
	{
	//	printf("\n agregando\n");
	anterior=archivo->cur->anterior;
	posterior=archivo->cur->posterior;
	
	free(archivo->cur);
	anterior->posterior=posterior;
	posterior->anterior=anterior;
	archivo->cur=posterior;
	
	
	
	archivo->tamanio=archivo->tamanio-1;

	}
	else if (archivo->cursor==0 && archivo->tamanio>0)
	{
	
	posterior=archivo->cur->posterior;
	
	free(archivo->cur);
	
	posterior->anterior=NULL;
	archivo->cur=posterior;
	
	archivo->tamanio=archivo->tamanio-1;
	
	archivo->inicio=posterior;
	}
	else printf("FUera de rango");
	
}









#endif
