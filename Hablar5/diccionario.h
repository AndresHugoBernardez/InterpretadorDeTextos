#ifndef _DICCIONARIO_H
#define _DICCIONARIO_H

#include<stdio.h>
#include<stdlib.h>
#include"cadenas.h"
#include"estructuras.h"
#include"pseudoarchivo.h"


/*

Ejemplo diccionario
<ente>
	<nombre>el</nombre>
	<clases>1</clases>
	<clase1>
		<significados>1</significados>
		<clase>artículo</clase>
		<gennum>masculino singular</gennum>
		<1> es un artículo que se usa antes de un sustantivo </1>
	</clase1>
</ente>

<ente>
	<nombre>la</nombre>
	<clases>1</clases>
	<clase1>
		<significados>1</significados>
		<clase>artículo</clase>
		<gennum>femenino singular</gennum>
		<1> es un artículo que se usa antes de un sustantivo </1>
	</clase1>
</ente>
*/

//========================================================================================
int cargarPalabraFile(char * cadena,char caracteractual,struct Pfile * archivo)
{
	int i;
	//long int posactual;
    char caracter;
				i=0;
			    caracter=caracteractual;
			    
				while (letraesalfanumerico(caracter))
				{
					cadena[i]=caracter;
					caracter=pfgetc(archivo);
					
					i=i+1;
				}
				
				//posactual=pftell(archivo);
				if (caracter!=EOF)pfseek(archivo,-1,SEEK_CUR);				
				cadena[i]='\0';
				return(i+1);
	
}

int CargarPalabraFile(char * cadena,char caracteractual,struct Pfile * archivo,int limite)
{
	int i;
	//long int posactual;
    char caracter;
				i=0;
			    caracter=caracteractual;
			    //printf(":");
				while (letraesalfanumerico(caracter)&&i<limite-2)
				{
					cadena[i]=caracter;
					caracter=pfgetc(archivo);
					//printf("%c",caracter);
					i=i+1;
				}
				//printf(":");
				//posactual=pftell(archivo);
				pfseek(archivo,-1,SEEK_CUR);				
				cadena[i]='\0';
				return(i+1);
	
}

int Buscacategoriafile(struct posicion *posicion,long int posicionactual,long int posicionactualfinal,char categoria[] ,struct Pfile * archivo)
{
	//FILE * archivo;
	int listo=0,encategoria=0,cierre=0,i=0,escategoria=0,j;
	long int posini,posfin,catini,catfin,posactual;
	char caracter, cadena[256]="pepito",cadena2[256]="";

	

	pfseek(archivo,posicionactual,SEEK_SET);
	caracter=1;
	
	while(caracter!=EOF && pftell(archivo)<=posicionactualfinal)
	{
		caracter=pfgetc(archivo);
		         
		
		if(caracter=='<')
		{
			cierre=0;
			encategoria=1;
			//printf("\n<<<<<<<<<<");
			//--------------
			
			catini=pftell(archivo)-1;
			posfin=catini;
			
		}
		else if (caracter=='>')
		{
			encategoria=0;
			cierre=0;
			//printf("\n>>>>>>>>>>>");
			//--------------
			
			catfin=pftell(archivo)-1;
			posini=catfin;
			
			if (listo==1)
			{
				posicion->inicial=posini;
				listo=2;
			}
			else if (listo==3)
			{
				posicion->catfinal=catfin;
				listo=4;
			}
		}
		else if (caracter=='/')
		{
			cierre=1;
			//printf("\n/////////");
			//--------------
			
		}
		else if (letraesalfanumerico(caracter))
			{   // cargar cadena y posicionar cursor
				
				
				
				if( encategoria)
				{
				
					cadena[0]='\0';
					while(caracter=='.'||caracter==' '||letraesalfanumerico(caracter))
					{
									
						if(letraesalfanumerico(caracter))CargarPalabraFile(cadena2,caracter,archivo,256);
						else if(caracter==' ') {cadena2[0]=' ';cadena2[1]='\0';}
						else if(caracter=='.') {cadena2[0]='.';cadena2[1]='\0';}
						Sumacadenas(cadena,cadena,cadena2,256);
						caracter=pfgetc(archivo);
					}
					if(caracter!=EOF)pfseek(archivo,-1,SEEK_CUR);
					
					 j=largocadena(cadena);
					 
					 j--;
					 caracter=cadena[j];
					 while(caracter==' '&&j>0)
					 {
					 	
					 	cadena[j]='\0';
					 	j--;
					 	caracter=cadena[j];
					 }
					 
					
					//printf(":%s*",cadena);
					//--------------
					
					
					
					if (!comparacad(cadena,categoria))
					{
						//printf("--->es categoria");
						escategoria=1;
						if (cierre==0)
						{
							
								posicion->catinicial=catini;
								listo=1;
							
							
						}
						else if (cierre==1)
						{
							if ( listo==2) 
							{
								posicion->final=posfin;
								listo=3;
								cierre=0;
							}
							
						}
						
					}
				}
				
				else
				CargarPalabraFile(cadena,caracter,archivo,256);
			}	
			
			 if (listo==4)	
			{
				//fclose(archivo);
				return(1);
			
			}
	}
	if (listo<4)
	{
	//fclose(archivo);
	return (0);
	}
	
	
}


