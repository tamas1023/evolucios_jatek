class Eloleny
{
    // a limit az 100 erő a szintlépéshez
    int ero;
    // szintlépésnél az erőből leveszünk 100 at, és szintetlépünk
    int szint;
    int elet;
    bool mozgatotte = false;

public:
    Eloleny()
    {
        this->ero = rand() % 100;
        this->szint = 1;
        this->elet = 1;
    };
    Eloleny(int ero)
    {
        if (ero < 0)
        {
            // ha -1 akkor az ero noveles,
            // ha -2 akkor az +1 elet
            if (ero == -1)
            {
                this->ero = rand() % 21 + 20;
                this->szint = -1;
                this->elet = 1;
            }
            else
            {
                this->ero = ero;
                this->szint = -2;
                this->elet = 1;
            }
        }
        else
        {
            this->ero = ero;
            this->szint = 1;
            this->elet = 1;
        }
    }
    bool operator>(const Eloleny &masik) const
    {
        return szint > masik.szint || (szint == masik.szint && ero > masik.ero);
    }
    void setEro(int e)
    {
        ero = e;
    }
    int getEro()
    {
        return ero;
    }
    int getSzint()
    {
        return szint;
    }
    void setSzint(int sz)
    {
        szint = sz;
    }
    int getElet()
    {
        return elet;
    }
    void setElet(int e)
    {
        elet = e;
    }
    void setMozgatotte(bool m)
    {
        mozgatotte = m;
    }
    bool getMozgatotte()
    {
        return mozgatotte;
    }
};
