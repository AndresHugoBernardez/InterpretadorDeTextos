#ifndef _ARCHIVOS_H
#define _ARCHIVOS_H


#include<stdio.h>
#include<stdlib.h>
#include"caracteres.h"
#include"pseudoarchivo.h"

//--------------------------ARCHIVO





//Muestra lo que está en la posiciones indicadas
/*void printfentrepos(long int inicio,long int final, char *direccion)
{
	FILE*archivo;
	char caracter='a';
	long int i;
	
	i=inicio;
	archivo=fopen(direccion,"r");
	fseek(archivo,inicio,SEEK_SET);
	caracter='a';
	while(caracter!=EOF&&i<=final)
	{
		caracter=fgetc(archivo);
		printf("%c",caracter);
		if(caracter=='\n')i=i+2;else i=i+1;
	}	
	fclose(archivo)	;
	
}/*/

//Muestra lo que está en la posiciones indicadas
void printfentreposfile(long int inicio,long int final,struct Pfile * archivo)
{

	char caracter='a';
	long int i;
	
	i=inicio;

	pfseek(archivo,inicio,SEEK_SET);
	caracter='a';
	while(caracter!=EOF&&i<=final)
	{
		caracter=pfgetc(archivo);
		printf("%c",caracter);
		if(caracter=='\n')i=i+2;else i=i+1;
	}		
	
}


// Carga en una cadena lo que esta contenido entre dos posiciones.
int CargaCadenaEntrePosFile(char * cadena,long int inicio,long int final,struct Pfile * archivo,int limitechar)
{

	char caracter='a';
	long int i,limite;
	
	

	pfseek(archivo,inicio,SEEK_SET);
	i=0;
	limite=limitechar-1;
	
	caracter='a';
	while(caracter!=EOF&&i<limite&&pftell(archivo)<=final)
	{
		caracter=pfgetc(archivo);
		cadena[i]=caracter;
		i++;		
	}	
	cadena[i]='\0';
	return(i+1);
}



#endif
