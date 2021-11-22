#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Fone {
    private:
        string id;
        string number;
    public:
        Fone(string id = "", string number = "") : id{id}, number{number} {}
        
        bool validate(string number) {
            for (int i=0; i<(int)number.size(); i++) {
                if (number[i]!='.' and number[i]!='(' and number[i]!=')' and (number[i]<48 or number[i]>57)) {
                    return false;
                }
            }
            return true;
        }

        string getNumber() {
            return number;
        }
        
        friend ostream& operator<<(ostream& os, Fone& fone) {
            os<<fone.id<<":"<<fone.number;
        }
};

class Contact {
    private:
        string prefix;
        string name;
        vector<Fone> fones;

    public:
        Contact(string name = "") : name{name} {}

        void addFone(Fone fone) {
            if (fone.validate(fone.getNumber())) {
                fones.push_back(fone);
            }
            else
                cout<<"fail: invalid number"<<endl;
        }

        void rmFone(int pos) {
            if (pos>(int)fones.size()-1 or pos<0) {
                cout<<"fail: invalid position"<<endl;
                return;
            }
            fones.erase(fones.begin() + pos);
        }

        friend ostream& operator<<(ostream& os, Contact& c) {
            os<<"- "<<c.name;
            int cont=0;
            if(!c.fones.empty()) {
                for(auto i : c.fones) {
                    os<<" ["<<cont<<":"<<i<<"]";
                    cont++;
                }
            }
            return os;
        }

};

int main() {

    string cmd{};
    string resto;
    Contact contato;

    while (cmd!="end") {
        cout<<"$";
        cin>>cmd;
        getline(cin, resto);
        stringstream ss(resto);

        if (cmd == "init") {
            string name = "";
            ss>>name;

            Contact temp(name); 
            contato = temp;
        }

        else if (cmd == "add") {
            string id;
            string number;
            ss>>id>>number;
            Fone fone(id, number);
            contato.addFone(fone);
        }
        
        else if(cmd == "rm") {
            int pos;
            ss>>pos;
            contato.rmFone(pos);
        }

        else if(cmd == "show") {
            cout<<contato<<endl;
        }
    }
}