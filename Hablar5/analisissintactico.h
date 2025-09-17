#ifndef _analisissintactico
#define _analisissintactico

#include "stdio.h"
#include "stdlib.h"
#include "diccionario.h"
#include "caracteres.h"
#include "cadenas.h"
#include "estructuras.h"
#include "sintaxisfile.h"
#include "sintaxis.h"
#include "buclefile.h"




int PoneSeparadores(long int inicio,long int final, struct palabras Palabra, struct sfile * Palabras)
{
	struct palabras oracion;
	
	
	if (inicio<=final&&inicio>=0&&final<=Palabras->tamanio)
	{
	oracion=Palabra;
	
	sfseek(Palabras,inicio,SEEK_SET);
	
	oracion.pos=1;
	oracion.id=Palabras->ids;
	sfput(oracion,Palabras);
	
	sfseek(Palabras,final+1,SEEK_SET);
	oracion.pos=2;
	oracion.id=Palabras->ids;
	sfput(oracion,Palabras);
	
	Palabras->ids++;
	
	return(1);
	}
	else
	return(-1);
	
}




void SeparadorDeOraciones(struct sfile * Palabras)
{
	char frase[5]="^^^",caracter;
	long int inicio,final;
	struct palabras  palabra,oracion;
	
	
	InicializarPalabraEnCero(&oracion);
	
	Asignacadena(oracion.word,frase,30);
	oracion.sintaxis=ORACION;
	
	
	sfseek(Palabras,0,SEEK_SET);

	inicio=0;
	
	
	while (Palabras->cursor<Palabras->tamanio)
	{
      palabra=Palabras->cur->palabra;
	  
	  //printf("[%s]",palabra.word);
	  if(palabra.word[1]=='\0')
	  {
	  	//printf("ok");
	  	caracter=palabra.word[0];
	  	
	  	if (caracter=='.'||caracter=='?'||caracter=='!'||caracter=='\n')
	  	{
		  	
			//printf("ok");
			
			
	  		if(caracter!='\n' ||  caracter=='\n'&& Palabras->cur->anterior->palabra.sintaxis!=ORACION)
	  		{
			 
	  			sfseek(Palabras,1,SEEK_CUR);
	  		
				final=sftell(Palabras);
	  		
	  			PoneSeparadores(inicio,final,oracion,Palabras);
	  			
	  		   					
					if((Palabras->cursor<Palabras->tamanio)&&Palabras->cur->palabra.word[0]=='\n'&&Palabras->cur->palabra.word[1]=='\0') 
						sfseek(Palabras,1,SEEK_CUR);

				 	inicio=sftell(Palabras);

	  		}
	  		
	  		
	  			
		}
	  }
      
      
      sfseek(Palabras,1,SEEK_CUR);
    }
	
	if(inicio<Palabras->tamanio)
	{
	
		final=sftell(Palabras);
	  	PoneSeparadores(inicio,final,oracion,Palabras);
	}
	
}





int PosicionSintaxis(long int * posinicio,long int * posfinal,long int inicio,long int fin,int sintaxis,struct sfile * Palabras)
{
	bool go;
	int id;
	sfseek(Palabras,inicio,SEEK_SET);
	
	go=false;
	while (Palabras->cursor<fin&& go==false)
	{
		if (Palabras->cur->palabra.sintaxis==sintaxis)
		{
			if (Palabras->cur->palabra.pos==1 )
			{
			*posinicio=sftell(Palabras);
			id=Palabras->cur->palabra.id;
			go=true;
			}
			else if (Palabras->cur->palabra.pos==3)
			{
				*posinicio=sftell(Palabras);
				*posfinal=*posinicio;
				return(2);
			}
		
		}
		
		if(go==false) sfseek(Palabras,1,SEEK_CUR);
	}
	
	if (go==true)
	{
		while (Palabras->cursor<fin&& go==true)
		{
			//printf("°");
			if (Palabras->cur->palabra.sintaxis==sintaxis &&Palabras->cur->palabra.pos==2&&Palabras->cur->palabra.id==id )
			{
			*posfinal=sftell(Palabras);
			go=false;
			return(1);
			}
			if(go==true) sfseek(Palabras,1,SEEK_CUR);
		}
		
		return(-2);
	}
	
	
	
	
     return(-1)	;
}


int PosicionSintaxisAlreves(long int * posinicio,long int * posfinal,long int inicio,long int fin,int sintaxis,struct sfile * Palabras)
{
	bool go;
	int id;
	sfseek(Palabras,fin,SEEK_SET);
	
	go=false;
	while (Palabras->cursor>inicio&& go==false)
	{
		if (Palabras->cur->palabra.sintaxis==sintaxis)
		{
			if (Palabras->cur->palabra.pos==2 )
			{
			*posfinal=sftell(Palabras);
			id=Palabras->cur->palabra.id;
			go=true;
			}
			else if (Palabras->cur->palabra.pos==3)
			{
				*posinicio=sftell(Palabras);
				*posfinal=*posinicio;
				return(2);
			}
		
		}
		if(go==false) sfseek(Palabras,-1,SEEK_CUR);
	}
	
	if (go==true)
	{
		while (Palabras->cursor>inicio&& go==true)
		{
			//printf("°");
			if (Palabras->cur->palabra.sintaxis==sintaxis &&Palabras->cur->palabra.pos==1&&Palabras->cur->palabra.id==id )
			{
			*posinicio=sftell(Palabras);
			go=false;
			return(1);
			}
			if(go==true) sfseek(Palabras,-1,SEEK_CUR);
		}
		
		return(-2);
	}
	
	
	
	
     return(-1)	;
}




