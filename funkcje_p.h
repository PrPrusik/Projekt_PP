#ifndef FUNKCJE_P_H
#define FUNKCJE_P_H

#include "zmienne.h"

void clear_buffer(void);
int czy_tekst(const char* str);
int pobierz_liczbe(const char* str);
void wczyt_nazwe(char* nazwa, const char* prompt);
void wczyt_gatunek(char* gatunek, const char* prompt);
void wczyt_poziom_m(int* poziom, const char* prompt);
void wczyt_poziom_n(int* poziom, const char* prompt);
void wczyt_date(data* data_karmienia);
void wczyt_status(stan* status_stworzenia);
const char* stan_to_string(stan status);
void podziel_liste(mistyczne_stworzenie* head, mistyczne_stworzenie** a, mistyczne_stworzenie** b);
mistyczne_stworzenie* scalaj_tekstowo(mistyczne_stworzenie* a, mistyczne_stworzenie* b, int pole);
mistyczne_stworzenie* scalaj_liczbowo(mistyczne_stworzenie* a, mistyczne_stworzenie* b, int pole);
#endif