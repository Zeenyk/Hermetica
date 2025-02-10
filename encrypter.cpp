#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <openssl/bn.h> //interi da 64 byte (512 bit), ottimizzata per RSA

#include <chrono> //per il log
#include <ctime>

using namespace std;

int main() {
    //per eseguire operazioni
    BN_CTX *ctx = BN_CTX_new();

    //due numeri primi p e q
    const char *pString = "11913142742716540880471335129760093579198508700132847983650404632751665022841644998848171345073148943441686300649270949725912665534551630141725552492730583";
    const char *qString = "11037005973539287277348662420722183896308180459173979650468032821847627600651592653800205853096674424601541199038005052471783763345555583428209664737379347";
    BIGNUM *p = BN_new();
    BIGNUM *q = BN_new();

    

    cout<<(BN_dec2bn(&p, pString) ? "Number initialized correctly" : "Error initializing the number")<<endl;
    cout<<(BN_dec2bn(&q, qString) ? "Number initialized correctly" : "Error initializing the number")<<endl;



    //un elemento dedlla coppia della chiave sia pubblica sia privata
    BIGNUM *n = BN_new();

    cout<<(BN_mul(n, p, q, ctx) ? "Multiplication executed with success" : "Error multiplying the numbers")<<endl;


    //dealloco la memoria
    BN_free(p);
    BN_free(q);
    BN_free(n);
    BN_CTX_free(ctx);
    return 0;
}


