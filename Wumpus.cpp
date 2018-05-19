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

jugador = 1

jugador en -6 = -5 viento y olor
jugador en -4 = -3 olor
jugador en -2 = -1 viento
*/
void efecto(int x1, int y1, int tipo){
	if(mapa[x1][y1] == -2){
		if (tipo == -4)
			mapa[x1][y1] = mapa[x1][y1] + tipo;
	} else if(mapa[x1][y1] == -4){
		if(tipo == -2)
			mapa[x1][y1] = mapa[x1][y1] + tipo;
	} else if (mapa[x1][y1] != 3){
		mapa[x1][y1] = mapa[x1][y1] + tipo;
	}
}
void olorViento(int x1, int y1, int caracter, int dimension){
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
void abismos(int cantidad){
	int dimension = cantidad;
	int a = dimension - ((double) (dimension*30)/100); // maximo de abismos aledaños
	cantidad = cantidad / 2; //Maximo de abismos principales
	
	while(cantidad != 0){
		//Ubicas abismo principal
		int x = rand()%dimension;
		int y = rand()%dimension;
		mapa[x][y] = 3;
		
		//Poner el viento del abismo principal
		olorViento(x,y,-2,dimension);
		
		
		//Misma logica para abismos aledaños
		int n = 2 + rand()%a; //Cantidad de aledaños al pincipal
		if (x != (dimension-1) && x !=0 && y != (dimension-1) && y !=0){
			while(n != 0){
				int x1 = (rand()%4) - 2 ;
				int y1 = (rand()%4) - 2;
				if(mapa[abs(x+x1)][abs(y+y1)] != 3){
					mapa[abs(x+x1)][abs(y+y1)] = 3;
					olorViento(abs(x+x1),abs(y+y1),-2,dimension);
				}
				n--;
			}
		}		
		cantidad--;
	}
}

void wumpus(int dimension){
	//Ubicar al wumpus
	int x1, y1;
	do{
		x1 = rand()%dimension;
		y1 = rand()%dimension;
	}while(mapa[x1][y1] == 3);
	mapa[x1][y1] = 5;
	
	//Poner el olor al rededor del wumpus
	olorViento(x1,y1,-4,dimension);
}

int main(int argc, char *argv[]) {
	srand(time(NULL));
	int n=10;
	//cin >> n;
	
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
		
		//Llenar el mundo con abismos, wumpus y personaje
		abismos(n);
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
