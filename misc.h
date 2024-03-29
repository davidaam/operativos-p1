#ifndef MISC_H
#define MISC_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Tipos de Nodos permitidos 
enum TIPO {STR,PAR,PERSONA};
typedef enum TIPO TIPO;

struct Nodo {
	void* val;
	struct Nodo* ant;
	struct Nodo* sig;
};
typedef struct Nodo Nodo;

struct Lista {
	int tam;
	Nodo* head;
	Nodo* tail;
};
typedef struct Lista Lista;

struct Persona {
	char* nombre;
	Lista* amigos;
};
typedef struct Persona Persona;

struct Par {
	char* p1;
	char* p2;
	Lista* comun;
};
typedef struct Par Par;

struct Archivo {
	char** contenido;
	int lineas;
};
typedef struct Archivo Archivo;

char* leerLinea(FILE*);
Nodo* nuevoNodo(void*);
void agregarNodo(Lista*,Nodo*);
Lista* concatListas(Lista*,Lista*);
Persona* crearPersona(char*);
Par* leerPar(FILE*);
void sort_str(char**,char**);
void sort_lista(Lista*, TIPO t);
void imprimir_par(FILE*,Par*);
void imprimir_lpar(FILE*,Lista*);
Nodo* desplazarNodo(Nodo*, int desp);
int contarDigitos(int);
#endif