#include <string>
#include <gatb/gatb_core.hpp>
#include "BreakPoint.hpp"



class ClassBreakpoint
{
    public:
    ClassBreakpoint(list < list<int> > result, list< list< list<int> > > sequenceBeforeCleaning);
    void Breakpoint();
    void BreakpointSequence(list<int> sequence);
    void analyse(int elementMemoirePrecedent, int elementMemoireSuivant, int nbInGroupOfN, list<int> sequence);
    void displayResult();
    std::map<std::string, BreakPoint*> getMap();




    private:
    list < list<int> > m_sequences;
    list < list< list<int> > > m_sequenceBeforeCleaning;
    std::map<std::string, BreakPoint*> m_result;
    int m_cpt;
};
