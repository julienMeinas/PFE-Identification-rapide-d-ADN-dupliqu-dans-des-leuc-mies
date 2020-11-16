#include <gatb/gatb_core.hpp>
#include <iostream>
#include <fstream>
#include <string.h>
#include "Class/Filter/ClassFilter.hpp"
#include "Class/Cleaning/ClassCleaning.hpp"
#include "Class/Breakpoint/ClassBreakpoint.hpp"

#define STR_URI_SEQUENCES               "-sequences"
#define PERCENTAGE_SIMILARITY_FLT3      0.3

/*Example: main -in gatb-core/gatb-core/test/db/reads1.fa -kmer-size 11 */


// une première version d'affichage du resultat qui sera bien sûr modifié
// par la suite
void displayResult(std::map<std::string, BreakPoint*> mapResult, std::string nomPatient, int nbSeqence) {
  ofstream m_resultFile;
  nomPatient.replace(8, 4, "Results");
  std::cout << "Rapport écrit dans le fichier " << nomPatient << '\n';
  m_resultFile.open (nomPatient + ".txt");
  m_resultFile << "Compte rendu des sequences " << nomPatient << " : " << "\n\n";
  m_resultFile << "Nombre de sequences FLT3 annalysé : " << nbSeqence << "\n\n";
  int nbSequenceDefectueuse = 0;
  for(std::map<std::string, BreakPoint*>::iterator i=mapResult.begin(); i!=mapResult.end(); ++i) {
    nbSequenceDefectueuse += i->second->getOccurence();
  }
  m_resultFile << "Nombre de duplications en tandem : " << nbSequenceDefectueuse << "\n";
  m_resultFile << "Détaille de ces duplications : " << "\n";
  for(std::map<std::string, BreakPoint*>::iterator i=mapResult.begin(); i!=mapResult.end(); ++i) {
    m_resultFile << i->second->displayResult();
  }
  m_resultFile << (double)nbSequenceDefectueuse/nbSeqence*100
    << " % des cellules sont atteintes" << '\n';
}


int main(int argc, char* argv[]) {
  std::cout << "Run main program \n" << '\n';

  /** We create a command line parser. */
  OptionsParser parser ("KmerTest");
  parser.push_back (new OptionOneParam (STR_KMER_SIZE, "kmer size",           true));
  parser.push_back (new OptionOneParam (STR_URI_INPUT, "transcript input",    true));
  parser.push_back (new OptionOneParam (STR_URI_SEQUENCES, "sequences input", true));

  try
  {
      /** We parse the user options. */
      IProperties* options = parser.parse (argc, argv);

      // étape 1 : Filtrer les données
      ClassFilter filtre(options->getInt(STR_KMER_SIZE), options->getStr(STR_URI_INPUT), options->getStr(STR_URI_SEQUENCES));
      filtre.Filter(PERCENTAGE_SIMILARITY_FLT3);

      // étape 2 : nettoyage des données
      ClassCleaning clean(filtre.getResult());
      clean.Cleaning();

      // étape 3 : recherche des points d'arrets
      ClassBreakpoint breakpoint(clean.getResult());
      breakpoint.Breakpoint();



      displayResult(breakpoint.getMap(), options->getStr(STR_URI_SEQUENCES), clean.getResult().size());







    }
    catch (OptionFailure& e)
    {
        return e.displayErrors (std::cout);
    }
    catch (Exception& e)
    {
        std::cerr << "EXCEPTION: " << e.getMessage() << std::endl;
    }

}
