#ifndef _LISTA_H
#define _LISTA_H

#include<stdio.h>
#include<stdlib.h>
#include"caracteres.h"
#include"diccionario.h"
#include"estructuras.h"
#include"pseudoarchivo.h"
#include"archivos.h"

///               LISTA
int leernombrecompleto(char* salida, long int posicionini,long int posicionfin,Pfile * archivo, int limitechar)
{
	struct posicion posicionfinal;
	long int tamanio;
	char cadena[10]="nombre",caracter,error[10]="error432";
	bool go;
	int i;
	

	i=0;
	if(Buscacategoriafile(&posicionfinal,posicionini,posicionfin,cadena,archivo))
	{   //printf("******************OK");
		CargaCadenaEntrePosFile(salida,posicionfinal.inicial+1,posicionfinal.final-1,archivo,limitechar);
	}
	else
	{
		//printf("*******************ERROR");
		i=Asignacadena(salida,error,MAX_CHAR);
	}
	return(i);
}


int devolvercadenanodo(char* cadena, struct nombre nodo, Pfile * archivo,int limitechar)
{
	int i;
	i=0;
	
		if(nodo.largo)
		{
			i=leernombrecompleto(cadena,nodo.posicion,nodo.posicion2,archivo,limitechar);
			//printf("***devolvercadenanodo lista:[%s] extraccion[%s]",nodo.palabra, cadena);
			
		}
		else
		{
			i=Asignacadena(cadena,nodo.palabra,limitechar);
			//printf(">> lista:[%s] extraccion[%s]",nodo.palabra, cadena);
		}
		
	return(i);
}


void crearlista (char * direccion1, char* direccion)
{

	struct nombre nodo1,nodo2,nodoactual;
	FILE * archivo2;
	struct Pfile * archivo;
	struct posicion posicion1,posicion2;
	long int posini,posfin;
	char caracter,cadena[256],ente[10]="ente",nombre[10]="nombre";
	int largo;
	
	archivo=pfopen(direccion1);
	archivo2 =fopen(direccion,"wb");
	
	pfseek(archivo,0,SEEK_END);
	posfin=pftell(archivo);
	posini=0;
	pfseek(archivo,0,SEEK_SET);
	
	while (Buscacategoriafile(&posicion1,posini,posfin,ente,archivo))
	{
		if (Buscacategoriafile(&posicion2,posicion1.inicial,posicion1.final,nombre,archivo))
		{
			
				    CargaCadenaEntrePosFile(cadena,posicion2.inicial+1,posicion2.final-1,archivo,256);
					largo=largocadena(cadena);
					/*asignacadena(nodo1.palabra,cadena);
					printf("nodo1:%s,cadena:%s_",nodo1.palabra,cadena);
					nodo1.largo=0;
					nodo1.posicion=posicion1.catinicial;
					fwrite(&nodo1,sizeof(struct nombre),1,archivo2);*/
					//printf("[%s]",cadena);
					if (largo<MAX_CHAR)
					{
					//printf("°");
					Asignacadena(nodo1.palabra,cadena,MAX_CHAR);
					nodo1.largo=0;
					nodo1.posicion=posicion1.catinicial;
					nodo1.posicion2=posicion1.catfinal;
					fwrite(&nodo1,sizeof(struct nombre),1,archivo2);
					}
					else
					{
					//printf("CORTADO_");
					cadena[28]='#';
					cadena[29]='\0';
					Asignacadena(nodo1.palabra,cadena,MAX_CHAR);
					
					nodo1.largo=1;
					nodo1.posicion=posicion1.catinicial;
					nodo1.posicion2=posicion1.catfinal;
					fwrite(&nodo1,sizeof(struct nombre),1,archivo2);	
					}
					
					//leernombrecompleto(cadena,nodo1.posicion,nodo1.posicion2,archivo,256);
					//printf("[%s]:pos:%ld",cadena,nodo1.posicion);
				
				
			
			
		}
		
		
		posini=posicion1.catfinal;
	}
	pfclose(archivo);
	fclose (archivo2);
		
	
	
}





