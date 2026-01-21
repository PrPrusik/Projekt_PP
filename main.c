#include <stdio.h>
#include <stdlib.h>
#include "zmienne.h"
#include "funkcje.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Blad: Nie podano nazwy pliku bazy!\n");
        printf("Uzycie: %s <nazwa_pliku>\n", argv[0]);
        return 1;
    }

    char *sciezka_pliku = argv[1];
    int opcja;
    int liczba_stworzen = 0;
    mistyczne_stworzenie *tab = NULL;

    do {
        printf("\n--- REZERWAT MAGOW: %s ---\n", sciezka_pliku);
        printf("1. Zarejestruj nowe stworzenie\n");
        printf("2. Wyszukaj (tekst + liczba)\n");
        printf("3. Zmodyfikuj dane\n");
        printf("4. Sortuj (tekstowo/liczbowo)\n");
        printf("5. Usun (pojedynczo/masowo)\n");
        printf("6. Zapisz dane do pliku\n");
        printf("7. Odczytaj dane z pliku\n");
        printf("8. Wyswietl wszystko\n");
        printf("0. Wyjdz\n");
        printf("Wybor: ");
        
        if (scanf("%d", &opcja) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        switch (opcja) {
            case 1: 
                dodaj(&tab, &liczba_stworzen); 
                break;
            case 2: 
                wyszukaj(tab, liczba_stworzen); 
                break;
            case 3: 
                modyfikuj(tab, liczba_stworzen); 
                break;
            case 4:
                printf("\n1. Alfabetycznie\n2. Liczbowo\nWybor: ");
                int s_opc; scanf("%d", &s_opc);
                if (s_opc == 1) sortuj_tekst(tab, liczba_stworzen);
                else if (s_opc == 2) sortuj_liczby(tab, liczba_stworzen);
                break;
            case 5:
                printf("\n1. Pojedyncze\n2. Masowe\nWybor: ");
                int u_opc; scanf("%d", &u_opc);
                if (u_opc == 1) usun_pojedyncze(tab, &liczba_stworzen);
                else if (u_opc == 2) usun_masowe(tab, &liczba_stworzen);
                break;
            case 6:
                zapisz(sciezka_pliku, tab, liczba_stworzen);
                break;
            case 7:
                wczytaj(sciezka_pliku, &tab, &liczba_stworzen);
                break;
            case 8:
                wyswietl(tab, liczba_stworzen);
                break;
            case 0:
                printf("Zamykanie systemu...\n");
                break;
        }
    } while (opcja != 0);

    free(tab);
    return 0;
}