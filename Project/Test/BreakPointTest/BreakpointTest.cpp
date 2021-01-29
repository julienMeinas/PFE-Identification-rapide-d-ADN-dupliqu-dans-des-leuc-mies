#include "stdio.h"
#include "assert.h"
#include <iostream>
#include "../../Class/Breakpoint/BreakPoint.hpp"


int previous = 170;
int next = 165;
int nbN = 5;
int occurence = 1;
BreakPoint* breakpoint = new BreakPoint(previous, next, nbN);


void
getPreviousPointTest()
{
    assert(breakpoint->getPreviousPoint()==previous);
}

void
getNextPointTest()
{
    assert(breakpoint->getNextPoint()==next);
}

void
getNbNTest()
{
    assert(breakpoint->getNbN()==nbN);
}

void
getOccurenceTest()
{
    assert(breakpoint->getOccurence()==occurence);
    breakpoint->addPoint();
    occurence++;
    assert(breakpoint->getOccurence()==occurence);
}


void 
containsTest()
{
    std::list<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    assert(breakpoint->contains(3, list) == 1);
    assert(breakpoint->contains(42, list) == 0);
}



int main() {
    getPreviousPointTest();
    getNextPointTest();
    getNbNTest();
    getOccurenceTest();
    containsTest();
    std::cout << "Test BreakPoint réussi" << "\n";
}