//
//  wyswietl.cpp
//  maszyna_wirtualna
//
//  Created by Tomasz Kisielewski on 11.05.2017.
//  Copyright © 2017 Tomasz Kisielewski. All rights reserved.
//

#include "header.hpp"

void wyswietlOperacje()
{
    cout << "| Format: | R2(6b) | R1(6b) | OP(4b) | INT(4B)   (tylko dla skocz i wczytaj)  |" << endl;
    cout << "+---------+--------+--------+----+---+--------------------+-------------------+" << endl;
    cout << "| R2, R1: Indeks rejestru (0-63) | OP: Kod rozkazu (0-10) | INT: liczba 4B    |" << endl;
    cout << "+----+----------+----------------+----+-------------------+-------------------+" << endl;
    cout << "| Op | Rozkaz   | Opis                | Format rozkazu SKOCZ: 0_R1_6_INT      |" << endl;
    cout << "+----+----------+---------------------+-----+---------------------------------+" << endl;
    cout << "|  0 | dodaj    | R1:=R1+R2           |  R1 | WARUNEK skoku (stan flagi)      |" << endl;
    cout << "|  1 | odejmij  | R1:=R1-R2           +-----+---------------------------------+" << endl;
    cout << "|  2 | mnoz     | R1:=R1*R2           |   0 | Zawsze                          |" << endl;
    cout << "|  3 | dziel    | R1:=R1/R2 R2:=R1%R2 |   1 | Ustanwiona Z (zero)             |" << endl;
    cout << "|  4 | porownaj | R3:=R1-R2           |   2 | Nieustawniona  Z (nie zero)     |" << endl;
    cout << "|  5 | kopiuj   | R1:=R2              |   3 | Ustawiona D (dodatnia)          |" << endl;
    cout << "|  6 | skocz    | skocz do instrukcji |   4 | Ustawiona U (ujemna)            |" << endl;
    cout << "|  7 | wczytaj  | R1:= stala INT      |   5 | Nieustawniona U (nieujemna)     |" << endl;
    cout << "|  8 | pobierz  | R1:= z klawiatury   |   6 | Nieustawniona D (niedodatania)  |" << endl;
    cout << "|  9 | wyswietl | wypisz R1           +-----+---------------------------------+" << endl;
    cout << "| 10 | zakoncz  | zakoncz program     | INT | skok o INT rozkazow             |" << endl;
    cout << "+----+----------+---------------------+-----+---------------------------------+" << endl;
    cout << "|           Operacje edytora          | Format rozkazu WCZYTAJ: 0_R1_7_INT    |" << endl;
    cout << "+----+----------+---------------------+-----+---------------------------------+" << endl;
    cout << "| 11 | zapisz   | zapisz plik         | INT | wczytaj do R1 stala INT         |" << endl;
}

void wyswietlMenu()
{
    cout << "+--------------------------------OPIS APLIKACJI-------------------------------+" << endl;
    cout << "| Aplikacja pozwala stworzyc i zapisac plik programu maszyny wirtualnej (VM)  |" << endl;
    cout << "| oraz jego wykonanie w VM, ktorej dzialanie jest opisane podczas tworzenia   |" << endl;
    cout << "| pliku oraz szczegolowy opis dostepny jest w MENU GLOWNYM.                   |" << endl;
    cout << "| Program jest wykonywany krokowo (instrukcja po instrukcji).                 |" << endl;
    cout << "| W czasie pracy wyswietlany jest obecny stan Maszyny Wirtualnej              |" << endl;
    cout << "| Autor: Tomasz Kisielewski EiT K3 s165678                                    |" << endl;
    cout << "+---------------------------------MENU GLOWNE---------------------------------+" << endl;
    cout << "| 1. Szczegolowy opis Maszyny Wirtualnej                                      |" << endl;
    cout << "| 2. Tworzenie pliku programu Maszyny Wirtualnej                              |" << endl;
    cout << "| 3. Wykonywanie liniowe programu Maszyny Wirtualnej                          |" << endl;
    cout << "| 4. Wykonywanie krokowe programu Maszyny Wirtualnej                          |" << endl;
    cout << "| 5. Przykladowe programy Maszyny Wirtualnej                                  |" << endl;
    cout << "| 0. Zakoncz program Maszyna Wirtualna                                        |" << endl;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    cout << "> ";
}

