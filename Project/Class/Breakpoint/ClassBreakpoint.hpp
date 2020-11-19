#include <string>
#include <gatb/gatb_core.hpp>
#include "BreakPoint.hpp"



class ClassBreakpoint
{
    public:
    ClassBreakpoint(list < list<int> > result);
    void Breakpoint();
    void BreakpointSequence(list<int> sequence);
    void analyse(int elementMemoirePrecedent, int elementMemoireSuivant, int nbInGroupOfN);
    void displayResult();
    std::map<std::string, BreakPoint*> getMap();




    private:
    list < list<int> > m_sequences;
    std::map<std::string, BreakPoint*> m_result;
};
