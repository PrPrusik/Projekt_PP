#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funkcje.h"

static void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int czy_tekst(const char *tekst) {
    if (strlen(tekst) == 0) return 0;
    for (size_t i = 0; i < strlen(tekst); i++) {
        if (!isalpha((unsigned char)tekst[i]) && tekst[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

int pobierz_liczbe(const char *komunikat) {
    int liczba;
    while (1) {
        printf("%s", komunikat);
        if (scanf("%d", &liczba) == 1) {
            return liczba;
        }
        printf("Blad: To nie jest poprawna liczba!\n");
        clear_buffer();
    }
}

void dodaj(mistyczne_stworzenie **tab, int *n) {
    mistyczne_stworzenie *temp = realloc(*tab, (*n + 1) * sizeof(mistyczne_stworzenie));
    if (temp == NULL) {
        printf("Blad krytyczny: Brak pamieci!\n");
        return;
    }
    *tab = temp;
    mistyczne_stworzenie *m = &(*tab)[*n];

    clear_buffer();
    do {
        printf("Nazwa: ");
        if (fgets(m->nazwa, MAX_ZN, stdin)) {
            m->nazwa[strcspn(m->nazwa, "\n")] = 0;
            if (czy_tekst(m->nazwa)) break;
        }
        printf("Blad: Nazwa moze zawierac tylko litery!\n");
    } while (1);

    do {
        printf("Gatunek: ");
        if (fgets(m->gatunek, MAX_ZN, stdin)) {
            m->gatunek[strcspn(m->gatunek, "\n")] = 0;
            if (czy_tekst(m->gatunek)) break;
        }
        printf("Blad: Gatunek moze zawierac tylko litery!\n");
    } while (1);

    do {
        m->poziom_mocy = pobierz_liczbe("Poziom mocy (1-999): ");
        if (m->poziom_mocy >= 1 && m->poziom_mocy <= 999)
            break;
        printf("Blad: Poziom mocy musi byc w zakresie 1–999!\n");
    } while (1);

    do {
        m->poziom_niebezpieczenstwa = pobierz_liczbe("Poziom niebezpieczenstwa (1-10): ");
        if (m->poziom_niebezpieczenstwa >= 1 && m->poziom_niebezpieczenstwa <= 10)
            break;
        printf("Blad: Poziom niebezpieczenstwa musi byc w zakresie 1–10!\n");
    } while (1);

    printf("Data karmienia (dd mm rrrr):\n");
    m->data_karmienia.dzien = pobierz_liczbe("Dzien: ");
    m->data_karmienia.miesiac = pobierz_liczbe("Miesiac: ");
    m->data_karmienia.rok = pobierz_liczbe("Rok: ");

    do {
        m->status_stworzenia = (stan)pobierz_liczbe("Status (0-4): ");
        if (m->status_stworzenia >= STABILNY && m->status_stworzenia <= W_KWARANTANNIE)
            break;
        printf("Blad: Status musi byc w zakresie 0–4!\n");
    } while (1);

    (*n)++;
    printf("Pomyslnie dodano stworzenie: %s\n", m->nazwa);
}


void wyszukaj(mistyczne_stworzenie *tab, int n) {
    char pref[MAX_ZN];
    int poziom, opcja1, opcja2;
    int znaleziono = 0;

    if (n == 0) {
        printf("Rejestr jest pusty. Nie ma czego szukac.\n");
        return;
    }

    do {
        printf("Po czym chcesz wyszukiwac (tekstowo)?\n");
        printf("1. Nazwa\n2. Gatunek\n");
        opcja1 = pobierz_liczbe("Wybor: ");
        if (opcja1 < 1 || opcja1 > 2) printf("Blad: Wybierz 1 lub 2.\n");
    } while (opcja1 < 1 || opcja1 > 2);

    clear_buffer();
    do {
        printf("Podaj prefiks (poczatkowe litery): ");
        if (fgets(pref, MAX_ZN, stdin)) {
            pref[strcspn(pref, "\n")] = 0;
            if (strlen(pref) > 0) break;
        }
        printf("Blad: Prefiks nie moze byc pusty.\n");
    } while (1);

    do {
        printf("Po jakim parametrze chcesz wyszukiwac (liczbowo)?\n");
        printf("1. Poziom mocy\n2. Poziom niebezpieczenstwa\n");
        opcja2 = pobierz_liczbe("Wybor: ");
        if (opcja2 < 1 || opcja2 > 2) printf("Blad: Wybierz 1 lub 2.\n");
    } while (opcja2 < 1 || opcja2 > 2);

    poziom = pobierz_liczbe("Podaj wartosc do porownania: ");

    printf("\n--- WYNIKI WYSZUKIWANIA ---\n");
    for (int i = 0; i < n; i++) {
        int tekst_pasuje = 0;
        int liczba_pasuje = 0;

        if (opcja1 == 1) {
            if (strncmp(tab[i].nazwa, pref, strlen(pref)) == 0) tekst_pasuje = 1;
        } else {
            if (strncmp(tab[i].gatunek, pref, strlen(pref)) == 0) tekst_pasuje = 1;
        }
        if (opcja2 == 1) {
            if (tab[i].poziom_mocy == poziom) liczba_pasuje = 1;
        } else {
            if (tab[i].poziom_niebezpieczenstwa == poziom) liczba_pasuje = 1;
        }

        if (tekst_pasuje && liczba_pasuje) {
            printf("Nazwa: %s | Gatunek: %s | Moc: %d | Niebezpieczenstwo: %d | Status: %d\n",
                   tab[i].nazwa, tab[i].gatunek, tab[i].poziom_mocy, 
                   tab[i].poziom_niebezpieczenstwa, tab[i].status_stworzenia);
            znaleziono = 1;
        }
    }

    if (!znaleziono) {
        printf("Brak wynikow spelniajacych oba kryteria.\n");
    }
}

void modyfikuj(mistyczne_stworzenie *tab, int n) {
    char nazwa_szukana[MAX_ZN];
    int opcja, status_val;
    int indeks = -1;

    clear_buffer();
    printf("Podaj nazwe stworzenia do modyfikacji: ");
    fgets(nazwa_szukana, MAX_ZN, stdin);
    nazwa_szukana[strcspn(nazwa_szukana, "\n")] = 0;

    for (int j = 0; j < n; j++) {
        if (strcmp(tab[j].nazwa, nazwa_szukana) == 0) {
            indeks = j;
            break;
        }
    }

    if (indeks == -1) {
        printf("Nie znaleziono stworzenia o nazwie: %s\n", nazwa_szukana);
        return;
    }

    do {
        printf("\nModyfikujesz: %s\n", tab[indeks].nazwa);
        printf("1. Gatunek\n2. Poziom mocy\n3. Poziom niebezpieczenstwa\n");
        printf("4. Data karmienia\n5. Status stworzenia\n0. Zakoncz\n");
        
        opcja = pobierz_liczbe("Wybor: ");

        switch (opcja) {
            case 1:
                do {
                    printf("Nowy gatunek: ");
                    clear_buffer();
                    fgets(tab[indeks].gatunek, MAX_ZN, stdin);
                    tab[indeks].gatunek[strcspn(tab[indeks].gatunek, "\n")] = 0;
                } while (!czy_tekst(tab[indeks].gatunek));
                break;
            case 2:
                do {
                    tab[indeks].poziom_mocy = pobierz_liczbe("Poziom mocy (1-999): ");
                    if (tab[indeks].poziom_mocy >= 1 && tab[indeks].poziom_mocy <= 999)
                        break;
                    printf("Blad: Poziom mocy musi byc w zakresie 1–999!\n");
                } while (1);
                break;
            case 3:
                do {
                    tab[indeks].poziom_niebezpieczenstwa = pobierz_liczbe("Poziom niebezpieczenstwa (1-10): ");
                    if (tab[indeks].poziom_niebezpieczenstwa >= 1 && tab[indeks].poziom_niebezpieczenstwa <= 10)
                        break;
                    printf("Blad: Poziom niebezpieczenstwa musi byc w zakresie 1–10!\n");
                } while (1);
                break;
            case 4:
                printf("Nowa data karmienia:\n");
                tab[indeks].data_karmienia.dzien = pobierz_liczbe("Dzien: ");
                tab[indeks].data_karmienia.miesiac = pobierz_liczbe("Miesiac: ");
                tab[indeks].data_karmienia.rok = pobierz_liczbe("Rok: ");
                break;
            case 5:             
                do {
                    status_val = pobierz_liczbe("Nowy status (0-4): ");
                    if (status_val >= STABILNY && status_val <= W_KWARANTANNIE) {
                        tab[indeks].status_stworzenia = (stan)status_val;
                        break;
                    }
                    printf("Blad: Status musi byc w zakresie 0–4!\n");
                } while (1);
                break;
            case 0:
                printf("Zakonczono edycje.\n");
                break;
            default:
                printf("Niepoprawna opcja.\n");
        }
    } while (opcja != 0);
}

void usun_pojedyncze(mistyczne_stworzenie *tab, int *n) {
    char nazwa[MAX_ZN];
    clear_buffer();

    printf("Podaj nazwe stworzenia do usuniecia: ");
    fgets(nazwa, MAX_ZN, stdin);
    nazwa[strcspn(nazwa, "\n")] = 0;

    for (int i = 0; i < *n; i++) {
        if (strcmp(tab[i].nazwa, nazwa) == 0) {

            if (tab[i].status_stworzenia == NIEBEZPIECZNY) {
                printf("Nie mozna usunac NIEBEZPIECZNEGO stworzenia!\n");
                return;
            }

            for (int j = i; j < *n - 1; j++)
                tab[j] = tab[j + 1];

            (*n)--;
            printf("Usunieto stworzenie.\n");
            return;
        }
    }
    printf("Nie znaleziono stworzenia.\n");
}

void usun_masowe(mistyczne_stworzenie *tab, int *n) {
    int opcja;
    clear_buffer();

    printf("Usuwanie masowe:\n");
    printf("1. Po gatunku\n");
    printf("2. Po poziomie niebezpieczenstwa\n");
    scanf("%d", &opcja);

    clear_buffer();

    int i = 0;
    if (opcja == 1) {
        char gatunek[MAX_ZN];
        printf("Podaj gatunek: ");
        fgets(gatunek, MAX_ZN, stdin);
        gatunek[strcspn(gatunek, "\n")] = 0;

        while (i < *n) {
            if (strcmp(tab[i].gatunek, gatunek) == 0 &&
                tab[i].status_stworzenia != NIEBEZPIECZNY) {

                for (int j = i; j < *n - 1; j++)
                    tab[j] = tab[j + 1];
                (*n)--;
            } else {
                i++;
            }
        }
    }
    else if (opcja == 2) {
        int poziom;
        printf("Podaj poziom niebezpieczenstwa: ");
        scanf("%d", &poziom);

        while (i < *n) {
            if (tab[i].poziom_niebezpieczenstwa == poziom &&
                tab[i].status_stworzenia != NIEBEZPIECZNY) {

                for (int j = i; j < *n - 1; j++)
                    tab[j] = tab[j + 1];
                (*n)--;
            } else {
                i++;
            }
        }
    }

    printf("Usuwanie masowe zakonczone.\n");
}


void sortuj_tekst(mistyczne_stworzenie *tab, int n) {
    printf("Po czym chcesz sortowanie alfabetyczne:\n");
    printf("1. Nazwa\n");
    printf("2. Gatunek\n");
    int opcja;
    scanf("%d", &opcja);
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (opcja == 1 && strcmp(tab[i].nazwa, tab[j].nazwa) > 0) {
                mistyczne_stworzenie tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            } else if (opcja == 2 && strcmp(tab[i].gatunek, tab[j].gatunek) > 0) {
                mistyczne_stworzenie tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }
    wyswietl(tab, n);
}

void sortuj_liczby(mistyczne_stworzenie *tab, int n) {
    printf("Po czym chcesz sortowanie liczbowe:\n");
    printf("1. Poziom mocy\n");
    printf("2. Poziom niebezpieczenstwa\n");
    int opcja;
    scanf("%d", &opcja);
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (opcja == 1 && tab[i].poziom_mocy < tab[j].poziom_mocy) {
                mistyczne_stworzenie tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }
            else if (opcja == 2 && tab[i].poziom_niebezpieczenstwa < tab[j].poziom_niebezpieczenstwa) {
                mistyczne_stworzenie tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }
    wyswietl(tab, n);
}

void zapisz(const char *plik, mistyczne_stworzenie *tab, int n) {
    FILE *f = fopen(plik, "wb");
    if (f == NULL) {
        printf("Blad: Nie mozna otworzyc pliku do zapisu!\n");
        return;
    }

    if (fwrite(&n, sizeof(int), 1, f) != 1) {
        printf("Blad podczas zapisu naglowka!\n");
    } else {
        fwrite(tab, sizeof(mistyczne_stworzenie), n, f);
        printf("Dane zapisane pomyslnie w %s.\n", plik);
    }
    fclose(f);
}

void wczytaj(const char *plik, mistyczne_stworzenie **tab, int *n) {
    FILE *f = fopen(plik, "rb");
    if (f == NULL) {
        printf("Blad: Plik %s nie istnieje!\n", plik);
        return;
    }

    int nowa_liczba;
    if (fread(&nowa_liczba, sizeof(int), 1, f) != 1) {
        printf("Blad: Nieczytelny format pliku!\n");
        fclose(f);
        return;
    }

    mistyczne_stworzenie *temp = realloc(*tab, nowa_liczba * sizeof(mistyczne_stworzenie));
    if (temp == NULL && nowa_liczba > 0) {
        printf("Blad: Brak pamieci do wczytania danych!\n");
        fclose(f);
        return;
    }

    *tab = temp;
    size_t przeczytano = fread(*tab, sizeof(mistyczne_stworzenie), nowa_liczba, f);
    *n = (int)przeczytano;

    if (przeczytano != (size_t)nowa_liczba) {
        printf("Ostrzezenie: Plik moze byc przerwany. Wczytano tylko %d rekordow.\n", *n);
    } else {
        printf("Wczytano %d stworzen z pliku.\n", *n);
    }

    fclose(f);
}

void wyswietl(mistyczne_stworzenie *tab, int n) {
    for (int i = 0; i < n; i++) {
        printf("nazwa:%s | gatunek:%s | moc:%d | niebezpieczenstwo:%d | data_karmienia:%02d-%02d-%04d | status:%d-\n",
               tab[i].nazwa,
               tab[i].gatunek,
               tab[i].poziom_mocy,
               tab[i].poziom_niebezpieczenstwa,
               tab[i].data_karmienia.dzien,
               tab[i].data_karmienia.miesiac,
               tab[i].data_karmienia.rok,
               tab[i].status_stworzenia);
               if(tab[i].status_stworzenia == STABILNY) {
                   printf("STABILNY\n");
               } else if(tab[i].status_stworzenia == NIESPOKOJNY) {
                   printf("NIESPOKOJNY\n");
               } else if(tab[i].status_stworzenia == AGRESYWNY) {
                   printf("AGRESYWNY\n");
               } else if(tab[i].status_stworzenia == NIEBEZPIECZNY) {
                   printf("NIEBEZPIECZNY\n");
               } else if(tab[i].status_stworzenia == W_KWARANTANNIE) {
                   printf("W_KWARANTANNIE\n");
               }
    }
    if (n == 0) {
        printf("Brak mistycznych stworzen do wyswietlenia.\n");
    }
}
