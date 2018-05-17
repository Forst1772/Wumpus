#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
int **mapa = NULL;
/* logica del mapa
	terreno = 0
	
	Wumpus = 5
	olor wumpus = -4
	
	abismo = 3
	viento = -2

	viento con olor = -6
	olor con abismo = -1

	jugador = 1
*/

void efecto(int x1, int y1, int tipo){
	mapa[x1][y1] = mapa[x1][y1] - tipo;
}

void wumpus(int dimension){
	int caracter = 4; // olor
	int x1, y1;
	do{
		x1 = rand()%dimension;
		y1 = rand()%dimension;
	}while(mapa[x1][y1] == 3);
	
	cout<< "(" << x1+1 << "," << y1+1 << ")\n";
	
	mapa[x1][y1] = 5;
	
	if(x1 != 0)
		efecto(x1-1,y1,caracter);
	if(y1 != 0)
		efecto(x1,y1-1,caracter);
	if(y1 != dimension)
		efecto(x1,y1+1,caracter);
	if(x1 != 0 && y1 !=0)
		efecto(x1-1,y1-1,caracter);
	if(x1 != 0 && y1 != dimension)
		efecto(x1-1,y1+1,caracter);
	
	
	if(x1 == (dimension-1)){
		if(x1 == dimension)
			efecto(x1+1,y1,caracter);
		if(x1 == dimension && y1 != 0)
			efecto(x1+1,y1-1,caracter);
		if(x1 == dimension && y1 != dimension)
			efecto(x1+1,y1+1,caracter);
	}else{
		if(x1 != dimension)
			efecto(x1+1,y1,caracter);
		if(x1 != dimension && y1 != 0)
			efecto(x1+1,y1-1,caracter);
		if(x1 != dimension && y1 != dimension)
			efecto(x1+1,y1+1,caracter);
	}
}

int main(int argc, char *argv[]) {
	srand(time(NULL));
	int n;
	cin >> n;
	
	if (n >= 10 && n <= 20){
		mapa = new int*[n];
		for(int i = 0; i < n; i++){
			mapa[i] =  new int[n];
		}
		
		
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				mapa[i][j] = 0;
			}
		}
		
		
		//LLenar abismos
		
		wumpus(n);
		
		//poner personaje
		
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				cout << mapa[i][j] << "\t";
			}
			cout << "\n";
		}
	}
	return 0;
}

