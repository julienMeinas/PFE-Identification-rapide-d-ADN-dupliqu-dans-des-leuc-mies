#include <gatb/gatb_core.hpp>
#include <string>
#include <iostream>
#include <fstream>

#include "ClassFilter.hpp"

using namespace std;

static const size_t span = KMER_SPAN(0);

/**
Classe permettant de réaliser l'étape 1 c'est à dire de filtrer
l'ensemble de séquences afin de ne garder que les gènes FLT3.
*/
ClassFilter::ClassFilter(int kmerSize, string bankTranscript, string bankSequences)
{
  m_kmerSize = kmerSize;
  m_bankTranscript = bankTranscript;
  m_bankSequences = bankSequences;
  TransformationFile.open ("Project/Results/Transformation.txt");
}

/**
Permet de créer le filtre de bloom dans la variable m_bloom
puis d'inserer les kmers du gène FLT3 dans le filtre de bloom

Le filtre de bloom est très effacace en temps pour vérifier la
présence d'un kmer dans le gène FLT3 car on utilise des tables
de bits pour stocker les kmers.
*/
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


/**
Permer de créer une table de hashage contenant les kmers
dans la variable m_hashMapTranscript
clé (String) : kmer
valeur (int) : position dans le gène FLT3séquence et des


exemple:
Si on a la séquence suivante ACGTCCC et des kmer de taille 3
alors la table de hashage sera la suivante:
{
"ACG" : 1,
"CGT" : 2,
"GTC" : 3,
"TCC" : 4,
"CCC" : 5
}
*/
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
        if(m_hashMapTranscript[model.toString(itKmer->value())] != "") {
          m_hashMapTranscript[model.toString(itKmer->value())] = m_hashMapTranscript[model.toString(itKmer->value())].append(";");
          m_hashMapTranscript[model.toString(itKmer->value())] = m_hashMapTranscript[model.toString(itKmer->value())].append(std::to_string(position));

        }
        else{
          m_hashMapTranscript[model.toString(itKmer->value())] = std::to_string(position);
          position++;
        }
      }
  }
}


/**
Permet de filtrer un fichier de sequences en ne gardant
seulement les séquences FLT3.
une séquences correspond au gène FLT3 si la ressemblance
dépasse p.

On va vérifier si chaque séquence correspond au gène FLT3
grâce au Filtre de Bloom, si la ressemblance est validé
on va écrire dans un fichier la séquence sous la forme suivante:
Pour chaque kmer de cette séquence on va écrire N si le kmer
n'est pas présent dans le gène FLT3 sinon la position de ce
kmer dans le gène.

exemple de fichier en sorti:
N N N 1 2 3 4 5 N N N 6 8 N N N ...
*/
void ClassFilter::Filter(float p)
{
  CreateBloomFilter();
  CreateHashMap();
  std::cout << "on réalise le filtre ici : " << '\n';
  IBank* sequences = Bank::open (m_bankSequences);
  LOCAL (sequences);

  u_int64_t nbSequences = 0;
  u_int64_t nbSequencesFLT3 = 0;

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
          nbSequencesFLT3++;
          std::string transformation = "";
          itKmer.setData (itSeq->getData());
          for (itKmer.first(); !itKmer.isDone(); itKmer.next())
          {
              std::string position = m_hashMapTranscript[model.toString (itKmer->value())];
              if(position == ""){
                transformation.append("N ");
              }
              else{
                transformation.append(position);
                transformation.append(" ");
              }
          }
          TransformationFile << transformation << "\n\n";
      }
      nbSequences++;
  }
  cout << "FOUND " << nbSequences << " sequences" << endl;
  std::cout << nbSequencesFLT3 << " Sequences FLT3 write in Project/Results/Transformation.txt" << '\n';
  TransformationFile.close();
}
