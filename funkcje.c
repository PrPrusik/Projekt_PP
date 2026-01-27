#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funkcje_p.h"
#include "funkcje.h"

void wpisz_stworzenie(mistyczne_stworzenie* nowe_stworzenie) {
    char buffer[MAX_ZN];

    wczyt_nazwe(nowe_stworzenie->nazwa, "Podaj nazwe stworzenia: ");

    wczyt_gatunek(nowe_stworzenie->gatunek, "Podaj gatunek stworzenia: ");

    wczyt_poziom_m(&nowe_stworzenie->poziom_mocy, "Podaj poziom mocy (1-999): ");

    wczyt_poziom_n(&nowe_stworzenie->poziom_niebezpieczenstwa, "Podaj poziom niebezpieczenstwa (1-10): ");

    wczyt_date(&nowe_stworzenie->data_karmienia);

    wczyt_status(&nowe_stworzenie->status_stworzenia);

    nowe_stworzenie->next = NULL;
}

void dodaj_stworzenie(mistyczne_stworzenie** head, mistyczne_stworzenie nowe_stworzenie) {
    mistyczne_stworzenie* nowy = (mistyczne_stworzenie*)malloc(sizeof(mistyczne_stworzenie));
    if (nowy == NULL) {
        printf("Blad alokacji pamieci!\n");
        return;
    }
    wpisz_stworzenie(nowy);

    if (*head == NULL) {
        *head = nowy;
    } else {
        mistyczne_stworzenie* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nowy;
    }
    printf("Stworzenie dodane pomyslnie.\n");
}

void wyswietl_stworzenia(const mistyczne_stworzenie* head) {
    if (head == NULL) {
        printf("Brak stworzen do wyswietlenia.\n");
        return;
    }
    const mistyczne_stworzenie* temp = head;
    while (temp != NULL) {
        printf("Nazwa: %s\n", temp->nazwa);
        printf("Gatunek: %s\n", temp->gatunek);
        printf("Poziom mocy: %d\n", temp->poziom_mocy);
        printf("Poziom niebezpieczenstwa: %d\n", temp->poziom_niebezpieczenstwa);
        printf("Data karmienia: %02d-%02d-%04d\n", temp->data_karmienia.dzien, temp->data_karmienia.miesiac, temp->data_karmienia.rok);
        printf("Status stworzenia: %d\n", temp->status_stworzenia);
        printf("--------------------------\n");
        temp = temp->next;
    }
}

void wyszukaj_stworzenie(const mistyczne_stworzenie* head, const char* nazwa) {
    if (head == NULL) {
        printf("Brak stworzen w bazie.\n");
        return;
    }
    const mistyczne_stworzenie* temp = head;
    
    printf("Po czym mam szukac stworzenia(tekstowo)? (1-Nazwa, 2-Gatunek): ");
    int wybor;
    do {
        wybor = pobierz_liczbe("Wpisz numer opcji (1-2): ");
        if (wybor < 1 || wybor > 2) {
            printf("Niepoprawna opcja. Prosze podac liczbe z zakresu 1-2.\n");
        }
    } while (wybor < 1 || wybor > 2);
    clear_buffer();

    printf("Po czym mam szukac stworzenia(liczbowo)? (1-Poziom mocy, 2-Poziom niebezpieczenstwa): ");
    int wybor_liczbowy;
    do {
        wybor_liczbowy = pobierz_liczbe("Wpisz numer opcji (1-2): ");
        if (wybor_liczbowy < 1 || wybor_liczbowy > 2) {
            printf("Niepoprawna opcja. Prosze podac liczbe z zakresu 1-2.\n");
        }
    } while (wybor_liczbowy < 1 || wybor_liczbowy > 2);
    clear_buffer();

    int znaleziono = 0;
    while (temp != NULL) {
        int tekst_match = 0;
        int liczbowy_match = 0;

        if (wybor == 1 && strcmp(temp->nazwa, nazwa) == 0) {
            tekst_match = 1;
        } else if (wybor == 2 && strcmp(temp->gatunek, nazwa) == 0) {
            tekst_match = 1;
        }

        if (wybor_liczbowy == 1 && temp->poziom_mocy == atoi(nazwa)) {
            liczbowy_match = 1;
        } else if (wybor_liczbowy == 2 && temp->poziom_niebezpieczenstwa == atoi(nazwa)) {
            liczbowy_match = 1;
        }

        if (tekst_match || liczbowy_match) {
            printf("Znaleziono stworzenie:\n");
            printf("Nazwa: %s\n", temp->nazwa);
            printf("Gatunek: %s\n", temp->gatunek);
            printf("Poziom mocy: %d\n", temp->poziom_mocy);
            printf("Poziom niebezpieczenstwa: %d\n", temp->poziom_niebezpieczenstwa);
            printf("Data karmienia: %02d-%02d-%04d\n", temp->data_karmienia.dzien, temp->data_karmienia.miesiac, temp->data_karmienia.rok);
            printf("Status stworzenia: %d\n", temp->status_stworzenia);
            printf("--------------------------\n");
            znaleziono++;
        }
        temp = temp->next;
    }
    if (znaleziono == 0) {
        printf("Nie znaleziono stworzenia o podanych kryteriach.\n");
    }
    printf("Liczba znalezionych stworzen: %d\n", znaleziono);
}

