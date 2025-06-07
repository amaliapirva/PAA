//arbore binar=fiecare nod are cel mult 2 succesori(nodul stang si drept)

#include<stdio.h>
#include<stdlib.h>

typedef struct Nod{
    int data;
    struct Nod* stanga;
    struct Nod* dreapta;

}Nod;

//cream un nod nou
Nod* creeazaNod(int val){
    Nod* nou=(Nod*)malloc(sizeof(Nod));
    nou->data=val;
    nou->stanga=NULL;
    nou->dreapta=NULL;
    return nou;
}

//inserare automata in arbore
Nod* inserare(Nod* radacina,int val)
{
    if(radacina==NULL)
        return creeazaNod(val);
    
    if(val<radacina->data)
        radacina->stanga=inserare(radacina->stanga,val);
    else if(val>radacina->data)
        radacina->dreapta=inserare(radacina->dreapta,val);
    
    return radacina;
}

//parcurgeri
void preordine(Nod* radacina){
    if(!radacina) return;
    printf(" %d ",radacina->data);
    preordine(radacina->stanga);
    preordine(radacina->dreapta);
}

void inordine(Nod* radacina){
    if(!radacina) return;
    inordine(radacina->stanga);
    printf(" %d ",radacina->data);
    inordine(radacina->dreapta);
}

void postordine(Nod* radacina){
    if(!radacina) return;
    postordine(radacina->stanga);
    postordine(radacina->dreapta);
    printf(" %d ",radacina->data);
}

Nod* minValueNod(Nod* nod)
{//gaseste cel mai mic nod dintr-un subarbore
    Nod* curent=nod;
    while(curent && curent->stanga!=NULL)
        curent=curent->stanga;
    return curent;
}
//stergerea unui nod
Nod* stergeNod(Nod* radacina,int val)
{
    if(radacina==NULL)
        return NULL;

    if(val<radacina->data)
       { radacina->stanga=stergeNod(radacina->stanga,val);}
    else if(val>radacina->data)
        {radacina->dreapta=stergeNod(radacina->dreapta,val);}
    else{
        //Caz 1: fara copii
        if(radacina->stanga==NULL && radacina->dreapta==NULL){
            free(radacina);
            return NULL;
        }
        //Caz 2: un copil
        if(radacina->stanga==NULL){
            Nod* temp=radacina->dreapta;
            free(radacina);
            return temp;
        }else if(radacina->dreapta==NULL){
            Nod* temp=radacina->stanga;
            free(radacina);
            return temp;
        }
        //Caz 3:2 copii
        Nod* succesor=minValueNod(radacina->dreapta);
        radacina->data=succesor->data;
        radacina->dreapta=stergeNod(radacina->dreapta,succesor->data);
    }
    return radacina;
}
int main()
{
    Nod* radacina=NULL;
    
    radacina=inserare(radacina,50);
    radacina=inserare(radacina,30);
    radacina=inserare(radacina,70);
    radacina=inserare(radacina,20);
    radacina=inserare(radacina,40);
    radacina=inserare(radacina,60);
    radacina=inserare(radacina,80);
    
    printf("Preordine: ");
    preordine(radacina);
    printf("\n");

    printf("Inordine: ");
    inordine(radacina);
    printf("\n");

    printf("Postordine: ");
    postordine(radacina);
    printf("\n");

    printf("Stergem nodul 70/n");
    radacina=stergeNod(radacina,70);

    printf("Inordine: ");
    inordine(radacina);
    return 0;
}