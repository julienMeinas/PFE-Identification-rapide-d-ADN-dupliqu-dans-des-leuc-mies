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
    sequencesBad.push_back(11);
    sequencesBad.push_back(4);
    sequencesBad.push_back(5);
    sequencesBad.push_back(6);
    assert(breakpoint->verificationSequence(sequencesBad) == (double)2/6);

    std::list< int > sequencesGood;
    sequencesGood.push_back(1);
    sequencesGood.push_back(2);
    sequencesGood.push_back(3);
    sequencesGood.push_back(4);
    sequencesGood.push_back(5);
    sequencesGood.push_back(6);
    assert(breakpoint->verificationSequence(sequencesGood) == (double)0/6);
}

void 
breakpointTest(ClassBreakpoint* breakpoint) 
{
    std::cout << breakpoint->getMap().size() << "\n";
    assert(breakpoint->getMap().size() == 0);
    breakpoint->Breakpoint(0.3);
    assert(breakpoint->getMap().size() == 1);
    std::map<std::string, BreakPoint*>::iterator i=breakpoint->getMap().begin();
    assert(i->second->getPreviousPoint() == 7);
    assert(i->second->getNextPoint() == 3);
    assert(i->second->getNbN() == 4);
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
    std::cout << "***************************" << "\n";
    std::cout << "Test ClassBreakPoint réussi" << "\n";
    std::cout << "***************************" << "\n";
}