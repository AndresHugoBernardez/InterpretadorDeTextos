#ifndef _CADENAS_H
#define _CADENAS_H

#include<stdio.h>
#include<stdlib.h>
#include"caracteres.h"

//====================================CADENAS



int charnumber(char c)
{
	switch(c)
	{
	case '0': return 0;break;
	case '1': return 1;break;
	case '2': return 2;break;
	case '3': return 3;break;
	case '4': return 4;break;
	case '5': return 5;break;
	case '6': return 6;break;
	case '7': return 7;break;
	case '8': return 8;break;
	case '9': return 9;break;
	default: return 0;
	}
	
	
}

char numberchar(int n)
{
	switch(n)
	{
	case 0: return '0';break;
	case 1: return '1';break;
	case 2: return '2';break;
	case 3: return '3';break;
	case 4: return '4';break;
	case 5: return '5';break;
	case 6: return '6';break;
	case 7: return '7';break;
	case 8: return '8';break;
	case 9: return '9';break;
	default: return 'x';
	}
	
	
}



int chartoint(char * cadena)
{
	int i,ten,n,r;
	char c;
	
	i=-1;
	c='a';

	while(c!='\0')
	{
		i++;
		c=cadena[i];
		
	}
	i--;

	r=0;
	ten=1;
	while (i>=0)
	{
		if (letraesnumero(cadena[i]))
		{
		n=charnumber(cadena[i])	;
		r=r+ten*n;
		ten=ten*10;
		}
		i--;
		
	}
	
	return(r);
	
}


void inttochar(char * cadena, int numero)
{
  char inversa [16],c;
  int i,k,ten,resto,unidad,cifra;
  
  
	if(numero<=0)
	{
 	 	inversa[0]='0';
 	 	inversa [1]='\0';
  		i=1;
 	}
 	else
 	{
  		resto=0;
  		ten=1;
  		i=0;
		while (numero / ten != 0)
		{
			ten=ten*10;
			cifra=(numero-resto)%ten;
			resto=resto+cifra;
			unidad=cifra/(ten/10);	
			//printf("\n cifra:%d, resto:%d, unidad:%d",cifra,resto,unidad);
			c=numberchar(unidad);
			inversa[i]=c;
			i++;				  	
		}
		
		
	}
	
	k=i-1;
	i=k;
	while (i>=0)
	{
		cadena[k-i]=inversa[i];
		i--;
						
	}
	cadena[k+1]='\0';
	
	
}




int asignacadena(char * cadena1, char * cadena2)
{
	int i;
	
	i=0;
	
	while ( cadena2[i]!='\0')
	{
		cadena1[i]=cadena2[i];
		i++;
	}
	cadena1[i]='\0';
	return(i+1);
}
int Asignacadena(char * cadena1, char * cadena2,int limite)
{
	int i;
	
	i=0;
	
	while ( cadena2[i]!='\0'&&i<limite-1)
	{
		cadena1[i]=cadena2[i];
		i++;
	}
	cadena1[i]='\0';
	return(i+1);
}


int sumacadenas(char*cadena3,char * cadena1, char * cadena2)
{
	int i,j;
	
	i=0;
	
	while ( cadena1[i]!='\0')
	{
		cadena3[i]=cadena1[i];
		i++;
	}
	j=0;
	while ( cadena2[j]!='\0')
	{
		cadena3[i]=cadena2[j];
		i++;
		j++;
	}
	
	cadena3[i]='\0';
	return(i+1);
}

int Sumacadenas(char*cadena3,char * cadena1, char * cadena2,int limite)
{
	int i,j;
	
	i=0;
	
	while ( cadena1[i]!='\0'&&i<limite-1)
	{
		cadena3[i]=cadena1[i];
		i++;
	}
	j=0;
	while ( cadena2[j]!='\0'&&i<limite-1)
	{
		cadena3[i]=cadena2[j];
		i++;
		j++;
	}
	
	cadena3[i]='\0';
	return(i+1);
}


// Da el número de caracteres de la cadena

int largocadena(char * cadena)
{
	int i;
	i=0;
	while(cadena[i]!='\0') i++;
	return(i);
}


// Si cadena1 < cadena2: -1   si cadena1 > cadena2: 1 si cadena1==cadena2: 0

int comparacad(char * cadena1, char * cadena2)
{
	int i;
	
	i=0;
	
	while (cadena1[i]!='\0'&& cadena2[i]!='\0'&& cadena1[i]==cadena2[i])
	{
		
		i++;
		
		//printf("\n 1: %c 2:%c",cadena1[i],cadena2[i]);
	}
		
	/*if(i>0)	
       {
		   	
		if (cadena1[i-1]=='_'&&cadena2[i-1]=='_')
		    {
				// ejemplo  Estados_     Estados_Unidos
			  if      (cadena1[i]=='\0'&&cadena2[i]!='\0') return(-3);
			   // Ejemplo Estados_Unidos  Estados_
		     else  if(cadena1[i]!='\0'&&cadena2[i]=='\0') return(3);
		 	}
	   }*/
	   //Ejemplo marcos marcos
	if (cadena1[i]=='\0'&& cadena2[i]=='\0')return(0);
	// Ejemplo Estados Estados_
    else if (cadena1[i]=='\0'&&letranoespalabra(cadena2[i])) return(-4);
	// Ejemplo Estados_ Estados
    else if(letranoespalabra(cadena1[i])&&cadena2[i]=='\0') return(4);
	// Ejemplo Ana Analia
	else if (i>0&& cadena1[i]=='\0'&& cadena2[i]!='\0') return(-2);
	// Ejemplo Analia Ana
	else if (i>0&& cadena1[i]!='\0'&& cadena2[i]=='\0') return(2);
	//Ejemplo  chancho pato
	else if (cadena1[i]<cadena2[i])return(-1);
	//Ejemplo   pato  chancho
	else if (cadena1[i]>cadena2[i])return(1);	
	else return(-1);
	
	
}
//========================================================================================
#endif
