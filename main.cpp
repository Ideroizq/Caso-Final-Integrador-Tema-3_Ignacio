//
// Created by nacho on 11/26/2024.
//

#include "main.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <stdexcept>

using namespace std;

// Colores de consola para resaltar la salida (opcional)
struct ColorConsole {
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto reset = "\033[0m";
};

// Simulación de una consola en un entorno gráfico
struct ConsoleBox {
    void new_text() {
        // Simula reiniciar la consola
        cout << "[Nueva Consola]" << endl;
    }
    void set_text(const string& text) {
        // Simula mostrar el texto en la consola
        cout << text << endl;
    }
};

// Instancia global de ConsoleBox
ConsoleBox* consoleBox = new ConsoleBox(); // Suponemos que está inicializado

// Función para cargar un script desde un archivo
void load_script(const char* filename, bool show_script = false) {
    FILE* file = nullptr;  // Puntero al archivo
    string script;         // Contenido del archivo

    try {
        // Intenta abrir el archivo en modo binario
        file = fopen(filename, "rb");
        if (!file) {
            throw runtime_error("No se pudo abrir el archivo.");
        }

        // Lee el archivo en bloques
        char buffer[4096];
        size_t bytes_read;
        while ((bytes_read = fread(buffer, 1, sizeof(buffer) - 1, file)) > 0) {
            buffer[bytes_read] = '\0'; // Asegura el final de la cadena
            script.append(buffer);
        }

        // Verifica errores de lectura
        if (ferror(file)) {
            throw runtime_error("Error durante la lectura del archivo.");
        }

        fclose(file); // Cierra el archivo
        file = nullptr;

        // Muestra el contenido del script si se solicita
        if (show_script) {
            cout << ColorConsole::fg_blue << script << ColorConsole::reset << endl;
        }

        // Simula cargar el script en la consola gráfica
        consoleBox->new_text();
        consoleBox->set_text(script);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        if (file) {
            fclose(file); // Asegura que el archivo se cierre en caso de error
        }
    }
}

// Sobrecarga para solicitar el nombre del archivo al usuario
void load_script() {
    char filename[500];
    cout << "Ingrese el nombre del archivo: ";
    cin.getline(filename, sizeof(filename)); // Usa getline para evitar errores con espacios
    load_script(filename, true); // Llama a la función principal
}

// Función principal de prueba
int main() {
    try {
        load_script(); // Llama a la función sin argumentos
    } catch (const exception& e) {
        cerr << "Se produjo un error: " << e.what() << endl;
    }
    return 0;
}
