//arbore binar
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

Nod* inserare(Nod* radacina,int val)
{
    if(radacina==NULL) return creeazaNod(val);
    if(val<radacina->val)
        radacina->stanga=inserare(radacina->stanga,val);
    if(val>radacina->val)
        radacina->dreapta=inserare(radacina->dreapta,val);
    return radacina;
}

void preordine(Nod* radacina)
{
    if(!radacina) return;
    printf("%d ",radacina->val);
    preordine(radacina->stanga);
    preordine(radacina->dreapta);
}

void inordine(Nod* radacina)
{
    if(!radacina) return;
    inordine(radacina->stanga);
    printf("%d ",radacina->val);
    inordine(radacina->dreapta);
}
void postordine(Nod* radacina)
{
    if(!radacina) return;
    postordine(radacina->stanga);
    postordine(radacina->dreapta);
    printf("%d ",radacina->val);
}

void elibereaza(Nod* radacina)
{
    if(!radacina) return;
    elibereaza(radacina->stanga);
    elibereaza(radacina->dreapta);
    free(radacina);
}
int main(int argc,char* argv[]){
    if(argc!=2)
    {
        printf("Eroare");
        return 1;
    }
    FILE* f=fopen(argv[1],"r");
    if(!f)
    {
        printf("Eroare");
        return 1;
    }
    Nod* radacina=NULL;
    int val;
    while(fscanf(f,"%d",&val)==1)
    {
        if(val>0)
            radacina=inserare(radacina,val);
    }
    fclose(f);
    preordine(radacina);
    inordine(radacina);
    postordine(radacina);
    elibereaza(radacina);
    return 0;
}