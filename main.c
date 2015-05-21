#include "reduce.h"
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
	FILE* fp = fopen("data","r+");
	Lista* lmap = (Lista*)malloc(sizeof(Lista));
	Lista* ltmp;
	Persona* p;
	FILE* fout = fopen("out","w");
	RedSocial* red = leerRedSocial(fp);
	Nodo* aux = red->usuarios->head;

	int nprocs = atoi(argv[1]);
	int nusers = red->usuarios->tam;
	int nprocs_map = nprocs;
	if (nprocs > nusers) {
		printf("Ha pedido crear más procesos/hilos que usuarios en la red.\nCrearé 1 proceso/hilo por usuario\n");
		nprocs_map = nusers;
	}
	int i,repartidos,parte;
	repartidos = 0;
	int cut_map = nusers / nprocs_map;
	int sobra_map = nusers % nprocs_map;
	pid_t* hijos = (pid_t*)malloc(sizeof(pid_t)*nprocs_map);

	for (; i < nprocs_map; i++) {
		parte = i < sobra_map ? cut_map+1 : cut_map;

		if ((hijos[i] = fork()) > 0) {
			// Padre
			repartidos += parte;
			aux = desplazarNodo(aux,repartidos);
		}
		else if (hijos[i] == 0) {
			// Hijo
			printf("Soy tu hijo! %ld\n",(long)getpid());
			while(aux != NULL && parte > 0) {
				ltmp = map(aux->val);
				lmap = concatListas(lmap,ltmp);
				aux = aux->sig;
				parte--;
			}
			char* fn;
			sprintf(fn,"%ld",(long)getpid());
			FILE* pout = fopen(fn,"w");
			imprimir_lpar(pout,lmap);
			exit(0);
		}
		else {
			perror("ForkError");
		}	
	}

	for (i=0; i < nprocs_map; i++) {
		wait(NULL);
		printf("Estoy orgulloso de ti!\n");

	}

	return 0;
}