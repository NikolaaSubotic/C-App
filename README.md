# C-App

Konzolna C aplikacija za upravljanje oglasima za posao.

## Build

```bash
gcc -std=c11 -Wall -Wextra -pedantic C/main.c C/source.c -o c-app
```

## Pokretanje

```bash
./c-app
```

Aplikacija cuva i ucitava podatke iz `oglasi.txt` fajla (u radnom direktorijumu).
