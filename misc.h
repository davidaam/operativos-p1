#ifndef MISC_H
#define MISC_H

struct Nodo {
	void* val;
	struct Nodo* sig;
}
typedef struct Nodo Nodo;

struct Lista {
	int tam;
	Nodo* ini;
}
typedef struct Lista Lista;

struct Persona {
	char* nombre;
	Lista* amigos;
}
typedef struct Persona Persona;

struct Par {
	char* p1;
	char* p2;
	Lista* comun;
}

typedef struct Par Par;

char* leerLinea(FILE*);
Nodo* nuevoNodo(void*);
void agregarNodo(Lista*,Nodo*);
Persona* parseLinea(FILE*);
void sort_str(char*,char*);
void sort_lstr(Lista*);
void sort_lpar(Lista*);
#endif