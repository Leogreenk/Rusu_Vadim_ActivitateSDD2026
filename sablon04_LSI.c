#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definim structura Masina cu atributele cerute
struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

// Afiseaza pe un singur rand atributele unei masini
void afisareMasina(Masina masina) {
	printf("%d %d %.2f %s %s %c\n", masina.id, masina.nrUsi, masina.pret, masina.model, masina.numeSofer, masina.serie);
}

// Parcurge vectorul si apeleaza functia de afisare pt fiecare element
void afisareVectorMasini(Masina* masini, int nrMasini) {
	for (int i = 0; i < nrMasini; i++) {
		afisareMasina(masini[i]);
	}
}

// Redimensioneaza vectorul si adauga o noua masina la final
void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
	// 1. Cream un vector temporar cu un spatiu in plus
	Masina* aux = (Masina*)malloc(sizeof(Masina) * ((*nrMasini) + 1));

	// 2. Copiem masinile vechi in noul vector
	for (int i = 0; i < *nrMasini; i++) {
		aux[i] = (*masini)[i];
	}

	// 3. Adaugam masina noua pe ultimul loc disponibil
	aux[*nrMasini] = masinaNoua;

	// 4. Eliberam adresa vechiului vector
	if (*masini != NULL) {
		free(*masini);
	}

	// 5. Mutam pointerul principal si crestem contorul
	*masini = aux;
	(*nrMasini)++;
}

// Citeste datele unei masini de pe o linie din fisier
Masina citireMasinaFisier(FILE* file) {
	Masina m;
	m.id = -1; // Setam un flag de eroare initial
	char bufferModel[100];
	char bufferSofer[100];

	// Daca citim fix 6 valori, alocam memorie pt texte si copiem
	if (fscanf(file, "%d %d %f %99s %99s %c", &m.id, &m.nrUsi, &m.pret, bufferModel, bufferSofer, &m.serie) == 6) {
		m.model = (char*)malloc(strlen(bufferModel) + 1);
		strcpy(m.model, bufferModel);

		m.numeSofer = (char*)malloc(strlen(bufferSofer) + 1);
		strcpy(m.numeSofer, bufferSofer);
	}
	return m;
}

// Deschide fisierul si incarca toate masinile intr-un vector
Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	FILE* file = fopen(numeFisier, "r");
	*nrMasiniCitite = 0;
	Masina* masini = NULL;

	if (file != NULL) {
		while (!feof(file)) { // Citim pana la sfaristul fisierului
			Masina m = citireMasinaFisier(file);
			if (m.id != -1) { // Daca masina e valida, o adaugam in vector
				adaugaMasinaInVector(&masini, nrMasiniCitite, m);
			}
		}
		fclose(file); // Foarte important sa inchidem fisierul
	}
	return masini;
}

// Curata memoria alocata pt a preveni memory leaks
void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	if (*vector != NULL) {
		// 1. Eliberam mai intai sirurile de caractere din fiecare masina
		for (int i = 0; i < *nrMasini; i++) {
			free((*vector)[i].model);
			free((*vector)[i].numeSofer);
		}
		// 2. Eliberam vectorul mare si resetam valorile
		free(*vector);
		*vector = NULL;
		*nrMasini = 0;
	}
}

int main() {
	int nrMasini = 0;

	// 1. Incarcam datele din fisier
	Masina* vectorMasini = citireVectorMasiniFisier("masini.txt", &nrMasini);

	// 2. Afisam si dezalocam
	if (vectorMasini != NULL) {
		afisareVectorMasini(vectorMasini, nrMasini);
		dezalocareVectorMasini(&vectorMasini, &nrMasini);
	}

	return 0;
}