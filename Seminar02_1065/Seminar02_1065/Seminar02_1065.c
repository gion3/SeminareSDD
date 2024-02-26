#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

struct Produs {
	float pret;
	int id;
	char* nume;
};

void citireVector(const char* numeFisier, int** vector, int* dimensiune) {
	//unde folosim vector si dimensiune avem nevoie de dereferentiere!!
	FILE* stream = NULL;
	stream = fopen(numeFisier, "r");
	if (stream != NULL) {
		//fara dereferentiere pt ca avem deja adresa ca parametru
		fscanf(stream, "%d", dimensiune);
		//dereferentiere si la vector si la dimensiune
		*vector = (int*)malloc(sizeof(int) * (*dimensiune));
		for (int i = 0; i < *dimensiune; i++) {
			//ne deplasam de la prima adresa
			fscanf(stream, "%d", (*vector) + i);
			//sau asa
			//fscanf(stream, "%d", &(*vector)[i]);
		}
		fclose(stream);
	}
	
}

void afisareProdus(struct Produs produs) {
	printf("\n Produsul %s are id: %d si pret: %.2f", produs.nume, produs.id, produs.pret);
}

struct Produs preluareProdusDinFisier(FILE* file) {
	struct Produs produs;
	if (file != NULL) {
		char buffer[20];

		fgets(buffer, 10, file);
		produs.pret = atof(buffer);
		
		fgets(buffer, 10, file);
		produs.id = atoi(buffer);

		fgets(buffer, 50, file);
		char* nume = strtok(buffer, "\n");
		produs.nume = malloc(sizeof(char) * (strlen(nume) + 1));
		strcpy(produs.nume, nume);
	}
	return produs;
}

void main() {
	int val1, val2;
	//citire doua voalori din fisier
	FILE* inStream = NULL;
	inStream = fopen("in.txt", "r");
	if (inStream != NULL) {
		fscanf(inStream, "%d", &val1);
		fscanf(inStream, "%d", &val2);
	}
	fclose(inStream);

	printf("\n Val1 = %d, val2= %d", val1, val2);

	//citire vector din fisier
	int* vector;
	int dimensiune;
	citireVector("vector.txt", &vector, &dimensiune);

	for (int i = 0; i < dimensiune; i++) {
		printf("\n vector de %d = %d", i, vector[i]);
	}
	free(vector);

	//citire struct produs din fisier
	FILE* file = NULL;
	file = fopen("produs.txt", "r");
	struct Produs produs = preluareProdusDinFisier(file);
	afisareProdus(produs);
}
//pt seminarul urmator: citirea unui vector de produse din fisier.