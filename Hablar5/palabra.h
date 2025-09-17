#ifndef _PALABRA_H
#define _PALABRA_H

#include<stdio.h>
#include<stdlib.h>
#include"cadenas.h"
#include"estructuras.h"
#include"pseudoarchivo.h"

//========================================================================================
int cargarPalabraFile(char * cadena,char caracteractual,struct Pfile * archivo)
{
	int i;
	long int posactual;
    char caracter;
				i=0;
			    caracter=caracteractual;
			    
				while (letraesalfanumerico(caracter))
				{
					cadena[i]=caracter;
					caracter=pfgetc(archivo);
					i=i+1;
				}
				posactual=pftell(archivo);
				pfseek(archivo,-1,SEEK_CUR);				
				cadena[i]='\0';
				return(i+1);
	
}

int CargarPalabraFile(char * cadena,char caracteractual,struct Pfile * archivo,int limite)
{
	int i;
	long int posactual;
    char caracter;
				i=0;
			    caracter=caracteractual;
			    
				while (letraesalfanumerico(caracter)&&i<limite-2)
				{
					cadena[i]=caracter;
					caracter=pfgetc(archivo);
					i=i+1;
				}
				posactual=pftell(archivo);
				pfseek(archivo,-1,SEEK_CUR);				
				cadena[i]='\0';
				return(i+1);
	
}

int Buscacategoriafile(struct posicion *posicion,long int posicionactual,long int posicionactualfinal,char categoria[] ,struct Pfile * archivo)
{
	//FILE * archivo;
	int listo=0,encategoria=0,cierre=0,i=0,escategoria=0;
	long int posini,posfin,catini,catfin,posactual;
	char caracter, cadena[256]="pepito";

	

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
				
				CargarPalabraFile(cadena,caracter,archivo,256);
				//printf("\n:%s:",cadena);
				//--------------
				
				
				if(encategoria)
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





#endif
