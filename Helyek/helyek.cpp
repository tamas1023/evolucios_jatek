
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
    Eloleny *ElsoElem()
    {
        return this->hely[0];
    }
    ~Helyek();
};
