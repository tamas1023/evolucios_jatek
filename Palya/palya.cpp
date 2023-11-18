#include <iostream>
#include <vector>
#include <ctime>

#include "../Helyek/helyek.cpp"

using namespace std;

class Palya
{
    int palyameret;
    int elolenydb;
    int korokSzama = 0;
    vector<vector<Helyek *>> palya;

public:
    Palya(const int &palyameret, const int &elolenydb) : palyameret(palyameret), elolenydb(elolenydb)
    {
        for (int i = 0; i < palyameret; i++)
        {
            palya.push_back(vector<Helyek *>());
            for (int j = 0; j < palyameret; j++)
            {
                palya[i].push_back(nullptr);
            }
        }

        elolenyekElhelyezese();
    };

    void palyaKiiratasa()
    {
        // első oszlop
        cout << "     ";
        for (int i = 0; i < palyameret; i++)
        {
            if (i < 10)
            {
                cout << i << "   ";
            }
            else
            {
                cout << i << "  ";
            }
        }
        cout << endl;
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
                cout << " " << i << " | ";
            }
            else
            {
                cout << i << " | ";
            }
            for (int j = 0; j < palyameret; j++)
            {
                // TODO átállítani majd == re mert ez ideiglenes
                if (palya[i][j] == nullptr || palya[i][j]->OsszesElem().size() == 0)
                {
                    cout << 0 << " | ";
                }
                else
                {
                    // int szam = rand() % (palyameret * palyameret - 2 + 1) + 2;
                    // TODO majd itt nem lesz elég csak a palya i j edik elemét kiíratni
                    int szam = palya[i][j]->ElsoElem()->getSzint();
                    if (szam >= 10)
                    {
                        cout << szam << "| ";
                    }
                    else
                    {
                        cout << szam << " | ";
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

    void palyaMozgatasa()
    {
        cout << "palyaMozgatasa" << endl;
        vector<pair<int, int>> mozgatasElolenyek = elolenyHelyek();
        cout << mozgatasElolenyek.size() << endl;

        for (int i = 0; i < mozgatasElolenyek.size(); i++)
        {
            int sor = mozgatasElolenyek[i].first;
            int oszlop = mozgatasElolenyek[i].second;
            Eloleny *eloleny = palya[sor][oszlop]->ElsoElem();
            cout << "Eloleny: " << eloleny->getEro() << endl;
            cout << "Helye: " << mozgatasElolenyek[i].first << ", " << mozgatasElolenyek[i].second << endl;
            palya[sor][oszlop] = nullptr;
            // palya[sor][oszlop] = new Helyek();
            // ide jön az új hely re lépés véletlenszerűen, 0 fel 1 jobbra 2 lefele 3-balra

            // Lehet hogy elírtam a sor oszlopokat, vagy nem,tudom

            int veletlenMerre = rand() % 4;
            cout << "Veletlen erteke: " << veletlenMerre << endl;
            switch (veletlenMerre)
            {
            case 0:
                if (sor - 1 < 0)
                {
                    sor = palyameret - 1;
                }
                else
                {
                    sor--;
                }
                cout << sor << ", " << oszlop << endl;
                // itt a baj, mert a hozzáadás null ponternél összecsuklik, meg kell nézni hogy van e elem, ha nincs new Eloleny
                // Ha már van akkor hozzaadEloleny
                palya[sor][oszlop] = new Helyek(eloleny);

                cout << "uj helye: " << sor << ", " << oszlop << endl;
                cout << palya[sor][oszlop]->ElsoElem()->getEro() << endl;
                // palya[sor][oszlop] = new Helyek(eloleny);
                break;
            case 1:
                if (oszlop + 1 >= palyameret)
                {
                    oszlop = 0;
                }
                else
                {
                    oszlop++;
                }
                cout << sor << ", " << oszlop << endl;

                palya[sor][oszlop] = new Helyek(eloleny);

                cout << "uj helye: " << sor << ", " << oszlop << endl;
                cout << palya[sor][oszlop]->ElsoElem()->getEro() << endl;
                // palya[sor][oszlop]->hozaadEloleny(eloleny);
                break;
            case 2:
                if (sor + 1 >= palyameret)
                {
                    sor = 0;
                }
                else
                {
                    sor++;
                }
                cout << sor << ", " << oszlop << endl;

                palya[sor][oszlop] = new Helyek(eloleny);

                cout << "uj helye: " << sor << ", " << oszlop << endl;
                cout << palya[sor][oszlop]->ElsoElem()->getEro() << endl;
                // palya[sor][oszlop]->hozaadEloleny(eloleny);
                break;
            case 3:
                if (oszlop - 1 < 0)
                {
                    oszlop = palyameret - 1;
                }
                else
                {
                    oszlop--;
                }
                cout << sor << ", " << oszlop << endl;

                palya[sor][oszlop] = new Helyek(eloleny);
                cout << "uj helye: " << sor << ", " << oszlop << endl;
                cout << palya[sor][oszlop]->ElsoElem()->getEro() << endl;
                // palya[sor][oszlop]->hozaadEloleny(eloleny);
                break;
            default:
                break;
            }
        }
        /*
        Eloleny *eloleny = palya[2][3]->ElsoElem();
        palya[2][3]->elveszEloleny();
        eloleny->setSzint(4);
        palya[3][3]->hozaadEloleny(eloleny);
        korokSzama++;
        vector<Eloleny *> elolenyek = palya[3][3]->OsszesElem();
        cout << palya[3][3]->ElsoElem()->getSzint() << endl;
        cout << palya[3][3]->OsszesElem()[1]->getSzint() << endl;
        cout << palya[3][3]->OsszesElem().size() << endl;
        cout << "Elso: " << elolenyek[0]->getSzint() << endl;
        cout << "Masodik: " << elolenyek[1]->getSzint() << endl;
        cout << "elmozgatott hely: " << palya[2][3]->OsszesElem().size() << endl;
        */
    }

    int getKorokSzama()
    {
        return korokSzama;
    }
    void elolenyekElhelyezese()
    {

        while (elolenydb > 0)
        {
            vector<pair<int, int>> uresPalyaHelyek = uresHelyekMerre();

            int i = rand() % uresPalyaHelyek.size();

            int sor = uresPalyaHelyek[i].first;
            int oszlop = uresPalyaHelyek[i].second;
            int ero = rand() % 100;
            palya[sor][oszlop] = new Helyek(ero);
            elolenydb--;
            // cout << palya[sor][oszlop]->ElsoElem()->getEro() << endl;
        }
    }
    vector<pair<int, int>> uresHelyekMerre()
    {

        vector<pair<int, int>> uresHelyek;
        for (int i = 0; i < palyameret; i++)
        {
            for (int j = 0; j < palyameret; j++)
            {
                if (palya[i][j] == nullptr)
                {
                    uresHelyek.push_back(make_pair(i, j));
                }
            }
        }
        return uresHelyek;
    }
    vector<pair<int, int>> elolenyHelyek()
    {
        vector<pair<int, int>> elolenyHelyek;
        for (int i = 0; i < palyameret; i++)
        {
            for (int j = 0; j < palyameret; j++)
            {
                if (palya[i][j] != nullptr)
                {
                    elolenyHelyek.push_back(make_pair(i, j));
                }
            }
        }
        return elolenyHelyek;
    }
};
