#include <stdio.h>
#include <stdlib.h>

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
        clear_buffer();
        switch (wybor)
        {
        case 1:
            dodaj_stworzenie(&head, (mistyczne_stworzenie){0});
            break;
        case 2:
            wyswietl_stworzenia(head);
            break;
        case 3:
            {
                char nazwa[MAX_ZN];
                printf("Podaj nazwe stworzenia do wyszukania: ");
                fgets(nazwa, MAX_ZN, stdin);
                nazwa[strcspn(nazwa, "\n")] = 0;
                wyszukaj_stworzenie(head, nazwa);
            }
            break;
        case 4:
            {
                char nazwa[MAX_ZN];
                printf("Podaj nazwe stworzenia do modyfikacji: ");
                fgets(nazwa, MAX_ZN, stdin);
                nazwa[strcspn(nazwa, "\n")] = 0;
                modyfikuj_stworzenie(head, nazwa);
            }
            break;
        case 5:
            {
                char nazwa[MAX_ZN];
                printf("Podaj nazwe stworzenia do usuniecia: ");
                fgets(nazwa, MAX_ZN, stdin);
                nazwa[strcspn(nazwa, "\n")] = 0;
                usun_stworzenie(&head, nazwa);
            }
            break;
        case 6:
            {
                int wybor_sortowania;
                printf("Wybierz typ sortowania:\n");
                printf("1. Tekstowy\n");
                printf("2. Liczbowy\n");
                wybor_sortowania = pobierz_liczbe("Wpisz numer opcji (1-2): ");
                clear_buffer();
                
                if (wybor_sortowania == 1) {
                    sortuj_tekstowo(&head);
                    break;
                } else if (wybor_sortowania == 2) {
                    sortuj_licbowo(&head);
                    break;
                } else {
                    printf("Niepoprawna opcja.\n");
                    break;
                }
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