#ifndef FUNKCJE_H
#define FUNKCJE_H

#include "zmienne.h"

void dodaj(mistyczne_stworzenie **tab, int *n);

void wyszukaj(mistyczne_stworzenie *tab, int n);

void modyfikuj(mistyczne_stworzenie *tab, int n);

void usun_pojedyncze(mistyczne_stworzenie *tab, int *n);

void usun_masowe(mistyczne_stworzenie *tab, int *n);

void sortuj_tekst(mistyczne_stworzenie *tab, int n);

void sortuj_liczby(mistyczne_stworzenie *tab, int n);

void zapisz(const char *plik, mistyczne_stworzenie *tab, int n);

void wczytaj(const char *plik, mistyczne_stworzenie **tab, int *n);

static void clear_buffer();

void wyswietl(mistyczne_stworzenie *tab, int n);

int czy_tekst(const char *tekst);

int pobierz_liczbe(const char *komunikat);
#endif