void AnalizadorDeArticulos(long int inicio, long int fin,struct sfile * Palabras)
{
	struct palabras actual,separador;
	char sintagma[10]="*S_A*",_el[5]="el",_la[5]="la",_los[5]="los",_las[5]="las",_un[5]="un";
	long int sini,sfin;
	int gen_num,persona,ok,saltear;
	bool relativo;
	
	
	persona=0;
	InicializarPalabraEnCero(&separador);
	Asignacadena(separador.word,sintagma,30);
	separador.sintaxis=S_ARTICULO;
	
	sfseek(Palabras,inicio,SEEK_SET);
	

		
	if (fin<Palabras->tamanio&&inicio<=fin)
	{
	
		while(Palabras->cursor<=fin)
		{
			
			actual=Palabras->cur->palabra;
			
			if(actual.clase==ARTICULO||actual.clase==ADJ_DETERMINATIVO)
			{
				sini=sftell(Palabras);
					gen_num=0;
					ok=0;
				
					
				/*saltear=0;
				
				if(!comparacad(actual.word,_el)||!comparacad(actual.word,_la)||!comparacad(actual.word,_los)||!comparacad(actual.word,_las)||!comparacad(actual.word,_un))
				{
					saltear=1;
				}*/	
				
				relativo=false;
				do
				{
					if(gen_num==0)gen_num=actual.gen_num;
					else if (gen_num==actual.gen_num)ok++;	
					sfseek(Palabras,1,SEEK_CUR);
					actual=Palabras->cur->palabra;
					
					if(actual.clase==RELATIVO) relativo=true;
					
					
					/*if(saltear==1)
					{
						saltear=0;
						sfseek(Palabras,1,SEEK_CUR);
					}
					actual=Palabras->cur->palabra;
					*/
					
					
				}
				while (actual.clase!=VERBO&&(actual.clase==SUSTANTIVO || actual.clase==ADJETIVO|| actual.clase==0)&& Palabras->cursor<fin&&!(actual.clase==SIMBOLO&&actual.word[0]=='.')&&relativo==false);
				
				
				if(relativo==false)
				{
				
					sfin=sftell(Palabras);
					
					separador.gen_num=gen_num;
					/*if(i>1&&ok>0){printf("okgenum");}
					else printf("error gen_num");*/
					persona=0;
					if(1<=gen_num&&gen_num<=3)
					{
						persona=3;
						//printf("persona_:%d",persona);
					}
					else if(4<=gen_num&&gen_num<=6)
					{
						persona=6;
						//printf("persona_:%d",persona);
					}
					
					separador.persona=persona;
					
					
					PoneSeparadores(sini,sfin,separador,Palabras);
					fin=fin+2;
				}
				else if(relativo==true)
				{
					sfseek(Palabras,-1,SEEK_CUR);
					Palabras->cur->palabra.clase=ART_RELATIVO;
					sfseek(Palabras,1,SEEK_CUR);
					
				}
				
			}
			
					
			
			sfseek(Palabras,1,SEEK_CUR);
		}
	
	}
	
}







void AnalizadorDePronombres(long int inicio, long int final,struct sfile * Palabras)
{
	struct palabras actual;
	long int ini,fini;
	int respuesta;
	
	
	
	sfseek(Palabras,inicio,SEEK_SET);
	
	
	while(Palabras->cursor<=final)
	{
		
		actual=Palabras->cur->palabra;
		
		if(actual.sintaxis!=ORACION&&actual.sintaxis!=0)
		{
			respuesta=PosicionSintaxis(&ini,&fini,Palabras->cursor,final,actual.sintaxis,Palabras);
			actual=Palabras->cur->palabra;
		}
		
		
		if(actual.clase==PRONOMBRE)
		{
			Palabras->cur->palabra.sintaxis=N_PRONOMBRE;
			Palabras->cur->palabra.pos=3;	
			
			
		}
		
		sfseek(Palabras,1,SEEK_CUR);
	}
	
	
	
}




