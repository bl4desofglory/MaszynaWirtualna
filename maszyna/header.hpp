//
//  header.hpp
//  maszyna_wirtualna
//
//  Created by Tomasz Kisielewski on 11.05.2017.
//  Copyright © 2017 Tomasz Kisielewski. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <fstream>

#ifndef header_hpp
#define header_hpp

using namespace std;

enum rejestry { r1 = 0, r2 = 1 };
enum flaga { flU = -1, flZ = 0, flD = 1 };
enum rozkaz { opDodaj = 0, opOdejmij = 1, opMnoz = 2, opDziel = 3, opPorownaj = 4, opKopiuj = 5, opSkocz = 6, opWczytaj = 7, opPobierz = 8, opWyswietl = 9, opZakoncz = 10, opZapisz = 11};
enum menuGlowne { mgZakoncz = 0, mgOpis, mgTworz, mgWykonajLiniowo, mgWykonajKrokowo, mgPrzyklady };
enum menuPomoc { mpPowrot = 0, mpOperacje};
enum menuOperacje { moPowrot = 0 };
enum trybWykonywania { tLiniowo = 0, tKrokowo = 1 };
enum bladOperacji { bladDziel = 0, bladEof, bladOtwarcia };

const char szF[3][2] = { "U", "Z", "D" };
const char szR[12][9] = { "dodaj"  , "odejmij" , "mnoz"   , "dziel"   ,
    "porownaj", "kopiuj"  , "skocz"  , "wczytaj" ,
    "pobierz" , "wyswietl", "zakoncz", "zapisz" };
const char s = ' ';

void wyswietlMenu();
void wyswietlMenuSzczegoly();
void wyswietlMenuOperacje();
void wyswietlMenuPrzyklady();
void wyswietlOperacje();
void wyswietlPrzyklad(int iKtory);
void wyswietlBlad(int iBlad);
void plikWykonaj(fstream &plik, int iTryb);
void wyswietlPlik(fstream &plik);
void plikTworz(fstream &plik);
void plikZamknij(fstream &plik);
int  plikOtworzWej(fstream &plik);
int  plikOtworzWyj(fstream &plik);
void plikSkok(fstream &plik, int &iSlowo, unsigned int &cntInstrukcja);
void menuGlowne(fstream &plik);
void menuSzczegoly(fstream &plik);
void menuOperacje(fstream &plik);
void menuPrzyklad(fstream &plik, int iKtory);
void menuPrzyklady(fstream &plik);

#endif /* header_hpp */
