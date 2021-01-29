#include <string.h>
#include "Class/Filter/ClassFilter.hpp"
#include "Class/Cleaning/ClassCleaning.hpp"
#include "Class/Breakpoint/ClassBreakpoint.hpp"

#define STR_URI_SEQUENCES               "-sequences"
#define STR_TRANSCRIPT                  "-transcript"
#define STR_BLOOMSIZE                   "-bloomsize"
#define STR_NBHASH_BLOOM                "-nhash_bloom"
#define STR_PERCENTAGE_SIMILARITY_FLT3  "-percentage_similarity_flt3"
#define STR_PERCENTAGE_FIABILITY_SEQ    "-percentage_fiability_seq"

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
      }
    }
    else{
        data += i->second->displayResult(kmer_size);
        data += ",\n";
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
  parser.push_back (new OptionOneParam (STR_URI_SEQUENCES, "sequences input", true));
  parser.push_back (new OptionOneParam (STR_TRANSCRIPT, "transcript input", true));
  parser.push_back (new OptionOneParam (STR_BLOOMSIZE, "bloom size", true));
  parser.push_back (new OptionOneParam (STR_NBHASH_BLOOM, "nb hash", true));
  parser.push_back (new OptionOneParam (STR_PERCENTAGE_SIMILARITY_FLT3, "percentage similarity flt3", true));
  parser.push_back (new OptionOneParam (STR_PERCENTAGE_FIABILITY_SEQ, "percentage fiability sequence", true));
  
  try
  {
      /** We parse the user options. */
      IProperties* options = parser.parse (argc, argv);
      int kmerSize = options->getInt(STR_KMER_SIZE);
      std:string sequencesFile = options->getStr(STR_URI_SEQUENCES);
      int bloomSize = options->getInt(STR_BLOOMSIZE);
      int nbHash_bloom = options->getInt(STR_NBHASH_BLOOM);
      int percentage_similarity_flt3 = options->getDouble(STR_PERCENTAGE_SIMILARITY_FLT3);
      int percentage_fiability_seq = options->getDouble(STR_PERCENTAGE_FIABILITY_SEQ);



      // étape 1 : Filtrer les données
      ClassFilter* filtre = new ClassFilter(kmerSize, sequencesFile, sequencesFile);
      filtre->Filter(percentage_similarity_flt3, bloomSize, nbHash_bloom);
      //filtre.displayResult();


      // étape 2 : nettoyage des données
      ClassCleaning* clean = new ClassCleaning(filtre->getResult());
      delete filtre;
      clean->Cleaning();

      // étape 3 : recherche des points d'arrets
      ClassBreakpoint* breakpoint = new ClassBreakpoint(clean->getResult());
      int size = clean->getResult().size();
      delete clean;
      breakpoint->Breakpoint(percentage_fiability_seq);


      //displayResult(breakpoint->getMap(), sequencesFile, size, FILTRE_DUPLICATION_OCCURENCE_1, kmerSize);
      delete breakpoint;





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
