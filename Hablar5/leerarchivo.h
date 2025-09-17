#ifndef _LEERARCHIVO_H
#define _LEERARCHIVO_H

#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>
#include <sys/stat.h>


#include"caracteres.h"
#include"archivos.h"
#include"cadenas.h"
#include"oraciones.h"
#include"diccionario.h"
#include"estructuras.h"
#include"lista.h"
#include"leerarchivo.h"
#include"pseudoarchivo.h"
#include "sintaxis.h"
#include "sintaxisfile.h"
#include "analisissintactico.h"
#include "preguntador.h"


void leerarchivo12(char *direccion1,char *direccion2,char *direccion3)
{
	FILE * farchivo,*farchivo2,*farchivo3;
	long int fin,fin2,catini,catfin,posini,posfin,posicion,tamanio;
	int i,j,k,*o;
	
	struct posicion posicion1,posicion2;
	char cadena[150]="hola",caracter, categoria[12]="clase",categoria2[100]="ind. pres.",FIN[6]="@FIN",cadenaaux[256];
	struct Pfile * archivo, *archivo2;
	struct Ppfile * archivo3;
	struct nombre nodo;
	struct sfile * palabras;
	struct palabras palabra;
	
	
		
	
	
	/*archivo=fopen(direccion1,"rt");
	archivo2=fopen(direccion2,"rt");
	archivo3=fopen(direccion3,"rb");*/
	
	printf("--");
	printf("--");
	printf("--");

	//system("pause");

	printf("\nabriendo1..\n");
	archivo=pfopen(direccion1);
	printf("\nabriendo2..\n");
	archivo2=pfopen(direccion2);
		printf("\nabriendo3..\n");
	archivo3=ppfopen(direccion3);

	//system("pause");
	
	
	
	
	printf("\nabiertos..\n");
	pfseek(archivo2,0,SEEK_END);
	fin= pftell(archivo2);
	pfseek(archivo,0,SEEK_END);
	fin2= pftell(archivo);
	
	printf(":");
	printfentreposfile(0,fin,archivo2);
	
	//printf("\n oraciones: %d",contaroraciones(0,fin,archivo2));
	//printf("\n parrafos: %d",contarparrafos(0,fin,archivo2));


	
//	Convertiroracion(palabras,archivo3);
	
	
		//printf("%s: ",palabras[i].palabra);
	
	
	/*
	fseek(archivo3,0,SEEK_END);
	tamanio=ftell(archivo3)/sizeof(struct nombre)-1;
	while (comparacad(cadena,"chau")!=0)
	{
	printf("\n----------Ingrese cadena:");
	 scanf("%s",&cadena);
	 printf("\n cadena=%s\n",cadena);
	printf("\nlista:\n");
	printflista(archivo3);
	
	i=Buscarpalabraenlistaenpos(&posicion,cadena,archivo3,0,tamanio);
	printf(" buscar=%d  posicion:%ld",i,posicion);

    i=OjearDiccionario(&posini,&posfin,cadena,archivo3,0,tamanio,posicion);
    printf(" Ojear=%d   posini=%ld  posfin=%ld \n",i,posini,posfin);

	}*/


  
   printf("\n ----lista\n");
   printflista(archivo3);
   printf("\n ----\n");
   
   
   
   //------------------------------------------------
   	/*ppfseek(archivo3,0,SEEK_END);
	
	//----
	//tamanio= ftell(archivo)/sizeof(struct nombre);
	tamanio=ppftell(archivo3); 
	printf("\n------\n >>>>>>>>>>>>>LISTA:<<<<<<<<<<<\n");
	ppfseek(archivo3,0,SEEK_SET);
	for (i=0;i<tamanio;i++)
	{
		ppfread(&nodo,sizeof(struct nombre),1,archivo3);
		printf("%s:%ld:%d;",nodo.palabra,nodo.posicion,nodo.largo);
		
		//leernombrecompleto(cadenaaux,nodo.posicion,nodo.posicion2,archivo,256);
		devolvercadenanodo(cadenaaux,nodo,archivo,256);
		printf("[%s]",cadenaaux);
		
		
	}
	printf("\n------\n");*/
   //------------------------------------------------
   
   

	
	
	cadenaaux[0]='\0';
	
	pfseek(archivo2,0,SEEK_SET);
	
	printf("\nleyendo...............................................");
	
	/*caracter='a';
	while(caracter!=EOF)
	{
	caracter=Leerpalabra(cadenaaux,archivo2,256);
	printf("\nCADENAAUX:[%s]",cadenaaux);
	}*/
	
	
	printf("\nconvirtiendo...");
	
	palabras=sfopen();
	
	ConvertirOracion(palabras,archivo2,archivo3,archivo);
	printf("\n...ok");
	
	

	
	
	printf("\n CLASIFICADOR\n");
	clasificador(palabras,archivo);
	DeteccionDeSimbolos(palabras);
	printf("\n end clasificador\n");


	printf("\n Separador de oraciones\n");
SeparadorDeOraciones(palabras);
	
	printf("\n end Separador\n");

	printf("\n Analisis SIntactico\n");
	AnalisisSintactico(palabras);
	printf("\n FIN Analisis SIntactico\n");


	printf("\n");
	i=0;
	
	sfseek(palabras,0,SEEK_END);
	tamanio=sftell(palabras);
	
	sfseek(palabras,0,SEEK_SET);
	while (sftell(palabras)<tamanio)
	{
		sfread(&palabra,sizeof(struct palabras),1,palabras);
		
		printf("%s:%d:%d:%d:%d:%d|%d",palabra.word,palabra.id,palabra.pos,palabra.clase,palabra.gen_num,palabra.persona,palabra.sintaxis);
		/*if (palabra.posicionlista!=-1)
		{
			if (0<Buscacategoriafile(&posicion2,palabra.posicionlista,palabra.posicionlista2,categoria,archivo))
			{
				CargaCadenaEntrePosFile(cadenaaux,posicion2.inicial+1,posicion2.final-1,archivo,256);
				printf("(%s)",cadenaaux);
			}
			if (0<Buscacategoriafile(&posicion2,palabra.posicionlista,palabra.posicionlista2,categoria2,archivo))
			{
				CargaCadenaEntrePosFile(cadenaaux,posicion2.inicial+1,posicion2.final-1,archivo,256);
				printf("(%s)",cadenaaux);
			}
		}*/
		printf(" ");
		i++;
	}
		
	
	preguntar(palabras);
	

	sfclose(palabras);
	ppfclose(archivo3);
	pfclose (archivo2);
	pfclose (archivo);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>	
}


