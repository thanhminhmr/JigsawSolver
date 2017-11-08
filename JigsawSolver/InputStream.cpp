#include "std.h"

#include <stdio.h>
#include <stdlib.h>
using namespace std;

int InputStream::piece_count;

Piece* InputStream::readFile(string filename) {
  string line;
  Piece *pieces;
  Point *points;
  char buffer[13];
  int n = 0;
  int id_tmp, point_count;
  int x_tmp, y_tmp;
  
  ifstream in(filename);
  
  if (in.is_open()) {
   	in >> n;
    piece_count = n;
  	pieces = new Piece[n];  
   	for (int i = 0; i < n; i++) {
   		in >> id_tmp >> point_count;
   		points = new Point[point_count];
   		for (int j = 0; j < point_count; j++) { 
   			in >> x_tmp >> y_tmp;
        Point point_tmp((int8_t) x_tmp, (int8_t) y_tmp);
   			points[j] = point_tmp;
   		}
      Piece piece_tmp(points, point_count);
      pieces[i] = piece_tmp;
        
   	}
    in.close();
    return pieces;
  }
 
  else cout << "Unable to open file"; 
  
    
}

int main(int argc, char** argv){
	InputStream is;
	Piece* pieces = is.readFile("../Doc/de_1_rand_reformat.txt");
  cout << is.piece_count << endl;
  for (int i = 0; i < is.piece_count; i++) {
    for (int j = 0; j < pieces[i].size; j++) {
     printf("%d %d ", pieces[i].getPoint()[j].x, pieces[i].getPoint()[j].y);
     
    }
    printf("\n");
  }
	return 0;
}

