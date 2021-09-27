#include <bits/stdc++.h>

using namespace std;

void aula(string dia){
    
    if(dia=="Segunda" or dia=="segunda" or dia=="Quarta" or dia=="quarta")
        cout<<"Hoje tem aula de POO com David Sena";

    else{
        cout<<"Hoje nao tem aula de POO com David Sena";
    }

}

int main () {

    string diahj;

    cout<<"Me diga o dia que direi se tera aula de POO com David Sena"<<endl;
    cin>>diahj;

    aula(diahj);

}