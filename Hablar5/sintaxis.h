#ifndef _sintaxis
#define _sintaxis

#include "stdio.h"
#include "stdlib.h"
#include "diccionario.h"
#include "caracteres.h"
#include "cadenas.h"
#include "estructuras.h"
#include "sintaxisfile.h"


char _sustantivo[11]="sustantivo";
char _adjetivo[14]="adjetivo";
char _articulo[10]="artículo";
char _pronombre[14]="pronombre";
char _verbo[10]="verbo";
char _adverbio[14]="adverbio";
char _preposicion[14]="preposición";
char _conjuncion[14]="conjunción";
char _interjeccion[14]="interjección";
char _adj_determinativo[30]="adjetivo determinativo";
char _pron_reflexivo[30]="pronombre reflexivo";
char _relativo[30]="relativo";

int SUSTANTIVO=1;
int ADJETIVO=2;
int ARTICULO=3;
int PRONOMBRE=4;
int VERBO=5;
int ADVERBIO=6;
int PREPOSICION=7;
int CONJUNCION=8;
int INTERJECCION=9;
int ADJ_DETERMINATIVO=10;
int PRON_REFLEXIVO=11;
int RELATIVO=12;
int ART_RELATIVO=13;//artículo de relativo ejemplo "el que"





int SIMBOLO=200;


char _masculino[11]="masculino";
char _femenino[11]="femenino";
char _singular[10]="singular";
char _plural[10]="plural";
char _neutral[8]="neutral";

char _primera[10]="primera";
char _segunda[10]="segunda";
char _tercera[10]="tercera";


// conjugación

char _infinitivo[14]="infinitivo";
char _gerundio[10]="gerundio";
char _participio[14]="participio";
char _imperativo[14]="imperativo";

char _indicativo[14]="indicativo";
char _subjuntivo[14]="subjuntivo";


char _presente[10]="presente";
char _preterito[14]="pretérito";
char _futuro[10]="futuro";
char _condicional[14]="condicional";

char _perfecto[10]="perfecto";
char _imperfecto[14]="imperfecto";
char _pluscuamperfecto[20]="pluscuamperfecto";
char _simple[10]="simple";
char _compuesto[14]="compuesto";
char _anterior[10]="anterior";

int INFINITIVO=1;
int INF_COMP=2;
int GERUNDIO=3;
int GER_COMP=4;
int PARTICIPIO=5;
int IMPERATIVO=6;
int I_PRESENTE=7;
int I_PRET_ANT=13;
int I_PRET_PLUS=14;
int I_PRET_IMP=9;
int I_PRET_PERF_S=8;
int I_PRET_PERF_C=12;
int I_FUT_IMP=10;
int I_FUT_PERF=15;
int I_COND_S=11;
int I_COND_C=16;
int S_PRESENTE=17;
int S_PRET_PERF=20;
int S_PRET_IMP=18;
int S_PRET_PLUS=21;
int S_FUT_IMP=19;
int S_FUT_PERF=22;
/*
"infinitivo";//1 y 2
"gerundio"// 3 y 4
"participio";// 5
"imperativo";// 6
indicativo presente  7
indicativo pretérito anterior 13
indicativo pretérito pluscuamperfecto 14
indicativo pretérito imperfecto 9
indicativo pretérito perfecto simple 8
indicativo pretérito perfecto compuesto 12
indicativo futuro imperfecto 10
indicativo futuro perfecto 15
indicativo condicional simple 11
indicativo condicional compuesto 16
subjuntivo presente 17
subjuntivo pretérito perfecto 20
subjuntivo pretérito imperfecto 18
subjuntivo pretérito pluscuamperfecto 21
subjuntivo futuro imperfecto 19
subjuntivo futuro perfecto 22

*/

