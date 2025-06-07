/*se citeste un arbore generalizat dintr-un fisier si se transforma intr-un arbore binar si se afiseaza in preordine*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct NodGen{
    int val;
    struct NodGen* primFiu;
    struct NodGen* frateDrept;
}NodGen;

typedef struct NodBin{
    int val;
    struct NodBin* stanga;
    struct NodBin* dreapta;
}NodBin;

NodGen* creeazaNodGen(int val)
{
    NodGen* nod=(NodGen*)malloc(sizeof(NodGen));
    nod->val=val;
    nod->primFiu=NULL;
    nod->frateDrept=NULL;
    return nod;
}

NodBin* creeazaNodBin(int val)
{
    NodBin* nod=(NodBin*)malloc(sizeof(NodBin));
    nod->val=val;
    nod->dreapta=NULL;
    nod->stanga=NULL;
    return nod;
}

void adaugaFiu(NodGen* parinte,NodGen* fiuNod)
{
    if(!parinte->primFiu){
        parinte->primFiu=fiuNod;
    }else{
        NodGen* p=parinte->primFiu;
        while(p->frateDrept)
            p=p->frateDrept;
        p->frateDrept=fiuNod;
    }
}

NodBin* transforma(NodGen* radacina)
{
    if(!radacina) return NULL;

    NodBin* nod=creeazaNodBin(radacina->val);
    nod->stanga=transforma(radacina->primFiu);
    nod->dreapta=transforma(radacina->frateDrept);
    return nod;
}

void preordine(NodBin* radacina)
{
    if(!radacina) return;
    printf("%d ",radacina->val);
    preordine(radacina->stanga);
    preordine(radacina->dreapta);
}
void elibereazaBinar(NodBin* radacina)
{
    if(!radacina) return;
    elibereazaBinar(radacina->stanga);
    elibereazaBinar(radacina->dreapta);
    free(radacina);
}

void elibereazaGen(NodGen* radacina)
{
    if(!radacina) return;
    elibereazaGen(radacina->primFiu);
    elibereazaGen(radacina->frateDrept);
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
        perror("Eroare la deschiderea fisierului");
        return 1;
    }

    char linie[256];
    NodGen* noduri[20]={0};
    int esteFiu[20]={0};

    while(fgets(linie,256,f)){
        int parinte;
        char* token=strtok(linie," \n");
        if(!token) continue;
        parinte=atoi(token);

        if(!noduri[parinte])
            noduri[parinte]=creeazaNodGen(parinte);
        
        token=strtok(NULL," \n");
        while(token){
            int fiu=atoi(token);
            if(!noduri[fiu])
                noduri[fiu]=creeazaNodGen(fiu);
            adaugaFiu(noduri[parinte],noduri[fiu]);
            esteFiu[fiu]=1;
            token=strtok(NULL," \n");
        }
    }
    fclose(f);

    NodGen* radacineGen=NULL;
    for(int i=0; i<20; i++)
    {
        if(noduri[i] && !esteFiu[i]){
            radacineGen=noduri[i];
            break;
        }
    }
    NodBin* radBin=transforma(radacineGen);
    preordine(radBin);
    elibereazaBinar(radBin);
    elibereazaGen(radacineGen);
    return 0;
}