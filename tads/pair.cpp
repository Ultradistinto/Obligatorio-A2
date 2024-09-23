#include <iostream>
#include <string>
using namespace std;

class myPair
{
private:
    int fst;
    int snd;

public:
    myPair(int fst, int snd)
    {
        this->fst = fst;
        this->snd = snd;
    }
    myPair()
    {
        this->fst = 0;
        this->snd = 0;
    }
    int getSnd()
    {
        return snd;
    }
    int getFst()
    {
        return fst;
    }
};