void crearyordenarlista(char *direccion1,char *direccion3)
{
	struct nombre nodo1;
	FILE * archivo,*archivo2;
	int i=0;
	long int total=0;
    struct stat buffer1,buffer2;
    Pfile * diccionario;
	Ppfile *lista;
    //char direccion1[20]="hola.txt",direccion2[20]="hola2.txt",direccion3[20]="lista.txt";
	
	stat(direccion1,&buffer1);

	stat(direccion3,&buffer2);

	//printf(" hola.txt: %s listas.txt:",ctime(&(buffer1.st_mtime)));
	//printf("%s", ctime(&( buffer2.st_mtime )));
	//printf("hola.txt %d listas.txt %d",buffer1.st_mtime,buffer2.st_mtime);
	
	if (buffer1.st_mtime>buffer2.st_mtime)
	{
	  
		
		printf("\n Creando lista...");
		crearlista(direccion1,direccion3);
		printf("\nlista lista!\n");
		
/*
lista=ppfopen(direccion3);
   printf("\n ----lista\n");
   printflista(lista);
   printf("\n ----\n");
   ppfclose(lista);
*/

		diccionario=pfopen(direccion1);
		
		ordenarlistamenoramayor(direccion3,diccionario);
		pfclose(diccionario);
		printf("\n-----\n ORDENADO:\n--------\n ");
	}
	/*
	archivo2=fopen("lista.txt","rb");
	i=0;
	fread(&nodo1,sizeof(struct nombre),1,archivo2);
	while(!feof(archivo2))
	{
		i++;
		printf("__%d:%s:%Ld",i,nodo1.palabra,nodo1.posicion);
		fread(&nodo1,sizeof(struct nombre),1,archivo2);
		
	}
	
	fseek(archivo2,0,SEEK_END);
	total=ftell(archivo2)/sizeof(struct nombre);
	printf("\n total= %Ld, %d",total,i);
	
	fclose(archivo2);*/
	
	
	
	//printf("\ncomparacion _:%c = %d",'_',comparacad("Estados_","Estados"));	
	//	printf(" >A>>>%d",'a'-'A');
	
	
}

#endif