void AnalizadorDePronReflexivo(long int inicio, long int final,struct sfile * Palabras)
{
	struct palabras actual,separador;
	long int ini,fini,sini,sfin;
	int respuesta,persona,gen_num;
	bool es_sustantivado=false;
	char separa[10]="*S_R*";
	
	
	
	InicializarPalabraEnCero(&separador);
	Asignacadena(separador.word,separa,30);
	separador.sintaxis=S_REFLEXIVO;
	
	sfseek(Palabras,inicio,SEEK_SET);
	
	
	while(Palabras->cursor<=final)
	{
		
		actual=Palabras->cur->palabra;
		
		if(actual.sintaxis!=ORACION&&actual.sintaxis!=0)
		{
			respuesta=PosicionSintaxis(&ini,&fini,Palabras->cursor,final,actual.sintaxis,Palabras);
			actual=Palabras->cur->palabra;
		}
		
		
		if(actual.clase==PRON_REFLEXIVO)
		{
			sini=sftell(Palabras);
			
			
			separador.gen_num=actual.gen_num;
			separador.persona=actual.persona;
			gen_num=actual.gen_num;
			
			
			
			sfseek(Palabras,1,SEEK_CUR);
			actual=Palabras->cur->palabra;
			if(actual.clase==VERBO)
			{
				sfseek(Palabras,-1,SEEK_CUR);
				Palabras->cur->palabra.sintaxis=N_PRON_REFLEXIVO;
				Palabras->cur->palabra.pos=3;
				es_sustantivado=false;
			}
			else if(actual.clase==SUSTANTIVO||actual.clase==ADJETIVO||actual.sintaxis==S_SUSTANTIVADO||actual.sintaxis==S_ADJETIVO|| (actual.sintaxis==0&&actual.clase==0))
			{
				while((actual.clase==SUSTANTIVO||actual.clase==ADJETIVO||actual.sintaxis==S_SUSTANTIVADO||actual.sintaxis==S_ADJETIVO|| (actual.sintaxis==0&&actual.clase==0))&&Palabras->cursor<=final)				
				{
					
					if(actual.sintaxis==S_SUSTANTIVADO||actual.sintaxis==S_ADJETIVO)
					{
						respuesta=PosicionSintaxis(&ini,&fini,Palabras->cursor,final,actual.sintaxis,Palabras);
						actual=Palabras->cur->palabra;
					}
					
					sfseek(Palabras,1,SEEK_CUR);
					actual=Palabras->cur->palabra;
				}
				sfin=sftell(Palabras);
				
				if(separador.persona==0)
				{
				
					persona=0;
					if(1<=gen_num&&gen_num<=3)
					{
						persona=3;
						//printf("persona_:%d",persona);
					}
					else if(4<=gen_num&&gen_num<=6)
					{
						persona=6;
						//printf("persona_:%d",persona);
					}
				}
				
				separador.persona=persona;
				
				PoneSeparadores(sini,sfin,separador,Palabras);
				final=final+2;
				
				
			}
			
		}
		
		sfseek(Palabras,1,SEEK_CUR);
	}
	
	
	
}



void AnalizadorDeSustantivos(long int inicio, long int final, struct sfile * Palabras)
{
	struct palabras actual,separador;
	long int ini, fini,sini,sfin;
	char separa[10]="*S_S*";
	int gen_num,persona,respuesta;
	
	InicializarPalabraEnCero(&separador);
	separador.sintaxis=S_SUSTANTIVADO;
	Asignacadena(separador.word,separa,30);
	
	
	sfseek(Palabras,inicio,SEEK_SET);
	
	
	while(Palabras->cursor<=final)
	{
		actual=Palabras->cur->palabra;
		
		if(actual.sintaxis!=ORACION&&actual.sintaxis!=0)
		{
			respuesta=PosicionSintaxis(&ini,&fini,Palabras->cursor,final,actual.sintaxis,Palabras);
			actual=Palabras->cur->palabra;
			
		}
		
		if(actual.clase==SUSTANTIVO)
		{
			sini=sftell(Palabras);
			
			gen_num=actual.gen_num;
			
			
			do
			{
				sfseek(Palabras,1,SEEK_CUR);
				actual=Palabras->cur->palabra;
				if(actual.sintaxis!=ORACION&&actual.sintaxis!=0)
				{
					respuesta=PosicionSintaxis(&ini,&fini,Palabras->cursor,final,actual.sintaxis,Palabras);
					actual=Palabras->cur->palabra;
					
				}
			}
			while(actual.clase!=VERBO&&(actual.clase==ADJETIVO||actual.clase==SUSTANTIVO||actual.clase==0)&&!(actual.clase==SIMBOLO&&actual.word[0]=='.')&&(actual.sintaxis==0||actual.sintaxis==S_SUSTANTIVADO)&&Palabras->cursor<final);
			sfin=sftell(Palabras);
			
			
			persona=0;
			if(1<=gen_num&&gen_num<=3)
				{
					persona=3;
					//printf("persona_:%d",persona);
				}
				else if(4<=gen_num&&gen_num<=6)
				{
					persona=6;
					//printf("persona_:%d",persona);
				}
			
			//printf("\n gen_num %d persona %d",gen_num,persona);
			separador.gen_num=gen_num;
			separador.persona=persona;
			
			
			PoneSeparadores(sini,sfin,separador,Palabras);
			final=final+2;
			
			
		}
		
		
		sfseek(Palabras,1,SEEK_CUR);
	}
	
	
	
	
}