void ordenarlistamenoramayor(char * direccion,Pfile * diccionario)
{
	FILE * archivo;
	long int tamanio,i,j,posicion,posicion2;
	struct nombre nodo,nodo2,nodo3;
	char cadena1[256],cadena2[256];
	int tamaniocadena1,tamaniocadena2,comparacion;
	
	
	archivo=fopen(direccion,"r+b");
	fseek(archivo,0,SEEK_END);
	
	tamanio= ftell(archivo)/sizeof(struct nombre);
	
	
	for (i=0;i<tamanio;i++)
	{
		posicion= i*sizeof(struct nombre);
		posicion2=posicion;
		fseek(archivo,posicion,SEEK_SET);
		
		fread(&nodo,sizeof(struct nombre),1,archivo);
		nodo3=nodo;
		devolvercadenanodo(cadena1,nodo,diccionario,256);
		
		//printf("\n");
		fseek(archivo,posicion,SEEK_SET);		
		for (j=i;j<tamanio;j++)
		{
			
			fread(&nodo2,sizeof(struct nombre),1,archivo);
			devolvercadenanodo(cadena2,nodo2,diccionario,256);
			//printf("nodo:");
			// Si cadena1 < cadena2: -1   si cadena1 > cadena2: 1 si cadena1==cadena2: 0
			comparacion=comparacad(cadena1,cadena2) ;
			
			//printf(" cad1:%s cad2:%s comp:%d|",cadena1,cadena2,comparacion);
			if(comparacion > 0 )
			{
				
				posicion2=ftell(archivo)-sizeof(struct nombre);	
				nodo=nodo2;
				//printf("nodo1:%s %ld nodo2:%s %ld",nodo.palabra,nodo.posicion,nodo2.palabra,nodo2.posicion);
				devolvercadenanodo(cadena1,nodo,diccionario,256);
				
			}
			
			
		}
		if (posicion!=posicion2)
			{
				fseek(archivo,posicion2,SEEK_SET);
				fread(&nodo2,sizeof(struct nombre),1,archivo);
				fseek(archivo,posicion,SEEK_SET);
				fwrite(&nodo2,sizeof(struct nombre),1,archivo);
				fseek(archivo,posicion2,SEEK_SET);
				fwrite(&nodo3,sizeof(struct nombre),1,archivo);
			}
		
		
	}
	fclose(archivo);
	
	
	
}



//Mostrar lista
void printflista(struct Ppfile * archivo)
{

	struct nombre nodo;
	long int i, tamanio;
	char cadena[256];
	

	ppfseek(archivo,0,SEEK_END);
	
	//tamanio= ftell(archivo)/sizeof(struct nombre);
	tamanio=ppftell(archivo); 
	//printf("\n LISTA:");
	ppfseek(archivo,0,SEEK_SET);
	for (i=0;i<tamanio;i++)
	{
		ppfread(&nodo,sizeof(struct nombre),1,archivo);
		printf("%s:%ld:%d;",nodo.palabra,nodo.posicion,nodo.largo);
	}
	//printf("\n");

	
}

//
//
/*
long int Buscarpalabraenlista(char* palabra,FILE*archivo)
{
	//--->FILE*archivo;
	struct nombre nodo1;
	long int posicion1,posicion2,posicion,tamanio;
	int comparacion,encontrado,i,correccion,bucleinfinito;
	char cadena[200],nopalabra[3]="##";
	//---->archivo=fopen(direccion,"rb");
	
	fseek(archivo,0,SEEK_END);
	tamanio=ftell(archivo)/sizeof(struct nombre);
	
	
	if (!comparacad(palabra,nopalabra)) return(-2);
	

	posicion1=0;
	posicion2=tamanio;
	encontrado=0;
	i=0;
	correccion=1;
	bucleinfinito=0;
	while(posicion1!=posicion2 && encontrado==0&& i<100)
	{
		i++;
		if(i>70) printf("\nerror n 145265");
		posicion=(posicion2-posicion1)/2;
		if (posicion2-posicion1==1) 
			{
				if(bucleinfinito==1) posicion1=posicion2;
				posicion=correccion;
				correccion=0;
				if(correccion==0 && posicion==0) {
				bucleinfinito=1;correccion=1;}
				
			}
		
		fseek(archivo,(posicion+posicion1)*sizeof(struct nombre),SEEK_SET);
		fread(&nodo1,sizeof(struct nombre),1,archivo);
		
		//printf("\n Analizando palabra:%s p:%d",nodo1.palabra,(posicion+posicion1));
		
		// Si cadena1 < cadena2: -1   si cadena1 > cadena2: 1 si cadena1==cadena2: 0
		
				
		comparacion=comparacad(nodo1.palabra,palabra);
		
		
		if (comparacion==0)
			{ encontrado=1;
			}
		else if (comparacion>0)
		{
			posicion2=posicion1+posicion;
			//printf("::p1=%d p2=%d",posicion1,posicion2);
		}
		else if (comparacion<0)
		{
			posicion1=posicion1+posicion;
			//printf("::p1=%d p2=%d",posicion1,posicion2);
		}
	}
	//--->fclose(archivo);
	if (encontrado==1) 
		{	
			//printf(" E:!"); // nombre:%s posicion:%d",nodo1.palabra,nodo1.posicion);
			return (nodo1.posicion);
		}
	else
		{
			//printf(" E:# ");
			return(-1);
		}
	
}

*/







