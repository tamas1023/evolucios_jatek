#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

int palyameret;
bool jomeret = false;
int elolenydb;
bool joeloleny = false;
vector<vector<int *>> palya;

// ezt majd át kell rakni a playa.cpp be, meg majd a többit is
// meg majd az int * helyett majd Eloleny típusút kell megcsinálni
void palyaKiiratasa()
{
    // első oszlop
    std::cout << "     ";
    for (int i = 0; i < palyameret; i++)
    {
        if (i < 10)
        {
            std::cout << i << "   ";
        }
        else
        {
            std::cout << i << "  ";
        }
    }
    std::cout << std::endl;
    for (int i = 0; i < palyameret; i++)
    {
        cout << "---|";
    }
    cout << "---|" << endl;
    // sorok
    for (int i = 0; i < palyameret; i++)
    {
        if (i < 10)
        {
            std::cout << " " << i << " | ";
        }
        else
        {
            std::cout << i << " | ";
        }
        for (int j = 0; j < palyameret; j++)
        {
            // TODO átállítani majd == re mert ez ideiglenes
            if (palya[i][j] == nullptr)
            {
                std::cout << 0 << " | ";
            }
            else
            {
                // int szam = rand() % (palyameret * palyameret - 2 + 1) + 2;
                // TODO majd itt nem lesz elég csak a palya i j edik elemét kiíratni
                int szam = *palya[i][j];
                if (szam >= 10)
                {
                    std::cout << szam << "| ";
                }
                else
                {
                    std::cout << szam << " | ";
                }
            }
        }
        cout << endl;
        for (int i = 0; i < palyameret; i++)
        {
            cout << "---|";
        }
        cout << "---|" << endl;
    }
}
int main(int argc, char const *argv[])
{

    while (!jomeret)
    {
        try
        {
            string valasz;

            cout << "Mekkora legyen a palya merete (szam * szam), minimum 4 maximum 10, ha nem ad meg semmit akkor 5 lesz a merete: " << endl;
            getline(cin, valasz);
            if (valasz.length() > 0)
            {
                palyameret = stoi(valasz);
                if (palyameret > 10)
                {
                    palyameret = 10;
                }
                if (palyameret < 4)
                {
                    palyameret = 4;
                }
                jomeret = true;
            }
            else
            {
                palyameret = 5;
                jomeret = true;
            }

            cout << "A palyameret: " << palyameret << endl;
        }
        catch (invalid_argument &e)
        {
            cerr << "Konvertalasi hiba: " << e.what() << '\n';
        }
        catch (const out_of_range &e)
        {
            cerr << "Tul hosszu szam: " << e.what() << '\n';
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
        }
    }

    while (!joeloleny)
    {
        try
        {
            string valasz;
            cout << "Adja meg a jelenlegi elolenyek szamat (2-tol, maximum(palyameret ig), ha nem ad meg szamot, akkor veletlen darab lesz hozzaadva: " << endl;
            getline(cin, valasz);
            if (valasz.length() > 0)
            {
                elolenydb = stoi(valasz);
                if (elolenydb >= 2 && elolenydb <= palyameret)
                {
                    joeloleny = true;
                }
            }
            else
            {
                // random szám generálás (2-tol, maximum(palyameret*palyameret ig))
                // példa: palyameret = 4, ekkor a tartomány:
                //(4 * 4 - 2 + 1) ez azt jelenti hogy 0 és 15 között sorsol, a 15 már nem tartozik bele
                // a +2 a végén meg azt csinálja, hogy előrébb lépleti a randomot-> 2 és 17 között, de a
                // 17 már nem tartozik bele
                elolenydb = rand() % (palyameret * palyameret - 2 + 1) + 2;
                joeloleny = true;
            }

            cout << "Az eloleny meret: " << elolenydb << endl;
        }
        catch (invalid_argument &e)
        {
            cerr << "Konvertalasi hiba: " << e.what() << '\n';
        }
        catch (const out_of_range &e)
        {
            cerr << "Tul hosszu szam: " << e.what() << '\n';
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
        }
    }

    // vector<vector<int *>> palya(palyameret, vector<int *>(palyameret));
    for (int i = 0; i < palyameret; i++)
    {
        palya.push_back(vector<int *>()); //
        for (int j = 0; j < palyameret; j++)
        {
            palya[i].push_back(nullptr);
        }
    }
    palyaKiiratasa();
    return 0;
}
