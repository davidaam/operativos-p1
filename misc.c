#include "misc.h"
/*
Determina si el apuntador al archivo dado apunta
al final del archivo

@param FILE* f : Apuntador al archivo

@return int : 1 si f apunta a EOF, 0 en caso contrario
*/
int finArchivo(FILE* f)
{
    if(fgetc(f) == EOF)
    {
        return 1;
    }
    fseek(f, -1, SEEK_CUR);
    return 0;
}

/*
Lee y devuelve una linea de un archivo

@param FILE* fuente : Apuntador al archivo

@return char* : Linea leida del archivo
*/
char* leerLinea(FILE* fuente)
{
	char c;
	size_t tam = 100; // tam inicial 
    char* string = (char*)malloc(tam*sizeof(char));
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


Persona* crearPersona(char* linea) {
	Persona* p = (Persona*)malloc(sizeof(Persona));
	char delim[4] = " ->";
	char* tok;
	
	tok = strtok(linea,delim);
	p->nombre = tok;
	p->amigos = (Lista*)malloc(sizeof(Lista));

	while ((tok = strtok(NULL,delim)) != NULL) {
		agregarNodo(p->amigos,nuevoNodo(tok));
	}
	// Nos aseguramos que toda lista de amigos
	// este ordenada
	sort_lista(p->amigos,STR);
	return p;
}

/*
Crea un nuevo nodo con el valor dado

@param void* val : Apuntador genérico al valor
del nodo a crear

@return Nodo : Nodo con el valor pasado
*/
Nodo* nuevoNodo(void* val) {
	Nodo* n = (Nodo*)malloc(sizeof(Nodo));
	n->val = val;
	return n;
}

/*
Agrega un nodo a la lista dada

@param Lista* l : Lista enlazada general
@param Nodo* n : Nodo a agregar
*/
void agregarNodo(Lista* l, Nodo* n) {
	if (l->head == NULL) {
		l->head = n;
		l->tail = n;
	}
	else {
		l->tail->sig = n;
		n->ant = l->tail;
		l->tail = n;
	}
	l->tam++;
}

/*
Concatena dos listas enlazadas y el resultado
es devuelto en la primera

@param Lista* l1 : Lista portadora
@param Lista* l2 : Lista con los nodos a agregar

@
*/
Lista* concatListas(Lista* l1, Lista* l2) {
	if (l1->tail != NULL) {
		l1->tail->sig = l2->head;
		l1->tam += l2->tam;
	}
	else {
		l1 = l2;
	}
	return l1;
}

/*
Toma dos strings y en el primero coloca el de menor
orden lexicografico en el primer parámetro y el de
mayor en el segundo

@param char* a
@param char* b

*/
void sort_str (char** a, char** b) {
	char* tmp;
	if (strcmp(*a,*b) > 0) {
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

/*
Toma una lista enlazada general y la ordena 
lexicograficamente usando Bubblesort

@param l: Lista*

*/

void sort_lista (Lista* l, TIPO t) {
	// Bubblesort
	Nodo* aux = l->head;
	int i,j,swap;
	for (i=0; i < l->tam-1; i++) {
		for (j=0; j < l->tam-i-1; j++) {
			swap = 0;
			switch (t) {
				case STR:
				{
					if (strcmp((char*)aux->val,(char*)aux->sig->val) > 0) {
						swap = 1;
					}
					break;
				}

				case PAR:
				{
					int comp = strcmp(((Par*)aux->val)->p1,((Par*)aux->sig->val)->p1);
					if (comp > 0) {
						swap = 1;
					}
					else if (comp == 0) {
						if (strcmp(((Par*)aux->val)->p2,((Par*)aux->sig->val)->p2) > 0) {
							swap = 1;
						}
					}
					break;
				}

				case PERSONA:
				{
					if (strcmp(((Persona*)aux->val)->nombre,((Persona*)aux->sig->val)->nombre) > 0) {
						swap = 1;
					}
					break;
				}
			}
			if (swap) {
				void* tmp = aux->val;
				aux->val = aux->sig->val;
				aux->sig->val = tmp;
			}
			aux = aux->sig;
		}
		aux = l->head;
	}
}

void imprimir_par(FILE* fp,Par* par) {
	fprintf(fp,"(%s %s) -> ",par->p1,par->p2);
	Nodo* aux = par->comun->head;
	while (aux != NULL) {
		fprintf(fp,"%s ",(char*)aux->val);
		aux = aux->sig;
	}
	fprintf(fp,"\n");
}
void imprimir_lpar(FILE* fp,Lista* l) {
	Nodo* aux = l->head;
	while (aux != NULL) {
		imprimir_par(fp,(Par*)aux->val);
		aux = aux->sig;
	}
}


Par* leerPar(FILE* fp) {
	Par* p = (Par*)malloc(sizeof(Par));
	char* tmp;
	char* delim = " ->()";
	char* linea = leerLinea(fp);
	p->p1 = strtok(linea,delim);
	p->p2 = strtok(NULL,delim);
	p->comun = (Lista*)malloc(sizeof(Lista));
	while ((tmp = strtok(NULL,delim)) != NULL) {
		agregarNodo(p->comun,nuevoNodo(tmp));
	}
	return p;
}

Archivo* leerArchivo(FILE* fp) {
	int nlineas = contarLineas(fp);
	char** contenido = (char**)malloc(sizeof(char*)*nlineas);	
	int i;
	for(i = 0; i < nlineas; i++) {
		contenido[i] = leerLinea(fp);
	}
	Archivo* a = (Archivo*)malloc(sizeof(Archivo));
	a->contenido = contenido;
	a->lineas = nlineas;

	return a;
}

int contarLineas(FILE* fp) {
	char c;
	int count = 1;
	while (!finArchivo(fp)) {
		if ((c = fgetc(fp)) == '\n') {
			count++;
		}
	}
	rewind(fp);
	return count;
}

int contarDigitos(int n) {
	int dig = 0;
	while (n >= 1) {
		n /= 10;
		dig++;
	}
	return dig;
}
/* Dada la direccion de un nodo, te devuelve el i-esimo nodo,
   después de éste. Si no es posible devuelve NULL
*/
Nodo* desplazarNodo(Nodo* n, int desp) {
	Nodo* aux = n;
	while (desp > 0 && aux != NULL) {
		aux = aux->sig;
		desp--;
	}
	return aux;
}