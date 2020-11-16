#include "ClassBreakpoint.hpp"



using namespace std;




/**
Classe permettant de réaliser l'étape 3 c'est à dire de trouver
les points d'arrets.
*/
ClassBreakpoint::ClassBreakpoint(list < list<std::string> > sequence)
{
  m_sequences = sequence;
}


/**
Pour chaque sequence on utilise la methode BreakpointSequence
pour trouver des points d'arrets
*/
void ClassBreakpoint::Breakpoint() {
  std::cout << "recherche de points d'arrets de la liste de sequences FLT3 : " << '\n';
  list<list<std::string>>::iterator itr;
  for (itr=m_sequences.begin(); itr != m_sequences.end(); itr++)
  {
    list<std::string> sequence = *itr;
    BreakpointSequence(sequence);
  }
  std::cout << "Recherche des points d'arrets fini !" << "\n\n";
}


/**
Permet de trouver un possible point d'arret sur la sequence
en parametre et la stocker dans la hashmap m_result
*/
void ClassBreakpoint::BreakpointSequence(list<std::string> sequence) {
  list<std::string>::iterator it;

  int inGroupOfN = 0;
  int nbInGroupOfN = 0;
  std::string elementMemoirePrecedent = "";
  std::string elementMemoire = "";
  for (it=sequence.begin(); it != sequence.end(); it++)
  {
    std::string element = *it;
    if(element == "N") {
      inGroupOfN = 1;
      nbInGroupOfN++;
      if(elementMemoire != "N") {
        elementMemoirePrecedent = elementMemoire;
      }
    }
    else{
      if(inGroupOfN == 1) {
        analyse(elementMemoirePrecedent, element, nbInGroupOfN);
        nbInGroupOfN = 0;
        inGroupOfN = 0;
      }
    }

    elementMemoire = element;
  }

}

/**
Permet de cibler sur la sequence, la partie qui contient
les "N" avec l'élement avant et après.
Cela nous permet de determiner si la défaillance est une
mutation ou une duplication en tandem avec la formule
elementPrecedent + nbDeN + 1 == elementSuivant (mutation)

s1 = 170 N N N N N N N N 179
s2 = 170 N N N N N N N N 139

s1 est une mutation car 170 + 8 + 1 = 179
s2 n'est pas une mutation car 170 + 8 + 1 != 139
  donc une possible duplication en tandem
*/
void ClassBreakpoint::analyse(std::string elementMemoirePrecedent, std::string elementMemoireSuivant, int nbInGroupOfN) {
  if(elementMemoireSuivant == "N" || elementMemoirePrecedent == "N" || elementMemoirePrecedent == "") {
    return;
  }
  if(std::stoi(elementMemoirePrecedent, nullptr, 10) + nbInGroupOfN + 1 == std::stoi(elementMemoireSuivant, nullptr, 10)) {
    // mutation
  }
  else{
    std::string key = elementMemoirePrecedent+elementMemoireSuivant+std::to_string(nbInGroupOfN);
    if(m_result[key] == 0) {
      BreakPoint *bp = new BreakPoint(std::stoi(elementMemoirePrecedent, nullptr, 10),
                                      std::stoi(elementMemoireSuivant, nullptr, 10),
                                      nbInGroupOfN);
      m_result[key] = bp;
    }
    else{
      m_result[key]->addPoint();
    }

  }
}


std::map<std::string, BreakPoint*> ClassBreakpoint::getMap() {
  return m_result;
}
