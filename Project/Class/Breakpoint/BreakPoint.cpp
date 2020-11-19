#include "BreakPoint.hpp"

// Class Breakpoint
BreakPoint::BreakPoint(int previousPoint, int nextPoint, int nbN, list< list< list<int> > > sequenceBeforeCleaning) {
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

void BreakPoint::addSequence(list<int> sequence) {
  m_sequence.push_back(sequence);
}

void BreakPoint::addSequenceBeforeCleaning(list< list<int> > sequenceBeforeCleaning) {
  m_sequenceBeforeCleaning.push_back(sequenceBeforeCleaning);
}


int BreakPoint::getOccurence() {
  return m_occurence;
}

std::string BreakPoint::displayResult() {
  std::string res = "";
  res = ("\n\nPositions du breakpoint : [" + std::to_string(m_previousPoint) +
  " - " + std::to_string(m_nextPoint) + "], nombre de N entre les deux : " + std::to_string(m_nbN)
   + ", occurence : " + std::to_string(m_occurence) + '\n');
  return res;
}


std::string BreakPoint::displaySequences() {
  std::string res;
  list< list<int> >::iterator itr;
  int cpt = 1;
  res = res + "\n\n\nSeqence après le nettoyage : \n";
  for(itr = m_sequence.begin(); itr != m_sequence.end(); itr++) {
    list<int> sequence = *itr;
    list<int>::iterator it;
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


int BreakPoint::contains(int var, list<int> list) {
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
  list< list< list<int> > >::iterator itr;
  int cpt = 1;
  int indice = 1;
  res = res + "\n\n\nsequence avant le nettoyage : \n";
  for (itr=m_sequenceBeforeCleaning.begin(); itr != m_sequenceBeforeCleaning.end(); itr++)
  {
    if(contains(cpt, m_listCpt) == 1){
      list<list<int>>sequence=*itr;
      list< list<int> >::iterator it;
      res = res + std::to_string(indice++) + " : ";
      for (it=sequence.begin(); it != sequence.end(); it++)
      {
         list<int> positions = *it;
         int nb = positions.size();
         list<int>::iterator i;
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
