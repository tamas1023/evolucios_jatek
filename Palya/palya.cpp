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
                if (palya[i][j]->OsszesElem().size() == 0)
                {
                    cout << 0 << " | ";
                }
                else
                {
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
            for (int i = 0; i < mozgatasElolenyek.size(); i++)
            {
                int sor = mozgatasElolenyek[i].first;
                int oszlop = mozgatasElolenyek[i].second;
                vector<Eloleny *> elolenyek = palya[sor][oszlop]->OsszesElem();
                for (int j = elolenyek.size() - 1; j >= 0; j--)
                {
                    // ezért kérjük le újra az összes elemet, mert a törlést mi lekezeljük a helyeknél,
                    // de a pályába nem
                    Eloleny *eloleny = elolenyek[j];
                    if (eloleny->getSzint() < 0)
                    {
                        // ha -1 akkor az ero noveles,
                        // ha -2 akkor az +1 elet
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
                        eloleny->setMozgatotte(true);
                        //  itt azert mert ha törlés volt, akkor "elcsúszás történik",
                        //  mert az elolenyek nem frissul, de a palya igen és itt keletkezik az elotás
                        //  de ezzel ezt kiküszöbölhetjük
                        int seged = j;
                        palya[sor][oszlop]->elveszElolenyHatul(seged);
                        int veletlenMerre = rand() % 4;
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
                }
            }
            // cout << "Harc" << endl;
            for (int i = 0; i < palyameret; i++)
            {
                for (int j = 0; j < palyameret; j++)
                {
                    if (palya[i][j]->OsszesElem().size() > 1)
                    {
                        palya[i][j]->Harc();
                    }
                    else
                    {
                        if (palya[i][j]->OsszesElem().size() == 1)
                        {
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
            // Ezzel egy véletlen számot generál 0 és 20 között,
            // majd hozzáad ehhez 20-at, ami 20 és 40 közötti tartományt eredményez.
            int ero = rand() % 21 + 20;
            palya[sor][oszlop] = new Helyek(ero);
            elolenydb--;
        }
    }
    vector<pair<int, int>> uresHelyekMerre()
    {
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
        vector<pair<int, int>> elolenyHelyek;
        for (int i = 0; i < palyameret; i++)
        {
            for (int j = 0; j < palyameret; j++)
            {
                if (palya[i][j]->OsszesElem().size() > 0)
                {
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
            }
        }
        return db;
    }
};
