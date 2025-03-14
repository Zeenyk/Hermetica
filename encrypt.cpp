/*
*
*  Hermetica RSA
*  author: zeenyk
*
*/



#include <utility>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <openssl/bn.h> //interi da 64 byte (512 bit), ottimizzata per RSA

using namespace std;

BIGNUM* euclidean(BIGNUM*, BIGNUM*);        //euclide esteso
BIGNUM* toBN(string);                       //da stringa a big num
string toString(BIGNUM*);                   //da big num a stringa


BIGNUM* encrypt(string, pair<BIGNUM*, BIGNUM*>);                                    //funzione per criptare
string decrypt(BIGNUM*, pair<BIGNUM*, BIGNUM*>);                                    //funzione per decriptare

pair<BIGNUM*, BIGNUM*> generate_private(pair<BIGNUM*, BIGNUM*>);           //genera la chiave pubblica presi {p, q}, e
pair<BIGNUM*, BIGNUM*> generate_public(pair<BIGNUM*, BIGNUM*>);            //genera la chiave privata presi {p, q}, e

const string E = "65537";





//genera chiavi pubblica e privata
pair<BIGNUM*, BIGNUM*> generate_public(pair<BIGNUM*, BIGNUM*>pq){
    BN_CTX *ctx = BN_CTX_new();

    BIGNUM* n = BN_new();
    BIGNUM* p = pq.first;
    BIGNUM* q = pq.second;

    BIGNUM* e = BN_new();
    BN_dec2bn(&e, E.c_str());

    BN_mul(n, p, q, ctx);

    BN_CTX_free(ctx);

    return {n, e};
}

pair<BIGNUM*, BIGNUM*> generate_private(pair<BIGNUM*, BIGNUM*>pq){
    BN_CTX *ctx = BN_CTX_new();

    BIGNUM *n = BN_new();
    BIGNUM *phi = BN_new();
    BIGNUM* p = pq.first;
    BIGNUM* q = pq.second;

    BIGNUM* e = BN_new();
    BN_dec2bn(&e, E.c_str());

    BN_mul(n, p, q, ctx);

    BN_sub_word(p, 1);
    BN_sub_word(q, 1);

    BN_mul(phi, p, q, ctx);

    BN_add_word(p, 1);
    BN_add_word(q, 1);


    BIGNUM* d = euclidean(e, phi);

    BN_CTX_free(ctx);
    BN_free(e);

    return {n, d};
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



//encrypt and decrypt the number
BIGNUM* encrypt(string str, pair<BIGNUM*, BIGNUM*> public_key){
    BN_CTX* ctx = BN_CTX_new();
    BIGNUM* msg = toBN(str);
    BIGNUM* n = public_key.first;
    BIGNUM* e = public_key.second;


    BN_mod_exp(msg, msg, e, n, ctx);

    BN_CTX_free(ctx);

    return msg;
}

string decrypt(BIGNUM* num, pair<BIGNUM*, BIGNUM*> private_key){
    BN_CTX* ctx = BN_CTX_new();
    string msg;
    BIGNUM* n = private_key.first;
    BIGNUM* d = private_key.second;

    BN_mod_exp(num, num, d, n, ctx);
    msg = toString(num);

    BN_CTX_free(ctx);

    return msg;
}





//da stringa a BIGNUM
BIGNUM* toBN(string str){
    BIGNUM* sum = BN_new();
    BN_zero(sum);

    BIGNUM* addend = BN_new();
    BN_one(addend);

    for(int i=0; i<str.length(); i++){
        BN_mul_word(addend, str[i]);
        BN_add(sum, sum, addend);


        BN_div_word(addend, str[i]);
        BN_mul_word(addend, 1000);
    }

    BN_free(addend);

    return sum;
}

//da BIGNUM a stringa
string toString(BIGNUM* num){
    string str = "";
    

    while(!BN_is_zero(num)){
        str += BN_mod_word(num, 1000);
        BN_div_word(num, 1000);
    }

    return str;
}