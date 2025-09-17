#ifndef _preguntador
#define _preguntador

#include "stdio.h"
#include "stdlib.h"
#include "diccionario.h"
#include "caracteres.h"
#include "cadenas.h"
#include "estructuras.h"
#include "sintaxisfile.h"
#include "sintaxis.h"
#include "analisissintactico.h"


//Ejemplo En la plaza Juan corre y trepa a los árboles. Un verbo corta la búsqueda de sintagma de preposicion
//   Juan corre por la palaza y pedro trepa por los árboles. La "y" divide a los sujetos de sus respectivas acciones.
int quienaccion(char * accion, long int posinicio, long int posfinal,struct sfile * Palabras)
{
	long int posverboini,posverbofin,ini,fin;
	struct palabras actual;
	bool seguir=true;
	int personaverbo;
	
	sfseek(Palabras,posinicio,SEEK_SET);
	while (Palabras->cursor<posfinal&&seguir)
	{
		actual=Palabras->cur->palabra;
		
		if(actual.sintaxis!=ORACION&&actual.sintaxis!=0)
		{
			
			PosicionSintaxis(&ini,&fin,Palabras->cursor,posfinal,actual.sintaxis,Palabras);
			actual=Palabras->cur->palabra;
			
		}
		if(actual.sintaxis==N_VERBAL&&!comparacad(actual.word,accion))
		{
			personaverbo=actual.persona;
			posverboini=ini;
			posverbofin=fin;
			seguir=false;
			
		}
		
		
		
		if(seguir)sfseek(Palabras,1,SEEK_CUR);
		
	}
	
	if (seguir==false)
	{
		sfseek(Palabras,posverboini,SEEK_SET);
		seguir=true;
		while(Palabras->cursor>posinicio&& seguir==true)
		{
			actual=Palabras->cur->palabra;
			
			if(actual.sintaxis!=ORACION&&actual.sintaxis!=0)
			{
			
			PosicionSintaxisAlreves(&ini,&fin,posinicio,Palabras->cursor,actual.sintaxis,Palabras);
			actual=Palabras->cur->palabra;
			
			}
			if((actual.sintaxis==SUJETO)&&actual.persona==personaverbo)
			{
				
				
				sfseek(Palabras,ini+1,SEEK_SET);
				
				while (Palabras->cursor<fin)
				{
					actual=Palabras->cur->palabra;
					printf("%s ",actual.word);
					sfseek(Palabras,1,SEEK_CUR);
				}
			
				
				seguir=false;
				
			}
			if(seguir==true)sfseek(Palabras,-1,SEEK_CUR);
			
		}
		
		if (seguir==true)
		{
			
			
			sfseek(Palabras,posverbofin,SEEK_SET);
			while(Palabras->cursor<posfinal&& seguir==true)
			{
				//printf("TT ");
				actual=Palabras->cur->palabra;
				
				if(actual.sintaxis!=ORACION&&actual.sintaxis!=0)
				{
				
				PosicionSintaxis(&ini,&fin,Palabras->cursor,posfinal,actual.sintaxis,Palabras);
				actual=Palabras->cur->palabra;
				//printf("kk");
				}
				if((actual.sintaxis==SUJETO)&&actual.persona==personaverbo)
				{
					
					
					sfseek(Palabras,ini+1,SEEK_SET);
					
					while (Palabras->cursor<fin)
					{
						actual=Palabras->cur->palabra;
						printf("%s ",actual.word);
						sfseek(Palabras,1,SEEK_CUR);
					}
				
					
					seguir=false;
					
				}
				if(seguir==true)sfseek(Palabras,1,SEEK_CUR);
				
			}
			
		}
		
		
		
		
		
		
		
	}

	
	
	return(0);
	
	
}




void preguntar(struct sfile * Palabras)
{
char cadena[256]="hola",chau[10]="chau", donde[10]="donde",quien[10]="quien",que[10]="que",corre[10]="corre";
long int posinicio,posfinal;

while( comparacad(cadena,chau))
{
	
	printf("\nPregunte:");
	scanf("%s",cadena);
	printf("\nha dicho '%s'",cadena);
	
   if(!comparacad(cadena,quien))	
   {
   	printf("\nQUIEN\n");
   	
   	posfinal=0;
   		while(PosicionSintaxis(&posinicio,&posfinal,posfinal,Palabras->tamanio,ORACION,Palabras)>0)
	{
		printf("\n %d\n",posinicio);
		quienaccion(corre,posinicio,posfinal,Palabras);
	
	}
   }
	
}





}






#endif
