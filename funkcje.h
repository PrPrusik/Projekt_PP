#ifndef FUNKCJE_H
#define FUNKCJE_H

#include "zmienne.h"

void dodaj_stworzenie(mistyczne_stworzenie** head);

void wpisz_stworzenie(mistyczne_stworzenie* nowe_stworzenie);

void wyswietl_stworzenia(const mistyczne_stworzenie* head);

void wyszukaj_stworzenie(const mistyczne_stworzenie* head);

void modyfikuj_stworzenie(mistyczne_stworzenie* head);

void usun_stworzenie(mistyczne_stworzenie** head);

void zwolnij_pamiec(mistyczne_stworzenie** head);

void sortuj_tekstowo(mistyczne_stworzenie** head, int pole);

void sortuj_liczbowo(mistyczne_stworzenie** head, int pole);

void zapisz_do_pliku(const mistyczne_stworzenie* head, const char* nazwa_pliku);

void wczytaj_z_pliku(mistyczne_stworzenie** head, const char* nazwa_pliku);

#endif