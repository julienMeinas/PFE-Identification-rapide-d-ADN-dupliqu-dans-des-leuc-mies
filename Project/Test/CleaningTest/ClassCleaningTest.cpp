#include "stdio.h"
#include "assert.h"
#include <iostream>
#include "../../Class/Cleaning/ClassCleaning.hpp"


void 
findPositionTest(ClassCleaning* clean)
{
    std::list< int > seq;
    seq.push_back(10);
    seq.push_back(55);
    seq.push_back(42);
    assert(clean->findPosition(41, seq) == 42);
    assert(clean->findPosition(54, seq) == 55);
    assert(clean->findPosition(9, seq) == 10);
}

void
cleaningSequenceTest(ClassCleaning* clean)
{
    std::list< std::list<int> > seq;
    std::list< int > s1;
    std::list< int > s2;
    std::list< int > s3;
    std::list< int > s4;
    std::list< int > s5;
    std::list< int > s6;
    std::list< int > s7;
    std::list< int > s8;
    std::list< int > s9;
    std::list< int > s10;
    std::list< int > s11;
    s1.push_back(-1);
    s2.push_back(-1);
    s3.push_back(-1);

    s4.push_back(2);
    s5.push_back(3);
    s5.push_back(11);

    s6.push_back(-1);
    s7.push_back(-1);

    s8.push_back(7);
    s9.push_back(8);

    s10.push_back(-1);
    s11.push_back(-1);

    seq.push_back(s1);
    seq.push_back(s2);
    seq.push_back(s3);
    seq.push_back(s4);
    seq.push_back(s5);
    seq.push_back(s6);
    seq.push_back(s7);
    seq.push_back(s8);
    seq.push_back(s9);
    seq.push_back(s10);
    seq.push_back(s11);
    
    assert(seq.size() == 11);
    std::list< int > sRes = clean->CleaningSequence(seq);
    assert(sRes.size() == 6);
    std::list< int >::iterator it;
    it = sRes.begin();
    assert(*it == 2);
    it++;
    assert(*it == 3);
    it++;
    assert(*it == -1);
    it++;
    assert(*it == -1);
    it++;
    assert(*it == 7);
    it++;
    assert(*it == 8);

}

int main() {
    std::list< std::list< std::list<int> > > sequences;
    std::list< std::list< int > > s1;
    std::list< std::list< int > > s2;
    sequences.push_back(s1);
    sequences.push_back(s2);
    ClassCleaning* clean = new ClassCleaning(sequences);
    findPositionTest(clean);
    cleaningSequenceTest(clean);
    std::cout << "**************************" << "\n";
    std::cout << "Class Cleaning Test réussi" << "\n";
    std::cout << "**************************" << "\n";
}