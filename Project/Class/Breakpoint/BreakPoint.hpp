#include <string>
#include <list>

class BreakPoint
{
  public:
  BreakPoint(int previousPoint, int nextPoint, int nbN);
  int getPreviousPoint();
  int getNextPoint();
  int getNbN();
  int getOccurence();
  void addPoint();
  std::string displayResult(int kmer_size);
  int contains(int var, std::list<int> list);
  void getList();

  private:
  int m_previousPoint;
  int m_nextPoint;
  int m_breakPoint;
  int m_nbN;
  int m_occurence;

};
