//arbore AVL structura+functionalitati
#include<stdio.h>
#include<stdlib.h>

typedef struct NodAVL{
    int val;
    int inaltime;
    struct NodAVL* stanga;
    struct NodAVL* dreapta;
}NodAVL;

int inaltime(NodAVL* n){
    return n ? n->inaltime : 0;
}

int max(int a,int b){
    return (a>b) ? a : b;
}

int factorEchilibru(NodAVL* n){
    return n ? inaltime(n->stanga) - inaltime(n->dreapta) : 0;
}

//rotatii
NodAVL* rotatieDreapta(NodAVL* y)
{
    NodAVL* x=y->stanga;
    NodAVL* T2=x->dreapta;
    
    x->dreapta=y;
    y->stanga=T2;

    y->inaltime=1+max(inaltime(y->stanga),inaltime(y->dreapta));
    x->inaltime=1+max(inaltime(x->stanga),inaltime(x->dreapta));
    return x;
}

NodAVL* rotatieStanga(NodAVL* x)
{
    NodAVL* y=x->dreapta;
    NodAVL* T2=y->stanga;

    y->stanga=x;
    x->dreapta=T2;

    x->inaltime=1+max(inaltime(x->stanga),inaltime(x->dreapta));
    y->inaltime=1+max(inaltime(y->stanga),inaltime(y->dreapta));
    return y;
}

NodAVL* inserareAVL(NodAVL* radacina,int val)
{
    if(!radacina){
        NodAVL* nod=(NodAVL*)malloc(sizeof(NodAVL));
        nod->val=val;
        nod->stanga=NULL;
        nod->dreapta=NULL;
        nod->inaltime=1;
        return nod;
    }
    if(val<radacina->val)
        radacina->stanga=inserareAVL(radacina->stanga,val);
    else if(val>radacina->val)
        radacina->dreapta=inserareAVL(radacina->dreapta,val);
    else
    return radacina;

    radacina->inaltime=1+max(inaltime(radacina->stanga),inaltime(radacina->dreapta));
    int echilibru=factorEchilibru(radacina);

    //avem 4 cazuri
    if(echilibru>1 && val<radacina->stanga->val)
        return rotatieDreapta(radacina); //left-left
    if(echilibru<-1 && val>radacina->dreapta->val)
        return rotatieStanga(radacina); //right-right
    if(echilibru>1 && val>radacina->stanga->val){
        radacina->stanga=rotatieStanga(radacina->stanga);
        return rotatieDreapta(radacina);//left-right
        }
    if(echilibru<-1 && val<radacina->dreapta->val){
        radacina->dreapta=rotatieDreapta(radacina->dreapta);
        return rotatieStanga(radacina);//right-left
    }
    return radacina;
}
void inordine(NodAVL* radacina)
{
    if(!radacina) return;
    inordine(radacina->stanga);
    printf("%d ",radacina->val);
    inordine(radacina->dreapta);
}

int main()
{
     NodAVL* rad = NULL;

    int valori[] = {30, 20, 40, 10, 25, 50, 5}; // creează rotații
    int n = sizeof(valori) / sizeof(valori[0]);

    for (int i = 0; i < n; i++) {
        rad = inserareAVL(rad, valori[i]);
    }

    printf("AVL in inordine: ");
    inordine(rad);
    printf("\n");

    return 0;
}