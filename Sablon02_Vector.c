#include<stdio.h>
#include<malloc.h>

struct Telefon {
	int id;
	int ram;
	char* producator;
	float pret;
	char serie;
};
struct Telefon initializare(int id, int ram, char* producator, float pret, char serie)
{
	struct Telefon t;
	t.id = id;
	t.ram = ram;
	t.producator = (char*)malloc((strlen(producator) + 1) * sizeof(char));
	strcpy(t.producator, producator);
	t.pret = pret;
	t.serie = serie;
	return t;
}
struct Telefon copiazatelefon(struct Telefon t) {
	struct Telefon telefon = initializare(t.id, t.ram, t.producator, t.pret, t.serie);
	return telefon;
}

void afisare(struct Telefon t) {
	printf("Id:%d\nram:%d\nProducator: %s\nPret: %fSerie %c\n\n", t.id, t.ram, t.producator, t.pret, t.serie);
}

void afisareVector(struct Telefon* vector, int nrelemente)
{
	for (int i = 0; i < nrelemente; i++)
		afisare(vector[i]);

}

struct Telefon* copiazaPrimeleNElemente(struct Telefon* vector, int nrElemente, int nrElementeCopiate) {
	if (nrElementeCopiate <= nrElemente)
	{
		struct Telefon* vectorNou = (struct Telefon*)malloc(sizeof(struct Telefon) * nrElementeCopiate);
		for (int i = 0; i < nrElementeCopiate; i++)
			vectorNou[i] = copiazatelefon(vector[i]);

	}
}



void dezalocare(struct Telefon** vector, int* nrElemente) {

	for (int i = 0; i < *nrElemente; i++)
	{
		free((*vector)[i].producator);
		(*vector)[i].producator = NULL;
	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}

void copiazaTelefoaneScumpe(struct Telefon* vector, char nrElemente, float pret_min, struct Telefon** vectorNou, int* dimensiune) {
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++)
	{
		if (vector[i].pret >= pret_min)
		{
			(*dimensiune)++;

		}
	}
	*vectorNou = malloc(*dimensiune * sizeof(struct Telefon));
	for (int i = 0; i < nrElemente; i++)
	{
		if (vector[i].pret >= pret_min)
		{
			(*vectorNou)[j] = copiazaTelefon;
			j += 1;
		}
	}



	//	//parametrul prag poate fi modificat in functie de 
	//	// tipul atributului ales pentru a indeplini o conditie
	//	//este creat un nou vector cu elementele care indeplinesc acea conditie
	//}
	//
	//struct Sablon getPrimulElementConditionat(struct Sablon* vector, int nrElemente, const char* conditie) {
		//trebuie cautat elementul care indeplineste o conditie
		//dupa atributul de tip char*. Acesta este returnat.
		// 	struct Sablon s;
		//s.id = 1;

		//return s;
	//}

	int main()
	{

		struct Telefon t;
		t = initializare(1, 8, "samsung", 3000.5, 'A');
		afisare(t);
		int nrtelefoane = 3;
		struct Telefon* telefoane = (struct Telefon*)malloc(sizeof(struct Telefon) * nrtelefoane);
		telefoane[0] = initializare(1, 8, "samsung", 3000.5, 'A');
		telefoane[1] = initializare(1, 8, "samsung", 3000.5, 'S');
		telefoane[2] = t;
		afisareVector(telefoane, nrtelefoane);
		int nrtelefoanecopiate = 2;
		struct Telefon* telefoanecopiate = copiazaPrimeleNElemete(telefoane, nrtelefoane, nrtelefoanecopiate);
		printf("vectortelefoane copiate \n");
		afisareVector(telefoanecopiate, nrtelefoanecopiate);
		dezalocare(&telefoane, &nrtelefoane);
		printf("vector telefoane dupa dezalocare: \n");
		afisareVector(telefoane, nrtelefoane);
		struct Telefon vectorNou;
		int dimensiune;

		copiazaTelefoaneScumpe(telefoane nrTelefoane, 2500, &vectorNou, &dimensiune);
		printf("telefoane scumpe: \n");
		afisareVector(vectorNou, dimensiune);


		return 0;
	}