class Eloleny
{
    int ero;

public:
    Eloleny()
    {
        this->ero = 10;
    };

    void setEro(int e)
    {
        ero = e;
    }

    int getEro()
    {
        return ero;
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