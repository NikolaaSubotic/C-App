#include <stdio.h>

#include "header.h"

int main(void) {
    Oglas oglasi[MAX_OGLASA];
    int n = 0;

    load(oglasi, &n);

    while (1) {
        switch (Meni()) {
            case 0:
                printf("\nIzlaz iz programa.\n");
                return 0;
            case 1:
                load(oglasi, &n);
                break;
            case 2:
                save(oglasi, n);
                break;
            case 3:
                add(oglasi, &n);
                break;
            case 4:
                all(oglasi, n);
                break;
            case 5:
                poNazivu(oglasi, n);
                break;
            case 6:
                poIskustvu(oglasi, n);
                break;
            case 7:
                vecaPlata(oglasi, n);
                break;
            case 8:
                vecaCRada(oglasi, n);
                break;
            default:
                printf("\nNepoznata opcija.\n");
                break;
        }
    }
}
