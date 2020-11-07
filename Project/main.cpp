#include <gatb/gatb_core.hpp>
#include <iostream>
#include <string.h>
#include "ClassFilter.hpp"

#define STR_URI_SEQUENCES   "-sequences"

/*Example: main -in gatb-core/gatb-core/test/db/reads1.fa -kmer-size 11 */

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
      filtre.Filter(0.15);



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
