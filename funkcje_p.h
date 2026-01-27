#ifndef FUNKCJE_P_H
#define FUNKCJE_P_H

#include "zmienne.h"

static void clear_buffer();
int czy_tekst(const char* str);
int pobierz_liczbe(const char* str);
void wczyt_nazwe(char* nazwa, const char* prompt);
void wczyt_gatunek(char* gatunek, const char* prompt);
void wczyt_poziom_m(int* poziom, const char* prompt);
void wczyt_poziom_n(int* poziom, const char* prompt);
void wczyt_date(data* data_karmienia);
void wczyt_status(stan* status_stworzenia);


#endif