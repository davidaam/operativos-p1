#include "map.h"

int main() {
	FILE* fp = fopen("data","r+");
	Lista* ldef = (Lista*)malloc(sizeof(Lista));
	Lista* ltmp;
	Persona* p;
	FILE* fout = fopen("out","w");
	while(!finArchivo(fp)) {
		p = parseLinea(fp);
		ltmp = map(p);
		ldef = concatListas(ldef,ltmp);
	}
	sort_lista(ldef,PAR);
	imprimir_lpar(stdout,ldef);
	return 0;
}