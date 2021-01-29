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

std::string BreakPoint::displayResult(int kmer_size) {
  std::string res = "{\"BreakpointPosition\" : \"" + std::to_string(m_previousPoint + kmer_size) + "\",";
  res = res += "\"pointBefore\" : \"" + std::to_string(m_previousPoint) + "\",";
  res = res += "\"pointAfter\" : \"" + std::to_string(m_nextPoint) + "\",";
  res = res += "\"numberN_Between\" : \"" + std::to_string(m_nbN) + "\",";
  res = res += "\"occurence\" : \"" + std::to_string(m_occurence) + "\"}";
  return res;
}



int BreakPoint::contains(int var, std::list<int> list) {
  std::list<int>::iterator itr;
  for(itr = list.begin(); itr != list.end(); itr++) {
    int el = *itr;
    if(el == var){
      return 1;
    }
  }
  return 0;
}