// SINTAXIS
int ORACION=1;
int S_SUSTANTIVADO=2;//SINTAGMA SUSTANTIVADO
int S_PREPOSICION=3;//SINTAGMA CON PREPOSICION
int N_VERBAL=4;//NUCLEO VERBAL
int N_PRONOMBRE=5;//NUCLEO DE PRONOMBRE
int S_ADJETIVO=6;//SINTAGMA ADJETIVO
int N_PRON_REFLEXIVO=7;//NUCLEO DE PRONOMBRE REFLEXIVO
int N_ADVERBIO=8;//NUCLEO DE ADVERBIO
int S_ARTICULO=9;// SINTAGMA CON ARTICULO
int S_REFLEXIVO=10;//SINTAGMA CON PRONOMBRE REFLEXIVO


int SUJETO=100;
int PREDICADO=101;


//CLASES DE ADVERVIOS


int LUGAR=1;
int TIEMPO=2;
int MODO=3;
int CANTIDAD=4;
int DUDA=5;
int AFIRMACION=6;
int NEGACION=7;

char _lugar[10]="lugar";
char _tiempo[10]="tiempo";
char _modo[10]="modo";
char _cantidad[10]="cantidad";
char _duda[10]="duda";
char _afirmacion[15]="afirmación";
char _negacion[10]="negación";


// Lee cadenas a partir de un caracter alfanumerico y lee espacios y puntos hasta un caracter especial como el "<"
void lectorcadena(char*cadena,char caracterin,Pfile*diccionario,int limitechar)

{ 	char cadena2[256],caracter;
	int j;

					caracter=caracterin;

					
					cadena[0]='\0';
					while(caracter=='.'||caracter==' '||letraesalfanumerico(caracter))
					{
									
						if(letraesalfanumerico(caracter))CargarPalabraFile(cadena2,caracter,diccionario,256);
						else if(caracter==' ') {cadena2[0]=' ';cadena2[1]='\0';}
						else if(caracter=='.') {cadena2[0]='.';cadena2[1]='\0';}
						Sumacadenas(cadena,cadena,cadena2,limitechar);
						caracter=pfgetc(diccionario);
					}
					if(caracter!=EOF)pfseek(diccionario,-1,SEEK_CUR);
					
					 j=largocadena(cadena);
					 
					 j--;
					 caracter=cadena[j];
					 while(caracter==' '&&j>0)
					 {
					 	
					 	cadena[j]='\0';
					 	j--;
					 	caracter=cadena[j];
					 }
}






// Indica cuantas clases se encontraron en la posicion de busqueda. esta señalizado asi <clases>23</clases>
int CuantasClases(long int posicionini,long int posicionfin,struct Pfile *diccionario)
{
	char clases[10]="clases",numero,cadena[10];
	int respuesta;
	struct posicion posicion1;
	
	respuesta=Buscacategoriafile(&posicion1,posicionini,posicionfin,clases,diccionario);
	if(respuesta>0)
	{
		CargaCadenaEntrePosFile(cadena,posicion1.inicial+1,posicion1.final-1,diccionario,256);
		//printf("cadena[%s]",cadena);
		numero=chartoint(cadena);
		return(numero);
		
	}
	
	
	return(-1);
}
// Indica cuantos significados se encontraron en la posicion de busqueda. esta señalizado asi <significados>23</significados>
int CuantosSignificados(long int posicionini,long int posicionfin,struct Pfile *diccionario)
{
	char clases[20]="significados",numero,cadena[10];
	int respuesta;
	struct posicion posicion1;
	
	respuesta=Buscacategoriafile(&posicion1,posicionini,posicionfin,clases,diccionario);
	if(respuesta>0)
	{
		CargaCadenaEntrePosFile(cadena,posicion1.inicial+1,posicion1.final-1,diccionario,256);
		//printf("cadena[%s]",cadena);
		numero=chartoint(cadena);
		return(numero);
		
	}
	
	
	return(-1);
}
// Devuelve la posicion de la clase numero N en posicion <claseN> </claseN>
int PosClaseNumero(struct posicion *posicion,long int posicion1, long int posicion2,int N, Pfile *diccionario)
{
	char cadena[40],clase[10]="clase",cadenaaux[10];
	int respuesta;
	
	inttochar(cadenaaux,N);
	Sumacadenas(cadena,clase,cadenaaux,40);
	//printf("CAD[%s] ",cadena);
						
	respuesta=Buscacategoriafile(posicion,posicion1,posicion2,cadena,diccionario);
	return(respuesta);
}

