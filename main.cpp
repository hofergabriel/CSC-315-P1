/*
    ***** pa1.cpp *****

Application to test the C++ large integer class.

Author: John M. Weiss, Ph.D.
Class:  CSC 315 Data Structures & Algorithms (PA#1)
Date:   Spring 2018

Modifications:
*/

//-----------------------------------------------------------------------------

#include <chrono>
#include <iostream>
using namespace std;

#include "largeint.h"

//-----------------------------------------------------------------------------
//          ***** main program to test LargeInt class *****
//-----------------------------------------------------------------------------

int main( int argc, char *argv[] )
{
    using namespace std::chrono;
    
    auto start = steady_clock::now();
    
    for(unsigned i = 0; i < 10000; i++)
    {
        LargeInt A = i;
        LargeInt B = i;
        
        A += B;
        A *= B;
    }
    
    auto end = steady_clock::now();
    
    std::cout << "That took: " << duration_cast<milliseconds>(end-start).count() << " milliseconds\n";

    return 0;
}
