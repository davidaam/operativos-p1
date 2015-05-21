#include "reduce.h"
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
	FILE* fp = fopen("data","r+");
	Lista* lmap = (Lista*)malloc(sizeof(Lista));
	Lista* ltmp;
	Persona* p;
	Archivo* entrada = leerArchivo(fp);
	char** usuarios = entrada->contenido;
	int nprocs = atoi(argv[1]);
	int nusers = entrada->lineas;
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

	for (i = 0; i < nprocs_map; i++) {
		parte = i < sobra_map ? cut_map+1 : cut_map;

		if ((hijos[i] = fork()) > 0) {
			// Padre
			repartidos += parte;
		}
		else if (hijos[i] == 0) {
			// Hijo
			printf("Soy tu hijo! %ld\n",(long)getpid());
			for (; parte > 0; parte--) {
				Persona* p = crearPersona(usuarios[parte+repartidos-1]);
				ltmp = map(p);
				lmap = concatListas(lmap,ltmp);
				parte--;
			}
			long pid = (long) getpid();
			char* fn = malloc(contarDigitos(pid)*sizeof(char));
			sprintf(fn,"%ld",pid);
			FILE* pout = fopen(fn,"w");
			imprimir_lpar(pout,lmap);
			free(ltmp);
			free(lmap);
			free(fn);
			exit(0);
		}
		else {
			perror("ForkError");
		}	
	}

	for (i=0; i < nprocs_map; i++) {
		wait(NULL);
		printf("Estoy orgulloso de ti!\n");
		// Unir archivos

		int dig_pid = contarDigitos(hijos[i]);

		char* fn = (char*)malloc(sizeof(char)*dig_pid);
		sprintf(fn,"%ld",(long)hijos[i]);
		FILE* fphijo = fopen(fn,"r");

		ltmp = (Lista*)malloc(sizeof(Lista));
		while (!finArchivo(fphijo)) {
			Par* p = leerPar(fphijo);
			agregarNodo(ltmp,nuevoNodo(p));
		}
		lmap = concatListas(lmap,ltmp);
	}
	FILE* fout = fopen("out","w");
	sort_lista(lmap,PAR);
	imprimir_lpar(fout,lmap);


	return 0;
}