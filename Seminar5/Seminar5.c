// Liste dublu inlantuite 
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Masina Masina;
typedef struct Nod Nod;
typedef struct LDI LDI;

struct Masina {
	char* producator;
	int serie;
};

struct Nod {
	Masina inf;
	Nod* next;
	Nod* prev;
};

struct LDI {
	Nod* prim;
	Nod* ultim;
};


void afisareMasina(Masina masina) {
	printf("\n Masina %s are seria %d.", masina.producator, masina.serie);
}

void traversareLista(LDI lista, int* nrMasini) {
	while (lista.prim) {
		afisareMasina(lista.prim->inf);
		(*nrMasini)++;
		lista.prim = lista.prim->next;
	}
}

void traversareListaDeLaFinal(LDI lista) {
	while (lista.ultim) {
		afisareMasina(lista.ultim->inf);
		lista.ultim = lista.ultim->prev;
	}
}

Masina initMasina(const char* producator, int serie) {
	Masina masinaNoua;
	masinaNoua.serie = serie;
	masinaNoua.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(masinaNoua.producator, producator);

	return masinaNoua;
}

void inserareLaInceput(Masina masina, LDI* ldi) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->prev = NULL;
	nou->next = ldi->prim;
	if (ldi->prim != NULL) {
		ldi->prim->prev = nou;
		ldi->prim = nou;
	}
	else {
		ldi->prim = nou;
		ldi->ultim = nou;
	}
}

void inserareLaFinal(Masina masina, LDI* ldi) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->prev = ldi->ultim;
	nou->next = NULL;
	if (ldi->ultim) {
		ldi->ultim-> next = nou;
		ldi->ultim = nou;
	}
	else {
		ldi->prim = nou;
		ldi->ultim = nou;
	}
}

void dezalocare(LDI* lista) {
	Nod* copie = lista->prim;
	while (copie) {
		free(copie->inf.producator);
		copie = copie->next;
		if (copie) {
			free(copie->prev);
		}
	}
	free(lista->ultim);
	lista->prim = lista->ultim = NULL;
}


void conversieLaVector(LDI lista, Masina** vectorMasini) {
	int nrMasini = 0;
	while (lista.prim) {
		(*vectorMasini)[nrMasini] = initMasina(lista.prim->inf.producator, lista.prim->inf.serie);
		nrMasini++;
		lista.prim = lista.prim->next;
	}
}

/*void traversareListaCirculara(LDI lista) {
	Nod* aux = lista.prim;
	while (aux->next != lista.prim) {
		afisareMasina(aux->inf);
		aux = aux->next;
	}
	afisareMasina(aux->inf);
}*/

//SAU

void traversareListaCirculara(LDI lista) {
	Nod* aux = lista.prim;
	do {
		afisareMasina(aux->inf);
		aux = aux->next;
	} while (aux != lista.prim);
	//better
}

void main() {
	LDI lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	inserareLaInceput(initMasina("ford", 1234), &lista);
	inserareLaInceput(initMasina("renault", 5678), &lista);
	inserareLaInceput(initMasina("hyundai", 9101), &lista);
	inserareLaInceput(initMasina("bmw", 1112), &lista);


	
	//transmisa prin valoare pt ca nu o modificam
	int nrMasini = 0;
	traversareLista(lista, &nrMasini);

	Masina* vector = (Masina*)malloc(sizeof(Masina) * nrMasini);
	conversieLaVector(lista, &vector);
	printf("\n\nAfisare masini din vector: \n");
	for (int i = 0; i < nrMasini; i++) {
		afisareMasina(vector[i]);
		free(vector[i].producator);

	}
	free(vector);


	//transformare in lista circulara
	lista.ultim->next = lista.prim;
	lista.prim->prev = lista.ultim;

	traversareListaCirculara(lista);

	//daca modificam -> transmitere prin pointer
	//dezalocare(&lista);
}