//
// Created by nacho on 11/26/2024.
//
//
// Created by nacho on 11/26/2024.
//

#include <iostream>
#include <string>
#include <cstdio>
#include <stdexcept>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::exception;
using std::runtime_error;
using std::string;

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
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
            script.append(buffer, bytes_read); // Evita problemas con buffer[bytes_read]
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
    string filename;
    cout << "Ingrese el nombre del archivo: ";
    std::getline(cin, filename); // Usa getline de string para mayor seguridad
    load_script(filename.c_str(), true); // Llama a la función principal
}

// Función principal de prueba
int main() {
    try {
        load_script(); // Llama a la función sin argumentos
    } catch (const exception& e) {
        cerr << "Se produjo un error: " << e.what() << endl;
    }

    // Libera recursos
    delete consoleBox;

    return 0;
}