void wyswietlMenuSzczegoly()
{
    cout << "+---------------------------OPIS MASZYNY WIRTUALNEJ---------------------------+" << endl;
    cout << "| Maszyna zawiera:                                                            |" << endl;
    cout << "| * 64 4-bajtowe rejestry pamieci indeksowane od 0                            |" << endl;
    cout << "| * 4-bajtowy rejestr instrukcji                                              |" << endl;
    cout << "| * 1-bajtowy rejestr flagi                                                   |" << endl;
    cout << "| - W kazdym rejestrze pamieci moze byc przechowywana liczba (int) ze znakiem |" << endl;
    cout << "| - Rejestr instrukcji przechowuje liczbe (int) bez znaku informujaca o tym,  |" << endl;
    cout << "|   ktora z kolei jest wykonwyana instrukcja. Jest autoinkrementowany,        |" << endl;
    cout << "|   operacja skoku zmienia odpowiednio jego wartosc                           |" << endl;
    cout << "| - Trojstanowy rejestr flagi przechowuje informacje o wyniku ostatniej       |" << endl;
    cout << "|   operacji arytmetycznej (dodawanie, odejmowanie, mnozenie, dzielenie,      |" << endl;
    cout << "|   porownanie) i w zaleznosi od jej rezultatu przyjmuje wartosc:             |" << endl;
    cout << "|    * flaga D (1) dla dodatniego wyniku                                      |" << endl;
    cout << "|    * flaga Z (0) dla zera                                                   |" << endl;
    cout << "|    * flaga U (-1) dla ujemnego wyniku                                       |" << endl;
    cout << "|   Ta informacja moze byc uzyta przy wykonywaniu operacji skoku              |" << endl;
    cout << "| - Na poczatku pracy Maszyny Wirtualnej wszystkie rejestry sa wyzerowane.    |" << endl;
    cout << "|                                                                             |" << endl;
    cout << "| Operacje:                                                                   |" << endl;
    cout << "| - Kazda operacja to 2-bajtowa liczba bez znakuw formacie little endian      |" << endl;
    cout << "|   i ewentualna liczba 4-bajtowa (int) ze znakiem.                           |" << endl;
    cout << "| - Operacje mozna podzielic na 3 sekcje: R2_R1_OP                            |" << endl;
    cout << "|    * R2 - 6 bitow - indeks drugiego rejestru pamieci                        |" << endl;
    cout << "|    * R1 - 6 bitow - indeks pierwszego rejestru pamieci                      |" << endl;
    cout << "|    * OP - 4 bity - kod operacji                                             |" << endl;
    cout << "| - Dla operacji o kodach 6 i 7 (skocz i wczytaj) za 2-bajtowa operacja stoi: |" << endl;
    cout << "|    * INT - 4 bajty - stala skoku albo stala wczytywana do rejestru          |" << endl;
    cout << "| - Dla operacji o kodach: 6, 7, 8, 9, 10 wartosc R2 w liczbie operacji to 0. |" << endl;
    cout << "| - Dla operacji o kodzie: 10 wartosc R1 w liczbie operacji to 0.             |" << endl;
    cout << "+--------------------------------MENU SZCZEGOLY-------------------------------+" << endl;
    cout << "| 1. Wyswietl dostepne operacje                                               |" << endl;
    cout << "| 0. Powrot do MENU GLOWNEGO                                                  |" << endl;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    cout << "> ";
}

void wyswietlMenuOperacje()
{
    cout << "+---------+--------+-----------DOSTEPNE OPERACJE------------------------------+" << endl;
    wyswietlOperacje();
    cout << "+----+----------+-----------------MENU OPERACJE-------------------------------+" << endl;
    cout << "| 0. Powrot do MENU SZCZEGOLY                                                 |" << endl;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    cout << "> ";
}

