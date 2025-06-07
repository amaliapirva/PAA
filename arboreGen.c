//structura unui arbore generalizat citit dintr-un fisier
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct Nod{
    int val;
    struct Nod* primFiu;
    struct Nod* frateDrept;
}Nod;

Nod* creeazaNod(int val)
{
    Nod* nod=(Nod*)malloc(sizeof(Nod));
    nod->val=val;
    nod->primFiu=NULL;
    nod->frateDrept=NULL;
    return nod; 
}

void adaugaFiu(Nod* parinte,Nod* fiuNou)
{
    if(!parinte->primFiu){
        parinte->primFiu=fiuNou;
    }else{
        Nod* p=parinte->primFiu;
        while(p->frateDrept)
            p=p->frateDrept;
        p->frateDrept=fiuNou;
    }
}

void afiseaza(Nod* radacina)
{
    if(!radacina) return;
    printf("%d ",radacina->val);
    afiseaza(radacina->primFiu);
    afiseaza(radacina->frateDrept);
}

void elibereaza(Nod* radacina)
{
    if(!radacina) return;
    elibereaza(radacina->primFiu);;
    elibereaza(radacina->frateDrept);
    free(radacina);
}

int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        printf("Numarul de argumente nu este bun");
        return 1;
    }
    FILE* f=fopen(argv[1],"r");
    if(!f)
    {
        perror("Eroare la deschiderea fisierului");
        return 1;
    }

    char linie[256];
    Nod* noduri[20]={0};
    int esteFiu[20]={0};

    while(fgets(linie,256,f))
    {
        int parinte;
        char* token=strtok(linie," \n");
        if(!token) continue;
        parinte=atoi(token);

        if(!noduri[parinte])
            noduri[parinte]=creeazaNod(parinte);

        token=strtok(NULL," \n");
        while(token){
            int fiu=atoi(token);
            if(!noduri[fiu])
                noduri[fiu]=creeazaNod(fiu);
            adaugaFiu(noduri[parinte],noduri[fiu]);
            esteFiu[fiu]=1;
            token=strtok(NULL," \n");
        }
    }
    fclose(f);

    Nod* radacina=NULL;
    for(int i=0; i<20; i++)
    {
        if(noduri[i] && !esteFiu[i])
        {
            radacina=noduri[i];
            break;
        }
    }
    if(!radacina){
        printf("Nu s-a gasit radacina");
        return 1;
    }

    afiseaza(radacina);
    elibereaza(radacina);

    return 0;
}