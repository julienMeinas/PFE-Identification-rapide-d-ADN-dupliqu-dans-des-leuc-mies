#include <gatb/gatb_core.hpp>
#include <string>
#include <iostream>
#include <fstream>

#include "ClassFilter.hpp"

using namespace std;

static const size_t span = KMER_SPAN(0);


ClassFilter::ClassFilter(int kmerSize, string bankTranscript, string bankSequences)
{
  m_kmerSize = kmerSize;
  m_bankTranscript = bankTranscript;
  m_bankSequences = bankSequences;
  TransformationFile.open ("Project/Results/Transformation.txt");
}

void ClassFilter::CreateBloomFilter()
{
  std::cout << "create bloom filter : " << '\n';
  int bloomsize = 1000000;
  int nhash=4;
  m_bloom = new bloom_type(bloomsize,nhash);

  IBank* transcript = Bank::open (m_bankTranscript);
  LOCAL (transcript);

  // We declare a kmer model with a given span size.
  Kmer<span>::ModelDirect model (m_kmerSize);

  // We declare an iterator on a given sequence.
  Kmer<span>::ModelDirect::Iterator itKmer (model);

  // We create an iterator over this bank.
  ProgressIterator<Sequence> itFLT3 (*transcript);

  // We loop over sequences.
  for (itFLT3.first(); !itFLT3.isDone(); itFLT3.next())
  {
      // We set the data from which we want to extract kmers.
      itKmer.setData (itFLT3->getData());

      // We iterate the kmers.
      for (itKmer.first(); !itKmer.isDone(); itKmer.next())
      {
          m_bloom->insert(itKmer->value());
      }
  }
}


void ClassFilter::CreateHashMap()
{
  std::cout << "create hashMap transcript : " << '\n';

  int position = 0;

  IBank* transcript = Bank::open (m_bankTranscript);
  LOCAL (transcript);

  // We declare a kmer model with a given span size.
  Kmer<span>::ModelDirect model (m_kmerSize);

  // We declare an iterator on a given sequence.
  Kmer<span>::ModelDirect::Iterator itKmer (model);

  // We create an iterator over this bank.
  ProgressIterator<Sequence> itFLT3 (*transcript);

  // We loop over sequences.
  for (itFLT3.first(); !itFLT3.isDone(); itFLT3.next())
  {
      // We set the data from which we want to extract kmers.
      itKmer.setData (itFLT3->getData());

      // We iterate the kmers.
      for (itKmer.first(); !itKmer.isDone(); itKmer.next())
      {
        m_hashMapTranscript[model.toString(itKmer->value())] = position;
        position++;
      }
  }
}



void ClassFilter::Filter(float p)
{
  CreateBloomFilter();
  CreateHashMap();
  std::cout << "on réalise le filtre ici : " << '\n';
  IBank* sequences = Bank::open (m_bankSequences);
  LOCAL (sequences);

  u_int64_t nbSequences = 0;

  // We declare a kmer model with a given span size.
  Kmer<span>::ModelDirect model (m_kmerSize);

  // We declare an iterator on a given sequence.
  Kmer<span>::ModelDirect::Iterator itKmer (model);

  // We create an iterator over this bank.
  ProgressIterator<Sequence> itSeq (*sequences);

  // We loop over sequences.
  for (itSeq.first(); !itSeq.isDone(); itSeq.next())
  {
      // We set the data from which we want to extract kmers.
      itKmer.setData (itSeq->getData());
      u_int64_t nbKmers     = 0;
      u_int64_t nbPresence  = 0;

      // We iterate the kmers.
      for (itKmer.first(); !itKmer.isDone(); itKmer.next())
      {
          nbKmers++;
          if(m_bloom->contains(itKmer->value())) {
            nbPresence++;
          }
      }
      if((double)nbPresence/nbKmers > p) {
          std::string transformation = "";
          itKmer.setData (itSeq->getData());
          for (itKmer.first(); !itKmer.isDone(); itKmer.next())
          {
              int position = m_hashMapTranscript[model.toString (itKmer->value())];
              if(!position){
                transformation.append("N ");
              }
              else{
                transformation.append(std::to_string(position));
                transformation.append(" ");
              }
          }
          TransformationFile << transformation << "\n\n";
      }
      nbSequences++;
  }
  TransformationFile.close();
  cout << "FOUND " << nbSequences << " sequences" << endl;
}

/**
TODO : Créer une banque de données avec seulement les gènes FLT3 (resultat final de la classe)
*/
