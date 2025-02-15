#include <utility>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <openssl/bn.h> //interi da 64 byte (512 bit), ottimizzata per RSA

#include <chrono> //per il log
#include <time.h>


using namespace std;


string code(){
    srand(time(NULL));

    string res = "";
    for(int i=0; i<50; i++){
        res += (char)(rand()%94 + 32);
    }

    return res;
}