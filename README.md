# Caso-Final-Integrador-Tema-3_Ignacio
https://github.com/Ideroizq/Caso-Final-Integrador-Tema-3_Ignacio.git

Trabajos prácticos
1. Carga de scripts en tiny-lisp
El módulo Labmain.cpp define la función load_script(), que se utiliza para cargar un script en la memoria y aplicarle la coloración sintáctica. Esta función se basa en la librería estándar de C.

Implementa las funciones load_script() y load_script(filename, true) en CLion, de tal manera que puedas abrir y leer archivos de texto. El primer método toma el nombre de un archivo como entrada del usuario, mientras que el segundo muestra el contenido del archivo. Ambos métodos deben cargar el script en la consola.

void load_script(const char* filename, bool show_script = false);
void load_script();
2. Asegurando la robustez del código
Asegúrate de que tu código pueda manejar diferentes tipos de errores de entrada. Esto incluye, pero no se limita a:

El usuario proporciona un nombre de archivo que no existe.
El archivo proporcionado no se puede abrir por alguna razón.
Se produce un error de lectura durante la lectura del archivo.
Para manejar estos y otros errores potenciales, es posible que desees agregar comprobaciones de errores adicionales y manejar los fallos de manera más sofisticada.

Notas
Este ejercicio no requiere el uso de funciones seguras específicas de Microsoft (las funciones con sufijo _s). En cambio, deberías usar las funciones estándar de C/C++ disponibles en todas las plataformas y compiladores, como fopen, printf y scanf.


Rúbrica
Carga de scripts (50 puntos)

Se proporciona una implementación correcta de load_script(const char* filename, bool show_script = false) que carga correctamente el archivo dado y muestra su contenido si show_script es verdadero. (25 puntos)
Se proporciona una implementación correcta de load_script() que solicita al usuario un nombre de archivo, llama a la función load_script(const char* filename, bool show_script = false) y maneja cualquier error de manera apropiada. (25 puntos)
Manejo de errores (50 puntos)

El código tiene un manejo de errores sólido y completo para el caso de que el nombre del archivo proporcionado no exista. (15 puntos)
El código tiene un manejo de errores sólido y completo para el caso de que el archivo proporcionado no se pueda abrir por alguna razón. (15 puntos)
El código tiene un manejo de errores sólido y completo para el caso de que se produzca un error de lectura durante la lectura del archivo. (20 puntos)
Total: 100 puntos

Propuesta de solución
En CLion, las funciones seguras de la biblioteca estándar de C (*_s funciones) generalmente no están disponibles porque estas son específicas de Microsoft y no son estándar de C/C++. Por lo tanto, en lugar de utilizar funciones como fopen_s, printf_s y scanf_s, puedes usar sus equivalentes no seguros, que son fopen, printf y scanf.

A continuación se muestra cómo se podría reescribir el código para CLion:

#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

struct ColorConsole
{
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
};

struct ConsoleBox
{
    void new_text() {/*...*/}
    void set_text(const string &text) { cout << text << endl; }
};

ConsoleBox *consoleBox = new ConsoleBox; // suponemos que ya está inicializado

void load_script(const char* filename, bool show_script = false)
{
    string script;
    FILE* f = nullptr;
    try
    {
        f = fopen(filename, "rb");
        if (!f)
        {
            cerr << "error de apertura de " << filename << endl;
            return;
        }

        int c;
        char buf[4001];
        while ((c = fread(buf, 1, 4000, f)) > 0)
        {
            buf[c] = 0;
            script.append(buf);
        }
        fclose(f);
        f = nullptr;

        if (show_script)
        {
            cout << ColorConsole::fg_blue << ColorConsole::bg_white;
            cout << script << endl;
        }
        consoleBox->new_text();
        consoleBox->set_text(script);
    }
    catch (...)
    {
        cerr << "error durante la lectura del archivo" << endl;
        if(f)
            fclose(f);
    }
}

void load_script()
{
    char filename[500];
    printf("Archivo: ");
    scanf("%499s", filename);
    load_script(filename, true);
}
Este código debería compilar y funcionar en CLion sin necesidad de agregar la directiva _CRT_SECURE_NO_WARNINGS, ya que no se están utilizando las versiones seguras específicas de Microsoft de las funciones de la biblioteca estándar de C.

Por último, ten en cuenta que este código no realiza una comprobación completa de errores y no es robusto contra varios tipos de errores de entrada. Dependiendo de tu caso de uso específico, es posible que desees agregar comprobaciones de errores adicionales y manejar los fallos de manera más sofisticada.


# Correccion compañero: Caso Final Integrador 3 de Alfredo Rubert
##Errores
</details>
1. Error en el manejo del buffer en la función load_script
Problema: buf[c] = 0; podría causar un desbordamiento de buffer si fread lee el tamaño máximo de caracteres permitidos (4000).
Solución: Cambia buf[c] = 0; por buf[c] = '\0'; y asegúrate de que el índice sea válido al agregar el carácter nulo.
2. No se inicializa el puntero FILE* f correctamente en el bloque try
Problema: Si ocurre una excepción antes de que se asigne un archivo a f, el manejo de errores intenta cerrar un puntero no inicializado.
Solución: Inicia explícitamente el puntero FILE* f = nullptr;.
3. Desbordamiento potencial en scanf en load_script()
Problema: Aunque el tamaño está limitado a 499 caracteres con %499s, si el usuario introduce más caracteres, puede provocar un comportamiento indefinido.
Solución: Usa fgets en lugar de scanf.
4. Asignación dinámica de ConsoleBox sin liberarla
Problema: consoleBox se asigna dinámicamente con new, pero nunca se libera, lo que puede causar fugas de memoria.
Solución: Libera consoleBox al final del programa o usa un puntero inteligente (unique_ptr o shared_ptr).
5. Uso de cadenas const char* en lugar de std::string
Problema: Aunque no es un error, puedes usar std::string para evitar el uso de punteros sin formato (char*) en C++ moderno.
Solución: Refactoriza para usar std::string en lugar de char*.
</details>
