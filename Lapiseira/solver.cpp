#include <iostream>

using namespace std;

class Grafite {

public:
    float calibre{0};
    string dureza{""};
    int tamanho{0};

    int desgastePorFolha();

};

class Lapiseira {

public:
    float calibre;
    Grafite grafite;

    void inserir(float cal, string dur, int tam);
    void ToString();
    void remover();
    void write(int quant);

};

int Grafite::desgastePorFolha() {
    if(dureza=="HB") return 1;
    else if(dureza=="2B") return 2;
    else if(dureza=="4B") return 4;
    else if(dureza=="6B") return 6;
    return 0;
}

void Lapiseira::inserir(float cal, string dur, int tam) {
    this->grafite.calibre = cal;
    this->grafite.dureza = dur;
    this->grafite.tamanho = tam;
}

void Lapiseira::ToString() {
    cout<<"calibre "<<this->calibre<<", grafite: ";

    if(this->grafite.tamanho>0)
        cout<<"["<<this->grafite.calibre<<":"<<this->grafite.dureza<<":"<<this->grafite.tamanho<<"]";
    else 
        cout<<"null";

}

void Lapiseira::remover() {
    this->grafite.calibre = 0;  
    this->grafite.dureza = "";
    this->grafite.tamanho = 0;
}

void Lapiseira::write(int quant) {
    int desgaste=grafite.desgastePorFolha();
    int cont=0;
    
    if(this->grafite.tamanho==0) {
        cout<<"fail: sem grafite"<<endl;
        return;
    }

    for (int i=0; i<quant; i++) {
        if (this->grafite.tamanho-desgaste>=0) {
            this->grafite.tamanho-=desgaste;
            cont++;
        }
        else {
            this->grafite.tamanho=0;
            cout<<"fail: folhas escritas completamente: "<<cont<<endl<<"warning: grafite acabou"<<endl;
            return;
        }
    }

    if(this->grafite.tamanho<desgaste) cout<<"warning: grafite acabou"<<endl;
}

int main(){

    string comando = "";
    Lapiseira *lapis1 = new Lapiseira();   
    
    while (comando!="end") {
        cout<<"$";
        cin>>comando;

        if(comando=="init") {
            cin>>lapis1->calibre;
        }
        else if(comando=="inserir") {
            float cal;
            string dur;
            int tam;
            cin>>cal>>dur>>tam;
            if(lapis1->grafite.tamanho!=0) {
                cout<<"fail: ja existe grafite"<<endl;
                continue;
            }
            if(cal!=lapis1->calibre) {
                cout<<"fail: calibre imcompativel"<<endl;
                continue;
            }
            lapis1->inserir(cal, dur, tam);
        }
        else if(comando=="show") {
            lapis1->ToString();
            cout<<endl;
        }
        else if(comando=="remover") {
            lapis1->remover();
        }
        else if(comando=="write") {
            int quant;
            cin>>quant;
            lapis1->write(quant);
        }
    }
    delete lapis1;
}