void AnalizadorDeAdjetivos(long int inicio,long int final, struct sfile * Palabras)
{
	
	struct palabras actual,separador;
	long int ini, fini,sini,sfin;
	char separa[10]="*S_S*",adjetivo[10]="*S_AD*";
	int gen_num,persona,respuesta;
	bool es_sustantivado;;
	
	InicializarPalabraEnCero(&separador);

	
	
	sfseek(Palabras,inicio,SEEK_SET);
	
	
	while(Palabras->cursor<=final)
	{
		actual=Palabras->cur->palabra;
		
		if(actual.sintaxis!=ORACION&&actual.sintaxis!=0)
		{
			respuesta=PosicionSintaxis(&ini,&fini,Palabras->cursor,final,actual.sintaxis,Palabras);
			actual=Palabras->cur->palabra;
			
		}
		
		if(actual.clase==ADJETIVO)
		{
			sini=sftell(Palabras);
			
			gen_num=actual.gen_num;
			es_sustantivado=false;
			
			do
			{
				sfseek(Palabras,1,SEEK_CUR);
				actual=Palabras->cur->palabra;
				if(actual.sintaxis!=ORACION&&actual.sintaxis!=0)
				{
					respuesta=PosicionSintaxis(&ini,&fini,Palabras->cursor,final,actual.sintaxis,Palabras);
					actual=Palabras->cur->palabra;
					
				}
				
				if(actual.clase==SUSTANTIVO)
				{
					es_sustantivado=true;
				}
				else if(actual.sintaxis==S_SUSTANTIVADO)
				{
					es_sustantivado=true;
				}
				
				
			}
			while(actual.clase!=VERBO&&(actual.clase==ADJETIVO||actual.clase==SUSTANTIVO||actual.clase==0)&&!(actual.clase==SIMBOLO&&actual.word[0]=='.')&&(actual.sintaxis==0||actual.sintaxis==S_SUSTANTIVADO)&&Palabras->cursor<final);
			sfin=sftell(Palabras);
			
			
			persona=0;
			if(1<=gen_num&&gen_num<=3)
				{
					persona=3;
					//printf("persona_:%d",persona);
				}
				else if(4<=gen_num&&gen_num<=6)
				{
					persona=6;
					//printf("persona_:%d",persona);
				}
			
			separador.gen_num=gen_num;
			separador.persona=persona;
			
			if(es_sustantivado==false)
			{
				Asignacadena(separador.word,adjetivo,30);
				separador.sintaxis=S_ADJETIVO;
				
			}
			else if(es_sustantivado==true)
			{
				Asignacadena(separador.word,separa,30);
				separador.sintaxis=S_SUSTANTIVADO;
				
			}
			
			//printf("\n gen_num %d persona %d",gen_num,persona);
			PoneSeparadores(sini,sfin,separador,Palabras);
			final=final+2;
			
			
		}
		
		
		sfseek(Palabras,1,SEEK_CUR);
	}
		
	
	
	
}
void AnalizadorDeAdverbios(long int inicio, long int final, struct sfile * Palabras)
{
	struct palabras actual;
	
	
	sfseek(Palabras,inicio,SEEK_SET);
	
	
	while (Palabras->cursor<=final)
	{
		actual=Palabras->cur->palabra;
		
		if(actual.clase==ADVERBIO)
		{
			
			Palabras->cur->palabra.sintaxis=N_ADVERBIO;
			Palabras->cur->palabra.pos=3;
			Palabras->cur->palabra.id=Palabras->ids;
			Palabras->ids++;
			
			
		}
		
		
		
		
		sfseek(Palabras,1,SEEK_CUR);
	}
	
	
	
	
	
	
}







void AnalizadorDePreposicion(long int inicio, long int fin, struct sfile * Palabras)
{
	struct palabras actual,separador;
	long int ini,fini,sini,sfin;
	int respuesta;
	char sintagma[10]="*PREP*";
	
	
	InicializarPalabraEnCero(&separador);
	Asignacadena(separador.word,sintagma,30);
	separador.sintaxis=S_PREPOSICION;
	
	sini=inicio;
	sfin=inicio;
	sfseek(Palabras,inicio,SEEK_SET);
	while(Palabras->cursor<=fin)
	{
		actual=Palabras->cur->palabra;
		//printf("<%s>",actual.word);
		
		if (actual.sintaxis!=ORACION&&actual.sintaxis!=0)
		{
		//printf("PP:%d",actual.sintaxis);
		respuesta=PosicionSintaxis(&ini,&fini,Palabras->cursor,fin,actual.sintaxis,Palabras);
		actual=Palabras->cur->palabra;
		//printf("resp:%d*%s*",respuesta,actual.word);
		}
		
		if(actual.clase==PREPOSICION)
		{
			sini=sftell(Palabras);
			
			do
			{
				
			  sfseek(Palabras,1,SEEK_CUR);
			  actual=Palabras->cur->palabra;
			 // printf("[%s]",actual.word);
		      if (actual.sintaxis!=ORACION&&actual.sintaxis!=0)
				{//printf("SS:%d",actual.sintaxis);
				respuesta=PosicionSintaxis(&ini,&fini,Palabras->cursor,fin,actual.sintaxis,Palabras);
				actual=Palabras->cur->palabra;
			//	printf("res%d*%s*",respuesta,actual.word);
				}	
			
			}
			while(actual.clase!=VERBO&&(actual.clase==ADVERBIO||actual.clase==SUSTANTIVO||actual.clase==ARTICULO||actual.clase==ADJETIVO||actual.sintaxis==S_SUSTANTIVADO||actual.sintaxis==S_ADJETIVO||actual.sintaxis==S_ARTICULO||actual.sintaxis==S_REFLEXIVO)&&Palabras->cursor<fin&&!(actual.clase==SIMBOLO&&actual.word[0]=='.'));
			sfin=sftell(Palabras);
			
			if(sfin==fini){
				PoneSeparadores(sini,sfin,separador,Palabras);
				fin+2;
				
			}
			else 
			{
			PoneSeparadores(sini,sfin,separador,Palabras);
			fin+2;
			}
			
		}
		
		sfseek(Palabras,1,SEEK_CUR);
	}
	
	
	
}






void AnalizadorDeConjuncion()
{
}

