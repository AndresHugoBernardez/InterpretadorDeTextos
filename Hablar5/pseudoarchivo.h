#ifndef _PSEUDOARCHIVO
#define _PSEUDOARCHIVO


#include<stdio.h>
#include<stdlib.h>
#include"estructuras.h"


struct textonodo
{
	char letra;
	struct textonodo * anterior,*posterior;
};

struct nombrenodo
{
	struct nombre nombre;
	struct nombrenodo *anterior,*posterior;
};

struct Pfile
{
	int cursor,tamanio;
	struct textonodo * inicio,*fin,*cur;
	
};

struct Ppfile
{
	int cursor,tamanio;
	struct nombrenodo * inicio,*fin,*cur;
	
};
struct Pfile * pfopen(const char * Filename)
{
	FILE * archivo;
	long int i,j, tamanio;
	struct Pfile * retorno;
	char caracter;
	struct textonodo * nodo, *inicio,*nodoaux;
	

    
	retorno=(struct Pfile*)malloc(sizeof (struct Pfile));

	archivo=fopen(Filename,"rt");
	fseek(archivo,0,SEEK_END);
	tamanio=ftell(archivo);

	inicio= (struct textonodo*)malloc(sizeof(struct textonodo) );
	nodo=inicio;
	nodo->anterior=NULL;

     j=0;
    fseek(archivo,0,SEEK_SET);
    for(i=0;i<tamanio;i++)
    {
    	nodoaux=nodo;
		caracter=fgetc(archivo);
		
		
		
		//---------CORRECCION DE ACENTO ñ ¿ y ¡
		
			if (caracter==-61)
		{	//printf("!");
			caracter=fgetc(archivo);
			i++;
			j++;
			switch(caracter)
			{
				case -95: caracter='á';break;
				case -87: caracter='é';break;
				case -83: caracter='í';break;
				case -77: caracter='ó';break;
				case -70: caracter='ú';break;
				case -127: caracter='Á';break;
				case -119: caracter='É';break;
				case -115: caracter='Í';break;
				case -109: caracter='Ó';break;
				case -102: caracter='Ú';break;
				case -79: caracter='ñ';break;
				case -111: caracter='Ñ';break;
				case EOF:{	fseek(archivo,-1,SEEK_CUR);
							i--;
							j--;
							caracter=fgetc(archivo);
							printf("ERROR1");
							break;
							}
				default: {fseek(archivo,-2,SEEK_CUR);
							caracter=fgetc(archivo);
							i--;
							j--;
							printf("ERROR2");
							break;
						}
			}
			
		}
		else if (caracter==-62)
		
		{ //printf("*");
			caracter=fgetc(archivo);
			i++;
			j++;
			switch(caracter)
			{
				case -95: caracter='¡';break;
				case -65: caracter='¿';break;
				case EOF:{	fseek(archivo,-1,SEEK_CUR);
							caracter=fgetc(archivo);
							i--;
							j--;
							printf("ERROR3");
							break;
							}
				default: {fseek(archivo,-2,SEEK_CUR);
							caracter=fgetc(archivo);
							i--;
							j--;
							printf("ERROR4");
							break;
						}
			}
		}
		
		//--------------------------------
		
		
    	nodo->letra=caracter;
    	nodo->posterior= (struct textonodo*)malloc(sizeof(struct textonodo) );
    	nodo=nodo->posterior;
    	nodo->anterior=nodoaux;
	}

	fclose(archivo);
	
	
	nodo->posterior=NULL;
	nodo->letra=EOF;
	
	retorno->inicio=inicio;
	retorno->cur=inicio;
	retorno->fin=nodo;
	retorno->cursor=0;
	retorno->tamanio=tamanio-j;//la jota es por la correccion de acento.
	//printf("\n text: %s",retorno->texto);

	return(retorno);
}

void pfclose(struct Pfile * archivo)
{
	
	long int i,tamanio;
	struct textonodo * nodo, *nodoaux;
	
	
	
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
char pfgetc(struct Pfile * archivo)
{
	char caracter;
	if(0<=archivo->cursor&& archivo->cursor <archivo->tamanio)
	{
	
	caracter=archivo->cur->letra;
	archivo->cursor=archivo->cursor+1;
	archivo->cur=archivo->cur->posterior;
	
	return(caracter);
	}
	else
	{
		archivo->cursor=archivo->tamanio;
		archivo->cur=archivo->fin;
		return(EOF);
	}
}


int pfseek(Pfile * archivo, long int offset, int origen)
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
					//printf("T");
					archivo->cur=archivo->cur->posterior;
					//printf(">%c",archivo->cur->letra);
				}
				if(offset<0)
				for(i=0;i<-offset;i++) 
				{
					//printf("Q");
					archivo->cur=archivo->cur->anterior;
					//printf(">%c",archivo->cur->letra);
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

long int pftell(struct Pfile * archivo)
{
	return(archivo->cursor);
}

//--------------------------------------------------------------

struct Ppfile * ppfopen(const char * Filename)
{
	FILE * archivo;
	long int i, tamanio;
	struct Ppfile * retorno;
	char caracter;
	struct nombrenodo * inicio,*nodo,*nodoaux;
	

    
	retorno=(struct Ppfile*)malloc(sizeof (struct Ppfile));

	archivo=fopen(Filename,"rb");
	fseek(archivo,0,SEEK_END);
	tamanio=ftell(archivo)/(sizeof(struct nombre));

    
    
	inicio= (struct nombrenodo*)malloc(sizeof(struct nombrenodo) );
	
	nodo=inicio;
	nodo->anterior=NULL;
	
    
    fseek(archivo,0,SEEK_SET);
    for(i=0;i<tamanio;i++)
    {
    	nodoaux=nodo;
    	fread(&(nodo->nombre),sizeof(struct nombre),1,archivo);
    	//printf("%s:%ld;",retorno->nombre[i].palabra,retorno->nombre[i].posicion);
    	nodo->posterior= (struct nombrenodo*)malloc(sizeof(struct nombrenodo) );
    	nodo=nodo->posterior;
    	nodo->anterior=nodoaux;
    }

	fclose(archivo);
	
	
	nodo->posterior=NULL;
	nodo->nombre.posicion=-1;
	nodo->nombre.palabra[0]='\0';
	
	retorno->inicio=inicio;
	retorno->cur=inicio;
	retorno->fin=nodo;
	retorno->cursor=0;
	retorno->tamanio=tamanio;
	//printf("\n text: %s",retorno->texto);

	return(retorno);
}

void ppfclose(struct Ppfile * archivo)
{
	long int i,tamanio;
	struct nombrenodo * nodo, *nodoaux;
	
	
	
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

int ppfseek(Ppfile * archivo, long int offset, int origen)
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

long int ppftell(struct Ppfile * archivo)
{
	return(archivo->cursor);
}

void ppfread(struct nombre * nombre,int Elemento, int cuenta, Ppfile * archivo)
{
	struct nombre nombrereturn;
	if(0<=archivo->cursor&&   archivo->cursor<archivo->tamanio)
	{
	
	*nombre=archivo->cur->nombre;
	archivo->cursor=archivo->cursor+1;
	archivo->cur=archivo->cur->posterior;

	}
	else
	{
		archivo->cursor=archivo->tamanio;
		archivo->cur=archivo->fin;
		nombrereturn.posicion=-1;
		nombrereturn.palabra[0]='\0';
		*nombre=nombrereturn;
	}
}

//-----------------------------

#endif
