#include <iostream>
#include <string>
using namespace std;

class myTrio
{
private:
    int fst;
    int snd;
    string trd;

public:
    myTrio(int fst, int snd, string trd)
    {
        this->fst = fst;
        this->snd = snd;
        this->trd = trd;
    }
    myTrio()
    {
        this->fst = 0;
        this->snd = 0;
        this->trd = "";
    }
    int getSnd()
    {
        return snd;
    }
    int getFst()
    {
        return fst;
    }
    string getTrd()
    {
        return trd;
    }
};