/* EMC control stand in example */

#include <stdio.h>
#include <iostream>
#include "sharedmemory.cpp"
using namespace std;

class EmcStandIn {

private:
    int total_signals;
    Smio sm;

public:

    EmcStandIn()
    {
        total_signals = 128;
        sm = Smio(total_signals);
    }

    EmcStandIn(size_t size)
    {
        total_signals = size;
        sm = Smio(total_signals);
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