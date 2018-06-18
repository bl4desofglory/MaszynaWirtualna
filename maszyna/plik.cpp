//
//  plik.cpp
//  maszyna_wirtualna
//
//  Created by Tomasz Kisielewski on 11.05.2017.
//  Copyright © 2017 Tomasz Kisielewski. All rights reserved.
//

#include "header.hpp"

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
            case opPobierz:
            case opWyswietl:
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
                        cout << "Bledna wartosc stalej!" << endl;
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
        iOperacja = iRozkaz & 15;
        itIndeks[r1] = (iRozkaz & 1008) >> 4;
        itIndeks[r2] = (iRozkaz & 64512) >> 10;
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
