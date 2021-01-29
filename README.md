- UE : Projet de fin d'étude

- Sujet : Identification rapide d'ADN dupliqué dans des leucémies

- Description : Les leucémies myéloïdes aiguës sont des cancers touchant les cellules du
sang et donc cette localité particulière ne permet pas de suivre l’évolution de la
maladie par les techniques classiques d’imagerie médicale. Alors, afin de suivre
l’évolution de la maladie, on utilise une technique alternative qui consiste à
s’intéresser à des marqueurs génétiques de cellules malades. En effet, dans une
grande partie des cas de leucémies myéloïdes aiguës, la maladie est étroitement
liée à certaines duplications du gène FLT3, qui en font des marqueurs génétiques
pertinents à étudier, notamment afin de détecter des rechutes de la maladie ou
de suivre l’efficacité des traitements.
Notre objectif au cours de cette UE est donc de concevoir un algorithme permettant
de détecter la présence et le nombre duplications en tandem du gène FLT3.
Pour se faire nous allons utiliser nous aider d'un projet qui a été réalisé en
Python et créer un algorithme en C++ plus performant.



- Installation : <br/>
$ git clone https://github.com/julienMeinas/PFE-Identification-rapide-d-ADN-duplique-dans-des-leucemies <br/>
$ cd PFE-Identification-rapide-d-ADN-duplique-dans-des-leucemies/ <br/>
$ make gatb <br/>
$ make Project/main <br/>


- Lancement du code : <br/>
$ ./Project/main -in ["FLT3 file"]  -kmer-size [Kmer_size] -sequences ["Sequences file"]


- Compiler le test de BreakPoint : <br/>
$ g++ Project/Test/Breakpoint/BreakpointTest.cpp Project/Class/Breakpoint/ClassBreakpoint.cpp Project/Class/Breakpoint/BreakPoint.cpp -o BreakPointTest

exemple : 
./Project/main -kmer-size 15 -bloomsize 1000000 -nhash_bloom 10 -percentage_similarity_flt3 0.3 -percentage_fiability_seq 0.5 -sequences Project/Data/P10-L1808674D09.fastq.gz -transcript Project/Data/FLT3.fa

Options : 
-kmer-size : la longueur des kmers

-bloomsize : la longueur de notre filtre de bloom

-nhash_bloom : le nombre de fonctions hashages utilisé pour l'utilisation du filtre de bloom

-percentage_similarity_flt3 : le pourcentage de ressemblance que doit dépacer une séquence afin d'être considéré comme étant une séquence flt3

-percentage_fiability_seq : Le pourcentage de fiabilité (nombre de suite cohérente / nombre de suite, par exemple la suite 1, 2, 3, 6, 7 est fiable à 3/4 = 0.75) que doit dépaser chaque séquence pour être utilisé

-sequences les sequences à annalyser

-transcript : la sequence de base (FLT3)