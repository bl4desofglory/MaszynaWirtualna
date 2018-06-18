//  POP 2017-01-23 projekt 2 Kisielewski Tomasz EIT 3 165678     IDE WINDOWS: CodeBlocks 16.01 KOMPILATOR WINDOWS: gcc 4.9.2
//
//  main.cpp
//  maszyna
//
//  Created by Tomasz Kisielewski on 11.12.2016.
//  Copyright © 2016 Tomasz Kisielewski. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cstring>

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

int main(int argc, const char * argv[])
{
    fstream plik;
    
    menuGlowne(plik);
    
    return 0;
}

void menuOperacje(fstream &plik)
{
    int iWybor = 0;
    
    do
    {
        wyswietlMenuOperacje();
        cin >> iWybor;
        switch(iWybor)
        {
            case moPowrot:
            {
                menuSzczegoly(plik);
                iWybor = 0;
                break;
            }
            default: break;
        }
    } while(iWybor != 0);
}

void menuSzczegoly(fstream &plik)
{
    int iWybor = 0;
    
    do
    {
        wyswietlMenuSzczegoly();
        cin >> iWybor;
        switch(iWybor)
        {
            case mpOperacje:
            {
                menuOperacje(plik);
                break;
            }
            case mpPowrot:
            {
                menuGlowne(plik);
                iWybor = 0;
                break;
            }
            default: break;
        }
    } while(iWybor != 0);
}

void menuPrzyklady(fstream &plik)
{
    int iWybor = 0;
    
    do
    {
        wyswietlMenuPrzyklady();
        cin >> iWybor;
        switch(iWybor)
        {
            case 1:
            case 2:
            case 3:
            case 4:
            {
                menuPrzyklad(plik, iWybor);
                break;
            }
            case 0:
            {
                menuGlowne(plik);
                iWybor = 0;
                break;
            }
            default: break;
        }
    } while(iWybor != 0);
}

void menuPrzyklad(fstream &plik, int iKtory)
{
    int iWybor = 0;
    
    do
    {
        wyswietlPrzyklad(iKtory);
        cin >> iWybor;
        switch(iWybor)
        {
            case 0:
            {
                menuPrzyklady(plik);
                iWybor = 0;
                break;
            }
            default: break;
        }
    } while(iWybor != 0);
}

void menuGlowne(fstream &plik)
{
    int iWybor = 0;
    
    do
    {
        wyswietlMenu();
        cin >> iWybor;
        switch(iWybor)
        {
            case mgOpis:
            {
                menuSzczegoly(plik);
            }
            case mgTworz:
            {
                while(plikOtworzWyj(plik));
                plikTworz(plik);
                break;
            }
            case mgWykonajLiniowo:
            {
                while(plikOtworzWej(plik));
                plikWykonaj(plik, tLiniowo);
                break;
            }
            case mgWykonajKrokowo:
            {
                while(plikOtworzWej(plik));
                plikWykonaj(plik, tKrokowo);
                break;
            }
            case mgPrzyklady:
            {
                menuPrzyklady(plik);
            }
            case mgZakoncz:
            {
                exit(0);
                break;
            }
            default: break;
        }
    } while(iWybor != 0);
}

int plikOtworzWej(fstream &plik)
{
    char plikNazwa[42];
    cout << "Podaj nazwe pliku (bez rozszerzenia):" << endl;
    cout << "> ";
    cin >> plikNazwa;
    strcat(plikNazwa, ".bin");
    plik.open(plikNazwa, ios::in | ios::binary);
    if(!plik.good())
    {
        cerr << "Blad otwarcia pliku: " << plikNazwa << endl;
        return -1;
    }
    return 0;
}

int plikOtworzWyj(fstream &plik)
{
    char plikNazwa[42];
    cout << "Podaj nazwe pliku (bez rozszerzenia):" << endl;
    cout << "> ";
    cin >> plikNazwa;
    strcat(plikNazwa, ".bin");
    plik.open(plikNazwa, ios::out | ios::binary);
    if(!plik.good())
    {
        cerr << "Blad otwarcia pliku: " << plikNazwa << endl;
        return -1;
    }
    return 0;
}

void plikZamknij(fstream &plik)
{
    plik.close();
}

