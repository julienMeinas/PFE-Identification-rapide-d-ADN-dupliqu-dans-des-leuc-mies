#include <string>
#include <gatb/gatb_core.hpp>

class BreakPoint
{
  public:
  BreakPoint(int previousPoint, int nextPoint, int nbN, list< list< list<int> > > sequenceBeforeCleaning);
  int getPreviousPoint();
  int getNextPoint();
  int getNbN();
  int getOccurence();
  void addPoint();
  void addSequence(list<int> sequence);
  void addSequenceBeforeCleaning(list< list<int> > sequenceBeforeCleaning);
  std::string displayResult();
  std::string displaySequences();
  std::string displaySequencesBeforeCleaning();
  void addCptToList(int cpt);
  int contains(int var, list<int> list);
  void getList();

  private:
  int m_previousPoint;
  int m_nextPoint;
  int m_nbN;
  int m_occurence;
  list< list<int> > m_sequence;
  list< list< list<int> > > m_sequenceBeforeCleaning;
  list<int> m_listCpt;

};
