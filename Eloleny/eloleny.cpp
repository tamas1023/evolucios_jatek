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
    /*
void harc(vector<vector<Eloleny *>> &palya)
{
    for (int i = 0; i < palya.size(); i++)
    {
        for (int j = 0; j < palya[i].size(); j++)
        {
            for (int k = 0; k < palya[i].size(); k++)
            {
                if (j != k)
                {
                    if (palya[i][j]->getEro() > palya[i][k]->getEro())
                    {
                        palya[i][j]->setEro(palya[i][j]->getEro() + palya[i][k]->getEro());
                    }
                    else
                    {
                        palya[i][k]->setEro(palya[i][k]->getEro() + palya[i][j]->getEro());
                    }
                }
            }
        }
    }
}
*/
};
