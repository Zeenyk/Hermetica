#include "encrypt.cpp"
#include "log.cpp"

using namespace std;


int main(){
    BIGNUM* p = BN_new();
    BN_generate_prime_ex(p, 512, 1, nullptr, nullptr, nullptr);

    BIGNUM* q = BN_new();
    BN_generate_prime_ex(q, 512, 1, nullptr, nullptr, nullptr);
    log("Access granted", BOLD, BRIGHT_GREEN, REVERSE);

    return 0;
}

