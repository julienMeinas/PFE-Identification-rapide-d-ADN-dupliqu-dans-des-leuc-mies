#include "BreakPoint.hpp"

// Class Breakpoint
BreakPoint::BreakPoint(int previousPoint, int nextPoint, int nbN) {
  m_previousPoint = previousPoint;
  m_nextPoint = nextPoint;
  m_nbN = nbN;
  m_occurence = 1;
}


int BreakPoint::getPreviousPoint() {
  return m_previousPoint;
}

int BreakPoint::getNextPoint() {
  return m_nextPoint;
}

int BreakPoint::getNbN() {
  return m_nbN;
}

void BreakPoint::addPoint() {
  m_occurence++;
}

int BreakPoint::getOccurence() {
  return m_occurence;
}

std::string BreakPoint::displayResult() {
  std::string res = "";
  res = ("Positions du breakpoint : [" + std::to_string(m_previousPoint) +
  " - " + std::to_string(m_nextPoint) + "], nombre de N entre les deux : " + std::to_string(m_nbN)
   + ", occurence : " + std::to_string(m_occurence) + '\n');
  return res;
}
