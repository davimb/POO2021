#include <iostream>
#include <map>
#include <memory>
#include <optional>

using namespace std;

class Client{
    private:
        string nome;
        string fone;
    public:
        Client(string nome = "", string fone = "") : nome{nome}, fone{fone} {}
        friend ostream& operator<<(ostream& os, const Client& c) {
            os<<c.nome<<":"<<c.fone;
            return os;
        }
    
        string getNome() {
            return this->nome;
        }
};

class Sala{
    private:
        map<int, shared_ptr<Client>> cliente;
    public:
        Sala(int quant = 0) {
            for(int i=0; i<quant; i++) {
                cliente[i] = nullptr;
            }
        }

        bool reservar(shared_ptr<Client> pessoa, int pos) {
            auto it = cliente.find(pos);
            if(it==cliente.end()) {
                cout<<"fail: cadeira nao existe"<<endl;
                return true;
            }

            for(auto i : cliente) {
                if(i.second==nullptr)
                    continue;
                if(i.second->getNome()==pessoa->getNome()) {
                    cout<<"fail: ja existe um cliente com este nome"<<endl;
                    return true;
                }
            }

            if(it->second!=nullptr)
                return false;
                
            cliente[pos]=pessoa;
            return true;
        }

        void cancelar(string name) {

            for(auto& i : cliente) {
                if(i.second==nullptr)
                    continue;
                if(i.second->getNome()==name) {
                    i.second = nullptr;
                    return;
                }
            }
            cout<<"fail: nao existe cliente com esse nome"<<endl;
        }

        friend ostream& operator<<(std::ostream& os, const Sala& s) {
            os<<"[";
            for (auto person : s.cliente) {
                if(person.second==nullptr)
                    os<<" -";
                else
                    os<<" "<<*person.second;
            }
            os<<" ]";
            return os;
        }
};

int main () {

    string cmd{};
    Sala cinema;

    while (cmd!="end") {
        cout<<"$";
        cin>>cmd;

        if (cmd=="init") {
            int valor;
            cin>>valor;
            Sala temp(valor);
            cinema = temp;
        }

        else if (cmd=="show") {
            cout<<cinema<<endl;
        }

        else if (cmd=="reservar") {
            string name;
            string fone;
            int pos;
            cin>>name>>fone>>pos;
            bool ok = cinema.reservar(make_shared<Client>(name, fone), pos);
            if(!ok) {
                cout<<"fail: lugar ja reservado"<<endl;
            }
        }

        else if (cmd=="cancelar") {
            string name;
            cin>>name;
            cinema.cancelar(name);
        }
    }
}