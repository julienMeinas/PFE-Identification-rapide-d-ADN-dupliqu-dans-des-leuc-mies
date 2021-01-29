#include <gatb/gatb_core.hpp>
#include <string>
#include <cstring>


typedef Bloom<Kmer<>::Type> bloom_type;

class ClassFilter
{
    public:
    ClassFilter(int kmerSize, std::string bankTranscript, std::string bankSequences);
    void CreateBloomFilter(int bloomSize, int nhash);
    void Filter(float p, int bloomSize, int nhash);
    void CreateHashMap();
    void displayResult();
    list < list< list<int> > > getResult();
    list<string> split (string s, string delimiter);


    private:
    std::string m_bankTranscript;
    std::string m_bankTranscriptReverse;
    std::string m_bankSequences;
    int m_kmerSize;
    bloom_type *m_bloom;
    std::map<std::string, std::string> m_hashMapTranscript;
    list < list< list<int> > > result;
    ofstream TransformationFile;

};