void plikTworz(fstream &plik)
{
    cout << "+---------+--------+--TWORZENIE PLIKU MASZYNY WIRTUALNEJ----------------------+" << endl;
    wyswietlOperacje();
    cout << "+----+----------+---------------------+---------------------------------------+" << endl;
    
    unsigned int cntInstrukcja = 0;
    short iRozkaz = 0;
    short iOperacja = 0;
    short itIndeks[2];
    int iSlowo = 0;
    bool bBlad = true;
    
    while(iOperacja != opZapisz)
    {
        cout << "Podaj operacje: " << endl << "> ";
        cin >> iOperacja;
        switch(iOperacja)
        {
            case opDodaj:
            case opOdejmij:
            case opMnoz:
            case opDziel:
            case opPorownaj:
            {
                bBlad = true;
                while(bBlad)
                {
                    cout << "Podaj indeks pierwszego rejestru (0 - 63): " << endl << "> ";
                    cin >> itIndeks[r1];
                    if((itIndeks[r1] < 0) || (itIndeks[r1] > 63))
                    {
                        cout << "Bledny indeks pierwszego rejestru!" << endl;
                    }
                    else
                        bBlad = false;
                }
                
                bBlad = true;
                while(bBlad)
                {
                    cout << "Podaj indeks drugiego rejestru (0 - 63): " << endl << "> ";
                    cin >> itIndeks[r2];
                    if((itIndeks[r2] < 0) || (itIndeks[r2] > 63))
                    {
                        cout << "Bledny indeks drugiego rejestru!" << endl;
                    }
                    else
                        bBlad = false;
                }
                
                iRozkaz = (itIndeks[r2] << 10) | (itIndeks[r1] << 4) | iOperacja;
                
                plik.write((char*)&iRozkaz, 2);
                cout << "Operacja " << szR[iOperacja] << ": " << itIndeks[r2] << "*2^10 + " << itIndeks[r1] << "*2^4 + " << iOperacja << " = "<< iRozkaz << endl;
                cntInstrukcja++;
                break;
            }
            case opWyswietl:
            case opPobierz:
            {
                bBlad = true;
                while(bBlad)
                {
                    cout << "Podaj indeks rejestru (0 - 63): " << endl << "> ";
                    cin >> itIndeks[r1];
                    if((itIndeks[r1] < 0) || (itIndeks[r1] > 63))
                    {
                        cout << "Bledny indeks rejestru!" << endl;
                    }
                    else
                        bBlad = false;
                }
                
                itIndeks[r2] = 0;
                
                iRozkaz = (itIndeks[r2] << 10) | (itIndeks[r1] << 4) | iOperacja;
   
                plik.write((char*)&iRozkaz, 2);
                cout << "Operacja " << szR[iOperacja] << ": " << itIndeks[r1] << "*2^4 + " << iOperacja << " = "<< iRozkaz << endl;
                cntInstrukcja++;
                break;
            }
            case opSkocz:
            {
                bBlad = true;
                while(bBlad)
                {
                    cout << "Podaj warunek skoku (0 - 6): " << endl << "> ";
                    cin >> itIndeks[r1];
                    if((itIndeks[r1] < 0) || (itIndeks[r1] > 6))
                    {
                        cout << "Bledny warunek skoku!" << endl;
                    }
                    else
                        bBlad = false;
                }
                
                itIndeks[r2] = 0;
                
                bBlad = true;
                while(bBlad)
                {
                    cout << "Podaj wartosc skoku: " << endl << "> ";
                    cin >> iSlowo;
                    if(cin.fail())
                    {
                        cout << "Bledna wartosc skoku!" << endl;
                    }
                    else
                        bBlad = false;
                }
                
                iRozkaz = (itIndeks[r2] << 10) | (itIndeks[r1] << 4) | iOperacja;
                
                plik.write((char*)&iRozkaz, 2);
                plik.write((char*)&iSlowo, 4);
                cout << "Operacja " << szR[iOperacja] << ": " << itIndeks[r2] << "*2^10 + " << itIndeks[r1] << "*2^4 + " << iOperacja << " = "<< iRozkaz << " SKOK: " << iSlowo << endl;
                cntInstrukcja++;
                break;
            }
            case opWczytaj:
            {
                bBlad = true;
                while(bBlad)
                {
                    cout << "Podaj indeks rejestru (0 - 63): " << endl << "> ";
                    cin >> itIndeks[r1];
                    if((itIndeks[r1] < 0) || (itIndeks[r1] > 63))
                    {
                        cout << "Bledny indeks rejestru!" << endl;
                    }
                    else
                        bBlad = false;
                }
                itIndeks[r2] = 0;
                
                bBlad = true;
                while(bBlad)
                {
                    cout << "Podaj wartosc stalej: " << endl << "> ";
                    if(!cin >> iSlowo)
                    {
                        cout << "Bledna wartosc skoku!" << endl;
                    }
                    else
                        bBlad = false;
                }
                
                iRozkaz = (itIndeks[r2] << 10) | (itIndeks[r1] << 4) | iOperacja;
                plik.write((char*)&iRozkaz, 2);
                plik.write((char*)&iSlowo, 4);
                cout << "Operacja " << szR[iOperacja] << ": " << itIndeks[r2] << "*2^10 + " << itIndeks[r1] << "*2^4 + " << iOperacja << " = "<< iRozkaz << " STALA: " << iSlowo << endl;
                cntInstrukcja++;
                break;
            }
            case opZakoncz:
            {
                itIndeks[r1] = 0;
                itIndeks[r2] = 0;
                
                iRozkaz = (itIndeks[r2] << 10) | (itIndeks[r1] << 4) | iOperacja;
                plik.write((char*)&iRozkaz, 2);
                cntInstrukcja++;
                break;
            }
            default:
            {
                cout << "Nieprawidlowa operacja!" << endl;
                break;
            }
        }
    }
    plikZamknij(plik);
}

