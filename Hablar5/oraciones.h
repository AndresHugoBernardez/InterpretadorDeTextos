#ifndef _ORACIONES_H
#define _ORACIONES_H

#include<stdio.h>
#include<stdlib.h>

#include"diccionario.h"
#include"estructuras.h"
#include"lista.h"
#include"pseudoarchivo.h"
#include"sintaxisfile.h"

//===========================ORACIONES
/*
int contaroraciones(long int inicio, long int fin, FILE * archivo)
{
	char caracter;
	int cantidad;
	
	fseek(archivo,inicio,SEEK_SET);
	cantidad=0;
	caracter=fgetc(archivo);
	while (caracter!=EOF && ftell(archivo)<=fin)
	{
		if (caracter=='.'||caracter=='?'||caracter=='!') cantidad=cantidad+1;
		caracter=fgetc(archivo);
	}
	return(cantidad);
}



int contarparrafos(long int inicio, long int fin, FILE * archivo)
{
	char caracter;
	int cantidad,enparrafo;
	
	fseek(archivo,inicio,SEEK_SET);
	cantidad=0;
	enparrafo=0;
	caracter=fgetc(archivo);
	while (caracter!=EOF && ftell(archivo)<=fin)
	{
		if (letraesalfanumerico (caracter)) enparrafo=1;
		else if ((enparrafo)&&(caracter=='\n')) 
		{
		enparrafo=0;
		cantidad=cantidad+1;
		}
		caracter=fgetc(archivo);
	}
	if (enparrafo) return(cantidad+1);
	return(cantidad);
}
*/



int Contarpalabras(struct palabras palabras[])
{
	int i;
	char fin[6]="@FIN";
	
	while (comparacad(palabras[i].word,fin)&&i<200) i++;
	return(i);
}


	
//***********************************************************
//***********************************************************
//***********************************************************
//***********************************************************

int Leerpalabra(char * cadena,Pfile * archivo,int limitechar)
{
	char caracter,letra,punto;
	int limite;
	long int i,j,posicion;
	bool go;
	
	go=true;
	caracter='a';
	limite=limitechar-1;
	
	i=largocadena(cadena);
	
	while(caracter!=EOF&& caracter!='\n'&&i<limite&&go)
	{
		
		caracter=pfgetc(archivo);
		
		//printf("z[%c]",caracter);
		if (caracter==' '||caracter=='\t')
		{
			if (i!=0) {
			cadena[i]=caracter;
			i++;
			}
			
		}
		
		else if(letraespalabra(caracter))
		{
			j=0;
			
			while(letraespalabra(caracter)&&i<limite)
			{   
				cadena[i]=caracter;
				letra=caracter;
				
				caracter=pfgetc(archivo);
				
				i++;				
				j++;
			}
			
			//  deteccion de siglas
			punto='.';
			
			if (caracter=='.'&&j==1)
			{	
				
				//printf("PUNTO");
				i=i-1;
				while (letraesalfabetica(letra)&& punto=='.'&&i<limite)
				{	
					cadena[i]=letra;
					i++;
					if(i<limite)
					{
					cadena[i]=punto;
					i++;
					}
					letra=pfgetc(archivo);
					caracter=letra;
					if(letra!=EOF)
					{
					punto=pfgetc(archivo);
					caracter=punto;
					}
					
					
				}
				
				if(punto!=EOF&&letra!=EOF)
				{
				
				pfseek(archivo,-1,SEEK_CUR);
			    }
				//else(caracter='a');
				
				
			}
			//------------	
		
			
			if(caracter!=EOF)pfseek(archivo,-1,SEEK_CUR);
			go=false;
			caracter='a';
			
			
		}
		else if(caracter=='.')
		{
			cadena[i]=caracter;
			
			letra=pfgetc(archivo);
			
			if(letra=='.')
			{
				letra=pfgetc(archivo);
				if(letra=='.')
				{
					i++;
					cadena[i]='.';
					i++;
					cadena[i]='.';
					
				}
				else
				pfseek(archivo,-2,SEEK_CUR);
			}
			else
			pfseek(archivo,-1,SEEK_CUR);
			
			i++;
			go=false;;
		}
		else if (letraessimbolotexto(caracter)||letraessimbolomatematico(caracter))
		{
			
			cadena[i]=caracter;
			
			if (i==0) go=false;;
			
			i++;
			
		}
		
	}
	cadena[i]='\0';
	
	if(caracter==EOF)return(EOF);
	else if (caracter=='\n') return('\n');
	else return('a');
}


