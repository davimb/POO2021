#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>
#include <vector>

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
        string name;
        vector<Fone> fones;

    public:
        Contact(string name = "") : name{name} {}

        vector<Fone> getFones() {
            return fones;
        }

        string getName() {
            return name;
        }

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

class Agenda {
    private:
        map<string, Contact> contatos;
        
    public:
        Agenda() {}

        void addContact(Contact contact) {
            auto it = contatos.find(contact.getName());
            if (it==contatos.end()) {
                contatos[contact.getName()] = contact;
            }
            else {
                for (auto i : contact.getFones()) {
                    it->second.addFone(i);
                }
            }
        }

        void rmFone(string name, int pos) {
            for (auto& i : contatos) {
                if (i.first == name) {
                    i.second.rmFone(pos);
                    return;
                }
            }
            cout<<"fail: invalid contact"<<endl;
        }

        void rmContact(string name) {
            auto it = contatos.find(name);
            if(it!=contatos.end()) {
                contatos.erase(it);
                return;
            }
            cout<<"fail: invalid contact"<<endl;
        }

        void show() {
            for (auto i : contatos) {
                cout<<i.second<<endl;
            }
        }

        vector<Contact> search(string pattern) {
            vector<Contact> result;
            for (auto& p : contatos) {
                stringstream ss;
                ss << p.second;
                string texto_da_pessoa = ss.str();
                if (texto_da_pessoa.find(pattern) != string::npos) {
                    result.push_back(p.second);
                }
            }
            return result;
        }
};

int main() {

    string cmd{};
    string resto;
    Agenda agenda;

    while (cmd!="end") {
        cout<<"$";
        cin>>cmd;
        getline(cin, resto);
        stringstream ss(resto);

        if (cmd == "add") {
            string contato{};
            string name{};
            ss>>name;
            Contact contact(name);

            while (ss>>contato) {
                string id{};
                string number{};
                int x=1;

                for (int i=0; i<(int)contato.size(); i++) {
                    if (contato[i] == ':') {
                        x*=-1;
                    }
                    else if (x == 1) {
                        id += contato[i];
                    }
                    else if (x == -1) {
                        number += contato[i];
                    }
                }
                Fone fonetemp(id, number);
                contact.addFone(fonetemp);
            }
            agenda.addContact(contact);
        }
        
        else if (cmd == "rmFone") {
            string name;
            int pos;
            ss>>name>>pos;
            agenda.rmFone(name, pos);
        }

        else if (cmd == "show") {
            agenda.show();
        }

        else if (cmd == "search") {
            string pattern;
            ss>>pattern;
            vector<Contact> aux = agenda.search(pattern);
            for (auto i : aux) {
                cout<<i<<endl;
            }
        }

        else if (cmd == "rm") {
            string name;
            ss>>name;
            agenda.rmContact(name);
        }
    }
}