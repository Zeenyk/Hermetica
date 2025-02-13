#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <openssl/bn.h> //interi da 64 byte (512 bit), ottimizzata per RSA

#include <chrono> //per il log
#include <ctime>

using namespace std;

BIGNUM* euclidean(BIGNUM*, BIGNUM*);

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


    //un elemento della coppia della chiave sia pubblica sia privata
    BIGNUM *n = BN_new();

    //il modulo per calcolare l'inverso modulare di e
    BIGNUM *phi = BN_new();

    cout<<(BN_mul(n, p, q, ctx) ? "Multiplication executed with success" : "Error multiplying the numbers")<<endl;

    BN_sub_word(p, 1);
    BN_sub_word(q, 1);

    cout<<(BN_mul(phi, p, q, ctx) ? "Multiplication executed with success" : "Error multiplying the numbers")<<endl;

    BN_add_word(p, 1);
    BN_add_word(q, 1);

    //scelgo e a piacere
    BIGNUM* e = BN_new();
    BN_dec2bn(&e,"65537");


    //calcolo d come l'inverso di e modulo phi
    BIGNUM* d = BN_new();
    d = euclidean(e, phi);

    

    //dealloco la memoria
    BN_free(p);
    BN_free(q);
    BN_free(n);
    BN_free(phi);
    BN_CTX_free(ctx);
    return 0;
}

//algoritmo di euclide esteso
BIGNUM* euclidean(BIGNUM* num, BIGNUM* mod){
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *old_y = BN_new(), *y = BN_new(), *new_y = BN_new();
    BIGNUM *old_r = BN_new(), *r = BN_new(), *new_r = BN_new();
    BIGNUM *q = BN_new();

    BN_zero(old_y);
    BN_one(y);

    
    BN_copy(old_r, mod);
    BN_mod(r, num, mod, ctx);
    

    while(!BN_is_zero(r)){
        BN_div(q, new_r, old_r, r, ctx);
        BN_copy(old_r, r);
        BN_copy(r, new_r);


        BN_mul(y, y, q, ctx);
        BN_sub(new_y, old_y, y);
        BN_div(y, nullptr, y, q, ctx);

        BN_copy(old_y, y);
        BN_copy(y, new_y);      
    }


    BN_free(y);
    BN_free(new_y);
    BN_free(old_r);
    BN_free(r);
    BN_free(new_r);
    BN_free(q);
    BN_CTX_free(ctx);

    if(BN_is_negative(old_y)) 
        BN_add(old_y, old_y, mod);

    return old_y;
}


