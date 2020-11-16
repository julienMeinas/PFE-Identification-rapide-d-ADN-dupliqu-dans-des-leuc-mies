#include <string>
#include <gatb/gatb_core.hpp>

class BreakPoint
{
  public:
  BreakPoint(int previousPoint, int nextPoint, int nbN);
  int getPreviousPoint();
  int getNextPoint();
  int getNbN();
  int getOccurence();
  void addPoint();
  std::string displayResult();

  private:
  int m_previousPoint;
  int m_nextPoint;
  int m_nbN;
  int m_occurence;

};
