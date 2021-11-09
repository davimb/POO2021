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
        vector<shared_ptr<Person>> fila;

        Motorcycle() : fila(5, nullptr){}

        void in(shared_ptr<Person> person) {
            for (int i=0; i<(int)fila.size(); i++) {
                if (fila[i]==nullptr) {
                    fila[i] = person;
                    return;
                }
            }
            cout<<"fail: fila cheio"<<endl;
        }

        void out() {
            if (fila[0]==nullptr) {
                cout<<"fail: fila ja esta vazia"<<endl;
                return;
            }
            fila[0] = nullptr;
            time = 0;
            fila.erase(fila.begin());
            fila.push_back(nullptr);
        }

        void drive(int time) {
            if (fila[0]==nullptr) {
                cout<<"fail: moto vazia"<<endl;
                return;
        }
            else {
                if (fila[0]->age > 10) 
                    cout<<"fail: muito grande para andar de moto"<<endl;   
                else if(this->time < time) {
                    cout<<"fail: "<<fila[0]->name<<" andou "<<this->time<<" e acabou o tempo"<<endl;
                    this->time = 0;
                }
                else
                    this->time-=time;
            }
            if (this->time==0) {
                cout<<"warning: tempo zerado"<<endl;
            }
        }
        
        void honk() {
            if (fila[0]!=nullptr) {
                cout<<"P";
                for(int i=0; i<power; i++) cout<<"e";
                cout<<"m";
            }
            else
                cout<<"fail: fila vazia";
        }

        friend ostream& operator<<(ostream& os, const Motorcycle& m) {
            os<<"potencia: "<<m.power<<", minutos: "<<m.time<<", pessoa: [[";
            int i = 0;
            for (auto person : m.fila) {
                if (person!=nullptr)
                    os<<*person<<"]";
                else
                    os<<"null"<<"]";
                if (i<(int)m.fila.size()-1) {
                    os<<", [";
                i++;
                }
            }
            os<<"]";
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