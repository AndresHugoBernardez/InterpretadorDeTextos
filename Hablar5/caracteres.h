

#ifndef _CARACTERES_H
#define _CARACTERES_H

#include<stdio.h>
#include<stdlib.h>


//-----------------------CARACTERES
int letraesnumero(char c)
{
	if (47<c&&c<58) return (1);
	else return(0);	
}

int letraesmayuscula(char c)
{
	if (64<c&&c<91) return (1);
	else return(0);	
}

char convertirdemayusculaaminuscula(char c)
{
	char caracter;
	
	switch (c)
	{
	case '�': caracter='�';	break;
	case '�': caracter='�';	break;
	case '�': caracter='�';	break;
	case '�': caracter='�';	break;
	case '�': caracter='�';	break;
	case '�': caracter='�';break;;
	default: caracter=c+32;
	}
	
	
	return(caracter);
}

int letraesminuscula(char c)
{
	if (96<c&&c<123) return (1);
	else return(0);	
}

int letraesalfabeto(char c)
{
	if (letraesmayuscula(c) || letraesminuscula(c)) return(1); 
	else return(0);
}

int letraesacento(char c)
{
	switch (c)
	
	{
	case '�':;
	case '�':;
	case '�':;
	case '�':;
	case '�':;
	case '�':;
	case '�':;
	case '�':;
	case '�':;
	case '�': return (1);break;
	default: return (0);
	}
	
}
int letraesacentomayuscula(char c)
{
	switch (c)
	
	{
	case '�':;
	case '�':;
	case '�':;
	case '�':;
	case '�': return (1);break;
	default: return (0);
	}
	
}


int letraesenie(char c)
{
	if ( c=='�'|| c== '�') return (1);
	else return (0);
	
}

int letraesguion(char c)
{
	if (c=='_'||c=='-') return(1);
	else return(0);
}

int letraesalfabetica(char c)
{
	if (letraesmayuscula(c) || letraesminuscula(c)||letraesenie(c)||letraesacento(c)) return(1); 
	else return(0);
}

int letraesalfanumerico(char c)
{
	if (letraesnumero(c)||letraesmayuscula(c) || letraesminuscula(c)||letraesenie(c)||letraesacento(c)) return(1); 
	else return(0);
}


int letraessimbolotexto(char c)
{
	if(c==','||c==';'||c==':'||c=='�'||c=='?'||c=='�'||c=='!'||c=='-'||c=='_'||c=='('||c==')'||c=='"'||c=='$'||c=='�'||c=='%') return(1);
	else return (0);
}

int letraessimbolomatematico(char c)
{
	if(c=='+'||c=='/'||c=='*'||c=='^'||c=='='||c=='-'||c=='<'||c=='>') return(1);
	else return (0);
}

int letraespalabra(char c)
{
	if (letraesalfanumerico(c)||  (!letraessimbolotexto(c)&&!letraessimbolomatematico(c)&&c!='.'&&c!=' '&&c!='\t'&&c!='\r'&&c!='\0'&&c!=EOF&&c!='\n')   ) return(1);
	else return(0);
}

int letranoespalabra(char c)
{
	if (letraessimbolotexto(c)||letraessimbolomatematico(c)||c=='.'||c==' '||c=='\t'||c=='\r'||c=='\0'||c=='\n'||c==EOF) return(1);
	else return(0);
}
#endif
