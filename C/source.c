#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

static void trim_newline(char *s) {
    size_t len;
    if (s == NULL) {
        return;
    }

    len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
    }
}

static int read_line(char *buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return 0;
    }

    trim_newline(buffer);
    return 1;
}

static int read_int_in_range(const char *prompt, int min, int max) {
    char line[64];
    long value;
    char *endptr;

    while (1) {
        printf("%s", prompt);
        if (!read_line(line, sizeof(line))) {
            return min;
        }

        value = strtol(line, &endptr, 10);
        if (*line == '\0' || *endptr != '\0') {
            printf("Neispravan unos. Pokusajte ponovo.\n");
            continue;
        }

        if (value < min || value > max) {
            printf("Unos mora biti u opsegu [%d, %d].\n", min, max);
            continue;
        }

        return (int)value;
    }
}

static int equals_ignore_case(const char *a, const char *b) {
    while (*a != '\0' && *b != '\0') {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) {
            return 0;
        }
        ++a;
        ++b;
    }

    return *a == '\0' && *b == '\0';
}

static void print_oglas(const Oglas *oglas, int index) {
    printf("\n[%d] Kompanija: %s\n", index + 1, oglas->ime);
    printf("Pozicija: %s\n", oglas->pozicija);
    printf("Iskustvo: %s\n", oglas->iskustvo);
    printf("Vrsta angazmana: %s\n", oglas->vrstaangazmana);
    printf("Pocetna plata: %d\n", oglas->pocetnaplata);
    printf("Nedeljno radno vreme: %d\n", oglas->radnovreme);
}

int Meni(void) {
    printf("\n=== MENI ===\n");
    printf("0. Izadji iz programa\n");
    printf("1. Ucitaj iz fajla\n");
    printf("2. Sacuvaj u fajl\n");
    printf("3. Dodaj novi oglas\n");
    printf("4. Prikaz svih oglasa\n");
    printf("5. Pretraga po nazivu kompanije\n");
    printf("6. Pretraga po iskustvu\n");
    printf("7. Oglasi sa platom iznad zadate\n");
    printf("8. Oglasi sa radnim vremenom iznad zadatog\n");

    return read_int_in_range("Vas izbor: ", 0, 8);
}

void add(Oglas oglasi[], int *n) {
    Oglas *novi;

    if (*n >= MAX_OGLASA) {
        printf("\nDostignut je maksimalan broj oglasa (%d).\n", MAX_OGLASA);
        return;
    }

    novi = &oglasi[*n];

    printf("\nUnesite ime kompanije: ");
    if (!read_line(novi->ime, sizeof(novi->ime)) || novi->ime[0] == '\0') {
        printf("Ime kompanije ne sme biti prazno.\n");
        return;
    }

    printf("Unesite naziv pozicije: ");
    if (!read_line(novi->pozicija, sizeof(novi->pozicija)) || novi->pozicija[0] == '\0') {
        printf("Naziv pozicije ne sme biti prazan.\n");
        return;
    }

    printf("Unesite nivo iskustva: ");
    if (!read_line(novi->iskustvo, sizeof(novi->iskustvo)) || novi->iskustvo[0] == '\0') {
        printf("Iskustvo ne sme biti prazno.\n");
        return;
    }

    printf("Unesite vrstu angazmana: ");
    if (!read_line(novi->vrstaangazmana, sizeof(novi->vrstaangazmana)) || novi->vrstaangazmana[0] == '\0') {
        printf("Vrsta angazmana ne sme biti prazna.\n");
        return;
    }

    novi->pocetnaplata = read_int_in_range("Unesite pocetnu platu: ", 0, 1000000000);
    novi->radnovreme = read_int_in_range("Unesite nedeljno radno vreme (sati): ", 1, 168);

    (*n)++;
    printf("\nOglas je uspesno dodat.\n");
}

void all(const Oglas oglasi[], int n) {
    int i;

    if (n == 0) {
        printf("\nTrenutno nema nijednog oglasa.\n");
        return;
    }

    for (i = 0; i < n; i++) {
        print_oglas(&oglasi[i], i);
    }
}

void poNazivu(const Oglas oglasi[], int n) {
    int i;
    int pogodaka = 0;
    char ime[MAX_IME];

    if (n == 0) {
        printf("\nNema oglasa za pretragu.\n");
        return;
    }

    printf("\nUnesite naziv kompanije: ");
    if (!read_line(ime, sizeof(ime)) || ime[0] == '\0') {
        printf("Unos je prazan.\n");
        return;
    }

    for (i = 0; i < n; i++) {
        if (equals_ignore_case(oglasi[i].ime, ime)) {
            print_oglas(&oglasi[i], i);
            pogodaka++;
        }
    }

    if (pogodaka == 0) {
        printf("\nNema oglasa za kompaniju \"%s\".\n", ime);
    }
}