void AnalizadorDeMultiClase()
{
}

void AnalizadorDeDesconocidos()
{
}

void PosSeseparadorDeSintagmas()
{
	
}

void ConstructorDeVerbos()
{
}

void AnalizadorDeVerbos(long int inicio, long int fin, struct sfile * Palabras)
{	struct palabras actual;
	long int sini,sfin,ini,fini,posicionactual;
	int respuesta,i,persona;
	char sintagma[10]="*PREP*";

	
	
	sfseek(Palabras,inicio,SEEK_SET);
	while(Palabras->cursor<=fin)
	{
		actual=Palabras->cur->palabra;
		//printf("<%s>",actual.word);
		
		if (actual.sintaxis!=ORACION&&actual.sintaxis!=0)
		{
		//printf("PP:%d",actual.sintaxis);
		respuesta=PosicionSintaxis(&ini,&fini,Palabras->cursor,fin,actual.sintaxis,Palabras);
		actual=Palabras->cur->palabra;
		//printf("resp:%d*%s*",respuesta,actual.word);
		}
		
		if(actual.clase==VERBO)
		{
			sini=sftell(Palabras);
			sfin=sini;
			do
			{
				
			  sfseek(Palabras,1,SEEK_CUR);
			  actual=Palabras->cur->palabra;
			  //printf("[%s]",actual.word);
		      if (actual.sintaxis!=ORACION&&actual.sintaxis!=0)
				{//printf("SS:%d",actual.sintaxis);
				respuesta=PosicionSintaxis(&ini,&fini,Palabras->cursor,fin,actual.sintaxis,Palabras);
				sfseek(Palabras,1,SEEK_CUR);
				actual=Palabras->cur->palabra;
				//printf("res%d*%s*",respuesta,actual.word);
				}
			  if(actual.clase==VERBO)sfin=sftell(Palabras);
			
			}
			while((actual.clase==VERBO));
			
			if(sini==sfin){posicionactual=sftell(Palabras);
			sfseek(Palabras,sini,SEEK_SET);
			Palabras->cur->palabra.sintaxis=N_VERBAL;
			Palabras->cur->palabra.pos=3;
			Palabras->cur->palabra.id=Palabras->ids;
			Palabras->ids++;
			sfseek(Palabras,posicionactual-sini,SEEK_CUR);
			}
			else
			{posicionactual=sftell(Palabras);
			sfseek(Palabras,sini,SEEK_SET);
			Palabras->cur->palabra.sintaxis=N_VERBAL;
			Palabras->cur->palabra.pos=1;
			sfseek(Palabras,sfin,SEEK_SET);
			Palabras->cur->palabra.sintaxis=N_VERBAL;
			Palabras->cur->palabra.pos=2;
			sfseek(Palabras,posicionactual-sfin,SEEK_CUR);
			}
			
		}
		
		sfseek(Palabras,1,SEEK_CUR);
	}
}


void AniadeCaracteristicasSintagma()
{
}

void AnalizaVariables()
{
}

void PingPalabra(long int ini,long int fini,struct sfile * Acumulador,struct sfile * Palabras)
{
	struct palabras nuevo;
	sfseek(Acumulador,0,SEEK_END);
	
	sfseek(Palabras,fini,SEEK_SET);
	nuevo=Palabras->cur->palabra;
	nuevo.posicionlista=ini;
	nuevo.posicionlista2=fini;
	sfput(nuevo,acumulador);
	
	
}

struct palabras PongPalabra(struct sfile * Acumulador)
{
	struct palabras retorno;
	if(Acumulador->tamanio>0)
	{
	sfseek(Acumulador,-1,SEEK_END);
	retorno=Acumulador->cur->palabra;
	sfsuprimir(Acumulador);
	}
	return(retorno);
}

