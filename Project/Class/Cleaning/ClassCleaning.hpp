#include <string>
#include <gatb/gatb_core.hpp>

class ClassCleaning
{
    public:
    ClassCleaning(list < list<std::string> > result);
    void Cleaning();
    list<std::string> CleaningSequence(list<std::string> sequence);
    void displayResult();
    list < list<std::string> > getResult();
    std::string findPosition(std::string elementMemoire, std::string element);
    list<string> split (string s, string delimiter);

    private:
    list < list<std::string> > m_result;

};
