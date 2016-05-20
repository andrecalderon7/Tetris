
#include "miniwin.h"
using namespace miniwin;

const int TAM=25; /*FIJA EL TAMAÑO DEL CUADRADO*/
const int FILAS = 20;
const int COLUMNAS = 10;

typedef int Tablero[COLUMNAS][FILAS];

struct Coord {
    int x, y;
};

struct Pieza {
        Coord origen; //pieza central
        Coord perifericos[3]; // bloques perifericos
        int color;

        Coord posicion(int n) const; // n entre 0 y 3, 0 centro,
};

Coord Pieza::posicion(int n) const{
    Coord ret = {origen.x, origen.y};
    if (n != 0){
        ret.x += perifericos[n-1].x;
        ret.y += perifericos[n-1].y;
    }
    return ret;
}

void cuadrado(int x, int y) /*ESTA FUNCION DEFINE LOS CUADRADOS QUE FORMARAN LAS PIEZAS*/{
rectangulo_lleno(1 + x * TAM, /*l +1 le pone un borde*/
                 1 + y * TAM,
                 x * TAM + TAM,
                 y * TAM + TAM);/*esquina superior derecha e inferior izquierda*/
}

void pinta_pieza(const Pieza& P) {
    color(P.color);
    for (int i = 0; i < 4; i++){
            Coord c = P.posicion(i);
            cuadrado(c.x, c.y);
    }
}

Coord rota_derecha(const Coord& c){
     Coord ret={-c.y, c.x};
     return ret;
}

Coord rota_izquierda(const Coord& c){
     Coord ret={c.y, -c.x};
     return ret;
}

void rota_derecha(Pieza& P){
    for (int i =0; i < 3; i++){
        P.perifericos[i] = rota_derecha(P.perifericos[i]);
    }
}

void rota_izquierda(Pieza& P){
    for (int i =0; i < 3; i++){
        P.perifericos[i] = rota_izquierda(P.perifericos[i]);
    }
}

void vacia_tablero(Tablero& T){
    for (int i = 0; i < COLUMNAS; i++){
        for (int j = 0; j < FILAS; j++){
            T[i][j] = NEGRO; // es negro pq el negro no se imprime, casilla vacia
        }
    }
}

void Pinta_tablero(const Tablero& T){
    for (int i = 0; i < COLUMNAS; i++){
        for (int j = 0; j < FILAS; j++){
            color(T[i][j]);
            cuadrado(i,j);
        }
    }
}

void incrustarP(Tablero& T, const Pieza& P){
    for (int i = 0; i < 4; i++){
            Coord c = P.posicion(i);
            T[c.x][c.y] = P.color;
        }
}
bool tablero_colision (const Tablero& T, const Pieza& P){
    // comprueba Limites/ del programa
    for (int i = 0; i <4; i++){
        Coord c = P.posicion(i);
            if (c.x <0 || c.x >= COLUMNAS){ //comprueba limites
                return true;
            }
            if (c.y <0 || c.y >= FILAS){ //comprueba limites
                return true;
            }
            if (T[c.x][c.y] !=NEGRO){ //comrpueba choque abajo
                return true;
            }
    }
    return false;
}

//Pieza s = { {4,4}, {{-1,0},{0,-1},{1,-1} }};
//Pieza L = { {5,5}, {{0,-2},{0,-1},{1,0} }};
//Pieza L2 = { {4,4}, {{0,-2},{0,-1},{-1,0} }};
//Pieza i = { {4,4}, {{0,-2},{0,-1},{0,1} }};
//Pieza T = { {4,4}, {{-1,0},{0,-1},{1,0} }};
//Pieza z = { {5,10}, {{-1,-1},{0,-1},{1,0} }, ROJO};
//Pieza L = { {5,10},{{0,-2},{0,-1},{1,0}}, AZUL };


int main() {
            vredimensiona(TAM *COLUMNAS, TAM*FILAS);
            Tablero T;
            vacia_tablero(T);
            T[0][19] = VERDE;
            T[1][19] = VERDE;
            T[5][19] = ROJO;
            T[4][13] = AMARILLO;
            Pinta_tablero(T);

            Pieza c = { {0,0}, {{1,0},{1,1},{0,1}}, MAGENTA};
            pinta_pieza(c);
            refresca();


            int t = tecla (); //configura el movimiento
            while (t != ESCAPE){
                       int x = c.origen.x; //copia posicion
                       int y = c.origen.y;
                    if (t == ABAJO){
                            c.origen.y++;
                    } else if (t == ARRIBA) {
                            c.origen.y--;
                    } else if (t == DERECHA) {
                            c.origen.x++;
                    } else if (t == IZQUIERDA) {
                            c.origen.x--;
                    }
                    if (tablero_colision(T,c)){ //define si hay colision
                        c.origen.x = x;
                        c.origen.y = y;
                    }
                    if (t != NINGUNA){
                            borra();
                            Pinta_tablero(T);
                            pinta_pieza(c);
                            refresca();
                    }
                        t = tecla();
            }
        vcierra();
        return 0;

    }
