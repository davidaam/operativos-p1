#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* leerLinea(FILE* fuente)
{
	char c;
	size_t tam = 100; // tam inicial 
    char* string = (char*)malloc(size_t*sizeof(char));
    size_t i = 0;
    while(((c = fgetc(fuente)) != EOF) && c != '\n') 
    {
        string[i++] = c;
        if (i == tam) {
        	string = realloc(string, sizeof(char)*tam*2);
        }
    }
    string[i++] = '\0';
    return realloc(string, sizeof(char)*i);
}

Nodo* nuevoNodo(void* val) {
	Nodo* n = (Nodo*)malloc(sizeof(Nodo));
	n->val = val;
	return n;
}

void agregarNodo(Lista* l, Nodo* n) {
	n->sig = l->ini;
	l->ini = n;
	l->tam++;
}

Persona* parseLinea(FILE* fp) {
	Persona* p = (Persona*)malloc(sizeof(Persona));

	char[4] delim = " ->";
	char* tok;
	char* linea = leerLinea(fp);
	
	tok = strtok(linea,delim);
	p->nombre = tok;
	p->amigos = (Lista*)malloc(sizeof(Lista));

	while ((tok = strtok(NULL,delim)) != NULL) {
		agregarNodo(p->amigos,nuevoNodo(tok));
	}
	return p;
}

/*
Toma dos strings y en el primero coloca el de menor
orden lexicografico en el primer parámetro y el de
mayor en el segundo

@param char* a
@param char* b

*/
void sort_str (char* a, char* b) {
	char* tmp;
	if (strcmp(a,b) > 0) {
		tmp = (char*)malloc(strlen(a)*sizeof(char));
		strcpy(tmp,a);
		a = (char*)malloc(strlen(b)*sizeof(char));
		strcpy(a,b);
		b = (char*)malloc(strlen(tmp)*sizeof(char));
		strcpy(b,tmp);
	}
}

/*
Toma una lista enlazada de strings y la ordena 
lexicograficamente usando Bubblesort

@param l: Lista*

*/
void sort_lstr (Lista* l) {
	// Bubblesort
	Nodo* aux_base = l->ini;
	Nodo* aux = aux_base;
	int i,j = 0;
	for (i=0; i < l->tam-1; i++) {
		for (j=0; j < l->tam-i; j++) {
			sort_str(aux->val,aux->sig->val);
			aux = aux->sig;
		}
		aux_base = aux_base->sig;
		aux = aux_base;
	}
}

/*
Toma dos pares y guarda en a el apuntador al par de menor
orden lexicográfico y en b el de mayor

@param Par* a
@param Par* b

*/
void sort_par (Par* a, Par* b) {
	Par* tmp;
	int comp = strcmp(a->p1,b->p1);
	if (comp > 0) {
		tmp = a;
		a = b;
		b = tmp;
	}
	else if (comp == 0) {
		if (strcmp(a->p2,b->p2) > 0) {
			tmp = a;
			a = b;
			b = tmp;
		}
	}
}


/*
Toma una lista enlazada de Par y la ordena 
lexicograficamente usando Bubblesort

@param l: Lista*

*/

void sort_lpar (Lista* l) {
	// Bubblesort
	Nodo* aux_base = l->ini;
	Nodo* aux = aux_base;
	int i,j = 0;
	for (i=0; i < l->tam-1; i++) {
		for (j=0; j < l->tam-i; j++) {
			sort_par(aux->val,aux->sig->val);
			aux = aux->sig;
		}
		aux_base = aux_base->sig;
		aux = aux_base;
	}
}