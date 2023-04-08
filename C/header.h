#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

typedef struct{
    char ime[50];
    char pozicija[100];
    char iskustvo[50];
    char vrstaangazmana[500];
    int pocetnaplata;
    int radnovreme;

} Oglas;

int Meni();

void load(Oglas oglas[], int *n);
void save(Oglas oglas[], int n);

void all(Oglas oglas[], int n);
void add(Oglas oglas[], int *n);

void poNazivu(Oglas oglas[], int n);
void poIskustvu(Oglas oglas[], int n);
void vecaPlata(Oglas oglas[], int n);
void vecaCRada(Oglas Oglas[], int n);
#endif // HEADER_H_INCLUDED
