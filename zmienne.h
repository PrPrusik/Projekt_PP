#ifndef ZMIENNE_H
#define ZMIENNE_H

#define MAX_ZN 101

typedef struct
{
    int dzien;
    int miesiac;
    int rok;
} data;

typedef enum
{
    STABILNY,
    NIESPOKOJNY,
    AGRESYWNY,
    NIEBEZPIECZNY,
    W_KWARANTANNIE
} stan;

typedef struct
{
    char nazwa[MAX_ZN];
    char gatunek[MAX_ZN];
    int poziom_mocy;
    int poziom_niebezpieczenstwa;
    data data_karmienia;
    stan status_stworzenia;
} mistyczne_stworzenie;

#endif
