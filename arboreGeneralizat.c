//structura arborelui generalizat+alte functionalitati
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NODURI 100

typedef struct Nod {
    int val;
    struct Nod* primFiu;
    struct Nod* frateDrept;
} Nod;

Nod* creeazaNod(int val) {
    Nod* nod = (Nod*)malloc(sizeof(Nod));
    nod->val = val;
    nod->primFiu = NULL;
    nod->frateDrept = NULL;
    return nod;
}

void adaugaFiu(Nod* parinte, Nod* fiuNod) {
    if (!parinte->primFiu) {
        parinte->primFiu = fiuNod;
    } else {
        Nod* p = parinte->primFiu;
        while (p->frateDrept)
            p = p->frateDrept;
        p->frateDrept = fiuNod;
    }
}

void afiseaza(Nod* radacina) {
    if (!radacina) return;
    printf("%d ", radacina->val);
    afiseaza(radacina->primFiu);
    afiseaza(radacina->frateDrept);
}

int numaraFii(Nod* nod) {
    int count = 0;
    Nod* fiu = nod->primFiu;
    while (fiu) {
        count++;
        fiu = fiu->frateDrept;
    }
    return count;
}

void elibereaza(Nod* radacina) {
    if (!radacina) return;
    elibereaza(radacina->primFiu);
    elibereaza(radacina->frateDrept);
    free(radacina);
}

void stergeNod(Nod** parinte, int valoare) {
    if (!*parinte) return;
    Nod* curent = (*parinte)->primFiu;
    Nod* anterior = NULL;

    while (curent) {
        if (curent->val == valoare) {
            if (anterior)
                anterior->frateDrept = curent->frateDrept;
            else
                (*parinte)->primFiu = curent->frateDrept;
            elibereaza(curent);
            return;
        }
        anterior = curent;
        curent = curent->frateDrept;
    }

    stergeNod(&(*parinte)->primFiu, valoare);
    stergeNod(&(*parinte)->frateDrept, valoare);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Utilizare: %s nume_fisier\n", argv[0]);
        return 1;
    }

    FILE* f = fopen(argv[1], "r");
    if (!f) {
        perror("Eroare la deschiderea fisierului");
        return 1;
    }

    char linie[256];
    Nod* noduri[MAX_NODURI] = {0};
    int esteFiu[MAX_NODURI] = {0};

    while (fgets(linie, 256, f)) {
        int parinte;
        char* token = strtok(linie, " \n");
        if (!token) continue;
        parinte = atoi(token);

        if (!noduri[parinte])
            noduri[parinte] = creeazaNod(parinte);

        token = strtok(NULL, " \n");
        while (token) {
            int fiu = atoi(token);
            if (!noduri[fiu])
                noduri[fiu] = creeazaNod(fiu);
            adaugaFiu(noduri[parinte], noduri[fiu]);
            esteFiu[fiu] = 1;
            token = strtok(NULL, " \n");
        }
    }
    fclose(f);

    Nod* radacina = NULL;
    for (int i = 0; i < MAX_NODURI; i++) {
        if (noduri[i] && !esteFiu[i]) {
            radacina = noduri[i];
            break;
        }
    }

    if (!radacina) {
        printf("Nu s-a gasit radacina.\n");
        return 1;
    }

    printf("Arbore in preordine:\n");
    afiseaza(radacina);
    printf("\n");

    printf("\nNumarul de fii pentru fiecare nod:\n");
    for (int i = 0; i < MAX_NODURI; i++) {
        if (noduri[i]) {
            printf("Nodul %d are %d fii\n", i, numaraFii(noduri[i]));
        }
    }

    int nodDeSters = 3;
    printf("\nStergem nodul %d...\n", nodDeSters);
    stergeNod(&radacina, nodDeSters);

    printf("Arbore dupa stergere:\n");
    afiseaza(radacina);
    printf("\n");

    elibereaza(radacina);
    return 0;
}
