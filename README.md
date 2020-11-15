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


- Lancement du code : <br/>
$ make main <br/>
$ ./Project/main -in ["FLT3 file"]  -kmer-size [Kmer_size] -sequences ["Sequences file"]
