#include <iostream>
#include <vector>

#include "../Helyek/helyek.cpp"

using namespace std;

class Palya
{
    int palyameret;
    int elolenydb;
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
        cout << "Palya letrejott!" << endl;
        elolenyekElhelyezese();
    };

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
                    int szam = palya[i][j]->ElsoElem()->getEro();
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

    void elolenyekElhelyezese()
    {
        cout << elolenydb << endl;
        while (elolenydb > 0)
        {
            vector<pair<int, int>> uresPalyaHelyek = uresHelyekMerre();
            cout << elolenydb << endl;
            int i = rand() % uresPalyaHelyek.size();
            cout << i << endl;
            int row = uresPalyaHelyek[i].first;
            int col = uresPalyaHelyek[i].second;
            palya[row][col] = new Helyek();
            elolenydb--;
            cout << palya[row][col]->ElsoElem()->getEro() << endl;
        }
    }
    vector<pair<int, int>> uresHelyekMerre()
    {
        cout << "ures kereses" << endl;
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
