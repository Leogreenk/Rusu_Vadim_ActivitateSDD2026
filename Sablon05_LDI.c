#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct Nod {
	Masina info;
	struct Nod* prev;
	struct Nod* next;
};
typedef struct Nod Nod;

struct ListaDubla {
	Nod* prim;
	Nod* ultim;
};
typedef struct ListaDubla ListaDubla;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	Masina m1;
	m1.id = -1;

	if (fgets(buffer, 100, file) == NULL) return m1;

	char* aux = strtok(buffer, sep);
	if (aux == NULL) return m1;

	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = (float)atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	m1.model = (char*)malloc(strlen(aux) + 1);
	strcpy(m1.model, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = (char*)malloc(strlen(aux) + 1);
	strcpy(m1.numeSofer, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("%d %d %.2f %s %s %c\n", masina.id, masina.nrUsi, masina.pret, masina.model, masina.numeSofer, masina.serie);
}

void afisareListaMasini(ListaDubla lista) {
	Nod* curent = lista.prim;
	while (curent != NULL) {
		afisareMasina(curent->info);
		curent = curent->next;
	}
}

void adaugaMasinaInLista(ListaDubla* lista, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = NULL;
	nou->prev = lista->ultim;

	if (lista->ultim != NULL) {
		lista->ultim->next = nou;
	}
	else {
		lista->prim = nou;
	}
	lista->ultim = nou;
}

void adaugaLaInceputInLista(ListaDubla* lista, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->prev = NULL;
	nou->next = lista->prim;

	if (lista->prim != NULL) {
		lista->prim->prev = nou;
	}
	else {
		lista->ultim = nou;
	}
	lista->prim = nou;
}

ListaDubla citireLDMasiniDinFisier(const char* numeFisier) {
	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	FILE* file = fopen(numeFisier, "r");
	if (file != NULL) {
		while (!feof(file)) {
			Masina m = citireMasinaDinFisier(file);
			if (m.id != -1) {
				adaugaMasinaInLista(&lista, m);
			}
		}
		fclose(file);
	}
	return lista;
}

void dezalocareLDMasini(ListaDubla* lista) {
	Nod* curent = lista->prim;
	while (curent != NULL) {
		Nod* temp = curent;
		curent = curent->next;

		free(temp->info.model);
		free(temp->info.numeSofer);
		free(temp);
	}
	lista->prim = NULL;
	lista->ultim = NULL;
}

float calculeazaPretMediu(ListaDubla lista) {
	if (lista.prim == NULL) return 0;

	float suma = 0;
	int contor = 0;
	Nod* curent = lista.prim;

	while (curent != NULL) {
		suma += curent->info.pret;
		contor++;
		curent = curent->next;
	}
	return suma / contor;
}

void stergeMasinaDupaID(ListaDubla* lista, int id) {
	Nod* curent = lista->prim;

	while (curent != NULL) {
		if (curent->info.id == id) {
			if (curent->prev != NULL) {
				curent->prev->next = curent->next;
			}
			else {
				lista->prim = curent->next;
			}

			if (curent->next != NULL) {
				curent->next->prev = curent->prev;
			}
			else {
				lista->ultim = curent->prev;
			}

			free(curent->info.model);
			free(curent->info.numeSofer);
			free(curent);
			return;
		}
		curent = curent->next;
	}
}

char* getNumeSoferMasinaScumpa(ListaDubla lista) {
	if (lista.prim == NULL) return NULL;

	Nod* curent = lista.prim;
	float maxPret = curent->info.pret;
	char* numeSoferMax = curent->info.numeSofer;

	while (curent != NULL) {
		if (curent->info.pret > maxPret) {
			maxPret = curent->info.pret;
			numeSoferMax = curent->info.numeSofer;
		}
		curent = curent->next;
	}

	char* copie = (char*)malloc(strlen(numeSoferMax) + 1);
	strcpy(copie, numeSoferMax);
	return copie;
}

int main() {
	ListaDubla lista = citireLDMasiniDinFisier("masini.txt");
	afisareListaMasini(lista);

	printf("\nPret mediu: %.2f\n", calculeazaPretMediu(lista));

	char* soferMax = getNumeSoferMasinaScumpa(lista);
	if (soferMax != NULL) {
		printf("Sofer cu masina cea mai scumpa: %s\n\n", soferMax);
		free(soferMax);
	}

	stergeMasinaDupaID(&lista, 2);
	afisareListaMasini(lista);

	dezalocareLDMasini(&lista);
	return 0;
}