// Devuelve la posicion del numero N en posicion <N> </N>
int PosNumero(struct posicion *posicion,long int posicion1, long int posicion2,int N, Pfile *diccionario)
{
	char cadena[10];
	int respuesta;
	
	inttochar(cadena,N);

	//printf("CAD[%s] ",cadena);
						
	respuesta=Buscacategoriafile(posicion,posicion1,posicion2,cadena,diccionario);
	return(respuesta);
}


//Obtener código de Número y Género.
int GetGennum(long int posicionini, long int posicionfin,struct Pfile * diccionario)
{
	int respuesta,sumatoria;
	char caracter,gennum[8]="gennum",cadena1[30];
	struct posicion posicionA;
	long int limite;
	
	//printf("\n GETGENUM...........\n");
	sumatoria=0;
	respuesta=Buscacategoriafile(&posicionA,posicionini,posicionfin,gennum,diccionario);
	if (respuesta>0)
	{
		
		pfseek(diccionario,posicionA.inicial+1,SEEK_SET);
		
		limite=posicionA.final;
		do
		{
		   caracter=pfgetc(diccionario);
		}while(!letraesalfanumerico(caracter) && pftell(diccionario)<limite);
		
		if (pftell(diccionario)<limite) 
		{
			CargarPalabraFile(cadena1,caracter,diccionario,30);
			
			//printf("%s:",cadena1);
			if(!comparacad(cadena1,_masculino))
			{
				sumatoria=1;				
			}
			else if (!comparacad(cadena1,_femenino))
			{
				sumatoria=2;
			}
			else if (!comparacad(cadena1,_neutral))
			{
				sumatoria=3;
			}
			else sumatoria=-10;
			
			do
			{
			   caracter=pfgetc(diccionario);
			}while(!letraesalfanumerico(caracter) && pftell(diccionario)<limite);
			
			if (pftell(diccionario)<limite) 
			{
				CargarPalabraFile(cadena1,caracter,diccionario,30);
				//printf("%s:",cadena1);
				if(!comparacad(cadena1,_singular))
				{
					sumatoria=sumatoria;				
				}
				else if (!comparacad(cadena1,_plural))
				{
					sumatoria=sumatoria+3;
				}
				else if (!comparacad(cadena1,_neutral))
				{
					sumatoria=sumatoria+6;
				}
				else sumatoria=sumatoria-10;
			
			}
		}
	}
	//printf("\n FIN GETGENUM...........\n");
	return(sumatoria);
}