void modyfikuj_stworzenie(mistyczne_stworzenie* head, const char* nazwa){
    if (head == NULL) {
        printf("Brak stworzen w bazie.\n");
        return;
    }
    mistyczne_stworzenie* temp = head;

    char buffer[MAX_ZN];

    printf("Podaj nazwe stworzenia ktore chcesz modyfikowac: ");
    do {
        fgets(buffer, MAX_ZN, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if (!czy_tekst(buffer)) {
            printf("Niepoprawna nazwa. Prosze uzyc tylko liter i spacji.\n");
        } 
    } while (!czy_tekst(buffer));
    clear_buffer();
    if (strcmp(temp->nazwa, buffer) != 0) {
        printf("Nie znaleziono stworzenia o podanej nazwie.\n");
        return;
    }
    printf("Modyfikowanie stworzenia: %s\n", temp->nazwa);
    printf("Wybierz pole do modyfikacji (nazwa nie może być modyfikowana):\n");
    printf("1. Gatunek\n");
    printf("2. Poziom mocy\n");
    printf("3. Poziom niebezpieczenstwa\n");
    printf("4. Data karmienia\n");
    printf("5. Status stworzenia\n");
    printf("0. Zakoncz modyfikacje\n");
    int wybor;
    do {
        do {
            wybor = pobierz_liczbe("Wpisz numer opcji (1-5): ");
            if (wybor < 0 || wybor > 5) {
                printf("Niepoprawna opcja. Prosze podac liczbe z zakresu 1-5.\n");
            }
        } while (wybor < 0 || wybor > 5);
        clear_buffer();
        switch (wybor)
        {
        case 1:
            wczyt_gatunek(temp->gatunek, "Podaj nowy gatunek stworzenia: ");
            break;
        case 2:
            wczyt_poziom_m(&temp->poziom_mocy, "Podaj nowy poziom mocy (1-999): ");
            break;
        case 3:
            wczyt_poziom_n(&temp->poziom_niebezpieczenstwa, "Podaj nowy poziom niebezpieczenstwa (1-10): ");
            break;
        case 4:
            wczyt_date(&temp->data_karmienia);
            break;
        case 5:
            wczyt_status(&temp->status_stworzenia);
            break;
        case 0:
            printf("Modyfikacja zakonczona.\n");
            return;
        default:
            printf("Niepoprawna opcja.\n");
            return;
        }
    } while (wybor != 0);
    printf("Stworzenie zmodyfikowane pomyslnie.\n");
}

void usun_stworzenie(mistyczne_stworzenie** head, const char* nazwa) {
    if (*head == NULL) {
        printf("Brak stworzen w bazie.\n");
        return;
    }
    printf("Podaj po czym mam usunac stworzenie?");
    printf("1. Nazwa\n");
    printf("2. Gatunek\n");
    printf("3. Poziom mocy\n");
    printf("4. Poziom niebezpieczenstwa\n");
    printf("5. Data karmienia\n");
    printf("6. Status stworzenia\n");
    int wybor = pobierz_liczbe("Wpisz numer opcji (1-6): ");
    clear_buffer();
    mistyczne_stworzenie* temp = *head;;
    mistyczne_stworzenie* prev = NULL;
    int znaleziono = 0;
    while (temp != NULL) {
        int do_usuniecia = 0;
        switch (wybor) {
            case 1:
                if (strcmp(temp->nazwa, nazwa) == 0) {
                    do_usuniecia = 1;
                }
                break;
            case 2:
                if (strcmp(temp->gatunek, nazwa) == 0) {
                    do_usuniecia = 1;
                }
                break;
            case 3:
                if (temp->poziom_mocy == atoi(nazwa)) {
                    do_usuniecia = 1;
                }
                break;
            case 4:
                if (temp->poziom_niebezpieczenstwa == atoi(nazwa)) {
                    do_usuniecia = 1;
                }
                break;
            case 5:
                {
                    char data_str[11];
                    snprintf(data_str, sizeof(data_str), "%02d-%02d-%04d", temp->data_karmienia.dzien, temp->data_karmienia.miesiac, temp->data_karmienia.rok);
                    if (strcmp(data_str, nazwa) == 0) {
                        do_usuniecia = 1;
                    }
                }
                break;
            case 6:
                if (temp->status_stworzenia == (stan)atoi(nazwa)) {
                    do_usuniecia = 1;
                }
                break;
            default:
                printf("Niepoprawna opcja.\n");
                return;
        }

        if (temp->status_stworzenia == NIEBEZPIECZNY) {
            printf("Nie mozna usunac niebezpiecznego stworzenia: %s\n", temp->nazwa);
            do_usuniecia = 0;
        }
        if (do_usuniecia) {
            znaleziono++;
            if (prev == NULL) {
                *head = temp->next;
            } else {
                prev->next = temp->next;
            }
            mistyczne_stworzenie* to_delete = temp;
            temp = temp->next;
            free(to_delete);
        } else {
            prev = temp;
            temp = temp->next;
        }
        printf("Liczba usunietych stworzen: %d\n", znaleziono);
    }
    if (znaleziono == 0) {
        printf("Nie znaleziono stworzenia o podanych kryteriach do usuniecia.\n");
    }
}

void zwolnij_pamiec(mistyczne_stworzenie** head) {
    mistyczne_stworzenie* temp = *head;
    while (temp != NULL) {
        mistyczne_stworzenie* to_delete = temp;
        temp = temp->next;
        free(to_delete);
    }
    *head = NULL;
}

void zapisz_do_pliku(const mistyczne_stworzenie* head, const char* nazwa_pliku) {
    FILE* file = fopen(nazwa_pliku, "wb");
    if (file == NULL) {
        printf("Nie mozna otworzyc pliku do zapisu.\n");
        return;
    }
    const mistyczne_stworzenie* temp = head;
    while (temp != NULL) {
        fwrite(temp, sizeof(mistyczne_stworzenie), 1, file);
        temp = temp->next;
    }
    fclose(file);
    printf("Dane zapisane do pliku: %s\n", nazwa_pliku);
}

void wczytaj_z_pliku(mistyczne_stworzenie** head, const char* nazwa_pliku) {
    FILE* file = fopen(nazwa_pliku, "rb");
    if (file == NULL) {
        printf("Nie mozna otworzyc pliku do odczytu.\n");
        return;
    }
    zwolnij_pamiec(head);
    mistyczne_stworzenie temp;
    while (fread(&temp, sizeof(mistyczne_stworzenie), 1, file) == 1) {
        dodaj_stworzenie(head, temp);
    }
    fclose(file);
    printf("Dane wczytane z pliku: %s\n", nazwa_pliku);
}

void sortuj_tekstowo(mistyczne_stworzenie** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }
    printf("Wybierz pole do sortowania tekstowego:\n");
    printf("1. Nazwa\n");
    printf("2. Gatunek\n");
    int wybor;
    do {
        wybor = pobierz_liczbe("Wpisz numer opcji (1-2): ");
        if (wybor < 1 || wybor > 2) {
            printf("Niepoprawna opcja. Prosze podac liczbe z zakresu 1-2.\n");
        }
    } while (wybor < 1 || wybor > 2);
    clear_buffer();
    int swapped;
    do {
        swapped = 0;
        mistyczne_stworzenie* ptr1 = *head;
        mistyczne_stworzenie* lptr = NULL;

        while (ptr1->next != lptr) {
            int cmp = 0;
            if (wybor == 1) {
                cmp = strcmp(ptr1->nazwa, ptr1->next->nazwa);
            } else if (wybor == 2) {
                cmp = strcmp(ptr1->gatunek, ptr1->next->gatunek);
            }
            if (cmp > 0) {
                mistyczne_stworzenie temp = *ptr1;
                *ptr1 = *(ptr1->next);
                *(ptr1->next) = temp;

                mistyczne_stworzenie* next_next = ptr1->next->next;
                ptr1->next->next = ptr1;
                ptr1->next = next_next;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    printf("Stworzenia posortowane tekstowo.\n");
}

void sortuj_licbowo(mistyczne_stworzenie** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }
    printf("Wybierz pole do sortowania liczbowego:\n");
    printf("1. Poziom mocy\n");
    printf("2. Poziom niebezpieczenstwa\n");
    int wybor;
    do {
        wybor = pobierz_liczbe("Wpisz numer opcji (1-2): ");
        if (wybor < 1 || wybor > 2) {
            printf("Niepoprawna opcja. Prosze podac liczbe z zakresu 1-2.\n");
        }
    } while (wybor < 1 || wybor > 2);
    clear_buffer();
    int swapped;
    do {
        swapped = 0;
        mistyczne_stworzenie* ptr1 = *head;
        mistyczne_stworzenie* lptr = NULL;

        while (ptr1->next != lptr) {
            int cmp = 0;
            if (wybor == 1) {
                cmp = ptr1->poziom_mocy - ptr1->next->poziom_mocy;
            } else if (wybor == 2) {
                cmp = ptr1->poziom_niebezpieczenstwa - ptr1->next->poziom_niebezpieczenstwa;
            }
            if (cmp > 0) {
                mistyczne_stworzenie temp = *ptr1;
                *ptr1 = *(ptr1->next);
                *(ptr1->next) = temp;

                mistyczne_stworzenie* next_next = ptr1->next->next;
                ptr1->next->next = ptr1;
                ptr1->next = next_next;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    printf("Stworzenia posortowane liczbowo.\n");
}