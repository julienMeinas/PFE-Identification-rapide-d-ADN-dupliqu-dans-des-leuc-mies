#include "ClassCleaning.hpp"
#include <iostream>
#include <string>


using namespace std;


/**
Classe permettant de réaliser l'étape 2 c'est à dire de nettoyer
l'ensemble de séquences afin d'y voir plus clair pour la recherche
des points d'arrets
*/
ClassCleaning::ClassCleaning(list < list< list<int> > > result)
{
  m_list = result;
}


void ClassCleaning::Cleaning()
{
  std::cout << "Nettoyage de la liste de sequences FLT3 : " << '\n';
  list< list<int> > res;
  list< list< list<int> > >::iterator itr;
  for(itr = m_list.begin(); itr != m_list.end(); itr++) {
    list< list<int> > sequence = *itr;
    res.push_back(CleaningSequence(sequence));
  }
  m_result = res;
  std::cout << "Nettoyage fini" << "\n\n";
}

list< int > ClassCleaning::CleaningSequence(list< list<int> > sequence)
{
  list< int > res;
  list< list<int> >::iterator it;

  int elementMemoire  = 0;
  int startGroupOfN   = 0;
  int endGroupOfN     = 0;
  int nbEndGroupOfN   = 0;

  for(it=sequence.begin(); it!= sequence.end(); it++)
  {
    list<int> positions = *it;
    // si l'élément présent est un "N"
    if(positions.front() == -1) {
      // si nous ne somme plus dans le premier groupe de N
      if(startGroupOfN != 0) {
        // on passe dans l'état "Dans un groupe de N"
        endGroupOfN = 1;
        // on stock le nombre de N
        nbEndGroupOfN++;
      }
    }
    // si on rencontre autre chose que N
    else{
      // on rencontre une position donc on sort de l'état "Premier groupe de N"
      startGroupOfN = 1;
      // Si on vient de sortir de l'état "Dans un groupe de N"
      if(endGroupOfN == 1) {
        // on sort de cet état donc on ajoute les N
        endGroupOfN = 0;
        // on ajoute les N
        for(int i = 0; i < nbEndGroupOfN; i++) {
          res.push_back(-1);
        }
        // on réinitalise le nombre de N à O
        nbEndGroupOfN = 0;
        // l'élément précedent est un N (= -1)
        elementMemoire = -1;
      }
      // on nettoie l'élement présent en fonction de l'élément precedent
      int elementClean = findPosition(elementMemoire, positions);
      // on ajoute l'element nettoyé
      res.push_back(elementClean);
      // l'élement présent devient l'élément précedent
      elementMemoire = positions.front();
    }
  }
  return res;
}


int ClassCleaning::findPosition(int elementMemoire, list<int> element){
  // si l'élément précedent est unitilisable
  if(elementMemoire == -1 || elementMemoire == 0) {
    // si la position est unique alors on la renvoie
    if(element.size() == 1) {
      return element.front();
    }
    // sinon on est incapable de connaitre la position alors on renvoie "N"
    else{
      return -1;
    }
  }

  // sinon si l'élément précedent est defini
  // si on a une seule position
  if(element.size() == 1) {
    return element.front();
  }
  // si on a plusieurs positions
  list<int>::iterator itr;
  // pour chaque position possible
  for(itr = element.begin(); itr != element.end(); itr++) {
    int nb = *itr;
    // si la position presente est la suite de la position precedente
    if(elementMemoire + 1 == nb) {
      //alors on renvoie la position
      return nb;
    }
  }
  // si on a trouvé aucune position coherente alors on renvoie N
  return -1;
}



list < list< int > > ClassCleaning::getResult()
{
  return m_result;
}


void ClassCleaning::displayResult() {
  std::cout << "listes en retour après le nettoyage : " << '\n';
  std::cout << m_result.size() << '\n';
  list< list<int> >::iterator itr;
  for(itr = m_result.begin(); itr != m_result.end(); itr++) {
    list<int> sequence = *itr;
    list<int>::iterator it;
    for(it = sequence.begin(); it != sequence.end(); it++) {
      int pos = *it;
      if(pos == -1) {
        std::cout << "N" << " ";
      }
      else{
        std::cout << *it << " ";
      }
    }
    std::cout << "\n" << '\n';
  }
}
