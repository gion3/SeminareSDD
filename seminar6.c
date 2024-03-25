#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

//STIVA - LIFO Ultima informatie inserata este prima informatie scoasa
// Atat inserarea cat si extragerea se face la acelasi capat. (fie ambele la inceput fie la final)
// La semiar folosim inserare si extragere LA INCEPUT
//COADA - FIFO Prima informatie inserata este prima informatie scoasa
// Inserarea si extragerea se fac la capete opuse.
// 

typedef struct Masina Masina;
typedef struct Nod Nod;

struct Masina {
	char* producator;
	int serie;
	long id;
};

struct Nod {
	Masina inf;
	Nod* next;
};

void afisareMasina(Masina masina) {
	printf("\n%ld. Masina %s are seria %d.",masina.id, masina.producator, masina.serie);
}

Masina initMasina(long id,const char* producator, int serie) {
	Masina masinaNoua;
	masinaNoua.id = id;
	masinaNoua.serie = serie;
	masinaNoua.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(masinaNoua.producator, producator);

	return masinaNoua;
}

void push(Nod** cap, Masina masina) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->next = *cap;
	*cap = nou;
}

void put(Nod** cap, Masina masina) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->next = NULL;
	if ((*cap) != NULL) {
		Nod* aux = *cap;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		*cap = nou;
	}
}

Masina pop(Nod** varf) {
	Masina masina;
	masina.id = -1;
	masina.producator = NULL;
	masina.serie = -1;
	
	if ((*varf) != NULL) {
		masina = (*varf)->inf; //dezalocarea pt informatia utila nu se face in functia pop!!!
		Nod* temp = *varf; //dar putem dezaloca nodul
		(*varf) = (*varf)->next;
		free(temp);
	}

	return masina;
}

Masina cautareDupaId(Nod** stiva, long id) {
	Masina masina;
	masina.id = -1;
	masina.producator = NULL;
	masina.serie = -1;

	Nod* stivaAux = NULL;

	while ((*stiva) != NULL && (*stiva)->inf.id != id) {
		push(&stivaAux, pop(stiva));
	}
	if (*stiva) {
		masina = pop(stiva);
	}
	while (stivaAux) {
		push(stiva, pop(&stivaAux));
	}

	return masina;
}

void main() {
	Masina masina;
	Nod* stiva = NULL;
	printf("\nStiva:");
	push(&stiva, initMasina(1,"Renault", 1234));
	push(&stiva, initMasina(2,"Ford", 5678));
	push(&stiva, initMasina(3,"Ford", 5679));
	push(&stiva, initMasina(4,"Ford", 5677));
	push(&stiva, initMasina(5,"Peugeot", 9101));
	push(&stiva, initMasina(6,"Bmw", 1213));

	Masina masinaCautata = cautareDupaId(&stiva,3);
	afisareMasina(masinaCautata);
	free(masinaCautata.producator);

	while (stiva) {
		masina = pop(&stiva);
		afisareMasina(masina);
		free(masina.producator);
	}

	Nod* coada = NULL;

	printf("\nCoada:");

	put(&coada, initMasina(1, "Renault", 1234));
	put(&coada, initMasina(2, "Ford", 5678));
	put(&coada, initMasina(3, "Ford", 5679));
	put(&coada, initMasina(4, "Ford", 5677));
	put(&coada, initMasina(5, "Peugeot", 9101));
	put(&coada, initMasina(6, "Bmw", 1213));

	while (coada) {
		masina = pop(&coada);
		afisareMasina(masina);
		free(masina.producator);
	}
}