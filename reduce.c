#include "reduce.h"

Par* reduce (Par* p1, Par* p2) {
	Lista* l = (Lista*)malloc(sizeof(Lista));
	Nodo* aux1 = p1->comun->head;
	Nodo* aux2 = p2->comun->head;

	while (aux1 != NULL && aux2 != NULL) {
		int comp = strcmp((char*)aux1->val,(char*)aux2->val);
		if (comp == 0) {
			agregarNodo(l,nuevoNodo(aux1->val,STR));
			aux1 = aux1->sig;
			aux2 = aux2->sig;
		}
		else if (comp > 0) {
			aux2 = aux2->sig;
		}
		else {
			aux1 = aux1->sig;
		}
	}
	return crearPar(p1->p1,p1->p2,l);
}