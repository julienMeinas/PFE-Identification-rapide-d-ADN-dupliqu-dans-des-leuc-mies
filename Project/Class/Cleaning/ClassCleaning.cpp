#include "ClassCleaning.hpp"
#include <iostream>
#include <string>


using namespace std;


/**
Classe permettant de réaliser l'étape 2 c'est à dire de nettoyer
l'ensemble de séquences afin d'y voir plus clair pour la recherche
des points d'arrets
*/
ClassCleaning::ClassCleaning(list < list<std::string> > result)
{
  m_result = result;
}


/**
Réalise le nettoyage de chaque sequence avec la méthode CleaningSequence
*/
void ClassCleaning::Cleaning() {
  std::cout << "Nettoyage de la liste de sequences FLT3 : " << '\n';
  list<list<std::string>> res;
  list<list<std::string>>::iterator itr;
  for (itr=m_result.begin(); itr != m_result.end(); itr++)
  {
    list<std::string> sequence = *itr;
    res.push_back(CleaningSequence(sequence));
  }
  m_result = res;
}


/**
Réalise le nettoyage de la sequence passé en parametre
*/
list<std::string> ClassCleaning::CleaningSequence(list<std::string> sequence) {
  list<std::string> res;
  list<std::string>::iterator it;

  std::string elementMemoire = "";
  int startGroupOfN = 0;
  int endGroupOfN = 0;
  int nbEndGroupOfN = 0;

  for (it=sequence.begin(); it != sequence.end(); it++)
  {
    std::string element = *it;
    if(element == "N") {
      if(startGroupOfN != 0) {
        endGroupOfN = 1;
        nbEndGroupOfN++;
      }
    }
    // si on rencontre autre chose que "N"
    else {
      startGroupOfN = 1;
      if(endGroupOfN == 1) {
        endGroupOfN = 0;
        for(int i = 0; i < nbEndGroupOfN; i++) {
          res.push_back("N");
        }
        nbEndGroupOfN = 0;
        elementMemoire = "N";
      }
      res.push_back(findPosition(elementMemoire, element));
      elementMemoire = element;
    }
  }
  return res;
}


/**
Realise le nettoyage d'une position si l'element present
contient plusieurs positions.
La position est déterminé en fonction de l'element précedent

exemple:
12 13   => 12 13
12 9;13 => 12 13
N  13   => N  13
*/
std::string ClassCleaning::findPosition(std::string elementMemoire, std::string element) {
  if(element == "N" || elementMemoire == "N" || elementMemoire == "") {
    return element;
  }
  list<std::string> elements = split(element, ";");

  list<std::string>::iterator itr;
  for (itr=elements.begin(); itr != elements.end(); itr++)
  {
    std::string nb = *itr;
    if(std::stoi(elementMemoire, nullptr, 10) + 1 == std::stoi(nb, nullptr, 10)) {
      return nb;
    }
  }
  return "N";
}


// for string delimiter
list<string> ClassCleaning::split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    list<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

/**
Permet d'afficher le resultat 
*/
void ClassCleaning::displayResult() {
  std::cout << "listes en retour après le nettoyage : " << '\n';
  list<list<std::string>>::iterator itr;
  for (itr=m_result.begin(); itr != m_result.end(); itr++)
  {
    list<std::string>tl=*itr;
    list<std::string>::iterator it;
    for (it=tl.begin(); it != tl.end(); it++)
    {
       cout<<*it;
       std::cout << " ";
    }
    std::cout << "\n\n" << '\n';
  }
}

list < list<std::string> > ClassCleaning::getResult() {
  return m_result;
}
