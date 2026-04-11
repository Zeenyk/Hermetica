#include "hermetica.cpp"

string logo[] =
{" _   _ " ,                                     
 "| | | | ",                                 
 "| |_| |___  ___  _   _ ___ ___ ___   ____  __ ",
 "|  _  / __)/ _ \\| | | / __|   ) \\ \\ / /  \\/ / ",
 "| | | > _)| |_) ) |_| > _) | || |\\ v ( ()  <  ",
 "|_| |_\\___)  __/| ._,_\\___) \\_)\\_)> < \\__/\\_\\ ",
 "          | |   | |              / ^ \\        ",
 "          |_|   |_|             /_/ \\_\\       "};

int main() {

    for(int i=0; i<8; i++) cout<<logo[i]<<endl;
    
    cout<<"\n-------------------------------------------------\n\n";

    //due numeri primi p e q
    BIGNUM *p = BN_new();
    BIGNUM *q = BN_new();

    BN_generate_prime_ex(p, 512, 1, nullptr, nullptr, nullptr);
    BN_generate_prime_ex(q, 512, 1, nullptr, nullptr, nullptr);


    
    auto pbk = generate_public({p, q});
    auto pvk = generate_private({p, q});
    
    


    string msg = "Ciao";


    cout<<"Messaggio: "<<msg<<endl<<endl;
    cout<<"Messaggio criptato: "<<BN_bn2dec(encrypt(msg, pbk))<<endl<<endl;
    cout<<"Messaggio decriptato: "<<decrypt(encrypt(msg, pbk), pvk)<<endl<<endl;

    
    //!IMPORTANTE!
    //dealloco la memoria 
    BN_free(p);
    BN_free(q);
    return 0;
}
