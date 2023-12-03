
#include <vector>
#include <iostream>
#include "../Eloleny/eloleny.cpp"

using namespace std;
class Helyek
{
    vector<Eloleny *> hely;

private:
public:
    Helyek(){

    };
    Helyek(Eloleny *eloleny)
    {
        hely.push_back(eloleny);
    }
    Helyek(int ero)
    {
        hely.push_back(new Eloleny(ero));
    }
    Eloleny *ElsoElem()
    {
        return this->hely[0];
    }
    void hozaadEloleny(Eloleny *eloleny)
    {
        try
        {
            hely.push_back(eloleny);
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
        }
    }
    void elveszEloleny()
    {
        hely.erase(hely.begin());
    }
    void elveszElolenyHatul(int j)
    {
        if (j == hely.size())
        {
            j = hely.size() - 1;
        }
        hely.erase(hely.begin() + j);
    }
    vector<Eloleny *> OsszesElem()
    {
        return hely;
    }
    void Harc()
    {

        int maxSzint = 0;
        int maxEro = 0;
        int maxIndex = 0;
        for (int i = 0; i < hely.size(); i++)
        {
            hely[i]->setMozgatotte(false);
            if (hely[i]->getSzint() > maxSzint || (hely[i]->getSzint() == maxSzint && hely[i]->getEro() > maxEro))
            {
                maxSzint = hely[i]->getSzint();
                maxEro = hely[i]->getEro();
                maxIndex = i;
            }
        }
        for (int i = 0; i < hely.size(); i++)
        {
            if (i != maxIndex)
            {
                hely[maxIndex]->setEro(hely[maxIndex]->getEro() + hely[i]->getEro());
                if (hely[i]->getSzint() == -2)
                {
                    hely[maxIndex]->setElet(hely[maxIndex]->getElet() + 1);
                }
            }
        }
        // itt azért megy visszafele, mert amikor eltávolítunk egy elemet egy vektorból,
        // akkor az összes elemet eltolja utána, hogy kitöltse a rést, ha nem visszafele lépkednénk
        // akkor át tudnánk ugorni egyes Élőlényeken
        for (int i = hely.size() - 1; i >= 0; i--)
        {
            if (i != maxIndex)
            {
                if (hely[i]->getElet() > 1)
                {
                    hely[i]->setElet(hely[i]->getElet() - 1);
                }
                else
                {
                    hely.erase(hely.begin() + i);
                }
            }
        }
    }
    void SzintLepes()
    {
        for (int i = 0; i < hely.size(); i++)
        {
            if (hely[i]->getEro() >= 100)
            {
                hely[i]->setSzint(hely[i]->getSzint() + 1);
                hely[i]->setEro(hely[i]->getEro() - 100);
            }
        }
    }
    ~Helyek();
};
