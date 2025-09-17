
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>
#include <sys/stat.h>

#include"pseudoarchivo.h"
#include"caracteres.h"
#include"archivos.h"
#include"cadenas.h"
#include"oraciones.h"
#include"diccionario.h"
#include"estructuras.h"
#include"lista.h"
#include"leerarchivo.h"
#include"sintaxis.h"


int main ()
{
FILE* archivo;
int inicio,fin,i;
char direccion1[20]="diccionario.txt",direccion2[20]="texto.txt",direccion3[20]="lista.txt";
long int poscursor,poscursorfinal;

setlocale(LC_ALL,"Spanish");

printf("hello world\n");
crearyordenarlista(direccion1,direccion3);

leerarchivo12(direccion1,direccion2,direccion3);

printf("\ntodo ok!");
//system("pause");

return(1);
}