void wyswietlMenuPrzyklady()
{
    cout << "+--------------------------------MENU PRZYKLADY-------------------------------+" << endl;
    cout << "| 1. Przyklad z zadania projektowego                                          |" << endl;
    cout << "| 2. Dodawanie dwoch licz                                                     |" << endl;
    cout << "| 3. Dzielenie 2 liczb                                                        |" << endl;
    cout << "| 4. Najwieksza z trzech                                                      |" << endl;
    cout << "| 0. Powrot do MENU GLOWNEGO                                                  |" << endl;
    cout << "+-----------------------------------------------------------------------------+" << endl;
    cout << "> ";
}

void wyswietlPrzyklad(int iKtory)
{
    switch(iKtory)
    {
        case 1:
        {
            cout << "+-----------------------PRZYKLAD Z ZADANIA PROJEKTOWEGO-----------------------+" << endl;
            cout << "| Nazwa pliku: projekt.bin                                                    |" << endl;
            cout << "+-----------------------------------------------------------------------------+" << endl;
            cout << "| * Pobierz liczbe z klawiatury do rejestru 0 (0*2^4+8 = 8)                   |" << endl;
            cout << "| * Porownaj rejestr 0 z rejestrem 2 (2*2^10+0*2^4+4 = 2052)                  |" << endl;
            cout << "| * Skocz o 2 instrukcje do przodu jesli nie zero (2*2^4+6 = 38 SKOK: 2)      |" << endl;
            cout << "| * Skoncz program (10 = 10)                                                  |" << endl;
            cout << "| * Do rejestru 1 dodaj rejestr 0 (0*2^10+1*2^4+0 = 16)                       |" << endl;
            cout << "| * Wypisz rejestr 1 (1*2^4+9 = 25)                                           |" << endl;
            cout << "| * Skocz o 6 instrukcji do tylu (0*2^4+6 = 6)                                |" << endl;
            cout << "+-----------------------------------------------------------------------------+" << endl;
            cout << "| 0. Powrot do MENU PRZYKLADY                                                 |" << endl;
            cout << "+-----------------------------------------------------------------------------+" << endl;
            cout << "> ";
            break;
        }
        case 2:
        {
            cout << "+----------------------------DODAWANIE DWOCH LICZB----------------------------+" << endl;
            cout << "| Nazwa pliku: dod_ab.bin                                                     |" << endl;
            cout << "+-----------------------------------------------------------------------------+" << endl;
            cout << "| * Pobierz liczbe z klawiatury do rejestru 0 (0*2^4 + 8 = 8)                 |" << endl;
            cout << "| * Pobierz liczbe z klawiatury do rejestru 1 (1*2^4 + 8 = 24)                |" << endl;
            cout << "| * Do rejestru 0 dodaj rejestr 1 (1*2^10 + 0*2^4 + 0 = 1024)                 |" << endl;
            cout << "| * Wypisz rejestr 0 (0*2^4 + 9 = 9)                                          |" << endl;
            cout << "| * Skoncz program (10 = 10)                                                  |" << endl;
            cout << "+-----------------------------------------------------------------------------+" << endl;
            cout << "| 0. Powrot do MENU PRZYKLADY                                                 |" << endl;
            cout << "+-----------------------------------------------------------------------------+" << endl;
            cout << "> ";
            break;
        }
        case 3:
        {
            cout << "+----------------------------DZIELENIE DWOCH LICZB----------------------------+" << endl;
            cout << "| Nazwa pliku: dziel_ab.bin                                                   |" << endl;
            cout << "+-----------------------------------------------------------------------------+" << endl;
            cout << "| * Pobierz liczbe z klawiatury do rejestru 0 (0*2^4 + 8 = 8)                 |" << endl;
            cout << "| * Pobierz liczbe z klawiatury do rejestru 1 (1*2^4 + 8 = 24)                |" << endl;
            cout << "| * Podziel rejestr 0 przez rejestr 1 (1*2^10 + 0*2^4 + 3 = 1027)             |" << endl;
            cout << "| * Wypisz rejestr 0 (0*2^4 + 9 = 9)                                          |" << endl;
            cout << "| * Wypisz rejestr 1 (1*2^4 + 9 = 25)                                         |" << endl;
            cout << "| * Skoncz program (10 = 10)                                                  |" << endl;
            cout << "+-----------------------------------------------------------------------------+" << endl;
            cout << "| 0. Powrot do MENU PRZYKLADY                                                 |" << endl;
            cout << "+-----------------------------------------------------------------------------+" << endl;
            cout << "> ";
            break;
        }
        case 4:
        {
            cout << "+--------------------------------NAJWIEKSZA Z 3-------------------------------+" << endl;
            cout << "| Nazwa pliku: max_3.bin                                                      |" << endl;
            cout << "+-----------------------------------------------------------------------------+" << endl;
            cout << "| * Pobierz liczbe z klawiatury do rejestru 0 (0*2^4 + 8 = 8)                 |" << endl;
            cout << "| * Pobierz liczbe z klawiatury do rejestru 1 (1*2^4 + 8 = 24)                |" << endl;
            cout << "| * Pobierz liczbe z klawiatury do rejestru 2 (2*2^4 + 8 = 40)                |" << endl;
            cout << "| * Porownaj rejestr 0 z rejestrem 1 (1*2^10 + 0*2^4 + 4 = 1028)              |" << endl;
            cout << "| * Skocz o 2 instrukcje do przodu jesli dodatnia (3*2^4 + 6 = 54 SKOK: 2)    |" << endl;
            cout << "| * Skocz o 4 instrukcje do przodu jesli ujemna (4*2^4 + 6 = 70 SKOK: 4)      |" << endl;
            cout << "| * Porownaj rejestr 0 z rejestrem 2 (2*2^10 + 0*2^4 + 4 = 2052)              |" << endl;
            cout << "| * Skocz o 6 instrukcje do przodu jesli dodatnia (3*2^4 + 6 = 54 SKOK: 6)    |" << endl;
            cout << "| * Skocz o 9 instrukcje do przodu jesli ujemna (4*2^4 + 6 = 70 SKOK: 9)      |" << endl;
            cout << "| * Porownaj rejestr 1 z rejestrem 2 (2*2^10 + 1*2^4 + 4 = 2068)              |" << endl;
            cout << "| * Skocz o 5 instrukcje do przodu jesli dodatnia (3*2^4 + 6 = 54 SKOK: 5)    |" << endl;
            cout << "| * Skocz o 6 instrukcje do przodu jesli ujemna (4*2^4 + 6 = 70 SKOK: 6)      |" << endl;
            cout << "| * Skoncz program (10 = 10)                                                  |" << endl;
            cout << "| * Wypisz rejestr 0 (0*2^4 + 9 = 9)                                          |" << endl;
            cout << "| * Skocz o 2 instrukcje do tylu (0*2^4 + 6 = 6 INT: -2)                      |" << endl;
            cout << "| * Wypisz rejestr 1 (1*2^4 + 9 = 25)                                         |" << endl;
            cout << "| * Skocz o 4 instrukcje do tylu (0*2^4 + 6 = 6 INT: -4)                      |" << endl;
            cout << "| * Wypisz rejestr 2 (1*2^4 + 9 = 41)                                         |" << endl;
            cout << "| * Skocz o 6 instrukcje do tylu (0*2^4 + 6 = 6 INT: -6)                      |" << endl;
            cout << "+-----------------------------------------------------------------------------+" << endl;
            cout << "| 0. Powrot do MENU PRZYKLADY                                                 |" << endl;
            cout << "+-----------------------------------------------------------------------------+" << endl;
            cout << "> ";
            break;
        }
    }
}

void wyswietlBlad(int iBlad)
{
    switch (iBlad) {
        case bladDziel:
        {
            cout << "+------------------------------------BLAD-------------------------------------+" << endl;
            cout << "|                     BLAD WYKONYWANIA: DZIELENIE PRZEZ 0                     |" << endl;
            cout << "+-----------------------------------------------------------------------------+" << endl;
            break;
        }
        case bladEof:
        {
            cout << "+------------------------------------BLAD-------------------------------------+" << endl;
            cout << "|                        BLAD WYKONYWANIA: KONIEC PLIKU                       |" << endl;
            cout << "+-----------------------------------------------------------------------------+" << endl;
            break;
        }
        default:
            break;
    }
}
