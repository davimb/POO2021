#include <bits/stdc++.h>
using namespace std;

class Person  {
    public:
        int age;
        string name;

        Person(string name = "", int age = 0) : age{age}, name{name} {}

        friend ostream& operator<<(ostream& os, const Person& p) {
            os<<p.name<<":"<<p.age;
            return os;
        }

};

class Motorcycle {
    public:
        int power {1};
        int time{0};
        vector<shared_ptr<Person>> vagao;

        Motorcycle() : vagao(5, nullptr){}

        void in(shared_ptr<Person> person) {
            for(int i=0; i<(int)vagao.size(); i++) {
                if(vagao[i]==nullptr) {
                    vagao[i] = person;
                    return;
                }
            }
            cout<<"fail: vagao cheio"<<endl;
        }

        void out() {
            if(vagao[0]==nullptr) {
                cout<<"fail: vagao ja esta vazio"<<endl;
                return;
            }
            vagao[0] = nullptr;
            power = 1;
            time = 0;
            vagao.erase(vagao.begin());
            vagao.push_back(nullptr);
        }

        void drive(int time) {
            if(vagao[0]==nullptr) {
                cout<<"fail: moto vazia"<<endl;
                return;
        }
            else {
                if(vagao[0]->age > 10) 
                    cout<<"fail: muito grande para andar de moto"<<endl;   
                else if(this->time < time) {
                    cout<<"fail: "<<vagao[0]->name<<" andou "<<this->time<<" e acabou o tempo"<<endl;
                    this->time = 0;
                }
                else
                    this->time-=time;
            }
            if(this->time==0) {
                cout<<"warning: tempo zerado"<<endl;
            }
        }
        
        void honk() {
            if(vagao[0]!=nullptr) {
                cout<<"P";
                for(int i=0; i<power; i++) cout<<"e";
                cout<<"m";
            }
            else
                cout<<"fail: vagao vazio";
        }

        friend ostream& operator<<(ostream& os, const Motorcycle& m) {
            int i = 0;
            for(auto person : m.vagao) {
                i++;
                if(person!=nullptr and i==1) {
                    os<<"vagao "<<i<<"->potencia: "<<m.power<<", minutos: "<<m.time<<", pessoa: ["<<*person<<"]"<<endl;
                }
                else if(i==1) {
                    os<<"vagao "<<i<<"->potencia: "<<m.power<<", minutos: "<<m.time<<", pessoa: [null]"<<endl;
                }
                else if(person!=nullptr) {
                    os<<"vagao "<<i<<"->potencia: 1, minutos: 0, pessoa: ["<<*person<<"]"<<endl;
                }
                else {
                    os<<"vagao "<<i<<"->potencia: 1, minutos: 0, pessoa: [null]"<<endl;
                }
            }
            return os;
    }
};

int main () {

    string comando{};
    int valor, age;
    string name;
    Motorcycle car;

    while(comando!="end") {
        cout<<"$";
        cin>>comando;

        if(comando=="init") {
            cin>>car.power;
        }

        else if(comando=="show") {
            cout<<car<<endl;
        }

        else if(comando=="in") {
            cin>>name>>age;
            car.in(make_shared<Person>(name, age));
        }

        else if(comando=="buy") {
            cin>>valor;
            car.time += valor;
        }

        else if(comando=="drive") {
            cin>>valor;
            car.drive(valor);
        }

        else if(comando=="honk") {
            car.honk();
            cout<<endl;
        }

        else if(comando=="out") {
            car.out();
        }
    }
}