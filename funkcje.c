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

void dodaj_stworzenie(mistyczne_stworzenie** head) {
    mistyczne_stworzenie* nowy = (mistyczne_stworzenie*)malloc(sizeof(mistyczne_stworzenie));
    if (nowy == NULL) {
        printf("Blad alokacji pamieci!\n");
        return;
    }
    wpisz_stworzenie(nowy);
    nowy->next = NULL;

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
        printf("Status stworzenia: %s\n", stan_to_string(temp->status_stworzenia));
        printf("--------------------------\n");
        temp = temp->next;
    }
}

void wyszukaj_stworzenie(const mistyczne_stworzenie* head) {
    if (head == NULL) {
        printf("Brak stworzen w bazie.\n");
        return;
    }

    char szukany_tekst[MAX_ZN];
    int szukana_liczba;
    stan szukany_status;

    printf("Wybierz kryterium wyszukiwania (tekstowo):\n");
    printf("1. Nazwa\n2. Gatunek\n");
    int wybor_tekstowy = pobierz_liczbe("Wpisz numer opcji (1-2): ");
    do {
        if (wybor_tekstowy < 1 || wybor_tekstowy > 2) {
            printf("Niepoprawna opcja. Prosze podac liczbe z zakresu 1-2.\n");
            wybor_tekstowy = pobierz_liczbe("Wpisz numer opcji (1-2): ");
        }
    } while (wybor_tekstowy < 1 || wybor_tekstowy > 2);
    if (wybor_tekstowy == 1){
        wczyt_nazwe(szukany_tekst, "Podaj nazwe stworzenia do wyszukania: ");
    }
    else if (wybor_tekstowy == 2){
        wczyt_gatunek(szukany_tekst, "Podaj gatunek stworzenia do wyszukania: ");
    }
    printf("wybierz kryterium wyszukiwania (liczbowo):\n");
    printf("1. Poziom mocy\n2. Poziom niebezpieczenstwa\n3. Status\n");
    int wybor_liczbowy = pobierz_liczbe("Wpisz numer opcji (1-3): ");
    do {
        if (wybor_liczbowy < 1 || wybor_liczbowy > 3) {
            printf("Niepoprawna opcja. Prosze podac liczbe z zakresu 1-3.\n");
            wybor_liczbowy = pobierz_liczbe("Wpisz numer opcji (1-3): ");
        }
    } while (wybor_liczbowy < 1 || wybor_liczbowy > 3);

    if (wybor_liczbowy == 1){
        szukana_liczba = pobierz_liczbe("Podaj poziom mocy stworzenia do wyszukania: ");
    }
    else if (wybor_liczbowy == 2){
        szukana_liczba = pobierz_liczbe("Podaj poziom niebezpieczenstwa stworzenia do wyszukania: ");
    }
    else if (wybor_liczbowy == 3){
        wczyt_status(&szukany_status);
    }

    int znaleziono = 0;
    const mistyczne_stworzenie* temp = head;

    printf("\n--- Wyniki wyszukiwania ---\n");
    while (temp != NULL) {
        int match = 0;

        if (wybor_tekstowy == 1 && strncmp(temp->nazwa, szukany_tekst, strlen(szukany_tekst)) == 0) {
            match = 1;
        } else if (wybor_tekstowy == 2 && strncmp(temp->gatunek, szukany_tekst, strlen(szukany_tekst)) == 0) {
            match = 1;
        }
        if (match) {
            if (wybor_liczbowy == 1 && temp->poziom_mocy == szukana_liczba) {
                match = 1;
            } else if (wybor_liczbowy == 2 && temp->poziom_niebezpieczenstwa == szukana_liczba) {
                match = 1;
            } else if (wybor_liczbowy == 3 && temp->status_stworzenia == szukany_status) {
                match = 1;
            } else {
                match = 0;
            }
        }
        if (match) {
            printf("Nazwa: %s\n", temp->nazwa);
            printf("Gatunek: %s\n", temp->gatunek);
            printf("Poziom mocy: %d\n", temp->poziom_mocy);
            printf("Poziom niebezpieczenstwa: %d\n", temp->poziom_niebezpieczenstwa);
            printf("Data karmienia: %02d-%02d-%04d\n", temp->data_karmienia.dzien, temp->data_karmienia.miesiac, temp->data_karmienia.rok);
            printf("Status stworzenia: %s\n", stan_to_string(temp->status_stworzenia));
            printf("--------------------------\n");
            znaleziono++;
        }
        temp = temp->next;
    }

    if (znaleziono == 0) {
        printf("Nie znaleziono stworzen spelniajacych kryteria.\n");
    } else {
        printf("Znaleziono: %d.\n", znaleziono);
    }
}

