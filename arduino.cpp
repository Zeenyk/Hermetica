string code(){
    srand(time(NULL));

    string res = "";
    for(int i=0; i<50; i++){
        res += (char)(rand()%94 + 32);
    }

    return res;
}