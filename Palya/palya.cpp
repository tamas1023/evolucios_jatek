#include <iostream>
#include <vector>

#include "../Helyek/helyek.cpp"

using namespace std;

class Palya
{
    int palyameret;
    vector<vector<Helyek *>> palya;

public:
    Palya(const int &palyameret) : palyameret(palyameret)
    {
        for (int i = 0; i < palyameret; i++)
        {
            palya.push_back(vector<Helyek *>()); //
            for (int j = 0; j < palyameret; j++)
            {
                palya[i].push_back(new Helyek());
            }
        }
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
};
