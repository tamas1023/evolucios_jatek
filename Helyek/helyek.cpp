
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
    Helyek()
    {
        hely.push_back(new Eloleny());
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
        hely.pop_back();
    }
    vector<Eloleny *> OsszesElem()
    {
        return hely;
    }
    ~Helyek();
};
