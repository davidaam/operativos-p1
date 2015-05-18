#include <stdio.h>
#include <stdlib.h>
#include "map.h"

/*
Crea un par compuesto por la persona dada y otra
persona cuyo nombre es proveido, asociando a este
par la lista de amigos de la persona dada
*/
Par* crearPar(Persona* persona,char* amigo) {
	Par* p = (Par*)malloc(sizeof(Par));
	p->p1 = persona->nombre;
	p->p2 = amigo;
	p->comun = persona->amigos;
	// Nos aseguramos que todos los pares esten
	// adecuadamente ordenados
	sort_str(&p->p1,&p->p2);
	return p; 
}

/*
Función de map, toma una persona y genera los
pares dados por la persona y cada uno de sus amigos,
asociando a este par la lista de amigos de la persona

@param Persona* p : Persona a la que se le aplica
					la función de mapeo

@return Lista* : Lista de pares resultantes
*/
Lista* map(Persona* p) {
	Lista* l = (Lista*)malloc(sizeof(Lista));
	Nodo* aux = p->amigos->head;
	while (aux != NULL) {
		Par* par = crearPar(p,aux->val);
		agregarNodo(l,nuevoNodo(par,PAR));
		aux = aux->sig;
	}
	return l;
}