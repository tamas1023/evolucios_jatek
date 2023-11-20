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
                palya[i].push_back(new Helyek());
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
                if (palya[i][j]->OsszesElem().size() == 0)
                {
                    cout << 0 << " | ";
                }
                else
                {
                    // int szam = rand() % (palyameret * palyameret - 2 + 1) + 2;
                    // TODO majd itt nem lesz elég csak a palya i j edik elemét kiíratni
                    int szam = palya[i][j]->ElsoElem()->getSzint();
                    if (szam < 0)
                    {
                        if (szam == -1)
                        {
                            cout << "X | ";
                        }
                        else
                        {
                            cout << "E | ";
                        }
                    }
                    else
                    {
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
        try
        {
            vector<pair<int, int>> mozgatasElolenyek = elolenyHelyek();
            // cout << mozgatasElolenyek.size() << endl;

            for (int i = 0; i < mozgatasElolenyek.size(); i++)
            {
                int sor = mozgatasElolenyek[i].first;
                int oszlop = mozgatasElolenyek[i].second;

                // a + élet miatt meg egy helyen több élőlény is lehet
                // cout << "Osszes elem lekeres elott" << endl;
                vector<Eloleny *> elolenyek = palya[sor][oszlop]->OsszesElem();
                // cout << elolenyek.size() << endl;
                int sikerestorlesek = 0;
                for (int j = elolenyek.size() - 1; j >= 0; j--)
                {
                    // ezért kérjük le újra az összes elemet, mert a törlést mi lekezeljük a helyeknél,
                    // de a pályába nem, és ez okoz problémát
                    // elolenyek = palya[sor][oszlop]->OsszesElem();
                    Eloleny *eloleny = elolenyek[j];
                    // cout << "Kivalasztott eloleny" << endl;
                    if (eloleny->getSzint() < 0)
                    {
                        // ha -1 akkor az ero noveles,
                        // ha -2 akkor az +1 elet
                        // cout << "Szint kisebb mint 0" << endl;
                        if (eloleny->getSzint() == -1)
                        {
                            eloleny->setMozgatotte(true);
                        }
                        else
                        {
                            eloleny->setMozgatotte(true);
                        }
                    }

                    // ha nincs mozgatva
                    if (!eloleny->getMozgatotte())
                    {
                        // cout << "Ha nincs mozgatva" << endl;
                        eloleny->setMozgatotte(true);
                        // cout << "Palya sor oszlop torles elott" << endl;
                        //  itt azert mert ha törlés volt, akkor "elcsúszás történik",
                        //  mert az elolenyek nem frissul, de a palya igen és itt keletkezik az elotás
                        //  de ezzel ezt kiküszöbölhetjük
                        int seged = j;
                        /*
                        if (sikerestorlesek > 0)
                        {
                            seged -= sikerestorlesek;
                        }
                        */
                        palya[sor][oszlop]->elveszElolenyHatul(seged);
                        sikerestorlesek++;
                        // cout << "torles utan" << endl;
                        int veletlenMerre = rand() % 4;
                        // cout << "Mozgas elott" << endl;
                        // cout << eloleny->getSzint() << endl;
                        // cout << eloleny->getEro() << endl;
                        // cout << eloleny->getElet() << endl;
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
                            // cout << "Hozzaadas elott" << endl;
                            // cout << sor << " " << oszlop << endl;
                            palya[sor][oszlop]->hozaadEloleny(eloleny);
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
                            // cout << "Hozzaadas elott" << endl;
                            // cout << sor << " " << oszlop << endl;
                            palya[sor][oszlop]->hozaadEloleny(eloleny);
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
                            // cout << "Hozzaadas elott" << endl;
                            // cout << sor << " " << oszlop << endl;
                            palya[sor][oszlop]->hozaadEloleny(eloleny);
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
                            // cout << "Hozzaadas elott" << endl;
                            // cout << sor << " " << oszlop << endl;
                            palya[sor][oszlop]->hozaadEloleny(eloleny);
                            break;
                        default:
                            break;
                        }
                    }
                    else
                    {
                        // cout << "Mozgatva volt" << endl;
                    }
                    // majd harcoláskor vissza kell állítani a motgatotte változót hamisra
                }

                // Eloleny *eloleny = palya[sor][oszlop]->ElsoElem();
                // palya[sor][oszlop]->elveszEloleny();

                // int veletlenMerre = rand() % 4;
                //  cout << "Veletlen erteke: " << veletlenMerre << endl;
            }
            /*
            for (int i = 0; i < palyameret; i++)
            {
                for (int j = 0; j < palyameret; j++)
                {
                    cout << palya[i][j]->OsszesElem().size() << ", Elemek: ";
                    int k = palya[i][j]->OsszesElem().size();
                    for (int l = 0; l < k; l++)
                    {
                        cout << palya[i][j]->OsszesElem()[l]->getEro() << ", ";
                    }
                    cout << endl;
                }
                cout << endl;
            }
            */
            // cout << "------------------------------------" << endl;
            // cout << "Harc" << endl;
            for (int i = 0; i < palyameret; i++)
            {
                for (int j = 0; j < palyameret; j++)
                {
                    // cout << "Hol esik ossze: " << palya[i][j]->OsszesElem().size() << endl;
                    if (palya[i][j]->OsszesElem().size() > 1)
                    {
                        // cout << "Harc a tulelesert" << endl;
                        palya[i][j]->Harc();
                    }
                    else
                    {
                        if (palya[i][j]->OsszesElem().size() == 1)
                        {
                            // cout << "Mozgatas beallitas" << endl;
                            // cout << "Meret: " << palya[i][j]->OsszesElem().size() << endl;
                            palya[i][j]->ElsoElem()->setMozgatotte(false);
                        }
                    }
                }
            }
            // cout << "Harc utan" << endl;
            korokSzama++;
            if (korokSzama % 10 == 0)
            {
                int veletlenErositesekDB;
                if (palyameret > 4 && palyameret <= 6)
                {
                    veletlenErositesekDB = rand() % 2 + 1;
                }
                else
                {
                    veletlenErositesekDB = rand() % 3 + 1;
                }
                vector<pair<int, int>> uresPalyaHelyek = uresHelyekMerre();
                if (!(uresPalyaHelyek.size() < veletlenErositesekDB))
                {
                    for (int i = 0; i < veletlenErositesekDB; i++)
                    {
                        uresPalyaHelyek = uresHelyekMerre();
                        int k = rand() % uresPalyaHelyek.size();
                        int sor = uresPalyaHelyek[k].first;
                        int oszlop = uresPalyaHelyek[k].second;
                        int veletpenErosites = -1 * (rand() % 10 + 1);
                        // ha -1 akkor az ero noveles,
                        // ha -2 akkor az +1 elet
                        // És itt van 20 % esélye hogy +1 életet csiáljon a játék
                        // A maradék 80% ban erőt csinál majd a játék
                        if (veletpenErosites < -8)
                        {
                            veletpenErosites = -2;
                        }
                        else
                        {
                            veletpenErosites = -1;
                        }

                        // ilyenkor módosítani kel majd a harcot
                        // palya[sor][oszlop]->hozaadEloleny(new Eloleny(veletpenErosites));
                        palya[sor][oszlop] = new Helyek(veletpenErosites);
                    }
                }

                for (int i = 0; i < palyameret; i++)
                {
                    for (int j = 0; j < palyameret; j++)
                    {
                        if (palya[i][j]->OsszesElem().size() > 0)
                        {
                            palya[i][j]->SzintLepes();
                        }
                    }
                }
            }
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
        }

        // cout << "palyaMozgatasa" << endl;

        // cout << "------------------------------------" << endl;
        // cout << "Uj palya: " << endl;
        /*
        for (int i = 0; i < palyameret; i++)
        {
            for (int j = 0; j < palyameret; j++)
            {
                cout << palya[i][j]->OsszesElem().size() << ", Elemek: ";
                int k = palya[i][j]->OsszesElem().size();
                for (int l = 0; l < k; l++)
                {
                    cout << palya[i][j]->OsszesElem()[l]->getEro() << ", ";
                }
                cout << endl;
            }
            cout << endl;
        }
        */

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
        // cout << "elolenyek elhelyezese: " << endl;
        while (elolenydb > 0)
        {
            vector<pair<int, int>> uresPalyaHelyek = uresHelyekMerre();
            // cout << uresPalyaHelyek.size() << endl;
            int i = rand() % uresPalyaHelyek.size();

            // cout << "I erteke: " << i << endl;

            int sor = uresPalyaHelyek[i].first;
            int oszlop = uresPalyaHelyek[i].second;
            // Ezzel egy véletlen számot generál 0 és 20 között,
            // majd hozzáad ehhez 20-at, ami 20 és 40 közötti tartományt eredményez.
            int ero = rand() % 21 + 20;
            palya[sor][oszlop] = new Helyek(ero);
            elolenydb--;
            // cout << palya[sor][oszlop]->ElsoElem()->getEro() << endl;
        }
    }
    vector<pair<int, int>> uresHelyekMerre()
    {
        // cout << "ures helyek: " << endl;
        vector<pair<int, int>> uresHelyek;
        for (int i = 0; i < palyameret; i++)
        {
            for (int j = 0; j < palyameret; j++)
            {
                if (palya[i][j]->OsszesElem().size() == 0)
                {
                    uresHelyek.push_back(make_pair(i, j));
                }
            }
        }
        return uresHelyek;
    }
    vector<pair<int, int>> elolenyHelyek()
    {
        // cout << "elolenyHelyek: " << endl;
        vector<pair<int, int>> elolenyHelyek;
        for (int i = 0; i < palyameret; i++)
        {
            for (int j = 0; j < palyameret; j++)
            {
                if (palya[i][j]->OsszesElem().size() > 0)
                {
                    // cout << palya[i][j]->OsszesElem().size() << endl;
                    elolenyHelyek.push_back(make_pair(i, j));
                }
            }
        }
        return elolenyHelyek;
    }

    int getElolenyDB()
    {
        int db = 0;
        for (int i = 0; i < palyameret; i++)
        {
            for (int j = 0; j < palyameret; j++)
            {
                int seged = 0;
                if (palya[i][j]->OsszesElem().size() > 0)
                {
                    seged = 0;
                    vector<Eloleny *> elolenyek = palya[i][j]->OsszesElem();
                    for (int k = 0; k < palya[i][j]->OsszesElem().size(); k++)
                    {
                        if (elolenyek[k]->getSzint() > 0)
                        {
                            seged++;
                        }
                    }
                }
                db += seged;
                // db += palya[i][j]->OsszesElem().size();
            }
        }
        return db;
    }
};