//Obtener código de Número y Género.
int GetTipo(long int posicionini, long int posicionfin,struct Pfile * diccionario)
{
	int respuesta,sumatoria;
	char caracter,gennum[8]="tipo",cadena1[30];
	struct posicion posicionA;
	long int limite;
	
	//printf("\n GETGENUM...........\n");
	sumatoria=0;
	respuesta=Buscacategoriafile(&posicionA,posicionini,posicionfin,gennum,diccionario);
	if (respuesta>0)
	{
		
		pfseek(diccionario,posicionA.inicial+1,SEEK_SET);
		
		limite=posicionA.final;
		do
		{
		//	printf("|");
		   caracter=pfgetc(diccionario);
		}while(!letraesalfanumerico(caracter) && pftell(diccionario)<limite);
		
		if (pftell(diccionario)<limite) 
		{
			CargarPalabraFile(cadena1,caracter,diccionario,30);
			
		//	printf("%s:",cadena1);
			if(!comparacad(cadena1,_lugar))
			{
				sumatoria=LUGAR;				
			}
			else if(!comparacad(cadena1,_modo))
			{
				sumatoria=MODO;
			}
			else if(!comparacad(cadena1,_tiempo))
			{
				sumatoria=TIEMPO;				
			}
			else if(!comparacad(cadena1,_cantidad))
			{
				sumatoria=CANTIDAD;
			}
			else if(!comparacad(cadena1,_duda))
			{
				sumatoria=DUDA;
			}
			else if(!comparacad(cadena1,_afirmacion))
			{
				sumatoria=AFIRMACION;
			}
			else if(!comparacad(cadena1,_negacion))
			{
				sumatoria=NEGACION;
			}
		
		
			
		}
	}
	//printf("\n FIN GETTIPO..........\n");
	return(sumatoria);
}


//Obtener código de persona.
int GetPersona(long int posicionini, long int posicionfin,struct Pfile * diccionario)
{
	int respuesta,sumatoria;
	char caracter,persona[10]="persona",cadena1[30];
	struct posicion posicionA;
	long int limite;
	
	//printf("\n GetPersona...........\n");
	sumatoria=0;
	respuesta=Buscacategoriafile(&posicionA,posicionini,posicionfin,persona,diccionario);
	if (respuesta>0)
	{
		//printf("inside!")
		pfseek(diccionario,posicionA.inicial+1,SEEK_SET);
		
		limite=posicionA.final;
		do
		{
		   caracter=pfgetc(diccionario);
		}while(!letraesalfanumerico(caracter) && pftell(diccionario)<limite);
		
		if (pftell(diccionario)<limite) 
		{
			CargarPalabraFile(cadena1,caracter,diccionario,30);
			
			//printf("%s:",cadena1);
			if(!comparacad(cadena1,_primera))
			{
				sumatoria=1;				
			}
			else if (!comparacad(cadena1,_segunda))
			{
				sumatoria=2;
			}
			else if (!comparacad(cadena1,_tercera))
			{
				sumatoria=3;
			}
			else sumatoria=-10;
			
			do
			{
			   caracter=pfgetc(diccionario);
			}while(!letraesalfanumerico(caracter) && pftell(diccionario)<limite);
			
			if (pftell(diccionario)<limite) 
			{
				CargarPalabraFile(cadena1,caracter,diccionario,30);
				//printf("%s:",cadena1);
				if(!comparacad(cadena1,_singular))
				{
					sumatoria=sumatoria;				
				}
				else if (!comparacad(cadena1,_plural))
				{
					sumatoria=sumatoria+3;
				}
				else sumatoria=sumatoria-10;
			
			}
		}
	}
	//printf("\n FIN GetPersona...........\n");
	return(sumatoria);
}





