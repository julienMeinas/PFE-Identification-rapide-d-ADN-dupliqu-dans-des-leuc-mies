#include "stdio.h"
#include "assert.h"
#include <iostream>
#include "../../Class/Breakpoint/ClassBreakpoint.hpp"


void
verificationSequenceTest(ClassBreakpoint* breakpoint)
{
    std::list< int > sequencesBad;
    sequencesBad.push_back(1);
    sequencesBad.push_back(2);
    sequencesBad.push_back(3);
    sequencesBad.push_back(4);
    sequencesBad.push_back(5);
    sequencesBad.push_back(6);
    assert(breakpoint->verificationSequence(sequencesBad) == (double)0/5);
}

void 
breakpointTest(ClassBreakpoint* breakpoint) 
{
    std::cout << breakpoint->getMap().size() << "\n";
    assert(breakpoint->getMap().size() == 0);
    breakpoint->Breakpoint(0.3);
    assert(breakpoint->getMap().size() == 1);
}



int main() {
    std::list< std::list< int > > sequences;
    std::list< int > sequencesMuatation;
    std::list< int > sequencesDuplication;
    // sequence avec mutation : 1 2 3 4 5 6 7 N N N N 12 13 14 
    sequencesMuatation.push_back(1);
    sequencesMuatation.push_back(2);
    sequencesMuatation.push_back(3);
    sequencesMuatation.push_back(4);
    sequencesMuatation.push_back(5);
    sequencesMuatation.push_back(6);
    sequencesMuatation.push_back(7);
    sequencesMuatation.push_back(-1);
    sequencesMuatation.push_back(-1);
    sequencesMuatation.push_back(-1);
    sequencesMuatation.push_back(-1);
    sequencesMuatation.push_back(12);
    sequencesMuatation.push_back(13);
    sequencesMuatation.push_back(14);
    sequences.push_back(sequencesMuatation);
    
    // sequence avec mutation : 1 2 3 4 5 6 7 N N N N 3 4 5 
    sequencesDuplication.push_back(1);
    sequencesDuplication.push_back(2);
    sequencesDuplication.push_back(3);
    sequencesDuplication.push_back(4);
    sequencesDuplication.push_back(5);
    sequencesDuplication.push_back(6);
    sequencesDuplication.push_back(7);
    sequencesDuplication.push_back(-1);
    sequencesDuplication.push_back(-1);
    sequencesDuplication.push_back(-1);
    sequencesDuplication.push_back(-1);
    sequencesDuplication.push_back(3);
    sequencesDuplication.push_back(4);
    sequencesDuplication.push_back(5);
    sequences.push_back(sequencesDuplication);

    ClassBreakpoint* breakpoint = new ClassBreakpoint(sequences);

    verificationSequenceTest(breakpoint);
    breakpointTest(breakpoint);
    std::cout << "Test ClassBreakPoint réussi" << "\n";
}