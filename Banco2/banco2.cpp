#include <iostream>
#include <list>
#include <map>
#include <memory>

using namespace std;

class Account {
protected:
    float balance = 0;
    string clientId{};
    int id{};
    string type{};
public:
    Account(int id = 0, string clientId = "") : id(id), clientId(clientId) {}

    float getBalance() {
        return balance;
    }
    
    virtual void deposit(float value) {
        balance += value;
    };

    virtual void monthlyUpdate() = 0;
    
    void transfer(Account& other, float value) {
        if(balance - value >=0) {
            other.balance += value;
            balance -= value;
        }
        else
            throw runtime_error("fail: saldo insuficiente");
    }

    void withdraw(float value) {
        if(balance - value >=0)
            balance-=value;
        else
            throw runtime_error("fail: saldo insuficiente");
    }

    friend ostream& operator<<(std::ostream& os, Account* account) {
        os<<account->id<<":"<<account->clientId<<":"<<account->balance<<":"<<account->type<<endl;
        return os;
    }
};

class SavingsAccount : public Account {
    public:
    SavingsAccount(int id = 0, string ClientId = "") : Account(id, ClientId) {
        type = "CP";
    }

    virtual void monthlyUpdate() {
        balance += balance;
    }
};

class CheckingAccount : public Account {
    public:
    CheckingAccount(int id = 0, string ClientId = "") : Account(id, ClientId) {
        type = "CC";
    }

    void monthlyUpdate() {
        balance -= 20;
    }
};

class Client {
    string name;
    list<shared_ptr<Account>> accounts;
public:
    Client(string clientId = "") : name(clientId) {
    }

    void addAcount(shared_ptr<Account> account) {
        accounts.push_back(account);
    }

    friend ostream& operator<<(std::ostream& os, const Client client) {
        os<<" - "<<client.name<<" [";
        for(int i=0; i<(int)client.accounts.size(); i++) {
            if(i == (int)client.accounts.size()-1) {
                os<<i;
                break;
            }
            os<<i<<", ";
        }
        os<<"]"<<endl;
        return os;
    }
};

class Bank {
    map<int, shared_ptr<Account>> accounts;
    map<string, Client> clients;

public:
    Bank() {
        
    }
    
    void addClient(string name) {
        auto it = clients.find(name);
        if(it == clients.end()) {
            clients[name] = Client(name);
            int tam = (int)accounts.size();
            accounts[tam] = make_shared<CheckingAccount>(tam, name);
            accounts[tam+1] = make_shared<SavingsAccount>(tam+1, name);
            clients[name].addAcount(accounts[tam]);
            clients[name].addAcount(accounts[tam+1]);
        }
        else
            throw runtime_error("fail: Cliente ja existe");
    }

    void deposit(int id, float value) {
        auto it = accounts.find(id);
        if(it != accounts.end()) 
            it->second->deposit(value);
        else
            throw runtime_error("fail: Conta invalida");
    }

    void montlyUpdate() {
        for(auto account : accounts)
            account.second->monthlyUpdate();
    }

    void transfer(int sender, int receiver, float value) {
        auto its = accounts.find(sender);
        auto itr = accounts.find(receiver);
        if(its != accounts.end() and itr != accounts.end()) {
                its->second->transfer(*(accounts[receiver]), value);
        }
        else
            throw runtime_error("fail: Saldo baixo");
    }
    
    void withdraw(int accountId, float value) {
        accounts[accountId]->withdraw(value);
    }

    friend ostream& operator<<(std::ostream& os, const Bank bank) {
        os<<"Clients:"<<endl;
        for(auto client : bank.clients) {
            os<<client.second;
        }
        os<<"Accounts:"<<endl;
        for(auto account : bank.accounts) {
            os<<account.second;
        }
    return os;
    }
};

int main () {
    Bank bank;
    string cmd{};
    while(cmd!="end") {
        cout<<"$";
        cin>>cmd;
        try{
        if(cmd == "end")
            break;

        else if(cmd == "addCli") {
            string name;
            cin>>name;
            bank.addClient(name);
        }
        
        else if(cmd == "deposito") {
            int id;
            float value;
            cin>>id>>value;
            bank.deposit(id, value);
        }

        else if(cmd == "transfer") {
            int de, para, value;
            cin>>de>>para>>value;
            bank.transfer(de, para, value);
        }
        else if(cmd == "saque") {
            int id, value;
            cin>>id>>value;
            bank.withdraw(id, value);
        }
        else if(cmd == "update") {
            bank.montlyUpdate();
        }

        else if(cmd == "show") 
            cout<<bank;

        } catch (std::runtime_error e) {
            cout<<e.what()<<endl;
        }
    }
}