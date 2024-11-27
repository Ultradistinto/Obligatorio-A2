#pragma once

template <class T1, class T2>
struct Par
{
    T1 fst;
    T2 snd;

    Par() {}
    Par(T1 t1, T2 t2)
    {
        fst = t1;
        snd = t2;
    }
};