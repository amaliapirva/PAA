//arbore B

#include<stdio.h>
#include<stdlib.h>

#define T 2

typedef struct BTreeNode{
    int *chei;//vector de chei
    struct BTreeNode **copii;//vector de pointeri catre copii
    int n;//numarul actual de chei
    int frunza;//1 daca e frunza, altfel 0
}BTreeNode;

//Creaza un nou nod de arbore B
BTreeNode* creeazaNod(int frunza)
{
    BTreeNode* nod=(BTreeNode*)malloc(sizeof(BTreeNode));
    nod->frunza=frunza;
    nod->chei=(int*)malloc((2*T-1)*sizeof(int));
    nod->copii=(BTreeNode**)malloc(2*T*sizeof(BTreeNode*));
    nod->n=0;
    return nod;
}

void afiseaza(BTreeNode* nod,int nivel){
    if(nod!=NULL){
        for(int i=0; i<nivel; i++) printf(" ");
        for(int i=0; i<nod->n; i++) printf("%d",nod->chei[i]);
        printf("\n");
        if(!nod->frunza){
            for(int i=0; i<=nod->n; i++) 
            afiseaza(nod->copii[i],nivel+1);
        }
    }
}

void imparteCopil(BTreeNode* x,int i,BTreeNode* y){
    BTreeNode* z=creareNod(y->frunza);
    z->n=T-1;

    for(int j=0; j<T-1; j++)
        z->chei[j]=y->chei[j+T];

    if(!y->frunza)
        for(int j=0; j<T; j++)
            z->copii[j]=y->copii[j+T];
    y->n=T-1;

    for(int j=x->n; j>=i+1; j--)
        x->copii[j+1]=x->copii[j];
    x->copii[i+1]=z;

    for(int j=x->n-1; j>=i; j--)
        x->chei[j+1]=x->chei[j];

    x->chei[i]=y->chei[T-1];
    x->n++;
}

// Insereaza o cheie intr-un nod care nu este plin
void insereazaNepin(BTreeNode* x, int k) {
    int i = x->n - 1;

    if (x->frunza) {
        while (i >= 0 && x->chei[i] > k) {
            x->chei[i + 1] = x->chei[i];
            i--;
        }
        x->chei[i + 1] = k;
        x->n++;
    } else {
        while (i >= 0 && x->chei[i] > k)
            i--;
        i++;

        if (x->copii[i]->n == 2 * T - 1) {
            imparteCopil(x, i, x->copii[i]);
            if (k > x->chei[i]) i++;
        }
        insereazaNepin(x->copii[i], k);
    }
}

// Insereaza cheia k in arbore
BTreeNode* insereaza(BTreeNode* radacina, int k) {
    if (radacina->n == 2 * T - 1) {
        BTreeNode* s = creareNod(0);
        s->copii[0] = radacina;
        imparteCopil(s, 0, radacina);
        insereazaNepin(s, k);
        return s;
    } else {
        insereazaNepin(radacina, k);
        return radacina;
    }
}

int main() {
    BTreeNode* radacina = creareNod(1); // radacina e frunza initial

    int valori[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(valori) / sizeof(valori[0]);

    for (int i = 0; i < n; i++)
        radacina = insereaza(radacina, valori[i]);

    printf("Arbore B:\n");
    afiseaza(radacina, 0);

    return 0;
}
