#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funkcje.h"
#include "funkcje_p.h"
#include "zmienne.h"

int main(int argc, char* argv[]){
    if (argc < 2) {
        printf("Uzycie: %s <nazwa_pliku>\n", argv[0]);
        return 1;
    }
    const char* nazwa_pliku = argv[1];
    mistyczne_stworzenie* head = NULL;
    wczytaj_z_pliku(&head, nazwa_pliku);
    int wybor;
    
    printf("\n--- EWIDENCJA MISTYCZNYCH STWORZEN ---\n");
    do
    {
        printf("\nCo chcesz zrobic:\n");
        printf("1. Dodaj stworzenie\n");
        printf("2. Wyswietl wszystkie stworzenia\n");
        printf("3. Wyszukaj stworzenie\n");
        printf("4. Modyfikuj stworzenie\n");
        printf("5. Usun stworzenie\n");
        printf("6. Sortuj stworzenia\n");
        printf("7. Zapisz do pliku\n");
        printf("8. Wczytaj z pliku\n");
        printf("0. Wyjdz\n");
        wybor = pobierz_liczbe("Wpisz numer opcji: ");
        switch (wybor)
        {
        case 1:
            dodaj_stworzenie(&head);
            break;
        case 2:
            wyswietl_stworzenia(head);
            break;
        case 3:
            wyszukaj_stworzenie(head);
            break;
        case 4:
            modyfikuj_stworzenie(head);
            break;
        case 5:
            usun_stworzenie(&head);
            break;
        case 6:{
            int typ;
            int pole;
            printf("Wybierz typ sortowania:\n1. Tekstowo\n2. Liczbowo\n");
            typ = pobierz_liczbe("Wpisz numer opcji (1-2): ");
            do {
                if (typ < 1 || typ > 2) {
                    printf("Niepoprawna opcja. Prosze podac liczbe z zakresu 1-2.\n");
                    typ = pobierz_liczbe("Wpisz numer opcji (1-2): ");
                }
            } while (typ < 1 || typ > 2);
            if (typ == 1) {
                printf("Wybierz pole do sortowania tekstowo:\n1. Nazwa\n2. Gatunek\n");
                pole = pobierz_liczbe("Wpisz numer opcji (1-2): ");
                do {
                    if (pole < 1 || pole > 2) {
                        printf("Niepoprawna opcja. Prosze podac liczbe z zakresu 1-2.\n");
                        pole = pobierz_liczbe("Wpisz numer opcji (1-2): ");
                    }
                } while (pole < 1 || pole > 2);
                sortuj_tekstowo(&head, pole);
                wyswietl_stworzenia(head);
            } else if (typ == 2) {
                printf("Wybierz pole do sortowania liczbowo:\n1. Poziom mocy\n2. Poziom niebezpieczenstwa\n");
                pole = pobierz_liczbe("Wpisz numer opcji (1-2): ");
                do {
                    if (pole < 1 || pole > 2) {
                        printf("Niepoprawna opcja. Prosze podac liczbe z zakresu 1-2.\n");
                        pole = pobierz_liczbe("Wpisz numer opcji (1-2): ");
                    }
                } while (pole < 1 || pole > 2);
                sortuj_liczbowo(&head, pole);
                wyswietl_stworzenia(head);
            }
            break;
        }
        case 7:
            zapisz_do_pliku(head, nazwa_pliku);
            break;
        case 8:
            wczytaj_z_pliku(&head, nazwa_pliku);
            break;
        case 0:
            zapisz_do_pliku(head, nazwa_pliku);
            zwolnij_pamiec(&head);
            printf("Koniec programu.\n");
            break;
        default:
            printf("Niepoprawna opcja. Sprobuj ponownie.\n");
            break;
        }
    } while (wybor != 0);
    
}