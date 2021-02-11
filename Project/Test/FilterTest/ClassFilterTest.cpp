#include "stdio.h"
#include "assert.h"
#include <iostream>
#include <gatb/gatb_core.hpp>
#include "../../Class/Filter/ClassFilter.hpp"


void
splitTest()
{
    ClassFilter* filtre = new ClassFilter(2, "transcript", "sequencesFile");
    string s1 = "1;2;3";
    list<string> s1Split = filtre->split(s1, ";");
    assert(s1Split.size() == 3);
    list<string>::iterator itr = s1Split.begin();
    assert(*itr == "1");
    itr++;
    assert(*itr == "2");
    itr++;
    assert(*itr == "3");
}


void
filterTest()
{
    ClassFilter* filtre = new ClassFilter(10, "Project/Test/FilterTest/transcriptTest.fa", "Project/Test/FilterTest/sequencesTest.fa");
    assert(filtre->getResult().size() == 0);
    filtre->Filter(0.9, 100000, 10);
    assert(filtre->getResult().size() == 1);
}


int main() {
    splitTest();
    filterTest();
    std::cout << "**************************" << "\n";
    std::cout << "Class Filter Test réussi" << "\n";
    std::cout << "**************************" << "\n";
}