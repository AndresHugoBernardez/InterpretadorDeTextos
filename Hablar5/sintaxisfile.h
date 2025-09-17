#ifndef _sintaxisfile
#define _sintaxisfile

#include "stdio.h"
#include "stdlib.h"
#include "estructuras.h"


struct sintaxisnodo
{
	struct palabras palabra;
	struct sintaxisnodo *anterior,*posterior;
};

struct sfile
{
	int cursor,tamanio,ids;
	struct sintaxisnodo * inicio,*fin,*cur;
	
};



struct sfile * sfopen()
{
	struct sfile * retorno;
	struct sintaxisnodo * inicio,*nodo,*nodoaux;
	

    
	retorno=(struct sfile*)malloc(sizeof (struct sfile));

	    
	inicio= (struct sintaxisnodo*)malloc(sizeof(struct sintaxisnodo) );
	
	nodo=inicio;
	nodo->anterior=NULL;
	nodo->posterior=NULL;
	nodo->palabra.sintaxis=-2;
	nodo->palabra.word[0]='F';
	nodo->palabra.word[1]='I';
	nodo->palabra.word[2]='N';
	nodo->palabra.word[3]='@';
	nodo->palabra.word[4]='@';
	nodo->palabra.word[5]='\0';


	retorno->inicio=inicio;
	retorno->cur=inicio;
	retorno->fin=nodo;
	retorno->cursor=0;
	retorno->tamanio=0;
	retorno->ids=0;
	
	return(retorno);
}


void sfclose(struct sfile * archivo)
{
	long int i,tamanio;
	struct sintaxisnodo * nodo, *nodoaux;
	
	
	
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


int sfseek(struct sfile * archivo, long int offset, int origen)
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

long int sftell(struct sfile * archivo)
{
	return(archivo->cursor);
}




void sfread(struct palabras * palabra ,int Elemento, int cuenta, struct sfile * archivo)
{
	struct palabras palabrareturn;
	if(0<=archivo->cursor&& archivo->cursor <archivo->tamanio)
	{
	
	*palabra=archivo->cur->palabra;
	archivo->cursor=archivo->cursor+1;
	archivo->cur=archivo->cur->posterior;

	}
	else
	{
		archivo->cursor=archivo->tamanio;
		archivo->cur=archivo->fin;
		palabrareturn.sintaxis=-1;
		palabrareturn.word[0]='\0';
		*palabra=palabrareturn;
	}
}




void sfput(struct palabras  palabra, struct sfile * archivo )
{
	struct sintaxisnodo *anterior,*nodo;
	if(0<archivo->cursor&& archivo->cursor <=archivo->tamanio)
	{
	//	printf("\n agregando\n");
	anterior=archivo->cur->anterior;
	anterior->posterior=(struct sintaxisnodo*)malloc(sizeof(struct sintaxisnodo) );
	
	nodo=anterior->posterior;
	nodo->palabra=palabra;
	nodo->anterior=anterior;
	nodo->posterior=archivo->cur;
	
	archivo->cur->anterior=nodo;
	
	archivo->cursor=archivo->cursor+1;
	archivo->tamanio=archivo->tamanio+1;

	}
	else if (archivo->cursor==0)
	{
	nodo=(struct sintaxisnodo*)malloc(sizeof(struct sintaxisnodo) );
	
	nodo->palabra=palabra;
	nodo->anterior=NULL;
	nodo->posterior=archivo->cur;
	
	archivo->cur->anterior=nodo;
	
	archivo->cursor=archivo->cursor+1;
	archivo->tamanio=archivo->tamanio+1;
	archivo->inicio=nodo;
	}
	else printf("FUera de rango");
	
}
void sfsuprimir( struct sfile * archivo )
{
	struct sintaxisnodo *anterior,*posterior;
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
