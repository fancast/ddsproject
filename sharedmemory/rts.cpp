/* RTS stand in example */

#include <stdio.h>
#include <iostream>
#include "sharedmemory.cpp"
using namespace std;

class RtsStandIn {

private:
    size_t total_signals;
    Smio sm;

public:

    RtsStandIn()
    {
        total_signals = 128;
        //sm = Smio(total_signals);
    }

    RtsStandIn(size_t size)
    {
        total_signals = size;
        //sm = Smio(total_signals);
    }


    auto write_Value(float* signals, int& size)
    {
        sm.write_Signals(signals, size);
    }

    auto read_Value()
    {
        return sm.get_Base_Address();
    }

};