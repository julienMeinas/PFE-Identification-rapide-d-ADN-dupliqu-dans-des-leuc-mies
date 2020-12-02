#include <string>
#include <list>

class BreakPoint
{
  public:
  BreakPoint(int previousPoint, int nextPoint, int nbN, std::list< std::list< std::list<int> > > sequenceBeforeCleaning);
  int getPreviousPoint();
  int getNextPoint();
  int getNbN();
  int getOccurence();
  void addPoint();
  void addSequence(std::list<int> sequence);
  void addSequenceBeforeCleaning(std::list< std::list<int> > sequenceBeforeCleaning);
  std::string displayResult(int kmer_size);
  std::string displaySequences();
  std::string displaySequencesBeforeCleaning();
  void addCptToList(int cpt);
  int contains(int var, std::list<int> list);
  void getList();

  private:
  int m_previousPoint;
  int m_nextPoint;
  int m_breakPoint;
  int m_nbN;
  int m_occurence;
  std::list< std::list<int> > m_sequence;
  std::list< std::list< std::list<int> > > m_sequenceBeforeCleaning;
  std::list<int> m_listCpt;

};
