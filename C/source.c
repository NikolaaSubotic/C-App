#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int Meni(){
    int opcija;
    printf("\n0. Izadji iz programa.\n");
    printf("1. Ucitaj iz fajla.\n");
    printf("2. Cuvaj u fajl.\n");
    printf("3. Dodaj novi oglas.\n");
    printf("4. Prikaz svih oglasa.\n");
    printf("5. Pretraga po nazivu.\n");
    printf("6. Pretraga po iskustvu.\n");
    printf("7. Prikaz oglasa sa vecom pocetnom platom.\n");
    printf("8. Ispisivanje oglasa sa vecom pocetnom platom.\n");
    printf("Vas unos: ");
    scanf("%d", &opcija);
    return opcija;
};

void add(Oglas oglas[], int *n){
    int i = *n;

    printf("\nUnesite ime kompanije: ");
    getchar();
    gets(oglas[i].ime);

    printf("Unesite naziv pozicije: ");
    gets(oglas[i].pozicija);

    printf("Unesite iskustvo: ");
    gets(oglas[i].iskustvo);

    printf("Unesite pocetnu platu: ");
    scanf("%s", &oglas[i].vrstaangazmana);

    printf("Unesite Vrstu angazmana: ");
    scanf("%d", &oglas[i].pocetnaplata);

    printf("Unesite nedeljno radno vreme: ");
    scanf("%d", &oglas[i].radnovreme);


    *n = (*n) + 1;

    printf("\nOglas dodata, molim sacuvajte unos!\n");
};

void all(Oglas oglas[], int n){
    int i;
    for(i = 0; i < n; i++){
        printf("\nNaziv: %s\n", oglas[i].ime);
        printf("naziv pozicije: %s\n", oglas[i].pozicija);
        printf("Iskustvo: %s\n", oglas[i].iskustvo);
        printf("Pocetna plata: %d\n", oglas[i].pocetnaplata);
        printf("Vrsta angazmana: %s", oglas[i].vrstaangazmana);
        printf("Radno vreme: %d\n", oglas[i].radnovreme);
    }
};

void poNazivu(Oglas oglas[], int n){
    int i;
    char ime[50];
    printf("\nUnesite ime oglasa koje zelite da prikazete: ");
    getchar();
    gets(ime);
    for(i = 0; i < n; i++){
        if(strcmp(oglas[i].ime, ime) == 0){
            printf("\nNaziv: %s\n", oglas[i].ime);
            printf("Naziv pozicije: %s\n", oglas[i].pozicija);
            printf("Iskustvo: %s\n", oglas[i].iskustvo);
            printf("Pocetna plata: %d\n", oglas[i].pocetnaplata);
            printf("Vrsta angazmana: %s\n", oglas[i].vrstaangazmana);
            printf("Radno vreme: %d\n", oglas[i].radnovreme);
        }
    }
};

void poIskustvu(Oglas oglas[], int n){
    int i;
    char iskustvo[50];
    printf("\nUnesite iskustvo: ");
    getchar();
    gets(poIskustvu);
    for(i = 0; i < n; i++){
        if(strcmp(oglas[i].iskustvo,iskustvo ) == 0){
            printf("\nNaziv: %s\n", oglas[i].ime);
            printf("POzicija: %s\n", oglas[i].pozicija);
            printf("Iskustvo: %s\n", oglas[i].iskustvo);
            printf("Vrsta angazmana: %s\n", oglas[i].vrstaangazmana);
            printf("Radno vreme: %d\n", oglas[i].radnovreme);
        }
    }
};

void vecaCRada(Oglas oglas[], int n){
    int i;
    float vecaCRada;
    printf("veca c rada: ");
    scanf("%d", &vecaCRada);
    for(i = 0; i < n; i++){
        if(oglas[i].pocetnaplata < vecaCRada){
            printf("\nNaziv: %s\n", oglas[i].ime);
            printf("Pozicija: %s\n", oglas[i].pozicija);
            printf("iskustvo: %s\n", oglas[i].iskustvo);
            printf("vrstaangazmana: %s\n", oglas[i].pocetnaplata);
            printf("nedeljno radno vreme: %d\n", oglas[i].radnovreme);
        }
    }
};

void vecaPlata(Oglas oglas[], int n){
    int i;
    float vecaPlata;
    printf("veca  plata: ");
    scanf("%d", &vecaPlata);
    for(i = 0; i < n; i++){
        if(oglas[i].radnovreme < vecaPlata){
            printf("\nNaziv: %s\n", oglas[i].ime);
            printf("Pozicija: %s\n", oglas[i].pozicija);
            printf("iskustvo: %s\n", oglas[i].iskustvo);
            printf("vrstaangazmana: %s\n", oglas[i].pocetnaplata);
            printf("nedeljno radno vreme: %d\n", oglas[i].radnovreme);
        }
    }
};

void save(Oglas oglas[], int n){
    FILE* fajl = fopen("oglasi.txt", "w");

    for(int i=0; i<n; i++){
        fprintf(fajl, "%s\n", oglas[i].ime);
        fprintf(fajl, "%s\n", oglas[i].pozicija);
        fprintf(fajl, "%s\n", oglas[i].iskustvo);
        fprintf(fajl, "%s\n", oglas[i].vrstaangazmana);
        fprintf(fajl, "%d\n", oglas[i].pocetnaplata);
        fprintf(fajl, "%d\n", oglas[i].radnovreme);
    }

    fclose(fajl);
    printf("\nUspesno sacuvano!\n");
};

void load(Oglas oglas[], int *n){
    FILE* fajl = fopen("oglasi.txt", "r");
    if(fajl == NULL){
        printf("\nFajl oglasi.txt ne postoji.\n");
        return;
    }

    int i = 0;
    while(!feof(fajl)){
        fgets(oglas[i].ime, 100, fajl);
        strtok(oglas[i].ime, "\n");
        fgets(oglas[i].pozicija, 10, fajl);
        strtok(oglas[i].pozicija, "\n");
        fgets(oglas[i].iskustvo, 50, fajl);
        strtok(oglas[i].iskustvo, "\n");
        fscanf(fajl, "%s", &oglas[i].vrstaangazmana);
        fgetc(fajl);
        fscanf(fajl, "%d", &oglas[i].pocetnaplata);
        fgetc(fajl);
        fscanf(fajl, "%d", &oglas[i].radnovreme);
        fgetc(fajl);

        i++;

    }

    *n = i - 1;
    fclose(fajl);
    printf("\nUspesno ucitano!\n");
}
