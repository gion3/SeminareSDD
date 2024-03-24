#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Masina Masina;
typedef struct Nod Nod;

struct Masina {
	char* producator;
	int serie;
};

struct Nod {
	Masina inf;
	Nod* next;
};

Masina initMasina(const char* producator, int serie) {
	Masina m;
	m.serie = serie;
	m.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(m.producator, producator);

	return m;
}

void afisareMasina(Masina masina) {
	printf("\nMasina %s are seria %d", masina.producator, masina.serie);
}

//pentru ca modificam lista finala -> transmitem lista prin pointer
void inserareLaInceput(Nod** cap, Masina masina) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->next = *cap;
	*cap = nou;
}

void parcurgereLista(Nod* cap) {
	while (cap != NULL) {
		afisareMasina(cap->inf);
		cap = cap->next;
	}
}

void inserareLaFinal(Nod** cap, Masina masina) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->next = NULL;

	if (*cap != NULL) {
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

void dezalocare(Nod** cap) {
	while ((*cap) != NULL) {
		Nod* copie = *cap;
		*cap = (*cap)->next;
		free(copie->inf.producator);
		free(copie);
	}
}

int nrAparitiiMasina(Nod* cap, char* producator) {
	int nr = 0;
	while (cap != NULL) {
		if (strcmp(cap->inf.producator, producator) == 0) {
			nr++;
		}
		cap = cap->next;
	}
	return nr;
}


void main() {

	Nod* cap = NULL;

	inserareLaInceput(&cap, initMasina("Ford", 1));
	inserareLaInceput(&cap, initMasina("Renault", 2));
	inserareLaInceput(&cap, initMasina("Mercedes", 3));
	inserareLaInceput(&cap, initMasina("Mercedes", 16));
	inserareLaInceput(&cap, initMasina("BMW", 4));

	parcurgereLista(cap);

	inserareLaFinal(&cap, initMasina("Toyota", 5));
	
	parcurgereLista(cap);

	printf("\nMasina %s apare in lista de %d ori", "Mercedes", nrAparitiiMasina(cap, "Mercedes"));
}