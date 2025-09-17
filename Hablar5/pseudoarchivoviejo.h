#ifndef _PSEUDOARCHIVO
#define _PSEUDOARCHIVO


#include<stdio.h>
#include<stdlib.h>
#include"estructuras.h"


struct Pfile
{
	int cursor,tamanio;
	char * texto;
	
};

struct Ppfile
{
	int cursor,tamanio;
	struct nombre * nombre;
	
};
struct Pfile * pfopen(const char * Filename)
{
	FILE * archivo;
	long int i, tamanio;
	struct Pfile * archivoreturn;
	char caracter;
	

    
	archivoreturn=(struct Pfile*)malloc(sizeof (struct Pfile));

	archivo=fopen(Filename,"rt");
	fseek(archivo,0,SEEK_END);
	tamanio=ftell(archivo);

	archivoreturn->texto= (char*)malloc((tamanio)*sizeof(char) );

    fseek(archivo,0,SEEK_SET);
    for(i=0;i<tamanio;i++)
    {
    	caracter=fgetc(archivo);
    	archivoreturn->texto[i]=caracter;
	}

	fclose(archivo);
	
	archivoreturn->texto[tamanio]=EOF;
	archivoreturn->cursor=0;
	archivoreturn->tamanio=tamanio;
	//printf("\n text: %s",archivoreturn->texto);

	return(archivoreturn);
}

void pfclose(struct Pfile * archivo)
{
	free(archivo->texto);
	free(archivo);
}
char pfgetc(struct Pfile * archivo)
{
	char caracter;
	if(0<=archivo->cursor <archivo->tamanio)
	{
	
	caracter=archivo->texto[archivo->cursor];
	archivo->cursor=archivo->cursor+1;
	return(caracter);
	}
	else
	{
		archivo->cursor=archivo->tamanio;
		return(EOF);
	}
}

int pfseek(Pfile * archivo, long int offset, int origen)
{
	long int suma;
	if(origen == SEEK_SET) 
	{
	    if(offset>=0 && offset<=archivo->tamanio)
			{
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
			archivo->cursor=suma;
			return(0);
		}
		else return(-1);
	}
	else if (origen=SEEK_END)
	{
		if (offset<=0&& archivo->tamanio>=-offset)
		{
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
	struct Ppfile * archivoreturn;
	char caracter;
	

    
	archivoreturn=(struct Ppfile*)malloc(sizeof (struct Ppfile));

	archivo=fopen(Filename,"rb");
	fseek(archivo,0,SEEK_END);
	tamanio=ftell(archivo)/(sizeof(struct nombre));

    printf("&%ld",tamanio);
	archivoreturn->nombre= (struct nombre*)malloc((tamanio)*sizeof(struct nombre) );
    printf("&");
    fseek(archivo,0,SEEK_SET);
    for(i=0;i<tamanio;i++)
    {
    	fread(&(archivoreturn->nombre[i]),sizeof(struct nombre),1,archivo);
    	//printf("%s:%ld;",archivoreturn->nombre[i].palabra,archivoreturn->nombre[i].posicion);
    }

	fclose(archivo);
	
	archivoreturn->nombre[tamanio].posicion=-1;
	archivoreturn->cursor=0;
	archivoreturn->tamanio=tamanio;
	//printf("\n text: %s",archivoreturn->texto);

	return(archivoreturn);
}

void ppfclose(struct Ppfile * archivo)
{
	free(archivo->nombre);
	free(archivo);
}

int ppfseek(Ppfile * archivo, long int offset, int origen)
{
	long int suma;
	if(origen == SEEK_SET) 
	{
	    if(offset>=0 && offset<=archivo->tamanio)
			{
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
			archivo->cursor=suma;
			return(0);
		}
		else return(-1);
	}
	else if (origen=SEEK_END)
	{
		if (offset<=0&& archivo->tamanio>=-offset)
		{
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
	if(0<=archivo->cursor <archivo->tamanio)
	{
	
	*nombre=archivo->nombre[archivo->cursor];
	archivo->cursor=archivo->cursor+1;

	}
	else
	{
		archivo->cursor=archivo->tamanio;
		nombrereturn.posicion=-1;
		nombrereturn.palabra[0]='\0';
		*nombre=nombrereturn;
	}
}

//-----------------------------

#endif
