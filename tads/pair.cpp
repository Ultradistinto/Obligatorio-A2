#include <iostream>
#include <string>

using namespace std;

template <typename T1, typename T2>
class myPair
{
private:
    T1 fst;
    T2 snd;

public:
    myPair(T1 fst, T2 snd)
    {
        this->fst = fst;
        this->snd = snd;
    }

    myPair()
    {
        this->fst = T1();
        this->snd = T2();
    }

    T2 getSnd()
    {
        return snd;
    }

    T1 getFst()
    {
        return fst;
    }
};
