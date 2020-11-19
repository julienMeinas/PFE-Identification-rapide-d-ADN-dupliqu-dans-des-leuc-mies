#include <string>
#include <gatb/gatb_core.hpp>

class ClassCleaning
{
    public:
    ClassCleaning(list < list< list<int> > > result);
    void Cleaning();
    list< int > CleaningSequence(list< list<int> > sequence);
    void displayResult();
    list < list<int> > getResult();
    int findPosition(int elementMemoire, list<int> element);

    private:
    list < list< list<int> > > m_list;
    list < list<int> > m_result;

};
