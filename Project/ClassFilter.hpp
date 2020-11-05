#include <string>
#include <gatb/gatb_core.hpp>

typedef Bloom<Kmer<>::Type> bloom_type;

class ClassFilter
{
    public:
    ClassFilter(int kmerSize, std::string bankTranscript, std::string bankSequences);
    void CreateBloomFilter();
    void Filter();


    private:
    std::string m_bankTranscript;
    std::string m_bankSequences;
    int m_kmerSize;
    bloom_type *m_bloom;

};