//Busqueda dicotomica
int Buscarpalabraenlistaenpos(long int * posicionencontrado, char* palabra,struct Ppfile*archivo,long int posicionini, long int posicionfin,Pfile * diccionario)
{
	//--->FILE*archivo;
	struct nombre nodo1;
	long int posicion1,posicion2,posicion,tamanio;
	int comparacion,encontrado,i,correccion,bucleinfinito, go;
	char nopalabra[3]="##",cadena[256]="";

	//---->archivo=fopen(direccion,"rb");
	
	// tamanio del archivo
	ppfseek(archivo,0,SEEK_END);
	//tamanio=ftell(archivo)/sizeof(struct nombre)-1;
	tamanio=ppftell(archivo)-1;
	
	// descontamos que sea una palabra
	if (!comparacad(palabra,nopalabra)) return(-2);
	


	// Error de posiciones y carga de ellos
    if (posicionini<=posicionfin)
    {
	
    if (posicionini>=0 &&posicionini<=tamanio) posicion1=posicionini;
    else {
    	 printf("\n Error 224 Buscarpalabraenlistaenpos posicionini fuera de rango\n");
    	 return (-100);
		}
	if (posicionfin<=tamanio&&posicionfin>=0) posicion2=posicionfin;
	else{
		printf("\n Error 225 Buscarpalabraenlistaenpos posicionfin fuera de rango\n");
		return(-100);
		}
	
		
	}
	else
	{
		printf ("\n Error 223 Buscarpalabraenlistaenpos posicionini>posicionfin\n");
		return (-100);
	}
	//-----------------------
	
	encontrado=0;
	i=0;
	correccion=1;
	bucleinfinito=0;
	go=1;
	do
	{
		i++;
		if(i>70) printf("\nerror n 145265");
		posicion=(posicion2-posicion1)/2;
		
		// correccion de resto
		if (posicion2-posicion1==1) 
			{
				if (bucleinfinito) go=0;
				posicion=correccion;
				correccion=0;
				if(correccion==0 && posicion==0) {
				bucleinfinito=1;}
				
			}
		
		//fseek(archivo,(posicion+posicion1)*sizeof(struct nombre),SEEK_SET);
		ppfseek(archivo,(posicion+posicion1),SEEK_SET);
		ppfread(&nodo1,sizeof(struct nombre),1,archivo);
		
		
		devolvercadenanodo(cadena,nodo1,diccionario,256);
		
		//printf("\n Analizando palabra:%s p:%d",nodo1.palabra,(posicion+posicion1));
		
		// Si cadena1 < cadena2: -1   si cadena1 > cadena2: 1 si cadena1==cadena2: 0
		
				
		comparacion=comparacad(cadena ,palabra);
		
		
		if (comparacion==0)
			{ encontrado=1;
			}
		else if (comparacion==2) { 	*posicionencontrado= posicion+posicion1;
								  	return(2);}
		else if (comparacion==4) { 	*posicionencontrado= posicion+posicion1;
								  	return(4);}								  	
		else if (comparacion>0)
		{
			posicion2=posicion1+posicion;
			//printf("::p1=%d p2=%d",posicion1,posicion2);
		}
		else if (comparacion<0)
		{
			posicion1=posicion1+posicion;
			//printf("::p1=%d p2=%d",posicion1,posicion2);
		}
	}
	while(posicion1!=posicion2 && !encontrado && i<100 && go);
	//--->fclose(archivo);
	if (encontrado==1) 
		{	
			//printf(" E:!"); // nombre:%s posicion:%d",nodo1.palabra,nodo1.posicion);
			*posicionencontrado= posicion+posicion1;
			return (1);
		}
	else
		{
			//printf(" E:# ");
			return(-1);
		}
	
}