void AnalizaSucesion(long int inicio, long int final, struct sfile * Palabras)
{
	struct palabras actual;
	long int posiciony,posicionfin,posicionini,ini,fini;
	char y[3]="y"
	int respuesta,NPREP;
	bucleinformation bucle;
	bool repetir=false,encontrado=false,primera=false;
	sfile * Acumulador;
	
	
	Acumulador=sfopen()
	
	
	
	int BUSCANI=1,BUSCACOMA=2,BUSCANADA=3,BUSQUEDA,LEERATRAS;
	
	sfseek(Palabras,inicio,SEEK_SET);
	
	
	printf("\n");
	while(Palabras->cursor<=final)
	{
		
		actual=Palabras->cur->palabra;
		
		// LEE Y
		if(actual.clase==conjuncion&&!comparacad(actual.word,y))
		{
			//LEER 1 adelante
			
			
			InicializarBucleEnCero(&bucle);
			
			bucle.posiciony=sftell(Palabras);
			
			
			sfseek(Palabras,1,SEEK_CUR);
			actual=Palabras->cur->palabra;
			
			if(actual.sintaxis!=ORACION&&actual.sintaxis!=0)
			{
				respuesta=PosicionSintaxis(&ini,&fini,Palabras->cursor,fin,actual.sintaxis,Palabras);
				actual=Palabras->cur->palabra;
			}
			
			
			if(actual.sintaxis==S_SUSTANTIVADO||actual.sintaxis==S_ADJETIVO)
			{
				//Actiivar opcion sustantivado/adjetivo
				if(actual.sintaxis==S_SUSTANTIVADO)
					{
						bucle.sustantivo=true;
					}
				else if (actual.sintaxis==S_ADJETIVO)
					{
						bucle.adjetivo=true
					}
				
				
				while((actual.sintaxis==S_SUSTANTIVADO||actual.sintaxis==S_ADJETIVO||actual.sintaxis==S_PREPOSICION)&&actual->cursor<final)
				{
					
					bucle.final=sftell(Palabras);
					sfseek(Palabras,1,SEEK_CUR);
					actual=Palabras->cur->palabra;
					if(actual.sintaxis!=ORACION&&actual.sintaxis!=0)
					{
					respuesta=PosicionSintaxis(&ini,&fini,Palabras->cursor,final,actual.sintaxis,Palabras);
					actual=Palabras->cur->palabra;
					}
					if(actual.sintaxis==S_SUSTANTIVADO)
					{
						bucle.sustantivo=true;
					}
					else if(actual.sintaxis==S_ADJETIVO)
					{
						bucle.adjetivo=true;
					}
					
				}
				
				sfseek(Palabras,bucle.posiciony,SEEK_SET);
				
				do
				{
					bucle.inicio=sftell(Palabras);
					
					sfseek(Palabras,-1, SEE_CUR);
					if(actual.sintaxis!=ORACION&&actual.sintaxis!=0)
					{
					respuesta=PosicionSintaxisAlreves(&ini,&fini,inicio,Palabras->cursor,actual.sintaxis,Palabras);
					actual=Palabras->cur->palabra;
					}
					
					//Analizar PREP
					if (actual.sintaxis==S_PREPOSICION)
					{
						repetir=0;
						posicionprep=fini;
						NPREP=0;
						do
						{
							NPREP++;
							sfseek(Palabras,-1, SEEK_CUR);
							if(actual.sintaxis!=ORACION&&actual.sintaxis!=0)
							{
							respuesta=PosicionSintaxisAlreves(&ini,&fini,inicio,Palabras->cursor,actual.sintaxis,Palabras);
							actual=Palabras->cur->palabra;
							}
						}
						while(actual.sintaxis==S_PREPOSICION);
						
					
						if(actual.sintaxis==S_SUSTANTIVADO||actual.sintaxis==S_ADJETIVO)
						{
							
							bucle.inicio==sftell(Palabras);
							
							if(actual.sintaxis==S_SUSTANTIVADO)
							{
								bucle.sustantivo=true;
							}
							else if(actual.sintaxis==S_ADJETIVO)
							{
								bucle.adjetivo=true;
							}
							//Es sustantivo
							do
							{
							
								sfseek(Palabras,-1,SEEK_CUR);
								actual=Palabras->cur->palabra;
								if(actual.sintaxis!=ORACION&&actual.sintaxis!=0)
								{
								respuesta=PosicionSintaxisAlreves(&ini,&fini,inicio,Palabras->cursor,actual.sintaxis,Palabras);
								actual=Palabras->cur->palabra;
								}
								if(actual.sintaxis==S_SUSTANTIVADO)
								{
									bucle.sustantivo=true;
								}
								else if(actual.sintaxis==S_ADJETIVO)
								{
									bucle.adjetivo=true;
								}
							}
							while(actual.sintaxis==S_SUSTANTIVADO||actual.sintaxis==S_ADJETIVO);
							
							if(actual.clase==SIMBOLO && actual.word[0]=',')
							repetir=true;
							else repetir=false;
							
							//Buscar la coma
						}
						else if (actual.sintaxis==S_ARTICULO)
						{
							// Buscar dentro del articulo
							//
							
							if(bucle.adjetivo==true&& bucle.sustantivo==false)
							{
								sfseek(Palabras,fini-1,SEEK_SET);
								actual=Palabras->cur->palabra;
								encontrado=false;
								primera=true;
								while(Palabras->cursor>ini&&encontrado=false&&(actual.clase==ADJETIVO||actual.clase==SUSTANTIVO))
								{
									bucle.inicio=sftell(Palabras);
									if(actual.clase==ADJETIVO&&primera==true)
									{
									
										encontrado=true;
										repetir=false;
										primera=false;
									}
									else
									{
										primera=false;
									}
									sfseek(Palabras,-1,SEEK_CUR);
									actual=Palabras->cur->palabra;
								}
							}
							if(bucle.sustantivo==true)
							{
								//buscar S_S
							}
							
							
							
						}
						else 
						{
							//Buscar dentro del primer PREP
							
							
							if(bucle.adjetivo==true&& bucle.sustantivo==false)
							{
								//Buscar adjetivo primero
								
								//Sino hay adjetivo, buscar en el siguiente PREP. asi hasta el final
								
								//Sino buscar S_S
							}
							if(bucle.sustantivo==true)
							{
								//buscar S_S
							}
						}
					
					}
					else if(actual.sintaxis==S_ADJETIVADO)
					{
						//Buscar
					}
					else if(actual.sintaxis==S_SUSTATIVADO)
					{
						//Buscar
					}
					
					
					
				}
				while(repetir==true);
				
				
				
				
			}
			
			
			
			
			//LEER 1 atras
			//LEER 1 adelante
			//LEER 1 atras
			
			
			
		}
		
		
		
	  sfseek(Palabras,1,SEEK_CUR);
	}
	printf("\n");
	
	
	sfclose(Acumulador);
}





