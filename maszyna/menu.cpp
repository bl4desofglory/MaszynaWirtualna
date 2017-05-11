//
//  menu.cpp
//  maszyna_wirtualna
//
//  Created by Tomasz Kisielewski on 11.05.2017.
//  Copyright © 2017 Tomasz Kisielewski. All rights reserved.
//

#include "header.hpp"

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
