//Citeste dintr-un fisier text numere intregi pozitive salvate printr-un spatiu si introdu aceste valori intr-un arbore binar
//ordonat. Programul va afisa la iesirea standard cele 3 parcurgeri ale arborelui fiecare pe cate o linie.
//numele fisierului text va fi primul argument

#include<stdio.h>
#include<stdlib.h>

typedef struct Nod{
    int val;
    struct Nod* stanga;
    struct Nod* dreapta;
}Nod;

Nod* creeazaNod(int val)
{
    Nod* nod=(Nod*)malloc(sizeof(Nod));
    nod->val=val;
    nod->stanga=NULL;
    nod->dreapta=NULL;
    return nod;
}

Nod* insereaza(Nod* radacina,int val)
{
    if(radacina==NULL) return creeazaNod(val);
    if(val<radacina->val)
        radacina->stanga=insereaza(radacina->stanga,val);
    else
        radacina->dreapta=insereaza(radacina->dreapta,val);
    return radacina;
}

void preordine(Nod* radacina)
{
    if(radacina==NULL) return;
    printf("%d",radacina->val);
    preordine(radacina->stanga);
    preordine(radacina->dreapta);
}

void inordine(Nod* radacina)
{
    if(radacina==NULL) return;
    inordine(radacina->stanga);
    printf("%d",radacina->val);
    inordine(radacina->dreapta);
}

void postordine(Nod* radacina)
{
    if(radacina==NULL)
    postordine(radacina->stanga);
    postordine(radacina->dreapta);
    printf("%d",radacina->val);
}

void elibereaza(Nod* radacina)
{
    if(radacina==NULL) return;
    elibereaza(radacina->stanga);
    elibereaza(radacina->dreapta);
    free(radacina);
}

int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        printf("Eroare la numarul de argumente");
        return 1;
    }
    FILE* f=fopen(argv[1],"r");
    if(!f)
    {
        perror("Eroare la deschierea fisierului");
        exit(EXIT_FAILURE);
    }

    Nod* radacina=NULL;
    int val;
    while(fscanf(f,"%d",&val)==1){
        if(val>0)
        radacina=insereaza(radacina,val);
    }
    fclose(f);
    
    preordine(radacina);
    inordine(radacina);
    postordine(radacina);
    elibereaza(radacina);

    return 0;
}