void modyfikuj_stworzenie(mistyczne_stworzenie* head){
    if (head == NULL) {
        printf("Brak stworzen w bazie.\n");
        return;
    }
    mistyczne_stworzenie* temp = head;
    char buffer[MAX_ZN];

    printf("Podaj nazwe stworzenia ktore chcesz modyfikowac: ");
    do {
        wczyt_nazwe(buffer, "");
    } while (!czy_tekst(buffer));
    while (temp != NULL && strcmp(temp->nazwa, buffer) != 0) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Nie znaleziono stworzenia o podanej nazwie.\n");
        return;
    }
    printf("Modyfikowanie stworzenia: %s\n", temp->nazwa);
    printf("Wybierz pole do modyfikacji (nazwa nie moze byc modyfikowana):\n");
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
            break;
        }
    } while (wybor != 0);
    printf("Stworzenie zmodyfikowane pomyslnie.\n");
}

void usun_stworzenie(mistyczne_stworzenie** head) {
    if (*head == NULL) {
        printf("Brak stworzen w bazie.\n");
        return;
    }
    printf("Podaj po czym mam usunac stworzenie?\n");
    printf("1. Nazwa\n");
    printf("2. Gatunek\n");
    printf("3. Poziom mocy\n");
    printf("4. Poziom niebezpieczenstwa\n");
    printf("5. Data karmienia\n");
    printf("6. Status stworzenia\n");

    int wybor = pobierz_liczbe("Wpisz numer opcji (1-6): ");

    char nazwa[MAX_ZN];
    int szukana_wartosc;
    stan szukany_status;
    data szukana_data;

    switch (wybor) {
        case 1:
            wczyt_nazwe(nazwa, "Podaj nazwe stworzenia do usuniecia: ");
            break;
        case 2:
            wczyt_gatunek(nazwa, "Podaj gatunek stworzenia do usuniecia: ");
            break;
        case 3:
            szukana_wartosc = pobierz_liczbe("Podaj poziom mocy stworzenia do usuniecia: ");
            break;
        case 4:
            szukana_wartosc = pobierz_liczbe("Podaj poziom niebezpieczenstwa stworzenia do usuniecia: ");
            break;
        case 5:
            wczyt_date(&szukana_data);
            break;
        case 6:
            wczyt_status(&szukany_status);
            break;
        default:
            printf("Niepoprawna opcja.\n");
            break;;
        }
    mistyczne_stworzenie* current = *head;
    mistyczne_stworzenie* previous = NULL;
    int znaleziono = 0;
     while (current != NULL) {
        int do_usuniecia = 0;
        if (wybor == 1 && strcmp(current->nazwa, nazwa) == 0) {
            do_usuniecia = 1;
        } else if (wybor == 2 && strcmp(current->gatunek, nazwa) == 0) {
            do_usuniecia = 1;
        } else if (wybor == 3 && current->poziom_mocy == szukana_wartosc) {
            do_usuniecia = 1;
        } else if (wybor == 4 && current->poziom_niebezpieczenstwa == szukana_wartosc) {
            do_usuniecia = 1;
        } else if (wybor == 5 && current->data_karmienia.dzien == szukana_data.dzien &&
                   current->data_karmienia.miesiac == szukana_data.miesiac &&
                   current->data_karmienia.rok == szukana_data.rok) {
            do_usuniecia = 1;
        } else if (wybor == 6 && current->status_stworzenia == szukany_status) {
            do_usuniecia = 1;
        }

        if (do_usuniecia && current->status_stworzenia == NIEBEZPIECZNY) {
            printf("Nie mozna usunac stworzenia o statusie NIEBEZPIECZNY.\n");
            previous = current;
            current = current->next;
            continue;
        }
        if (do_usuniecia) {
            mistyczne_stworzenie* temp = current;
            printf("Usunieto stworzenie: %s\n", current->nazwa);
            if (previous == NULL) {
                *head = current->next;
                current = *head;
            } else {
                previous->next = current->next;
                current = previous->next;
            }
            free(temp);
            znaleziono++;
        }
        previous = current;
        current = current->next;
    }
    printf("Liczba usunietych stworzen: %d\n", znaleziono);
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
    int zapisano = 0;
    if (file == NULL) {
        printf("Nie mozna otworzyc pliku do zapisu.\n");
        return;
    }
    const mistyczne_stworzenie* temp = head;
    while (temp != NULL) {
        fwrite(&temp->nazwa, sizeof(char), MAX_ZN, file);
        fwrite(&temp->gatunek, sizeof(char), MAX_ZN, file);
        fwrite(&temp->poziom_mocy, sizeof(int), 1, file);
        fwrite(&temp->poziom_niebezpieczenstwa, sizeof(int), 1, file);
        fwrite(&temp->data_karmienia, sizeof(data), 1, file);
        fwrite(&temp->status_stworzenia, sizeof(stan), 1, file);
        temp = temp->next;
        zapisano++;
    }
    fclose(file);
    printf("Dane zapisane do pliku: %s\n", nazwa_pliku);
    if (zapisano == 0) {
        printf("Brak danych do zapisania w pliku.\n");
    } else {
        printf("Liczba zapisanych stworzen: %d\n", zapisano);
    }
}

