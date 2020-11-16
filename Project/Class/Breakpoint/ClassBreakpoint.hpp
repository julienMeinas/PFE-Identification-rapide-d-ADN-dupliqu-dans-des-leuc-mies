#include <string>
#include <gatb/gatb_core.hpp>
#include "BreakPoint.hpp"



class ClassBreakpoint
{
    public:
    ClassBreakpoint(list < list<std::string> > result);
    void Breakpoint();
    void BreakpointSequence(list<std::string> sequence);
    void analyse(std::string elementMemoirePrecedent, std::string elementMemoireSuivant, int nbInGroupOfN);
    void displayResult();
    std::map<std::string, BreakPoint*> getMap();
    void addPoint(std::string elementMemoirePrecedent, std::string elementMemoireSuivant, int nbInGroupOfN);




    private:
    list < list<std::string> > m_sequences;
    std::map<std::string, BreakPoint*> m_result;
};
