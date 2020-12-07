#include <string.h>
#include "Class/Filter/ClassFilter.hpp"
#include "Class/Cleaning/ClassCleaning.hpp"
#include "Class/Breakpoint/ClassBreakpoint.hpp"

#define STR_URI_SEQUENCES               "-sequences"
#define PERCENTAGE_SIMILARITY_FLT3      0.3
#define FILTRE_DUPLICATION_OCCURENCE_1  1
#define DISPLAY_SEQUENCE                0
#define DISPLAY_SEQUENCE_BEFORE_CLEAN   0



// une première version d'affichage du resultat qui sera bien sûr modifié
// par la suite
void displayResult(std::map<std::string, BreakPoint*> mapResult, std::string nomPatient, int nbSeqence, int filtreOccurence1, int kmer_size) {
  ofstream m_resultFile;
  nomPatient.replace(8, 4, "Results");
  m_resultFile.open (nomPatient + ".json");
  std::string data = "{\"name\" : \"" + nomPatient + "\",\n ";
  data += "\"numberSequencesAnalysed\" : \"" + std::to_string(nbSeqence) + "\",\n ";

  int nbSequenceDefectueuse = 0;
  for(std::map<std::string, BreakPoint*>::iterator i=mapResult.begin(); i!=mapResult.end(); ++i) {
    if(i->second->getOccurence() == 1) {
      if(filtreOccurence1 != 1) {
        nbSequenceDefectueuse += i->second->getOccurence();
      }
    }
    else{
        nbSequenceDefectueuse += i->second->getOccurence();
    }
  }
  data += "\"numberTandemDuplication\" : \"" + std::to_string(nbSequenceDefectueuse) + "\",\n ";
  data += "\"détails\" : \n[\n";
  for(std::map<std::string, BreakPoint*>::iterator i=mapResult.begin(); i!=mapResult.end(); ++i) {
    if(i->second->getOccurence() == 1) {
      if(filtreOccurence1 != 1) {
        data += i->second->displayResult(kmer_size);
        data += ",\n";
        if(DISPLAY_SEQUENCE == 1) {
          m_resultFile << i->second->displaySequences();
        }
        if(DISPLAY_SEQUENCE_BEFORE_CLEAN == 1) {
          m_resultFile << i->second->displaySequencesBeforeCleaning();
        }
      }
    }
    else{
        data += i->second->displayResult(kmer_size);
        data += ",\n";
        if(DISPLAY_SEQUENCE == 1) {
          m_resultFile << i->second->displaySequences();
        }
        if(DISPLAY_SEQUENCE_BEFORE_CLEAN == 1) {
          m_resultFile << i->second->displaySequencesBeforeCleaning();
        }
    }
  }
  data += "],\n \"percentage\" : \"" + std::to_string((double)nbSequenceDefectueuse/nbSeqence*100) + "\"}";
  m_resultFile << data;
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
      //filtre.displayResult();


      // étape 2 : nettoyage des données
      ClassCleaning clean(filtre.getResult());
      clean.Cleaning();

      // étape 3 : recherche des points d'arrets
      ClassBreakpoint breakpoint(clean.getResult(), filtre.getResult());
      breakpoint.Breakpoint();


      displayResult(breakpoint.getMap(), options->getStr(STR_URI_SEQUENCES), clean.getResult().size(), FILTRE_DUPLICATION_OCCURENCE_1, options->getInt(STR_KMER_SIZE));
      std::cout << "taille avant : " << filtre.getResult().size() << '\n';
      std::cout << "taille après : " << clean.getResult().size() << '\n';





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