/*
int BuscaNombreCategoria(struct posicion * posicionfinal, long int inicio, long int final,char*cadena1,struct Pfile * archivo)
{ 
	long int  actual, actualfinal;
	char caracter, cadena[256], ente[10]="ente",nombre[10]="nombre";
	struct posicion posicion1, posicion2;
	
actual=inicio;
actualfinal=final;

while (Buscacategoriafile(&posicion1,actual,actualfinal,ente,archivo))
{

actual=posicion1.catfinal;

if (Buscacategoriafile(&posicion2,posicion1.inicial,posicion1.final,nombre,archivo))
	{
	
	//printf("\n-------------------------------\n:");
	//printfentrepos(posini2,posfin2,"hola.txt");
	//printf(":");
	
	caracter='a';
	pfseek(archivo,posicion2.inicial,SEEK_SET);
	while (caracter!=EOF&& pftell(archivo)<=posicion2.final)
	{
		caracter=pfgetc(archivo);
		if (letraesalfanumerico(caracter))
		{
			CargarPalabraFile(cadena,caracter,archivo,256);
			//printf("cadena:%s:",cadena);
			if(!comparacad(cadena,cadena1)) {
			
			posicionfinal->catinicial=posicion1.catinicial;
			posicionfinal->catfinal=posicion1.catfinal;
			posicionfinal->inicial=posicion1.inicial;
			posicionfinal->final=posicion1.final;
				
			//printf("es cadena");	
			return(1);
			}
		}
	}
	
	//printf("\n==============\n:");
	//printfentrepos(catini,catfin,direccion);
	//printf(":\n-------------------------------\n");
	}

}
return (0);
}
*/


/*
// Carga en una cadena lo que esta entre comillas
int CargarCadenaEntreComillas(char * cadena,long int posicionini, long int posicionfin, Pfile* diccionario,long int limitechar)
{
	char caracter;
	bool entrecomillas;
	int i,limite;
	
	pfseek(diccionario,posicionini,SEEK_SET);
	caracter='a';
	while (caracter!='"'&& caracter!=EOF && pftell(diccionario)<posicionfin)
	{caracter=pfgetc(diccionario);
	}
	
	caracter=pfgetc(diccionario);
	i=0;
	limite=limitechar-1;
	while (caracter!='"'&& caracter!=EOF && pftell(diccionario)<posicionfin&&i<limite)
	{
		cadena[i]=caracter;
		caracter=pfgetc(diccionario);
		i++;
	}
	caracter[i]='\0';
	return(i);
}


*/



#endif
