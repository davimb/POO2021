#include <iostream>
#include <memory>
#include <optional>
#include <list>

using namespace std;

class Kid {
    private:
        int age;
        string name;
    public:
        Kid(string name = "", int age = 0) : name{name}, age{age} {
        }

        friend ostream& operator<<(ostream& os, const Kid& k) {
            os<<k.name<<":"<<k.age;
        }

        string getNome() {
            return name;
        }

        int getIdade() {
            return age;
        }
};

class Trampoline {
    private:
        list<shared_ptr<Kid>> play;
        list<shared_ptr<Kid>> wait;

    public:
        Trampoline() {}
        
        void arrive(shared_ptr<Kid> kid) {
            wait.push_back(kid);
        }

        void in() {
            if(wait.empty()) {
                cout<<"fail: nao ha mais criancas na fila de espera"<<endl;
                return;
            }
            play.push_back(wait.front());
            wait.pop_front();
        }
        
        void out() {
            if(play.empty()) {
                cout<<"fail: nao ha mais criancas no pula pula"<<endl;
                return;
            }
            wait.push_back(play.front());
            play.pop_front();
        }
        
        void remove() {
            if(wait.empty()) {
                cout<<"fail: nao ha mais criancas para remover da fila de espera"<<endl;
                return;
            }
            wait.pop_front();
        }
        
        friend ostream& operator<<(ostream& os, const Trampoline& t) {
            os<<"=> ";
            list<shared_ptr<Kid>> temp;
            temp = t.wait;
            while (!temp.empty()) {
                cout<<*temp.back()<<" ";
                temp.pop_back();
            }
            cout<<"=> [ ";
            temp = t.play;
            while (!temp.empty()) {
                cout<<*temp.back()<<" ";
                temp.pop_back();
            }
            cout<<"]"<<endl;
        }
};

int main ()  {

    string cmd{};
    Trampoline trampoline;
    
    while (cmd!="end") {
        cout<<"$";
        cin>>cmd;

        if (cmd=="arrive") {
            string name;
            int age;
            cin>>name>>age;
            trampoline.arrive(make_shared<Kid>(name, age));
        }
        else if (cmd=="in") {
            trampoline.in();
        }
        else if (cmd=="out") {
            trampoline.out();
        }
        else if (cmd=="remove") {
            trampoline.remove();
        }
        else if (cmd=="show") {
            cout<<trampoline;
        }
    }
}