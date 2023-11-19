#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

#include "Palya/palya.cpp"

using namespace std;

int palyameret;
bool jomeret = false;
int elolenydb;
bool joeloleny = false;
bool playamenet = true;
vector<vector<int *>> palya;

// ezt majd át kell rakni a playa.cpp be, meg majd a többit is
// meg majd az int * helyett majd Eloleny típusút kell megcsinálni

int main(int argc, char const *argv[])
{
    srand(time(0));
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
            cout << "Adja meg a jelenlegi elolenyek szamat (2-tol, maximum palyameret * palyameret-ig), ha nem ad meg szamot, akkor veletlen darab lesz hozzaadva: " << endl;
            getline(cin, valasz);
            if (valasz == "")
            {
                elolenydb = rand() % (palyameret * palyameret - 2 + 1) + 2;
                joeloleny = true;
                cout << "Az eloleny meret: " << elolenydb << endl;
                break;
            }
            elolenydb = stoi(valasz);
            if (elolenydb >= 2 && elolenydb <= palyameret * palyameret)
            {
                joeloleny = true;
            }
            else
            {
                if (elolenydb > palyameret * palyameret)
                {
                    elolenydb = palyameret * palyameret;
                    joeloleny = true;
                }
                else
                {
                    // random szám generálás (2-tol, maximum(palyameret*palyameret ig))
                    // példa: palyameret = 4, ekkor a tartomány:
                    //(4 * 4 - 2 + 1) ez azt jelenti hogy 0 és 15 között sorsol, a 15 már nem tartozik bele
                    // a +2 a végén meg azt csinálja, hogy előrébb lépleti a randomot-> 2 és 17 között, de a
                    // 17 már nem tartozik bele
                    if (elolenydb < 2)
                    {
                        elolenydb = 2;
                    }
                    else
                    {
                        elolenydb = rand() % (palyameret * palyameret - 2 + 1) + 2;
                    }
                    // elolenydb = rand() % (palyameret * palyameret - 2 + 1) + 2;
                    joeloleny = true;
                }
            }

            cout << "Az eloleny meret: " << elolenydb << endl;
            cout << endl
                 << "-----------------------------------------------" << endl
                 << endl;
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
    try
    {
        Palya palya(palyameret, elolenydb);
        palya.palyaKiiratasa();
        while (playamenet)
        {
            // ide jön a gombokra a mozgás, a harc, esetleg a power uppok (+1 élet, és + erő), a megjelenítés
            // nem biztos hogy itt kell majd mindet meghívni
            string input = "";
            cout << endl
                 << "-----------------------------------------------" << endl
                 << endl;

            cout << "Korok szama: " << to_string(palya.getKorokSzama()) << endl
                 << endl;
            cout << "Muveletek:" << endl;
            cout << "  - [Enter] - Kovetkezo kor" << endl;
            cout << "  - q - Kilepes" << endl;
            cout << "Muvelet: ";
            getline(cin, input);
            cout << endl
                 << "-----------------------------------------------" << endl
                 << endl;
            if (input == "")
            {
                palya.palyaMozgatasa();
                palya.palyaKiiratasa();
            }
            if (input == "q")
            {
                playamenet = false;
                cout << "Kilepes..." << endl;
            }
        }

        // vector<vector<int *>> palya(palyameret, vector<int *>(palyameret));
    }
    catch (const bad_alloc &e)
    {
        cerr << "Failed to allocate memory: " << e.what() << endl;
        // Handle the error gracefully, e.g., exit the program or prompt the user to provide a smaller size.
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
