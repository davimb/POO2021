#include <iostream>
using namespace std;

class Person  {
    public:
        int age;
        string name;

        Person(int age = 0, string name = "") : age{age}, name{name} {}

        friend ostream& operator<<(ostream& os, const Person& p) {
            os<<p.name<<":"<<p.age;
            return os;
        }

};

class Motorcycle {
    public:
        int power {1};
        int time{0};
        Person *person {nullptr};

        Motorcycle(){}

        bool in(Person *person) {
            if(this->person!=nullptr) {
                cout<<"fail: moto ocupada"<<endl;
                return false;
            }
            this->person = person;
            return true;
        }

        Person *out() {
            if(this->person==nullptr) {
                cout<<"fail: moto vazia";
            }
            Person *pessoa = person;
            this->person=nullptr;
            return pessoa;
        }

        void drive(int time) {
            if(person==nullptr)
                cout<<"fail: moto vazia"<<endl;
            else {
                if(person->age > 10) 
                    cout<<"fail: muito grande para andar de moto"<<endl;   
                else if(this->time < time) {
                    cout<<"fail: andou "<<this->time<<" e acabou o tempo"<<endl;
                    this->time = 0;
                }
                else
                    this->time-=time;
            }
        }
        
        void honk() {
            if(person!=nullptr) {
                cout<<"P";
                for(int i=0; i<power; i++) cout<<"e";
                cout<<"m";
            }
            else
                cout<<"fail: moto vazia";
        }

        friend ostream& operator<<(ostream& os, const Motorcycle& m) {
            if(m.person!=nullptr)
                os<<"potencia: "<<m.power<<", minutos: "<<m.time<<", pessoa: ["<<*m.person<<"]";
            else
                os<<"potencia: "<<m.power<<", minutos: "<<m.time<<", pessoa: "<<"null";
            return os;
    }
};

int main () {

    string comando{};
    int valor;
    Motorcycle car;

    while(comando!="end") {
        cout<<"$";
        cin>>comando;

        if(comando=="init") {
            cin>>valor;
            car.power = valor; 
        }

        else if(comando=="show") {
            cout<<car<<endl;
        }

        else if(comando=="in") {
            Person *p = new Person;
            cin>>p->name>>p->age;
            if(!car.in(p))
                delete p;
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
            Person *pessoa = car.out();
            if(pessoa != nullptr) {
                delete pessoa;
            }
        }
    }
}