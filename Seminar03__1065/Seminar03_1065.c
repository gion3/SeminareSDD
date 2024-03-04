#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produs Produs;

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

void afisareProdus(Produs produs) {
	printf("\n Produsul %s are id: %d si pret: %.2f\n", produs.nume, produs.id, produs.pret);
}

Produs preluareProdusDinFisier(FILE* file) {
	Produs produs;
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

void citireProduseDinFisier(FILE* file, Produs** vectorProduse, int* nrProduse) {
	if (file != NULL) {
		while (!feof(file)) {
			*vectorProduse = (Produs*)realloc((*vectorProduse), (1 + (*nrProduse)) * sizeof(Produs));
			(*vectorProduse)[*nrProduse] = preluareProdusDinFisier(file);
			(*nrProduse)++;
		}
	}
}

void citireMatriceProduse(Produs*** matriceProduse,int nrLinii,int nrColoane) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane; j++) {
			printf("Pretul pentru pozitia(%d,%d)", i, j);
			scanf("%f", &(*matriceProduse)[i][j].pret);

			printf("Id-ul pentru pozitia(%d,%d)", i, j);
			scanf("%d", &(*matriceProduse)[i][j].id);

			printf("Denumirea pentru pozitia(%d,%d)", i, j);
			(*matriceProduse)[i][j].nume = (char*)malloc(sizeof(char) * 20);
			scanf("%s", (*matriceProduse)[i][j].nume);
		}
	}
}

void citireMatriceDeLaTastatura(Produs*** matriceProduse, int* nrLinii, int* nrColoane) {
	printf("\nNr linii:");
	scanf("%d", nrLinii);
	printf("\nNr coloane:");
	scanf("%d", nrColoane);

	*matriceProduse = (Produs**)malloc(sizeof(Produs*) * (*nrLinii));
	for (int i = 0; i < (*nrLinii); i++) {
		(*matriceProduse)[i] = (Produs*)malloc(sizeof(Produs) * (*nrColoane));
	}

	citireMatriceProduse(matriceProduse, *nrLinii, *nrColoane);
}

void afisareMatriceProduse(Produs** matriceProduse, int nrLinii, int nrColoane) {
	for (int i = 0; i < nrLinii; i++) {
		for (int j = 0; j < nrColoane; j++) {

			afisareProdus(matriceProduse[i][j]);
		}
	}
}

void main() {
	/*int val1, val2;
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
	free(vector);*/

	//citire struct produs din fisier
	FILE* file = NULL;
	file = fopen("produs.txt", "r");
	Produs produs = preluareProdusDinFisier(file);
	afisareProdus(produs);


	//citire vector de produse din fisier
	Produs* vectorProduse = NULL;
	int nrProduse = 0;
	file = NULL;
	file = fopen("produse.txt", "r");

	citireProduseDinFisier(file, &vectorProduse, &nrProduse);

	for (int i = 0; i < nrProduse; i++) {
		afisareProdus(vectorProduse[i]);
		free(vectorProduse[i].nume);
	}

	free(vectorProduse);

	
	//citire matrice de produse de la tastatura
	Produs** matriceProduse = NULL;
	int nrLinii;
	int nrColoane;

	citireMatriceDeLaTastatura(&matriceProduse, &nrLinii, &nrColoane);
	afisareMatriceProduse(matriceProduse, nrLinii, nrColoane);

}
//pt seminarul urmator: citirea unui vector de produse din fisier.