int BuscaSujeto(long int inioracion, long int finoracion,struct sfile * Palabras)
{
	struct palabras actual,sujeto;
	long int posverboini,posverbofin,ini,fini,inisujeto,finsujeto,inisujeto2,finsujeto2,posicionactual,i,j;
	int respuesta,gen_num1,gen_num2,sintaxis,persona1,persona2,personaverbo;
	bool seguir,principio,final;
	char sujetocode[10]="SUJ";
	
	gen_num1=0;
	gen_num2=0;
	persona1=0;
	persona2=0;
	personaverbo=-5;
	InicializarPalabraEnCero(&sujeto);
	Asignacadena(sujeto.word,sujetocode,30);
	sujeto.sintaxis=SUJETO;
	
	sfseek(Palabras,inioracion,SEEK_SET);
	
	seguir=true;
	principio=false;
	final=false;
	
	printf("\n BUSCA SUJETO:\n");
	while (Palabras->cursor<finoracion&&seguir)
	{
		actual=Palabras->cur->palabra;
		
		if(actual.sintaxis!=0&& actual.sintaxis!=ORACION)
		{
		respuesta=PosicionSintaxis(&ini,&fini,Palabras->cursor,finoracion,actual.sintaxis,Palabras);
		actual=Palabras->cur->palabra;
		}
		
		if(actual.sintaxis==N_VERBAL)
		{
			printf("VERBO_");
			if(actual.pos==3) 
			{posverboini=sftell(Palabras);
			 posverbofin=posverboini;
			 personaverbo=actual.persona;
			 
			}
			else if (actual.pos==2)
			{
				posverboini=ini;
				posverbofin=fini;;;
				personaverbo=actual.persona;
				
			}
			
			seguir=false;
		}
		
		
		
		if(seguir)sfseek(Palabras,1,SEEK_CUR);
	}
	
	i=0;
	seguir=true;
	sfseek(Palabras,posverboini,SEEK_SET);
	while (Palabras->cursor>inioracion&&seguir)
	{
		i++;
		actual=Palabras->cur->palabra;
		posicionactual=sftell(Palabras);
		
		if (actual.sintaxis!=0&&actual.sintaxis!=ORACION)
		{
			sintaxis=actual.sintaxis;
			respuesta=PosicionSintaxisAlreves(&ini,&fini,inioracion,Palabras->cursor,actual.sintaxis,Palabras);
			actual=Palabras->cur->palabra;
			printf("ALVERRErestpuesta[%d][%s][%d]",respuesta,actual.word,actual.pos);
			if(actual.sintaxis!=S_ARTICULO&&actual.sintaxis!=S_REFLEXIVO&&sintaxis!=S_SUSTANTIVADO&&sintaxis!=N_PRONOMBRE&&actual.persona==personaverbo)i=i+posicionactual-ini;	
		}
		
		
		if ((actual.sintaxis==S_SUSTANTIVADO||actual.sintaxis==N_PRONOMBRE||actual.sintaxis==S_ARTICULO||actual.sintaxis==S_REFLEXIVO)&&actual.persona==personaverbo)
		{
			printf("1SUJETO ON_");
			inisujeto=ini;
			finsujeto=fini;
			
			
			
			
			
			do
			{
			
				sfseek(Palabras,fini+1,SEEK_SET);
				actual=Palabras->cur->palabra;
				
				if(actual.sintaxis==S_PREPOSICION&&actual.pos==1)
				{
					respuesta=PosicionSintaxis(&ini,&fini,Palabras->cursor,finoracion,actual.sintaxis,Palabras);
					finsujeto=fini;
				}
			}while(actual.sintaxis==S_PREPOSICION&&actual.pos==1);
			
			
			
			seguir=false;
			principio=true;
			gen_num1=actual.gen_num;
			persona1=actual.persona;
			
		}
		
		
		if(seguir)sfseek(Palabras,-1,SEEK_CUR);
		
		
	}
	j=0;
	seguir=true;
	sfseek(Palabras,posverboini,SEEK_SET);
	while (Palabras->cursor<finoracion&&seguir)
	{
		j++;
		actual=Palabras->cur->palabra;
		posicionactual=sftell(Palabras);
		
		if (actual.sintaxis!=0&&actual.sintaxis!=ORACION)
		{
			sintaxis=actual.sintaxis;
			respuesta=PosicionSintaxis(&ini,&fini,Palabras->cursor,finoracion,actual.sintaxis,Palabras);
			actual=Palabras->cur->palabra;
			printf("DERECHOrestpuesta[%d][%s][%d]",respuesta,actual.word,actual.pos);
			if(actual.sintaxis!=S_ARTICULO&&actual.sintaxis!=S_REFLEXIVO&&sintaxis!=S_SUSTANTIVADO&&sintaxis!=N_PRONOMBRE&&actual.persona==personaverbo)j=j+fini-posicionactual;	
		}
		
		
		if ((actual.sintaxis==S_SUSTANTIVADO||actual.sintaxis==N_PRONOMBRE||actual.sintaxis==S_ARTICULO||actual.sintaxis==S_REFLEXIVO)&&actual.persona==personaverbo)
		{
			printf("SUJETO ON2_");
			inisujeto2=ini;
			finsujeto2=fini;
			
			
			
			
			
			do
			{
			
				sfseek(Palabras,fini+1,SEEK_SET);
				actual=Palabras->cur->palabra;
				
				if(actual.sintaxis==S_PREPOSICION&&actual.pos==1)
				{
					respuesta=PosicionSintaxis(&ini,&fini,Palabras->cursor,finoracion,actual.sintaxis,Palabras);
					finsujeto=fini;
				}
			}while(actual.sintaxis==S_PREPOSICION&&actual.pos==1);
			
			
			seguir=false;
			final=true;
			gen_num2=actual.gen_num;
			persona2=actual.persona;
			
		}
		
		
		if(seguir)sfseek(Palabras,1,SEEK_CUR);
		
		
	}
	
	
	if(principio==true&&final==true)
	
	{
		printf("truetrue");
		if(i<=j)
		{
			sujeto.gen_num=gen_num1;
			sujeto.persona=persona1;
			PoneSeparadores(inisujeto,finsujeto+1,sujeto,Palabras);
			return(1);
		}
		else
		{
			sujeto.gen_num=gen_num2;
			sujeto.persona=persona2;
			PoneSeparadores(inisujeto2,finsujeto2+1,sujeto,Palabras);
			return(2);
		}	
		
	}
	else if(principio==true)
	{
		printf("truefalse");
		sujeto.gen_num=gen_num1;
		sujeto.persona=persona1;
		PoneSeparadores(inisujeto,finsujeto+1,sujeto,Palabras);
		return(3);
	}
	else if(final==true)
	{	printf("falsetrue");
		sujeto.gen_num=gen_num2;
		sujeto.persona=persona2;
		PoneSeparadores(inisujeto2,finsujeto2+1,sujeto,Palabras);
		return(4);
	}
	
	
	
return(0)	;
	
	
	
}