void plikWykonaj(fstream &plik, int iTryb)
{
    int iRejestr[64];
    short iFlaga = flZ;
    unsigned int cntInstrukcja = 0;
    short iRozkaz = 0;
    short iOperacja = 0;
    short iGUI = 0;
    short itIndeks[2];
    char ctRozkaz[2];
    char ctSlowo[4];
    int iSlowo = 0;
    int iBufor = 0;
    unsigned long iWczytano = 0;
    
    for(int i = 0; i < 64; i++)
        iRejestr[i] = 0;
    
    while(iGUI != 2)
    {
        if(iOperacja == opZakoncz)
            break;
        
        plik.read(ctRozkaz, 2);
        iWczytano = plik.gcount();
        iRozkaz = ((int)ctRozkaz[r2] << 8) | (int)ctRozkaz[r1];
        iOperacja = iRozkaz & 0b1111;
        itIndeks[r1] = (iRozkaz & 0b1111110000) >> 4;
        itIndeks[r2] = (iRozkaz & 0b1111110000000000) >> 10;
        cntInstrukcja++;
        
        if(iOperacja == opSkocz)
        {
            plik.read(ctSlowo, 4);
            iSlowo = ((int)ctSlowo[3] << 24) | ((int)ctSlowo[2] << 16) | ((int)ctSlowo[1] << 8) | ((int)ctSlowo[0]);
            iBufor = itIndeks[r1];
            itIndeks[r1] = 0;
            iWczytano += 4;
        }
        
        cout << "+--------------------WYKONYWANIE PLIKU MASZYNY WIRTUALNEJ---------------------+" << endl;
        cout << "| OP("<<setw(2)<<iOperacja<<"): "<<setw(11-strlen(szR[iOperacja]))<<s<<szR[iOperacja]<<" R1("<<setw(2)<<itIndeks[r1]<<"): "<<setw(10)<<iRejestr[itIndeks[r1]]<<" R2("<<setw(2)<<itIndeks[r2]<<"):"<<setw(10)<<iRejestr[itIndeks[r2]]<<" SLOWO: "<<setw(10)<<iSlowo<<"  |"<< endl;
        cout << "| ROZKAZ: "<<setw(11)<<iRozkaz<<" FLAGA: "<<szF[iFlaga+1]<<setw(11)<<s<<"KROK: "<<setw(11)<<cntInstrukcja<<setw(20)<<s<<"|"<<endl;
        cout << "| WCZYTANO:   "<<iWczytano<<" bajty"<<setw(20)<<s<<"KARETKA: "<<setw(8)<<plik.tellg()<<setw(20)<<s<<"|" << endl;
        
        if(iTryb == tKrokowo)
        {
            cout << "+--------------------------------------+--------------------------------------+" << endl;
            cout << "| 1. Wykonaj instrukcje                | 2. Zakoncz wykonywanie pliku         |" << endl;
            cout << "+--------------------------------------+--------------------------------------+" << endl;
            cin >> iGUI;
        }
        else
            cout << "+-----------------------------------------------------------------------------+" << endl;
            
        
        switch(iOperacja)
        {
            case opDodaj: // dodaj
            {
                iRejestr[itIndeks[r1]] += iRejestr[itIndeks[r2]];
                if(iRejestr[itIndeks[r1]] > 0)
                    iFlaga = flD;
                else if(iRejestr[itIndeks[r1]] < 0)
                    iFlaga = flU;
                else
                    iFlaga = flZ;
                break;
            }
            case opOdejmij: // odejmij
            {
                iRejestr[itIndeks[r1]] -= iRejestr[itIndeks[r2]];
                if(iRejestr[itIndeks[r1]] > 0)
                    iFlaga = flD;
                else if(iRejestr[itIndeks[r1]] < 0)
                    iFlaga = flU;
                else
                    iFlaga = flZ;
                break;
            }
            case opMnoz: // mnoz
            {
                iRejestr[itIndeks[r1]] *= iRejestr[itIndeks[r2]];
                if(iRejestr[itIndeks[r1]] > 0)
                    iFlaga = flD;
                else if(iRejestr[itIndeks[r1]] < 0)
                    iFlaga = flU;
                else
                    iFlaga = flZ;
                break;
            }
            case opDziel:
            {
                iBufor = iRejestr[itIndeks[r1]];
                
                if(iRejestr[itIndeks[r2]])
                {
                    iRejestr[itIndeks[r1]] /= iRejestr[itIndeks[r2]];
                    iRejestr[itIndeks[r2]] = iBufor%iRejestr[itIndeks[r2]];
                    
                    if(iRejestr[itIndeks[r1]] > 0)
                        iFlaga = flD;
                    else if(iRejestr[itIndeks[r1]] < 0)
                        iFlaga = flU;
                    else
                        iFlaga = flZ;
                }
                else
                    wyswietlBlad(bladDziel);
                break;
            }
            case opPorownaj:
            {
                iBufor = iRejestr[itIndeks[r1]]-iRejestr[itIndeks[r2]];
                if(iBufor > 0)
                    iFlaga = flD;
                else if(iBufor < 0)
                    iFlaga = flU;
                else
                    iFlaga = flZ;
                break;
            }
            case opKopiuj:
            {
                iRejestr[itIndeks[r1]] = iRejestr[itIndeks[r2]];
                break;
            }
            case opSkocz:
            {
                switch(iBufor)
                {
                    case 0:
                    {
                        plikSkok(plik, iSlowo, cntInstrukcja);
                        break;
                    }
                    case 1:
                    {
                        if(iFlaga == flZ)
                            plikSkok(plik, iSlowo, cntInstrukcja);
                        break;
                    }
                    case 2:
                    {
                        if(iFlaga != flZ)
                            plikSkok(plik, iSlowo, cntInstrukcja);
                        break;
                    }
                    case 3:
                    {
                        if(iFlaga == flD)
                            plikSkok(plik, iSlowo, cntInstrukcja);
                        break;
                    }
                    case 4:
                    {
                        if(iFlaga == flU)
                            plikSkok(plik, iSlowo, cntInstrukcja);
                        break;
                    }
                    case 5:
                    {
                        if(iFlaga != flU)
                            plikSkok(plik, iSlowo, cntInstrukcja);
                        break;
                    }
                    case 6:
                    {
                        if(iFlaga != flD)
                            plikSkok(plik, iSlowo, cntInstrukcja);
                        break;
                    }
                    default: break;
                }
                break;
            }
            case opWczytaj:
            {
                plik.read(ctSlowo, 4);
                iSlowo = ((int)ctSlowo[3] << 24) | ((int)ctSlowo[2] << 16) | ((int)ctSlowo[1] << 8) | ((int)ctSlowo[0]);
                break;
            }
            case opPobierz:
            {
                cout << ">> ";
                cin >> iRejestr[itIndeks[r1]];
                break;
            }
            case opWyswietl:
            {
                cout << "<< ";
                cout << iRejestr[itIndeks[r1]] << endl;
                break;
            }
            case opZakoncz:
            {
                system("PAUSE");
                break;
            }
            default: break;
        }
        
        if(plik.eof())
        {
            wyswietlBlad(bladEof);
            iGUI = 2;
        }
    }
    plikZamknij(plik);
    
    return;
}

void plikSkok(fstream &plik, int &iSlowo, unsigned int &cntInstrukcja)
{
    char ctBufor[2];
    plik.seekg(0, ios_base::beg);
    unsigned long cntRozkazy = 0;
    cntInstrukcja += iSlowo - 1;
    while(cntRozkazy != cntInstrukcja)
    {
        plik.read(ctBufor, 2);
        cntRozkazy++;
        if((((int)ctBufor[r1] & opSkocz) == opSkocz) || (((int)ctBufor[r1] & opWczytaj) == opWczytaj))
        {
            plik.read(ctBufor, 2);
            plik.read(ctBufor, 2);
        }
    }
}

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