//Obtener código de conjugación.
int GetConjugacion(long int posicionini, long int posicionfin,struct Pfile * diccionario)
{
	int respuesta,sumatoria;
	char caracter,conjugacion[15]="conjugación",cadena1[30];
	struct posicion posicionA;
	long int limite;
	
	//printf("\n GetPersona...........\n");
	sumatoria=0;
	respuesta=Buscacategoriafile(&posicionA,posicionini,posicionfin,conjugacion,diccionario);
	if (respuesta>0)
	{
		//printf("inside!")
		pfseek(diccionario,posicionA.inicial+1,SEEK_SET);
		
		limite=posicionA.final;
		do
		{
		   caracter=pfgetc(diccionario);
		}while(!letraesalfanumerico(caracter) && pftell(diccionario)<limite);
		
		if (pftell(diccionario)<limite) 
		{
			CargarPalabraFile(cadena1,caracter,diccionario,30);
			
			//printf("%s:",cadena1);
			//INFINITIVO
			if(!comparacad(cadena1,_infinitivo))
			{
				
				
			
				do
				{
				   caracter=pfgetc(diccionario);
				}while(!letraesalfanumerico(caracter) && pftell(diccionario)<limite);
				
				if (pftell(diccionario)<limite) 
				{
					CargarPalabraFile(cadena1,caracter,diccionario,30);
					//printf("%s:",cadena1);				
				
					if(!comparacad(cadena1,_compuesto))
					{
						sumatoria=INF_COMP;
						return(sumatoria);
				
					}
					else
					{
						sumatoria=INFINITIVO;
						return(sumatoria);
					}
				}
				else
					{
						sumatoria=INFINITIVO;
						return(sumatoria);
					}
				
			}
			//GERUNDIO
			else if(!comparacad(cadena1,_gerundio))
			{
				
				
			
				do
				{
				   caracter=pfgetc(diccionario);
				}while(!letraesalfanumerico(caracter) && pftell(diccionario)<limite);
				
				if (pftell(diccionario)<limite) 
				{
					CargarPalabraFile(cadena1,caracter,diccionario,30);
					//printf("%s:",cadena1);				
				
					if(!comparacad(cadena1,_compuesto))
					{
						sumatoria=GER_COMP;
						return(sumatoria);
				
					}
					else
					{
						sumatoria=GERUNDIO;
						return(sumatoria);
					}
				}
				else
					{
						sumatoria=GERUNDIO;
						return(sumatoria);
					}
				
			}
			//PARTICIPIO
			else if (!comparacad(cadena1,_participio))
			{
				sumatoria=PARTICIPIO;
				return(sumatoria);
			}
			//IMPERATIVO
			else if (!comparacad(cadena1,_imperativo))
			{
				sumatoria=IMPERATIVO;
				return(sumatoria);
			}
			//INDICATIVO
			else if(!comparacad(cadena1,_indicativo))
			{
				sumatoria=1;
				
			
				do
				{
				   caracter=pfgetc(diccionario);
				}while(!letraesalfanumerico(caracter) && pftell(diccionario)<limite);
				
				if (pftell(diccionario)<limite) 
				{
					CargarPalabraFile(cadena1,caracter,diccionario,30);
					//printf("%s:",cadena1);				
					//Presente  
					if(!comparacad(cadena1,_presente))
					{
						sumatoria=I_PRESENTE;
						return(sumatoria);
				
					}
					else if(!comparacad(cadena1,_preterito))
					{
						
							do
							{
							   caracter=pfgetc(diccionario);
							}while(!letraesalfanumerico(caracter) && pftell(diccionario)<limite);
							
							if (pftell(diccionario)<limite) 
							{
								CargarPalabraFile(cadena1,caracter,diccionario,30);
								//printf("%s:",cadena1);	
									//Pretérito anterior
									if(!comparacad(cadena1,_anterior))
									{
										sumatoria=I_PRET_ANT;
										return(sumatoria);
								
									}
									//Pretérito pluscuamperfecto
									else if(!comparacad(cadena1,_pluscuamperfecto))
									{
										sumatoria=I_PRET_PLUS;
										return(sumatoria);
								
									}
									//Pretérito imperfecto
									else if(!comparacad(cadena1,_imperfecto))
									{
										sumatoria=I_PRET_IMP;
										return(sumatoria);
								
									}
									else if(!comparacad(cadena1,_perfecto))
									{
										do
										{
										   caracter=pfgetc(diccionario);
										}while(!letraesalfanumerico(caracter) && pftell(diccionario)<limite);
										
										if (pftell(diccionario)<limite) 
										{
											CargarPalabraFile(cadena1,caracter,diccionario,30);
											//printf("%s:",cadena1);	
												//Pretérito perfecto simple
												if(!comparacad(cadena1,_simple))
												{
													sumatoria=I_PRET_PERF_S;
													return(sumatoria);
											
												}
												//Pretérito perfecto compuesto
												else if(!comparacad(cadena1,_compuesto))
												{
													sumatoria=I_PRET_PERF_C;
													return(sumatoria);
											
												}
										}
												
									}			
								
						
							}
					}
					else if(!comparacad(cadena1,_futuro))
					{
						
							do
							{
							   caracter=pfgetc(diccionario);
							}while(!letraesalfanumerico(caracter) && pftell(diccionario)<limite);
							
							if (pftell(diccionario)<limite) 
							{
								CargarPalabraFile(cadena1,caracter,diccionario,30);
								//printf("%s:",cadena1);	
									//Futuro imperfecto
									if(!comparacad(cadena1,_imperfecto))
									{
										sumatoria=I_FUT_IMP;
										return(sumatoria);
								
									}
									//Futuro perfecto
									else if(!comparacad(cadena1,_perfecto))
									{
										sumatoria=I_FUT_PERF;
										return(sumatoria);
								
									}
							}
							
							
					}
					else if(!comparacad(cadena1,_condicional))
					{
						
							do
							{
							   caracter=pfgetc(diccionario);
							}while(!letraesalfanumerico(caracter) && pftell(diccionario)<limite);
							
							if (pftell(diccionario)<limite) 
							{
								CargarPalabraFile(cadena1,caracter,diccionario,30);
								//printf("%s:",cadena1);	
									//Condicional simple
									if(!comparacad(cadena1,_simple))
									{
										sumatoria=I_COND_S;
										return(sumatoria);
								
									}
									//Condicional compuesto
									else if(!comparacad(cadena1,_compuesto))
									{
										sumatoria=I_COND_C;
										return(sumatoria);
								
									}
							}
							
							
					}
					
					

				}
				
			}
			//SUBJUNTIVO
			else if(!comparacad(cadena1,_subjuntivo))
			{
				sumatoria=1;
				
			
				do
				{
				   caracter=pfgetc(diccionario);
				}while(!letraesalfanumerico(caracter) && pftell(diccionario)<limite);
				
				if (pftell(diccionario)<limite) 
				{
					CargarPalabraFile(cadena1,caracter,diccionario,30);
					//printf("%s:",cadena1);				
					//Presente 
					if(!comparacad(cadena1,_presente))
					{
						sumatoria=S_PRESENTE;
						return(sumatoria);
				
					}
					else if(!comparacad(cadena1,_preterito))
					{
						do
						{
						   caracter=pfgetc(diccionario);
						}while(!letraesalfanumerico(caracter) && pftell(diccionario)<limite);
						
						if (pftell(diccionario)<limite) 
						{
							CargarPalabraFile(cadena1,caracter,diccionario,30);
							//printf("%s:",cadena1);				
							//Pretérito perfecto
							if(!comparacad(cadena1,_perfecto))
							{
								sumatoria=S_PRET_PERF;
								return(sumatoria);
						
							}
							//Pretérito imperfecto
							else if(!comparacad(cadena1,_imperfecto))
							{
								sumatoria=S_PRET_IMP;
								return(sumatoria);
						
							}
							//Pretérito pluscuamperfecto
							else if(!comparacad(cadena1,_pluscuamperfecto))
							{
								sumatoria=S_PRET_PLUS;
								return(sumatoria);
						
							}
						}
				
					}
					else if(!comparacad(cadena1,_futuro))
					{
						do
						{
						   caracter=pfgetc(diccionario);
						}while(!letraesalfanumerico(caracter) && pftell(diccionario)<limite);
						
						if (pftell(diccionario)<limite) 
						{
							CargarPalabraFile(cadena1,caracter,diccionario,30);
							//printf("%s:",cadena1);				
							//Futuro imperfecto
							if(!comparacad(cadena1,_imperfecto))
							{
								sumatoria=S_FUT_IMP;
								return(sumatoria);
						
							}
							//Futuro perfecto
							else if(!comparacad(cadena1,_perfecto))
							{
								sumatoria=S_FUT_PERF;
								return(sumatoria);
						
							}

						}
				
					}
					
				}
				
			}
			
			
			
			sumatoria=-10;
			

		}
	}
	//printf("\n FIN GetPersona...........\n");
	return(sumatoria);
}