void ConvertirOracion(struct sfile * Palabras, Pfile * texto, Ppfile * lista, Pfile *diccionario)
{
	
	char cadena[256],cadenaaux[256],cadena2[256],finparrafo[3],guion[3]="_";
	int k,encontrado,comparacion,respuesta,j;
	long int posicion1,posicion2,posicion3,posicion4,posicioninicial,cursor;
	struct nombre nodo1,nodoaux;
	struct palabras palabra, finalparrafo;
	char caracter,caracteraux;
	bool Encontrad,Mayuscula,minusculizar;

	
	
	//Inicializando variables
	        
			InicializarPalabraEnCero(&palabra);
			
	        
			finparrafo[0]='\n';
			finparrafo[1]='\0';
			
			InicializarPalabraEnCero(&finalparrafo);
			Asignacadena(finalparrafo.word,finparrafo,30);
			
	
	//----
	
	
	sfseek(Palabras,0,SEEK_SET);
	Mayuscula=false;
	minusculizar=false;
	pfseek(texto,0,SEEK_SET);
	
	cursor=pftell(texto);
	caracter='a';
	
	
	
	
	
	while(caracter!=EOF)
	{
		
		
		
		posicion1=0;
		ppfseek(lista,0,SEEK_END);
		//posicion2=ftell(lista)/sizeof(struct nombre)-1;
		posicion2=ppftell(lista)-1;
		
		posicion3=0;
		//Asignacadena(cadena,Palabras[i].palabra,256);
		
		cadena[0]='\0';
		pfseek(texto,cursor,SEEK_SET);
		caracter=Leerpalabra(cadena,texto,256);
		if(caracter=='\n') { 
		cursor=pftell(texto);}
		
		//printf("\n[%s]",cadena);
		if (caracter=='\n'&&cadena[0]=='\0')
		{
						
			sfput(finalparrafo,Palabras);
			Mayuscula=true;
		}
		
		
		encontrado=0;
		Encontrad=false;
		k=0;
		comparacion=1;
		
		if (sftell(Palabras)==0) Mayuscula=true;
		else if(sftell(Palabras)>0 &&(Palabras->cur->anterior->palabra.word[0]=='.'||Palabras->cur->anterior->palabra.word[0]=='¿'||Palabras->cur->anterior->palabra.word[0]=='¡') && Palabras->cur->anterior->palabra.word[1]=='\0')
		{
			Mayuscula=true;
		   }   
		
		if(minusculizar)
		{
			cadena[0]=convertirdemayusculaaminuscula(cadena[0]);
			Mayuscula=false;
			minusculizar=false;
		}
		
		
		
		while (encontrado==0&&caracter!=EOF&&caracter!='\n')
		{
		    //printf("*");
			respuesta=Buscarpalabraenlistaenpos(&posicioninicial,cadena,lista,posicion1,posicion2,diccionario);
			if(respuesta>0)
			{
				//printf("|");
				
				respuesta=OjearDiccionario(&posicion1,&posicion2,cadena,lista,posicion1,posicion2,posicioninicial,diccionario);

				if (respuesta>0)
				{
					//printf(">");
					posicion3=posicion1;
					
					
					
					//--------
					ppfseek(lista,posicion1,SEEK_SET);
					ppfread(&nodo1,sizeof(struct nombre),1,lista);
						
					devolvercadenanodo(cadena2,nodo1,diccionario,256);
					comparacion=comparacad(cadena2 ,cadena);
					if(comparacion==0)
					{
						nodoaux=nodo1;
						cursor=pftell(texto);
						Encontrad=true;
						
					}
					//------
					
					if(posicion1!=posicion2)
					{
					//	printf("#");
						k=k+1;
						
						
						
						Asignacadena(cadenaaux,cadena,256);
						caracteraux=Leerpalabra(cadenaaux,texto,256);

						if (caracteraux!='\n'&&caracteraux!=EOF)
						{
							Asignacadena(cadena,cadenaaux,256);
						//	printf("[%s]",cadena);
						}
						else 
						{
							Sumacadenas(cadena,cadena,guion,256);
							Sumacadenas(cadena,cadena,guion,256);
						}
					}
					else
					{
						
						if (comparacion==0)
						{ 
						//	printf(":bingo!");
							
							
							Asignacadena(palabra.word,nodoaux.palabra,30);
							palabra.posicionlista=nodoaux.posicion;
							palabra.posicionlista2=nodoaux.posicion2;
							
							
							sfput(palabra,Palabras);
							
							Mayuscula=false;
							minusculizar=false;
							
							encontrado=1;
						}
						else 
						{
						
					    //printf("&");
						k=k+1;
	
						Asignacadena(cadenaaux,cadena,256);
						caracteraux=Leerpalabra(cadenaaux,texto,256);

						if (caracteraux!='\n'&&caracteraux!=EOF)
						{
							Asignacadena(cadena,cadenaaux,256);
						//	printf("[%s]",cadena);
						}
						else 
						{
							Sumacadenas(cadena,cadena,guion,256);
							Sumacadenas(cadena,cadena,guion,256);
						}
						
						}
					}
					
				}
				else 
				{
					//printf("outOje");
				encontrado=-2;
				}
			}
			
			
			else if (k>0)
				{
					//printf("KK");
										
					
					if (Encontrad==true)
						{ 
						
						
														
							Asignacadena(palabra.word,nodoaux.palabra,30);
							palabra.posicionlista=nodoaux.posicion;
							palabra.posicionlista2=nodoaux.posicion2;
							
							
							sfput(palabra,Palabras);
							
							//printf(":bingo4!");
							encontrado=1;
							Mayuscula=false;
							minusculizar=false;
						}
					else encontrado=-7;
				}
			else encontrado=-1;	
			
			
			
		}
		
	//printf("encontrado:%d",encontrado);		
		if (encontrado<0&&caracter!=EOF&&caracter!='\n')
		{
			
			if(Mayuscula) minusculizar=true;
			else
			
			{

			cadena[0]='\0';
			pfseek(texto,cursor,SEEK_SET);
		    caracter=Leerpalabra(cadena,texto,256);

		    cursor=pftell(texto);
		    
		    
		    
			
			Asignacadena(palabra.word,cadena,30);
			palabra.posicionlista=-1;
			palabra.posicionlista2=-1;
			
							
			sfput(palabra,Palabras);
			
			
			}
		}
	
	
		//if(caracter!=EOF&&!minusculizar&&caracter!='\n')i++;
		
	
	}
		
	
	
}
#endif
