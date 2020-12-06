#include <string>
#include <list>
#include <map>
#include <iostream>
#include "BreakPoint.hpp"



class ClassBreakpoint
{
    public:
    ClassBreakpoint(std::list < std::list<int> > result, std::list< std::list< std::list<int> > > sequenceBeforeCleaning);
    void Breakpoint();
    void BreakpointSequence(std::list<int> sequence);
    double verificationSequence(std::list<int> sequence);
    void analyse(int elementMemoirePrecedent, int elementMemoireSuivant, int nbInGroupOfN, std::list<int> sequence);
    void displayResult();
    std::map<std::string, BreakPoint*> getMap();




    private:
    std::list < std::list<int> > m_sequences;
    std::list < std::list< std::list<int> > > m_sequenceBeforeCleaning;
    std::map<std::string, BreakPoint*> m_result;
    int m_cpt;
};
