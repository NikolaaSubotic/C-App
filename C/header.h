#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#define MAX_OGLASA 100
#define MAX_IME 50
#define MAX_POZICIJA 100
#define MAX_ISKUSTVO 50
#define MAX_VRSTA_ANGAZMANA 500

typedef struct {
    char ime[MAX_IME];
    char pozicija[MAX_POZICIJA];
    char iskustvo[MAX_ISKUSTVO];
    char vrstaangazmana[MAX_VRSTA_ANGAZMANA];
    int pocetnaplata;
    int radnovreme;
} Oglas;

int Meni(void);

void load(Oglas oglasi[], int *n);
void save(const Oglas oglasi[], int n);

void all(const Oglas oglasi[], int n);
void add(Oglas oglasi[], int *n);

void poNazivu(const Oglas oglasi[], int n);
void poIskustvu(const Oglas oglasi[], int n);
void vecaPlata(const Oglas oglasi[], int n);
void vecaCRada(const Oglas oglasi[], int n);

#endif // HEADER_H_INCLUDED
