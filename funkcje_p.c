#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funkcje_p.h"

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int czy_tekst(const char* str) {
    if (str == NULL || strlen(str) == 0) {
        return 0;
    }
    for (size_t i = 0; i < strlen(str); i++) {
        if (!isalpha((unsigned char)str[i]) && str[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

int pobierz_liczbe(const char* str) {
    int liczba;
    while (1)
    {
       printf("%s", str);
       if (scanf("%d", &liczba) != 1) {
           printf("Niepoprawne dane. Prosze podac liczbe calkowita.\n");
           clear_buffer();
       } else {
           clear_buffer();
           return liczba;
       } 
    }
}

void wczyt_nazwe(char* nazwa, const char* prompt) {
    char buffer[MAX_ZN];
    do {
        printf("%s", prompt);
        fgets(buffer, MAX_ZN, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if (!czy_tekst(buffer)) {
            printf("Niepoprawna nazwa. Prosze uzyc tylko liter i spacji.\n");
        } 
    } while (!czy_tekst(buffer));
    strncpy(nazwa, buffer, MAX_ZN);
}

void wczyt_gatunek(char* gatunek, const char* prompt) {
    char buffer[MAX_ZN];
    do {
        printf("%s", prompt);
        fgets(buffer, MAX_ZN, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        if (!czy_tekst(buffer)) {
            printf("Niepoprawny gatunek. Prosze uzyc tylko liter i spacji.\n");
        } 
    } while (!czy_tekst(buffer));
    strncpy(gatunek, buffer, MAX_ZN);
}

void wczyt_poziom_m(int* poziom, const char* prompt) {
    do {
        *poziom = pobierz_liczbe(prompt);
        if (*poziom < 1 || *poziom > 999) {
            printf("Niepoprawny poziom mocy. Prosze podac liczbe z zakresu 1-999.\n");
        }
    } while (*poziom < 1 || *poziom > 999);
}

void wczyt_poziom_n(int* poziom, const char* prompt) {
    do {
        *poziom = pobierz_liczbe(prompt);
        if (*poziom <1 || *poziom >10) {
            printf("Niepoprawny poziom niebezpieczenstwa. Prosze podac liczbe z zakresu 1-10.\n");
        }
    } while (*poziom <1 || *poziom >10);
}

void wczyt_date(data* data_karmienia) {
    printf("Podaj date karmienia (dzien miesiac rok): \n");
    data_karmienia->dzien = pobierz_liczbe("Dzien: ");
    data_karmienia->miesiac = pobierz_liczbe("Miesiac: ");
    data_karmienia->rok = pobierz_liczbe("Rok: ");
}

void wczyt_status(stan* status_stworzenia) {
    int status;
    do {
        printf("Podaj status stworzenia (0-Stabilny, 1-Niespokojny, 2-Agresywny, 3-Niebezpieczny, 4-W Kwarantannie): \n");
        status = pobierz_liczbe("Wpisz numer statusu (0-4): ");
        if (status < 0 || status > 4) {
            printf("Niepoprawny status. Prosze podac liczbe z zakresu 0-4.\n");
        }
    } while (status < 0 || status > 4);
    *status_stworzenia = (stan)status;
}

const char* stan_to_string(stan status) {
    switch (status) {
        case STABILNY:
            return "Stabilny";
        case NIESPOKOJNY:
            return "Niespokojny";
        case AGRESYWNY:
            return "Agresywny";
        case NIEBEZPIECZNY:
            return "Niebezpieczny";
        case W_KWARANTANNIE:
            return "W Kwarantannie";
        default:
            return "Nieznany";
    }
}

void podziel_liste(mistyczne_stworzenie* head, mistyczne_stworzenie** a, mistyczne_stworzenie** b){
    mistyczne_stworzenie* slow = head;
    mistyczne_stworzenie* fast = head->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *a = head;
    *b = slow->next;
    slow->next = NULL;
}

mistyczne_stworzenie* scalaj_tekstowo(mistyczne_stworzenie* a, mistyczne_stworzenie* b, int pole){
    if (a == NULL) return b;
    if (b == NULL) return a;
    int cmp;
    if (pole == 1) {
        cmp = strcmp(a->nazwa, b->nazwa);
    } else {
        cmp = strcmp(a->gatunek, b->gatunek);
    }

    mistyczne_stworzenie* wynik;
    if (cmp <= 0) {
        wynik = a;
        wynik->next = scalaj_tekstowo(a->next, b, pole);
    } else {
        wynik = b;
        wynik->next = scalaj_tekstowo(a, b->next, pole);
    }
    return wynik;
}
mistyczne_stworzenie* scalaj_liczbowo(mistyczne_stworzenie* a, mistyczne_stworzenie* b, int pole){
    if (a == NULL) return b;
    if (b == NULL) return a;
    int cmp;
    if (pole == 1) {
        cmp = a->poziom_mocy - b->poziom_mocy;
    } else {
        cmp = a->poziom_niebezpieczenstwa - b->poziom_niebezpieczenstwa;
    }

    mistyczne_stworzenie* wynik;
    if (cmp <= 0) {
        wynik = a;
        wynik->next = scalaj_liczbowo(a->next, b, pole);
    } else {
        wynik = b;
        wynik->next = scalaj_liczbowo(a, b->next, pole);
    }
    return wynik;
}