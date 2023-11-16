#include <iostream>
#include <vector>

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
                if (palya[i][j] == nullptr)
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
        cout << "IDEEEE" << endl;
        Eloleny *eloleny = palya[2][3]->ElsoElem();
        palya[2][3] = nullptr;
        eloleny->setSzint(4);
        palya[3][3]->addEloleny(eloleny);
        korokSzama++;
        vector<Eloleny *> elolenyek = palya[3][3]->OsszesElem();
        cout << palya[3][3]->ElsoElem()->getSzint() << endl;
        cout << palya[3][3]->OsszesElem().size() << endl;
        cout << "Elso: " << elolenyek[0]->getSzint() << endl;
        cout << "Masodik: " << elolenyek[1]->getSzint() << endl;
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

            int row = uresPalyaHelyek[i].first;
            int col = uresPalyaHelyek[i].second;
            palya[row][col] = new Helyek();
            elolenydb--;
            // cout << palya[row][col]->ElsoElem()->getEro() << endl;
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
};