void wczytaj_z_pliku(mistyczne_stworzenie** head, const char* nazwa_pliku) {
    FILE* file = fopen(nazwa_pliku, "rb");
    if (file == NULL) {
        printf("Nie mozna otworzyc pliku do odczytu.\n");
        return;
    }

    zwolnij_pamiec(head);
    int wczytano = 0;

    while (1) {
        mistyczne_stworzenie* nowe_stworzenie = (mistyczne_stworzenie*)malloc(sizeof(mistyczne_stworzenie));
        if (nowe_stworzenie == NULL) {
            printf("Blad alokacji pamieci podczas wczytywania z pliku.\n");
            break;
        }
        if (fread(nowe_stworzenie->nazwa, sizeof(char), MAX_ZN, file) != MAX_ZN) {
            free(nowe_stworzenie);
            break;
        }

        fread(nowe_stworzenie->gatunek, sizeof(char), MAX_ZN, file);
        fread(&nowe_stworzenie->poziom_mocy, sizeof(int), 1, file);
        fread(&nowe_stworzenie->poziom_niebezpieczenstwa, sizeof(int), 1, file);
        fread(&nowe_stworzenie->data_karmienia, sizeof(data), 1, file);
        fread(&nowe_stworzenie->status_stworzenia, sizeof(stan), 1, file);
        nowe_stworzenie->next = NULL;

        if (*head == NULL) {
            *head = nowe_stworzenie;
        } else {
            mistyczne_stworzenie* temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = nowe_stworzenie;
        }
        wczytano++;
    }
    fclose(file);
    printf("Dane wczytane z pliku: %s\n", nazwa_pliku);
    if (wczytano == 0) {
        printf("Brak danych do wczytania w pliku.\n");
    } else {
        printf("Liczba wczytanych stworzen: %d\n", wczytano);
    }
}

void sortuj_tekstowo(mistyczne_stworzenie** head, int wybor) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }
    
    mistyczne_stworzenie* a;
    mistyczne_stworzenie* b;

    podziel_liste(*head, &a, &b);
    sortuj_tekstowo(&a, wybor);
    sortuj_tekstowo(&b, wybor);

    *head = scalaj_tekstowo(a, b, wybor);
}

void sortuj_liczbowo(mistyczne_stworzenie** head, int wybor) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    mistyczne_stworzenie* a;
    mistyczne_stworzenie* b;

    podziel_liste(*head, &a, &b);
    sortuj_liczbowo(&a, wybor);
    sortuj_liczbowo(&b, wybor);

    *head = scalaj_liczbowo(a, b, wybor);
}