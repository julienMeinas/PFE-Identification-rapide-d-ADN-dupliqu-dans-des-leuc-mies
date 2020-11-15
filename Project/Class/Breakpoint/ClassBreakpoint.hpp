#include <string>
#include <gatb/gatb_core.hpp>



class ClassBreakpoint
{
    public:
    ClassBreakpoint(list < list<std::string> > result);
    void Breakpoint();
    void BreakpointSequence(list<std::string> sequence);
    void analyse(std::string elementMemoirePrecedent, std::string elementMemoireSuivant, int nbInGroupOfN);
    void displayResult();
    std::map<std::string, int> getMap();





    private:
    list < list<std::string> > m_sequences;
    std::map<std::string, int> m_result;
};
