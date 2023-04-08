#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main()
{
    Oglas oglas[100];
    int n = 0;
    load(oglas, &n);
    printf("\nUcitano %d oglasa.\n", n);

    while(1){
        int instrukcija = Meni();
        switch(instrukcija){
            case 0:
                return 0;
            case 1:
                load(oglas, &n);
                printf("\nUcitano %d oglasa.\n", n);
                break;
            case 2:
                save(oglas, n);
                break;
            case 3:
                add(oglas, &n);
                break;
            case 4:
                all(oglas, n);
                break;
            case 5:
                poNazivu(oglas, n);
                break;
            case 6:
                poIskustvu(oglas, n);
                break;
            case 7:
                vecaPlata(oglas, n);
                break;
            case 8:
                vecaCRada(oglas, n);
                break;

            default:
                printf("\nFunkcija nije podrzana!\n");
                break;
        }
    }
    return 0;
}