void poIskustvu(const Oglas oglasi[], int n) {
    int i;
    int pogodaka = 0;
    char iskustvo[MAX_ISKUSTVO];

    if (n == 0) {
        printf("\nNema oglasa za pretragu.\n");
        return;
    }

    printf("\nUnesite trazeni nivo iskustva: ");
    if (!read_line(iskustvo, sizeof(iskustvo)) || iskustvo[0] == '\0') {
        printf("Unos je prazan.\n");
        return;
    }

    for (i = 0; i < n; i++) {
        if (equals_ignore_case(oglasi[i].iskustvo, iskustvo)) {
            print_oglas(&oglasi[i], i);
            pogodaka++;
        }
    }

    if (pogodaka == 0) {
        printf("\nNema oglasa za iskustvo \"%s\".\n", iskustvo);
    }
}

void vecaPlata(const Oglas oglasi[], int n) {
    int i;
    int prag;
    int pogodaka = 0;

    if (n == 0) {
        printf("\nNema oglasa za pretragu.\n");
        return;
    }

    prag = read_int_in_range("\nUnesite minimalnu pocetnu platu: ", 0, 1000000000);

    for (i = 0; i < n; i++) {
        if (oglasi[i].pocetnaplata > prag) {
            print_oglas(&oglasi[i], i);
            pogodaka++;
        }
    }

    if (pogodaka == 0) {
        printf("\nNema oglasa sa platom vecom od %d.\n", prag);
    }
}

void vecaCRada(const Oglas oglasi[], int n) {
    int i;
    int prag;
    int pogodaka = 0;

    if (n == 0) {
        printf("\nNema oglasa za pretragu.\n");
        return;
    }

    prag = read_int_in_range("\nUnesite minimalno nedeljno radno vreme: ", 1, 168);

    for (i = 0; i < n; i++) {
        if (oglasi[i].radnovreme > prag) {
            print_oglas(&oglasi[i], i);
            pogodaka++;
        }
    }

    if (pogodaka == 0) {
        printf("\nNema oglasa sa radnim vremenom vecim od %d sati.\n", prag);
    }
}

void save(const Oglas oglasi[], int n) {
    int i;
    FILE *fajl = fopen("oglasi.txt", "w");

    if (fajl == NULL) {
        perror("Neuspesno otvaranje oglasi.txt za upis");
        return;
    }

    for (i = 0; i < n; i++) {
        fprintf(fajl, "%s\n", oglasi[i].ime);
        fprintf(fajl, "%s\n", oglasi[i].pozicija);
        fprintf(fajl, "%s\n", oglasi[i].iskustvo);
        fprintf(fajl, "%s\n", oglasi[i].vrstaangazmana);
        fprintf(fajl, "%d\n", oglasi[i].pocetnaplata);
        fprintf(fajl, "%d\n", oglasi[i].radnovreme);
    }

    fclose(fajl);
    printf("\nUspesno sacuvano (%d oglasa).\n", n);
}

void load(Oglas oglasi[], int *n) {
    int i = 0;
    char linija[64];
    FILE *fajl = fopen("oglasi.txt", "r");

    if (fajl == NULL) {
        *n = 0;
        printf("\nFajl oglasi.txt ne postoji. Nastavlja se sa praznom listom.\n");
        return;
    }

    while (i < MAX_OGLASA && fgets(oglasi[i].ime, sizeof(oglasi[i].ime), fajl) != NULL) {
        trim_newline(oglasi[i].ime);

        if (fgets(oglasi[i].pozicija, sizeof(oglasi[i].pozicija), fajl) == NULL ||
            fgets(oglasi[i].iskustvo, sizeof(oglasi[i].iskustvo), fajl) == NULL ||
            fgets(oglasi[i].vrstaangazmana, sizeof(oglasi[i].vrstaangazmana), fajl) == NULL ||
            fgets(linija, sizeof(linija), fajl) == NULL) {
            printf("\nDetektovan nepotpun zapis u fajlu. Prekid ucitavanja.\n");
            break;
        }
        trim_newline(oglasi[i].pozicija);
        trim_newline(oglasi[i].iskustvo);
        trim_newline(oglasi[i].vrstaangazmana);
        oglasi[i].pocetnaplata = (int)strtol(linija, NULL, 10);

        if (fgets(linija, sizeof(linija), fajl) == NULL) {
            printf("\nDetektovan nepotpun zapis u fajlu. Prekid ucitavanja.\n");
            break;
        }
        oglasi[i].radnovreme = (int)strtol(linija, NULL, 10);

        i++;
    }

    *n = i;
    fclose(fajl);
    printf("\nUspesno ucitano %d oglasa.\n", *n);
}
