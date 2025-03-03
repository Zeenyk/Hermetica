#include <iostream>
#include <string.h>
#include <time.h> 
#include <iomanip>

//Tipologia testo
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"
#define UNDERLINE "\033[4m"
#define BLINK   "\033[5m"
#define REVERSE "\033[7m"
#define HIDDEN  "\033[8m"

// Colori standard
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

// Colori ad alta intensità (Bright)
#define BRIGHT_BLACK   "\033[90m"
#define BRIGHT_RED     "\033[91m"
#define BRIGHT_GREEN   "\033[92m"
#define BRIGHT_YELLOW  "\033[93m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN    "\033[96m"
#define BRIGHT_WHITE   "\033[97m"


using namespace std;

template <typename... Args>
void log(string str, Args... args) {
    std::initializer_list<const char*> lista = {args...};

    for (const char* code : lista) {
        std::cout << code;
    }

    time_t now = time(nullptr); // Ottieni il tempo corrente
    tm* localTime = localtime(&now); // Converti in ora locale

    ostringstream oss;
    oss << put_time(localTime, "%Y-%m-%d %H:%M:%S"); // Formattazione

    cout<<"[" + oss.str() + "] " + str <<RESET<<endl;
}