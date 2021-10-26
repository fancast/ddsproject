/* RTDS stand in example */

#include <stdio.h>
#include <iostream>
#include "sharedmemory.cpp"
using namespace std;

class RtsStandIn {

private:
    float *command_signals;
    int total_signals;
    Smio sm;

public:

    RtsStandIn()
    {
        total_signals = 128;
        sm = new Smio();
    }

    RtsStandIn(size_t size)
    {
        total_signals = size;
        Smio shared_memory_io(total_signals);
        sm = shared_memory_io;
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