void AnalisisSintactico(struct sfile *Palabras)
{
	long int inicio,final;
	
	printf("\nAnalizar Artículos");
	final=0;
	while(PosicionSintaxis(&inicio,&final,final,Palabras->tamanio,ORACION,Palabras)>0)
	{
	
		printf("\ninicio:%ld final=%ld",inicio,final);
		
		AnalizadorDeArticulos(inicio,final,Palabras);
	
	}
	
	printf("\nAnalizar Pronombre Reflexivos");
	final=0;
	while(PosicionSintaxis(&inicio,&final,final,Palabras->tamanio,ORACION,Palabras)>0)
	{
	
		printf("\ninicio:%ld final=%ld",inicio,final);
		
		AnalizadorDePronReflexivo(inicio,final,Palabras);
	
	}
	
	
	
	
	printf("\nAnalizar Sustantivos");
	final=0;
	while(PosicionSintaxis(&inicio,&final,final,Palabras->tamanio,ORACION,Palabras)>0)
	{
	
		printf("\ninicio:%ld final=%ld",inicio,final);
		
		AnalizadorDeSustantivos(inicio,final,Palabras);
	
	}	
	
	printf("\nAnalizar Adjetivos");
	final=0;
	while(PosicionSintaxis(&inicio,&final,final,Palabras->tamanio,ORACION,Palabras)>0)
	{
	
		printf("\ninicio:%ld final=%ld",inicio,final);
		
		AnalizadorDeAdjetivos(inicio,final,Palabras);
	
	}	
	printf("\nAnalizar Adverbios");
	
	
		final=0;
	while(PosicionSintaxis(&inicio,&final,final,Palabras->tamanio,ORACION,Palabras)>0)
	{
	
		printf("\ninicio:%ld final=%ld",inicio,final);
		
		AnalizadorDeAdverbios(inicio,final,Palabras);
	
	}	
	printf("\nAnalizar Pronombres");
	
	
	final=0;
	while(PosicionSintaxis(&inicio,&final,final,Palabras->tamanio,ORACION,Palabras)>0)
	{
	
		printf("\ninicio:%ld final=%ld",inicio,final);
		
		AnalizadorDePronombres(inicio,final,Palabras);
	
	}
	
	printf("\nAnalizar preposicion");
	final=0;
		while(PosicionSintaxis(&inicio,&final,final,Palabras->tamanio,ORACION,Palabras)>0)
	{
	
		printf("\ninicio:%ld final=%ld",inicio,final);
		
		AnalizadorDePreposicion(inicio,final,Palabras);
	
	}
		
		
	printf("\nAnalizar verbos");
		final=0;
		while(PosicionSintaxis(&inicio,&final,final,Palabras->tamanio,ORACION,Palabras)>0)
	{
	
		printf("\ninicio:%ld final=%ld",inicio,final);
		
		AnalizadorDeVerbos(inicio,final,Palabras);
	
	}
	
	
	
	printf("\nAnalizar sucesiones");
		final=0;
		while(PosicionSintaxis(&inicio,&final,final,Palabras->tamanio,ORACION,Palabras)>0)
	{
	
		printf("\ninicio:%ld final=%ld",inicio,final);
		
		AnalizaSucesion(inicio,final,Palabras);
	
	}
	
	
	
	printf("\nBusca sujetos");
	final=0;
		while(PosicionSintaxis(&inicio,&final,final,Palabras->tamanio,ORACION,Palabras)>0)
	{
	
		printf("\ninicio:%ld final=%ld",inicio,final);
		
		BuscaSujeto(inicio,final,Palabras);
	
	}




}










#endif