void clasificador(struct sfile *Palabras,Pfile * diccionario)
{
	struct posicion posicion1,posicion2,posicion3;
	char clase[10]="clase",  clases[10]="clases",caracter,cadena[256],cadenaaux[20],significado[20]="significado";
	int respuesta, j,numero;
	long int cursor;
	
		

	
	sfseek(Palabras,0,SEEK_SET);
	
	while (Palabras->cursor<Palabras->tamanio)
	{
		
		printf("%s",Palabras->cur->palabra.word);
		if (Palabras->cur->palabra.posicionlista!=-1)
		{
		
			numero=CuantasClases(Palabras->cur->palabra.posicionlista,Palabras->cur->palabra.posicionlista2,diccionario);
			if(numero>0)
			{
					//printf("ALPHA");
							
					if(numero==1)
					{
						//printf("OMEGA");
						Palabras->cur->palabra.n_clase=1;
						
						respuesta=PosClaseNumero(&posicion1,Palabras->cur->palabra.posicionlista,Palabras->cur->palabra.posicionlista2,1,diccionario);
						if(respuesta>0)
						{
							//printf("GAMMA");
							respuesta=Buscacategoriafile(&posicion2,posicion1.inicial,posicion1.final,clase,diccionario);
							if(respuesta>0)
							{
								//printf("ok!!!");
								pfseek(diccionario,posicion2.inicial+1,SEEK_SET);
								
								do caracter=pfgetc(diccionario);
								while (!letraesalfanumerico(caracter)&&pftell(diccionario)<posicion2.catfinal);
								
									if(pftell(diccionario)<=posicion2.catfinal)lectorcadena(cadena,caracter,diccionario,256);
									else {cadena[0]='@',cadena[1]='\0';}
									//printf(":%s:",cadena);
								
								
								
								switch(cadena[0])
								{
								
								case 'a':
								{
									if(!comparacad(cadena,_adjetivo)) {Palabras->cur->palabra.clase=ADJETIVO;
									Palabras->cur->palabra.gen_num=GetGennum(posicion1.inicial,posicion1.final,diccionario);
									 printf("(es adjetivo:%d:)",Palabras->cur->palabra.gen_num);
									 }
									else if(!comparacad(cadena,_adj_determinativo)) {Palabras->cur->palabra.clase=ADJ_DETERMINATIVO;
									Palabras->cur->palabra.gen_num=GetGennum(posicion1.inicial,posicion1.final,diccionario);
									 printf("(es adjetivo determinativo:%d:)",Palabras->cur->palabra.gen_num); 
									 }	
									else if(!comparacad(cadena,_articulo)) {Palabras->cur->palabra.clase=ARTICULO;
									Palabras->cur->palabra.gen_num=GetGennum(posicion1.inicial,posicion1.final,diccionario);
									 printf("(es artículo:%d:)",Palabras->cur->palabra.gen_num);
									  }
									else if(!comparacad(cadena,_adverbio)) {Palabras->cur->palabra.clase=ADVERBIO; 
									Palabras->cur->palabra.tipo=GetTipo(posicion1.inicial,posicion1.final,diccionario);
									printf("(es adverbio:%d:)",Palabras->cur->palabra.tipo);}	
									
								}break;
								case 'c':
								{
									if(!comparacad(cadena,_conjuncion)) {Palabras->cur->palabra.clase=CONJUNCION; printf("(es conjunción)");}
								}break;
								case 'i':
									if(!comparacad(cadena,_interjeccion)) {Palabras->cur->palabra.clase=INTERJECCION; printf("(es interjección)");}
									break;
								case 'p':
								{
									if(!comparacad(cadena,_pronombre)) {Palabras->cur->palabra.clase=PRONOMBRE; 
									Palabras->cur->palabra.persona=GetPersona(posicion1.inicial,posicion1.final,diccionario);
									printf("(es pronombre:%d:)",Palabras->cur->palabra.persona);}	
									else if(!comparacad(cadena,_preposicion)) {Palabras->cur->palabra.clase=PREPOSICION; printf("(es preposición)");}
									else if(!comparacad(cadena,_pron_reflexivo)){Palabras->cur->palabra.clase=PRON_REFLEXIVO;
									Palabras->cur->palabra.persona=GetPersona(posicion1.inicial,posicion1.final,diccionario);
									Palabras->cur->palabra.gen_num=GetGennum(posicion1.inicial,posicion1.final,diccionario);
									printf("(es pronombre reflexivo:%d:%d:)",Palabras->cur->palabra.persona,Palabras->cur->palabra.gen_num);}	
									
								}break;
								case 'r':
									if(!comparacad(cadena,_relativo)){Palabras->cur->palabra.clase=RELATIVO;
									Palabras->cur->palabra.gen_num=GetGennum(posicion1.inicial,posicion1.final,diccionario);
									printf("(es relativo:%d)",Palabras->cur->palabra.gen_num);}
									break;
								case 's':
									 if(!comparacad(cadena,_sustantivo)) {Palabras->cur->palabra.clase=SUSTANTIVO; 
									 Palabras->cur->palabra.gen_num=GetGennum(posicion1.inicial,posicion1.final,diccionario);
									 printf("(es sustantivo:%d:)",Palabras->cur->palabra.gen_num);
									 }
									 break;
								case 'v':
									if(!comparacad(cadena,_verbo)) {Palabras->cur->palabra.clase=VERBO; 
									 Palabras->cur->palabra.persona=GetPersona(posicion1.inicial,posicion1.final,diccionario);
									 Palabras->cur->palabra.conjugacion=GetConjugacion(posicion1.inicial,posicion1.final,diccionario);
									 printf("(es verbo:%d:%d:)",Palabras->cur->palabra.persona,Palabras->cur->palabra.conjugacion);
									 }break;
								}
								
								
								
								
								
								
								
								
								
								/*
								numero=CuantosSignificados(posicion1.inicial,posicion1.final,diccionario);
								if(numero>0)
								{
									//printf("SIn[%d]",numero);
									respuesta=PosNumero(&posicion3,posicion1.inicial,posicion1.final,1,diccionario);
									if(respuesta>0)
									{
										//printf("found");
										respuesta=Buscacategoriafile(&posicion2,posicion3.inicial,posicion3.final,significado,diccionario);
										if (respuesta>0)
										{
											CargaCadenaEntrePosFile(cadena,posicion2.inicial+1,posicion2.final-1,diccionario,256);
											printf("SIGNIFICADO:%s",cadena);
										}
									}
								}
								*/	
							}
						}
					}

			}
		}
		printf(" ");
		sfseek(Palabras,1,SEEK_CUR);
	}
	
	
	
	
}


void DeteccionDeSimbolos(struct sfile * Palabras)
{
	struct palabras actual;
	char c;
	sfseek(Palabras,0,SEEK_SET);
	
	
	while (Palabras->cursor<Palabras->tamanio)
	{
		
		actual=Palabras->cur->palabra;
		
		if(actual.clase==0)
		{
			if(actual.word[1]=='\0')
			{
				c=actual.word[0];
				if(letraessimbolotexto(c)||letraessimbolomatematico(c)||c=='.'||c=='\n')
				{
					Palabras->cur->palabra.clase=SIMBOLO;
				}		
				
				
				
			}
			
		}
		
		
		sfseek(Palabras,1,SEEK_CUR);
	}
	
	
	
	
}







#endif
