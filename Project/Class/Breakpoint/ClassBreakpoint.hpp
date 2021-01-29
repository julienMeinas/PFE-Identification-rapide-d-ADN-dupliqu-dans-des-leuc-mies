#include <string>
#include <list>
#include <map>
#include <iostream>
#include "BreakPoint.hpp"



class ClassBreakpoint
{
    public:
    ClassBreakpoint(std::list < std::list<int> > result);
    void Breakpoint(double percentageFiabilitySequence);
    void BreakpointSequence(std::list<int> sequence, double percentageFiabilitySequence);
    double verificationSequence(std::list<int> sequence);
    void analyse(int elementMemoirePrecedent, int elementMemoireSuivant, int nbInGroupOfN, std::list<int> sequence, double percentageFiabilitySequence);
    void displayResult();
    std::map<std::string, BreakPoint*> getMap();




    private:
    std::list < std::list<int> > m_sequences;
    std::map<std::string, BreakPoint*> m_result;
    int m_cpt;
};
