
#include <vector>

#include "../Eloleny/eloleny.cpp"

using namespace std;
class Helyek
{
    vector<Eloleny *> hely;

private:
    /* data */
public:
    // ezek a helyek lesznek beletenni az egyes pálya helyekre, és ennek lesz vektor a oda jönnek az előlények
    Helyek(){
        // hely.push_back(new Eloleny());
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
        hely.push_back(eloleny);
    }
    void elveszEloleny()
    {
        hely.erase(hely.begin());
        // hely.pop_back();
    }
    vector<Eloleny *> OsszesElem()
    {
        return hely;
    }
    void Harc()
    {
        int maxEro = 0;
        int maxIndex = 0;
        for (int i = 0; i < hely.size(); i++)
        {
            if (hely[i]->getEro() > maxEro)
            {
                maxEro = hely[i]->getEro();
                maxIndex = i;
            }
        }
        for (int i = 0; i < hely.size(); i++)
        {
            if (i != maxIndex)
            {
                hely[maxIndex]->setEro(hely[maxIndex]->getEro() + hely[i]->getEro());
            }
        }
        // itt azért megy visszafele, mert amikor eltávolítunk egy elemet egy vektorból,
        // akkor az összes elemet eltolja utána, hogy kitöltse a rést, ha nem visszafele lépkednénk
        // akkor át tudnánk ugorni egyes Élőlényeken
        for (int i = hely.size() - 1; i >= 0; i--)
        {
            if (i != maxIndex)
            {
                hely.erase(hely.begin() + i);
            }
        }
    }
    ~Helyek();
};
