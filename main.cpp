#include<iostream>
using namespace std;
#include<vector>
#include "akko.h"
#include<iomanip>

/*
 *  Si descomentas la línea de arriba el compilador ya no sabría si la función pausa()
 *  es la función del namespace Akko o la función que está declarada abajo.
 *  Ambas funciones tienen como parámetro (string msj)
 *
 *  Sabiendo esto puedes crear tus propias funciones sin importar que tengan
 *  el mismo nombre, ya que para ejecutar las del archivo akko.h
 *  puedes utilizar Akko::Funcion() para no confundir al compilador.
 *
*/

void pausa(string msj){
    cout << "Esto es una pausa " << endl;
}

int main(){

     Akko::nombre_ventana("Titulo de la ventana");
     Akko::limpiar_ventana();

     Akko::lista_archivos("Archivos", "torrent");
     Akko::pausa("");

     Akko::lista_archivos("Archivos", "");
     Akko::pausa("Hola mundo");

     Akko::lista_archivos("Archivos", "jpg");
     Akko::pausa("Adios mundo");

     Akko::lista_archivos("Archivos/01", "");
     Akko::pausa("");

     Akko::lista_archivos("Archivos/01", "pdf");
     Akko::pausa("Adios mundo");

     Akko::limpiar_ventana();
     pausa("Esta es una funcion direrente");

     for(int i = 0; i < 5; ++i){
         cout << i + 1 << " " << flush;
         Akko::esperar(0.1);
     }
     for(int i = 0; i < 5; ++i){
         cout << i + 1 << endl;
         Akko::esperar(0.1);
     }

     Akko::limpiar_ventana();
     Akko::nombre_ventana("Lain");
     Akko::mostrar_archivo("lain.txt", 0.0009);
     Akko::mostrar_archivo("black_mage.txt", 0.0009);
     Akko::pausa("");
     
    int num, a, b;
    cout << "Numeros al azar<int>: ";
    cin >> num;
    cout << "Minimo: ";
    cin >> a;
    cout << "Maximo: ";
    cin >> b;
    
    for(int i = 0; i != num; ++i) {
        cout << i + 1 << ") " << Akko::numero_random(a, b) << '\n';
    }
    
    double da, db;
    int decimales;
    cout << "Numeros al azar<double>: ";
    cin >> num;
    cout << "Numero de decimales: ";
    cin >> decimales;
    cout << "Minimo: ";
    cin >> da;
    cout << "Maximo: ";
    cin >> db;
    
    for(int i = 0; i != num; ++i) {
        cout << fixed << setprecision(decimales) << i + 1 << ") " << Akko::numero_random(da, db) << '\n';
    }

    return 0;
}
