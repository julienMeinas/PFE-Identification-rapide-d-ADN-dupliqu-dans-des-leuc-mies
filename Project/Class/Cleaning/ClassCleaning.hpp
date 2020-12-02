#include <string>
#include <list>
#include <iostream>

class ClassCleaning
{
    public:
    ClassCleaning(std::list < std::list< std::list<int> > > result);
    void Cleaning();
    std::list< int > CleaningSequence(std::list< std::list<int> > sequence);
    void displayResult();
    std::list < std::list<int> > getResult();
    int findPosition(int elementMemoire, std::list<int> element);

    private:
    std::list < std::list< std::list<int> > > m_list;
    std::list < std::list<int> > m_result;

};
