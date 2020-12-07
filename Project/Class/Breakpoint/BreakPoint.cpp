#include "BreakPoint.hpp"

// Class Breakpoint
BreakPoint::BreakPoint(int previousPoint, int nextPoint, int nbN, std::list< std::list< std::list<int> > > sequenceBeforeCleaning) {
  m_previousPoint = previousPoint;
  m_nextPoint = nextPoint;
  m_nbN = nbN;
  m_occurence = 1;
  m_sequenceBeforeCleaning = sequenceBeforeCleaning;
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

void BreakPoint::addSequence(std::list<int> sequence) {
  m_sequence.push_back(sequence);
}

void BreakPoint::addSequenceBeforeCleaning(std::list< std::list<int> > sequenceBeforeCleaning) {
  m_sequenceBeforeCleaning.push_back(sequenceBeforeCleaning);
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


std::string BreakPoint::displaySequences() {
  std::string res;
  std::list< std::list<int> >::iterator itr;
  int cpt = 1;
  res = res + "\n\n\nSeqence après le nettoyage : \n";
  for(itr = m_sequence.begin(); itr != m_sequence.end(); itr++) {
    std::list<int> sequence = *itr;
    std::list<int>::iterator it;
    res = res + std::to_string(cpt++) + " : ";
    for(it = sequence.begin(); it != sequence.end(); it++) {
      int pos = *it;
      if(pos == -1) {
        res = res + "N ";
      }
      else{
        res = res + std::to_string(*it) + " ";
      }
    }
    res = res + "\n";
  }
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

std::string BreakPoint::displaySequencesBeforeCleaning(){
  std::string res;
  std::list< std::list< std::list<int> > >::iterator itr;
  int cpt = 1;
  int indice = 1;
  res = res + "\n\n\nsequence avant le nettoyage : \n";
  for (itr=m_sequenceBeforeCleaning.begin(); itr != m_sequenceBeforeCleaning.end(); itr++)
  {
    if(contains(cpt, m_listCpt) == 1){
      std::list< std::list<int> >sequence=*itr;
      std::list< std::list<int> >::iterator it;
      res = res + std::to_string(indice++) + " : ";
      for (it=sequence.begin(); it != sequence.end(); it++)
      {
         std::list<int> positions = *it;
         int nb = positions.size();
         std::list<int>::iterator i;
         for (i=positions.begin(); i != positions.end(); i++) {
           int position = *i;
           if(position == -1) {
             res = res + "N ";
           }
           else{
             res = res + std::to_string(position);
             if(nb > 1) {
               res = res + ";";
               nb--;
             }
           }
         }
         res = res + " ";
      }
      res = res + "\n";
      indice++;
    }
    cpt++;
  }
  return res;
}


void BreakPoint::addCptToList(int cpt) {
  m_listCpt.push_back(cpt);
}
