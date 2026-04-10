#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definirea structurii
struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

// Afiseaza datele unei singure masini
void afisareMasina(Masina masina) {
	printf("%d %d %.2f %s %s %c\n", masina.id, masina.nrUsi, masina.pret, masina.model, masina.numeSofer, masina.serie);
}

// Parcurge si afiseaza tot vectorul
void afisareVectorMasini(Masina* masini, int nrMasini) {
	for (int i = 0; i < nrMasini; i++) {
		afisareMasina(masini[i]);
	}
}

// Adauga o masina noua in vectorul alocat dinamic
void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
	// 1. Alocam un vector nou, mai mare cu 1 element
	Masina* aux = (Masina*)malloc(sizeof(Masina) * ((*nrMasini) + 1));

	// 2. Copiem elementele vechi
	for (int i = 0; i < *nrMasini; i++) {
		aux[i] = (*masini)[i];
	}

	// 3. Punem noua masina pe ultima pozitie
	aux[*nrMasini] = masinaNoua;

	// 4. Eliberam vectorul vechi (doar invelisul)
	if (*masini != NULL) {
		free(*masini);
	}

	// 5. Actualizam pointerul si dimensiunea
	*masini = aux;
	(*nrMasini)++;
}

// Citeste o singura masina din fisier
Masina citireMasinaFisier(FILE* file) {
	Masina m;
	m.id = -1; // Marcaj pt a verifica daca s-a citit corect
	char bufferModel[100];
	char bufferSofer[100];

	// Daca reusim sa citim 6 elemente de pe un rand, alocam dinamic textele
	if (fscanf(file, "%d %d %f %99s %99s %c", &m.id, &m.nrUsi, &m.pret, bufferModel, bufferSofer, &m.serie) == 6) {
		m.model = (char*)malloc(strlen(bufferModel) + 1);
		strcpy(m.model, bufferModel);

		m.numeSofer = (char*)malloc(strlen(bufferSofer) + 1);
		strcpy(m.numeSofer, bufferSofer);
	}
	return m;
}

// Deschide fisierul si citeste toate masinile in vector
Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	FILE* file = fopen(numeFisier, "r");
	*nrMasiniCitite = 0;
	Masina* masini = NULL;

	if (file != NULL) {
		while (!feof(file)) { // Cat timp nu am ajuns la final
			Masina m = citireMasinaFisier(file);
			if (m.id != -1) { // Daca citirea a fost valida, adaugam in vector
				adaugaMasinaInVector(&masini, nrMasiniCitite, m);
			}
		}
		fclose(file); // Inchidem fisierul mereu la final
	}
	return masini;
}

// Elibereaza toata memoria pt a nu avea memory leaks
void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	if (*vector != NULL) {
		// 1. Eliberam intai textele din interiorul fiecarei masini
		for (int i = 0; i < *nrMasini; i++) {
			free((*vector)[i].model);
			free((*vector)[i].numeSofer);
		}
		// 2. Eliberam vectorul in sine
		free(*vector);
		*vector = NULL;
		*nrMasini = 0;
	}
}

int main() {
	int nrMasini = 0;

	// 1. Citim si incarcam datele
	Masina* vectorMasini = citireVectorMasiniFisier("masini.txt", &nrMasini);

	// 2. Afisam si curatam la final
	if (vectorMasini != NULL) {
		afisareVectorMasini(vectorMasini, nrMasini);
		dezalocareVectorMasini(&vectorMasini, &nrMasini);
	}

	return 0;
}