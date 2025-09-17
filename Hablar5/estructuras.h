#ifndef _ESTRUCTURAS
#define _ESTRUCTURAS



struct posicion {
  long int catinicial,catfinal, inicial, final;
} ;
struct palabras
{
	
	long int posicionlista,posicionlista2;
	char word [30];
	int clase, persona, tipo, gen_num,conjugacion,sintaxis,id,pos,n_clase,n_sig;
	
};




int MAX_CHAR=30;

struct nombre {
	long int posicion,posicion2;
	char palabra[30];
	bool largo;
	
	
};

struct nombrelargo
{
	long int posicion;
	char palabra[250];
	int largo;
	
	
};




void InicializarPalabraEnCero(struct palabras * palabra)
{
	struct palabras cero;
	cero.clase=0;
	cero.conjugacion=0;
	cero.gen_num=0;
	cero.id=-1;
	cero.n_clase=0;
	cero.n_sig=0;
	cero.persona=0;
	cero.pos=0;
	cero.posicionlista=-1;
	cero.posicionlista2=-1;
	cero.sintaxis=0;
	cero.tipo=0;
	cero.word[0]='\0';
	*palabra=cero;
}


#endif
