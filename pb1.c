/*Intr o baza de date sunt memorate intrari de tipul nume(string),data nasterii in Unix epoch time(int)
Baza de date este implementata sub forma unui arbore B. Sa se implementeze o functie care afiseaza numele tuturor persoanelor nascute dupa o data primita ca parametru*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 2
#define NN (2*N)

typedef struct{
    char nume[100];
    int birthdate;
}Persoana

typedef struct nod{
    Persoana persoana;
    struct pagina *p;
    int contor;
}NOD;

typedef struct pagina{
    int m; //numarul curent de chei in pagina
    struct pagina *p0; //referinta la copilul din stanga primei chei
    NOD elem[NN];
}PAGINA;

typedef PAGINA* refPagina;

//cream persoana
Persoana creeazaPersoana(const char* nume, int birthdate){
    Persoana p;
    strcpy(p.nume,nume);
    p.birthdate=birthdate;
    return p;
}

//creare pagina noua
refPagina creeazaPagina()
{
    refPagina p=(refPagina)malloc(sizeof(PAGINA));
    p->m=0;
    p->p0=NULL;
    for(int i=0; i<NN; i++)
    {
        p->elem[i].p=NULL;
    }
    return p;
}

//inserare sortata intr un nod
void inserarelaPozitie(refPagina pag,int k,Persoana persoana,refPagina dreapta){
    for(int i=pag->m; i>k; i--){
        pag->elem[i]=pag->elem[i-1];
    }
    pag->elem[k].persoana=persoana;
    pag->elem[k].p=dreapta;
    pag->m++;
}

int inserare(refPagina *pagRef,Persoana persoana, Persoan *cheieMedian,refPagina *dreaptaNoua)
{
    refPagina pag=*pagRef;
    int i;
    if(pag==NULL)
    {
        *cheieMedian=persoana;
        *dreaptaNoua=NULL;
        return 1;
    }
    i=pag->m-1;
    
}