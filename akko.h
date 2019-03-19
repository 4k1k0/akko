/*
 * Akko.h tiene funciones básicas y repetitivas,
 * de una manera que funcionen tanto en Windows
 * como en GNU/Linux.
 *
 * Funciones:
 *
 *     nombre_ventana     Cambia el título de la consola. Utiliza una string como parámetro.
 *
 *     limpiar_ventana    Limpia la consola. No tiene parámetro.
 *
 *     esperar            Pausa el programa por x segundos. Admite 0.5 como medio segundo.
 *                        Si se utiliza en GNU y se quiere imprimir un mensaje en horizontal. E.g.
 *                            "Esperando"
 *                            "Esperando."
 *                            "Esperando.."
 *                            "Esperando..."
 *                        Donde hay una función pausa(x) entre cada punto:
 *                            cout << "Esperando"; pausa(x); cout << "."; pausa(x); cout << "."; pausa(x); cout << "."; pausa(x);
 *                        El mensaje "Esperando..." tardaría 3 veces X para poderse visualizar, sin notarse la animación, esto debido
 *                        a que se tiene que limpiar el buffer antes de la función pausa(x). Para esto se utiliza *flush*
 *                            cout << "Esperando" << flush; pausa(x); cout << "." << flush;
 *                            pausa(x); cout << "." << flush; pausa(x); cout << "." << flush; pausa(x);
 *                        De esta manera se puede ejecuta la función pausa(x) entre cada cout, creando una pequeña animación en el texto.
 *                        Si lo que se desea es mostrar texto de manera vertical dejando una pausa(x) entre cada cout
 *                        la función no tiene problemas, ya que al utilizar *endl* entre cada *cout* se limpia el buffer. E.g.
 *                            for(int i = 0; i < 3; ++i){
 *                                cout << i << endl;
 *                                pausa(x);
 *                            }
 *                        Esto funciona correctamente y no hay necesidad de utilizar *flush*.
 *                        *Este problema es sólo de GNU, en Windows no hay necesidad de utilizar flush*
 *
 *     pausa              Pausa la consola hasta que se presione Enter. Utiliza una string como parámetro,
 *                        pero si el parámetro es "" se utiliza el mensaje por defecto.
 *
 *     lista_archivos     Muestra una lista de los archivos del directorio indicado.
 *                        Donde los parámetro son *directorio* y *extensión de los archivos (sin el punto)*.
 *                        Si el primer parámetro se deja como "" se mostrará la carpeta raíz del ejecutable.
 *                        Si el segundo parámetro se deja como "" se mostrarán todos los archivos.
 *
 *     mostrar_archivo    Muestra el contenido de un archivo en la consola.
 *                        El primer parámetro es el nombre del archivo y el segundo el tiempo de animación.
 *                        El tiempo se ingresa de la misma manera que en la función pausa() y el tiempo es
 *                        por caracter.
 *                        Pensé en esto como una manera de mostrar arte ASCII pero funciona bien con cualquier
 *                        tipo de archivo de texto plano.
 *
 *     numero_random      Obtiene un número al azar delimitado por sus dos parámetros. La función fue declarada
 *                        dos veces, ya que una devuelve números <int> y la otra números <double>.
 *                        En caso de que se quiera imprimir un número exacto de decimales se puede hacer uso de
 *                        las funciones std::fixed y std::setprecision de la librería <iomanip> E.g.
 *                          std::cout << std::fixed << std::setprecision(decimales) << Akko::numero_random(min, max);
 *                        No se usó un template para construir la función ya que
 *                          uniform_real_distribution<double>
 *                          uniform_int_distribution<int>
 *                        funcionan de manera diferente.
 *
 * Librerías:
 *
 *     fstream            Necesaria para la función mostrarArchivo()
 *
 *     windows.h          *Sólo en Windows* Necesaria para la función nombreVentana()
 *
 *     random             Necesaria para la función numero_random()
 *
 *     chrono             Necesaria para la función numero_random() y para la función esperar()
 *
 * Akko(https://myanimelist.net/character/15658/Akiko_Oohashi)
 */
#ifndef AKKO_H
#define AKKO_H

#include<fstream>
#include<random>
#include<chrono>
#include<thread>
#ifdef _WIN32
#include<windows.h>
#endif

namespace Akko{

    void nombre_ventana(string nombre) {
        #ifdef _WIN32
        const char* n = nombre.c_str();
            SetConsoleTitle(n);
        #else
            char esc_start[] = { 0x1b, ']', '0', ';', 0 };
            char esc_end[] = { 0x07, 0 };
            cout << esc_start << nombre << esc_end;
        #endif
    }
    void limpiar_ventana() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    void esperar(double segundos) {
        using namespace std::chrono;
        if(segundos <= 0.0) return;
        segundos *= 1000;
        auto t0 = high_resolution_clock::now();
        this_thread::sleep_for(milliseconds{static_cast<int>(segundos)});
    }
    void pausa(string msj){
        if(msj == "") msj = "Presiona Enter para continuar";
        cout << msj << endl;
        cin.get();
        cin.clear();
    }
    void lista_archivos(string directorio, string extension) {
        string cd;
        (directorio == "") ? cd = "" : cd = "cd " + directorio + " && ";
        if(extension != "") extension = " *" + extension;
        #ifdef _WIN32
            //cd += "dir /b" + extension;
            cd += "dir /b /a-d" + extension;
            const char* a = cd.c_str();
            system(a);
        #else
            cd += "ls --color" + extension;
            const char* a = cd.c_str();
            system(a);
        #endif
    }
    void mostrar_archivo(string n, double t) {
        ifstream archivo {n};
        if(!archivo) cout << "Error al abrir el archivo " << n << "\n";
        char c;
        while(archivo.get(c)) {
            cout << c << flush;
            esperar(t);
        }
        archivo.close();
    }
    int numero_random(int min, int max) {
        if(min > max) {
            int n3 = min;
            min = max;
            max = n3;
        }
        unsigned semilla = chrono::system_clock::now().time_since_epoch().count();
        default_random_engine generador(semilla);
        uniform_int_distribution<int> distribucion(min, max);
        int numero = distribucion(generador);
        return numero;
    }
    double numero_random(double min, double max) {
        if(min > max) {
            double n3 = min;
            min = max;
            max = n3;
        }
        unsigned semilla = chrono::system_clock::now().time_since_epoch().count();
        default_random_engine generador(semilla);
        uniform_real_distribution<double> distribucion(min, max);
        double numero = distribucion(generador);
        return numero;
    }
} // namespace Akko

#endif
