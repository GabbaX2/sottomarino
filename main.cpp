#include <iostream>
#include <ctime>
#include <cstdlib>

const int MEASURES = 50;
const int MIN_DEPTH = 5;
const int MAX_DEPTH = 20;

void measure_depth(int[]);

/*
 questa funzione stampa il grafico delle profondità della scansione passata come parametro.
le celle di acqua saranno rappresentate da '.', quelle di terra da '@'

il secondo parametro sono profondità e posizione del sottomarino
*/
void plot_depth(int[],int[]);

/*
funzione che fa lo smoothing dei dati letti. 

per i punti non estremi (non il primo e l'ultimo) dato il punto di posizione i, fa la media tra i, i-1 e i+1
per i punti estremi faccio la media tra l'estremo e due volte il suo adiacente. Nel caso della posizione 0, farò media tra i valori delle posizioni 0,1,1
*/
void smooth(int[]);

int main() {
  std::srand(std::time(nullptr));
  int depth[MEASURES] = {0};
  int sottomarino[2] = {5,0};
  char cmd; // contiene il comando dell'utente
  int punteggio = 0;
  
  measure_depth(depth);
  for(const auto v: depth) {
    std::cout << v<<" ";
  }
  std::cout << "\n";
  smooth(depth);
  plot_depth(depth,sottomarino);

  while(sottomarino[1]< MEASURES && sottomarino[0] < depth[sottomarino[1]]) {
    punteggio += sottomarino[0];
    std::cout << "cmd (w per andare verso la superficie, s per andare in profondità)> ";
    std::cin >> cmd;
  
    switch(cmd) {
      case 'w':
        sottomarino[0] -=1;
        break;
      case 's':
        sottomarino[0] += 1;
    }
    sottomarino[1] +=1;
    plot_depth(depth,sottomarino);
  }
  if (sottomarino[1] == MEASURES){
    std::cout << "Sei stato promosso a pomodoro con un punteggio di " << punteggio << ". congratulazioni!\n";
  } else {
    std::cout << "Sei stato destituito dal tuo incarico per aver distrutto il sottomarino affidatoti. il punteggio che ha realizzato è: "<<punteggio<< "\n";
  }
  std::cout << "\nbye.\n";
} 

void measure_depth(int values[]){
  for(auto i = 0; i < MEASURES;i++) {
    values[i] = std::rand() % (MAX_DEPTH-MIN_DEPTH+1) + MIN_DEPTH;
  }
}

void plot_depth(int values[], int s_pos[]) {
  for(auto d=0;d<MAX_DEPTH;d++) {
    //scorro le varie profondità
    for(auto v=0;v<MEASURES;v++) {
      // scorro le varie misurazioni fatte

      if (d < values[v]) {
        if (s_pos[0] == d && s_pos[1] == v) {
          std::cout << "@";
        } else {
          std::cout << ".";
        }
      } else {
        std::cout << "#";
      }
    }
    std::cout << "\n";
    
  }
}

void smooth(int values[]) {
  for(auto i = 0; i < MEASURES;i++){
    int v0,v1,v2;
    if (i==0) {
      v0 = values[0];
      v1 = values[1];
      v2 = values[1];
    } else if (i == MEASURES-1) {
      v0 = values[MEASURES-1];
      v1 = values[MEASURES-2];
      v2 = values[MEASURES-2];
    } else {
      v0 = values[i-1];
      v1 = values[i];
      v2 = values[i+1];
    }
    int media =(v0+v1+v2)/3;
    values[i] = media;
  }
}