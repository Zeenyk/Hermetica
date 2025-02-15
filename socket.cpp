#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <future> //funzioni asincrone
#include <chrono>
#include <thread>


using namespace std;

#define RPORT 3219
#define LPORT 3220

void client(int server_socket){
    
}

void server(int client_socket){
    
}

int main(){
    future<void> res1 = async(launch::async, client, );
    future<void> res2 = async(launch::async, server, );
       
}