// Una vez estimada la posicion de la palabra, busca todas las palabras
int OjearDiccionario(long int * posicionencontrado1,long int * posicionencontrado2, char* palabra,struct Ppfile*archivo,long int posicionini,long int posicionfin,long int posicionencontrado,Pfile * diccionario)
{
	//--->FILE*archivo;
	struct nombre nodo1;
	long int posicion1,posicion2,posicion;
	int comparacion,encontrado,i,correccion,bucleinfinito, go;
	char cadena[256];

	//printf("\n Ojeando:");
	
		// 
	posicion=posicionencontrado;

	
	//fseek(archivo,posicion*sizeof(struct nombre),SEEK_SET);
	ppfseek(archivo,posicion,SEEK_SET);
	ppfread(&nodo1,sizeof(struct nombre),1,archivo);
	
	devolvercadenanodo(cadena,nodo1,diccionario,256);		
	comparacion=comparacad(cadena ,palabra);
	//printf(">%s<//%s",nodo1.palabra,palabra,comparacion);
	
	if (comparacion==2)//la busqueda esta arriba.
	{  
		//printf("{2}");
		go=1;
		while(comparacion==2&&go)
		{
		    posicion2=posicion;	
			posicion=posicion-5;
			if(posicion<=posicionini)
			{
				posicion=posicionini;
				go=0;
			}
			//printf("posiciones:2[%ld]1[%ld]",posicion2,posicion);
				//fseek(archivo,posicion*sizeof(struct nombre),SEEK_SET);
				ppfseek(archivo,posicion,SEEK_SET);
				ppfread(&nodo1,sizeof(struct nombre),1,archivo);
				
				devolvercadenanodo(cadena,nodo1,diccionario,256);		
			    comparacion=comparacad(cadena ,palabra);
			//printf("°|%s",cadena);
		}
		
		
		go=1;
		while (comparacion!=2&&go)
		{
			//printf("°>");
			posicion=posicion+1;
			
			if (posicion>=posicion2)
			{
				go=0;
				posicion=posicion2;
			}
		//	printf("posiciones:2[%ld]1[%ld]",posicion2,posicion);
				//fseek(archivo,posicion*sizeof(struct nombre),SEEK_SET);
				ppfseek(archivo,posicion,SEEK_SET);
				ppfread(&nodo1,sizeof(struct nombre),1,archivo);
				devolvercadenanodo(cadena,nodo1,diccionario,256);		
			    comparacion=comparacad(cadena ,palabra);

		}
		// si esta bien programado posicion2 es la primera posicion en que comparacad da 2
		posicion2=posicion;
		
		
		//------------FASE2
		
		posicion1=posicion;
		comparacion=0;
		go=1;
		while((comparacion==0||comparacion==4)&&go)
		{
			//printf("°$");
		    posicion1=posicion;	
			posicion=posicion-5;
			if(posicion<=posicionini)
			{
				posicion=posicionini;
				go=0;
			}
		
				//fseek(archivo,posicion*sizeof(struct nombre),SEEK_SET);
				ppfseek(archivo,posicion,SEEK_SET);
				ppfread(&nodo1,sizeof(struct nombre),1,archivo);
				devolvercadenanodo(cadena,nodo1,diccionario,256);		
			    comparacion=comparacad(cadena ,palabra);
			
		}
		
		
		go=1;
		while ((comparacion!=0&&comparacion!=4)&&go)
		{
			posicion=posicion+1;
			
			if (posicion>=posicion1)
			{
				go=0;
				posicion=posicion1;
			}
			//printf("###");
			//printf("posiciones:2[%ld]1[%ld]",posicion2,posicion);
				//fseek(archivo,posicion*sizeof(struct nombre),SEEK_SET);
				ppfseek(archivo,posicion,SEEK_SET);
				ppfread(&nodo1,sizeof(struct nombre),1,archivo);
				devolvercadenanodo(cadena,nodo1,diccionario,256);		
			    comparacion=comparacad(cadena ,palabra);
		//	printf("nodo[%s]",cadena);
		}
		posicion1=posicion;
		
		if(posicion1==posicion2) 
		{
			*posicionencontrado1=-1L;
			*posicionencontrado2=-1L;
			return(-1);
		}
		else
		{
			*posicionencontrado1=posicion1;
			*posicionencontrado2=posicion2-1;
			
			return(2);
			
		}
		
		
	}
	
	else if (comparacion==4)//la busqueda esta en medio.
	{
		//printf("{4}");
		posicion2=posicion;

		posicion1=posicion;
		go=1;
		//printf("°");
		while((comparacion==0||comparacion==4)&&go)
		{ 
			
		    posicion1=posicion;	
			posicion=posicion-5;
			//printf("*%ld",posicion);
			if(posicion<=posicionini)
			{
				posicion=posicionini;
				go=0;
				//printf("-%ld",posicion);
			}
			
				//fseek(archivo,posicion*sizeof(struct nombre),SEEK_SET);
				ppfseek(archivo,posicion,SEEK_SET);
				ppfread(&nodo1,sizeof(struct nombre),1,archivo);
				devolvercadenanodo(cadena,nodo1,diccionario,256);		
			    comparacion=comparacad(cadena ,palabra);
			    //printf(":%d",comparacion);
		}
		
		
		go=1;
		//printf("!");
		while ((comparacion!=0&&comparacion!=4)&&go)
		{
			posicion=posicion+1;
		//printf("*%ld",posicion);
			if (posicion>=posicion1)
			{
			//	printf("$");
				posicion=posicion1;
				go=0;
			}

				//fseek(archivo,posicion*sizeof(struct nombre),SEEK_SET);
				ppfseek(archivo,posicion,SEEK_SET);
				ppfread(&nodo1,sizeof(struct nombre),1,archivo);
				devolvercadenanodo(cadena,nodo1,diccionario,256);		
			    comparacion=comparacad(cadena ,palabra);
				//printf("c:%s>>%s<",nodo1.palabra,palabra);
		}
		
		posicion1=posicion;
		
		//FASE2
		
		posicion=posicion2;
		comparacion=4;
		go=1;
		//printf("#");
		while((comparacion==0||comparacion==4)&&go)
		{
		    posicion2=posicion;	
			posicion=posicion+5;
			//printf("*%ld",posicion);
			if(posicion>=posicionfin)
			{
				posicion=posicionfin;
				//printf("$%ld",posicion);
				go=0;
			}
		
				//fseek(archivo,posicion*sizeof(struct nombre),SEEK_SET);
				ppfseek(archivo,posicion,SEEK_SET);
				ppfread(&nodo1,sizeof(struct nombre),1,archivo);	
				devolvercadenanodo(cadena,nodo1,diccionario,256);	
			    comparacion=comparacad(cadena ,palabra);
			    //printf("c:%s>>%s<",nodo1.palabra,palabra);
			
		}
		
		//printf("Q");
		go=1;
		while (comparacion!=4&&go)
		{
			posicion=posicion-1;
			//printf("*%ld",posicion);
			if (posicion<=posicion2)
			{
			//	printf("$");
				go=0;
				posicion=posicion2;
			}

				//fseek(archivo,posicion*sizeof(struct nombre),SEEK_SET);
				ppfseek(archivo,posicion,SEEK_SET);
				ppfread(&nodo1,sizeof(struct nombre),1,archivo);
				devolvercadenanodo(cadena,nodo1,diccionario,256);		
			    comparacion=comparacad(cadena ,palabra);
			    //printf("c:%s>>%s<",nodo1.palabra,palabra);

		}	
		posicion2=posicion;
		
		
		*posicionencontrado1=posicion1;
		*posicionencontrado2=posicion2;
		//printf("ENCONTR: %ld %ld..",posicion1,posicion2);
			
		if(posicion1==posicion2)	
		{
			return(2);
		}
		else
		{
			return(4);
		}
	}
	
	else if (comparacion==0)//la busqueda esta abajo.
	{
		//printf("{0}");
		posicion1=posicion;
		posicion2=posicion;
		
				
		go=1;
		while((comparacion==0||comparacion==4)&&go)
		{
		    posicion2=posicion;	
			posicion=posicion+5;
			if(posicion>=posicionfin)
			{
				posicion=posicionfin;
				go=0;
			}
		
				//fseek(archivo,posicion*sizeof(struct nombre),SEEK_SET);
				ppfseek(archivo,posicion,SEEK_SET);
				ppfread(&nodo1,sizeof(struct nombre),1,archivo);
				devolvercadenanodo(cadena,nodo1,diccionario,256);		
			    comparacion=comparacad(cadena ,palabra);
			
		}
		
		
		go=1;
		while ((comparacion!=0&&comparacion!=4)&&go)
		{
			posicion=posicion-1;
			
			if (posicion<=posicion2)
			{
				go=0;
				posicion=posicion;
			}

				//fseek(archivo,posicion*sizeof(struct nombre),SEEK_SET);
				ppfseek(archivo,posicion,SEEK_SET);
				ppfread(&nodo1,sizeof(struct nombre),1,archivo);
				devolvercadenanodo(cadena,nodo1,diccionario,256);		
			    comparacion=comparacad(cadena ,palabra);

		}	
		posicion2=posicion;
		
		
		*posicionencontrado1=posicion1;
		*posicionencontrado2=posicion2;
				
		if(posicion1==posicion2)	
		{
			return(1);
		}
		else
		{
			return(4);
		}	
		
		
	}	
	else 
	{
		
		*posicionencontrado1=-1;
		*posicionencontrado2=-1;
		
		return(-1);
		
	}
	
	
	
	
	
}

















#endif
