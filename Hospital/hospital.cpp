#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <list>

using namespace std;

class IPaciente;

class IMedico {
    public:
        virtual void addPaciente(shared_ptr<IPaciente> paciente) = 0;
        virtual string getName() = 0;
        virtual string getClasse() = 0;
        virtual list<shared_ptr<IPaciente>> getPacientes() = 0;
};

class IPaciente {
    public:
        virtual void addMedico(shared_ptr<IMedico> medico) = 0;
        virtual string getName() = 0;
        virtual string getDiagnostico() = 0;
        virtual list<shared_ptr<IMedico>> getMedicos() = 0;
        virtual bool getEspecialidade(shared_ptr<IMedico> medico) = 0;
};

class Medico : public IMedico {
    string classe;
    string sender;
    map<string, shared_ptr<IPaciente>> pacientes;

    public:
    Medico(string sender, string classe) : sender{sender}, classe{classe} {

    }

    void addPaciente(shared_ptr<IPaciente> paciente) {
        auto it = pacientes.find(paciente->getName());

        if(it == pacientes.end()) {
            pacientes[paciente->getName()] = paciente;
        }
        else
            throw runtime_error("Paciente ja esta ligado ao medico");
    }

    string getName() {
        return sender;
    }

    string getClasse () {
        return classe;
    }

    list<shared_ptr<IPaciente>> getPacientes() {
        list<shared_ptr<IPaciente>> aux;
        for(auto pac : pacientes) {
            aux.push_back(pac.second);
        }
        return aux;
    }

};

class Paciente : public IPaciente {
    string diagnostico;
    string sender;
    map<string, shared_ptr<IMedico>> medicos;

    public:
    Paciente(string sender, string diagnostico) : sender{sender}, diagnostico{diagnostico}{

    }

    void addMedico(shared_ptr<IMedico> medico) {
        auto it = medicos.find(medico->getName());

        if(it == medicos.end()) {
            medicos[medico->getName()] = medico;
        }
        else
            throw runtime_error("Medico ja esta ligado ao paciente");
    }
    
    bool getEspecialidade(shared_ptr<IMedico> medico) {
        for(auto med : medicos) {
            if(med.second->getClasse() == medico->getClasse()) {
                return true;
            }
        }
        return false;
    }

    string getName() {
        return sender;
    }

    string getDiagnostico() {
        return diagnostico;
    }
    
    list<shared_ptr<IMedico>> getMedicos() {
        list<shared_ptr<IMedico>> aux;
        for(auto med : medicos) {
            aux.push_back(med.second);
        }
        return aux;
    }

};

class Hospital {
    map<string, shared_ptr<IMedico>> medicos;
    map<string, shared_ptr<IPaciente>> pacientes;

public:
    Hospital() {

    }

    void addMedico(shared_ptr<IMedico> medico) {
        auto it = medicos.find(medico->getName());

        if(it == medicos.end()) {
            medicos[medico->getName()] = medico;
        }
        else 
            throw runtime_error("Ja existe esse medico");
    }

    void addPaciente(shared_ptr<IPaciente> paciente) {
        auto it = pacientes.find(paciente->getName());

        if(it == pacientes.end()) {
            pacientes[paciente->getName()] = paciente;
        }
        else 
            throw runtime_error("Ja existe esse paciente");
    }

    void vincular(string nomeMedico, string nomePaciente) {
        auto med = medicos.find(nomeMedico);
        auto pac = pacientes.find(nomePaciente);

        if(med != medicos.end() and pac != pacientes.end()) {
            if(!pac->second->getEspecialidade(med->second)) {
                medicos[nomeMedico]->addPaciente(pacientes[nomePaciente]);
                pacientes[nomePaciente]->addMedico(medicos[nomeMedico]);
            }
            else
                throw runtime_error("Paciente ja tem um medico da especialidade");
        }
        else if(med == medicos.end()) {
            throw runtime_error("Medico nao existe");
        }
        else
            throw runtime_error("Paciente nao existe");

    }

    friend ostream& operator<<(ostream& os, const Hospital hospital) {
        for(auto pac : hospital.pacientes) {
            os<<"Pac: "<<pac.second->getName()<<":"<<pac.second->getDiagnostico()<<"   Med: [";
            
            list<shared_ptr<IMedico>> aux = pac.second->getMedicos();
            int i = 0;
            for(auto med : aux) {
                if(med->getName() == aux.back()->getName()) {
                    os<<med->getName();
                    continue;
                }
                os<<med->getName()<<", ";
            }
            os<<"]"<<endl;
        }

        for(auto med : hospital.medicos) {
            os<<"Med: "<<med.second->getName()<<":"<<med.second->getClasse()<<"   Med: [";
            
            list<shared_ptr<IPaciente>> aux = med.second->getPacientes();
            for(auto pac : aux) {
                if(pac->getName() == aux.back()->getName()) {
                    os<<pac->getName();
                    continue;
                }
                os<<pac->getName()<<", ";
            }
            os<<"]"<<endl;
        }
        return os;
    }
};

int main () {
    Hospital hospital;
    string cmd{};
    
    while(cmd!="end") {
        cout<<"$";
        string resto;
        cin>>cmd;
        getline(cin, resto);
        stringstream ss(resto);
        
        try {
            if(cmd == "addPacs") {
                string str, name, diag, aux{};
                while(ss>>str) {
                    for (int i=0; i<(int)str.size(); i++) {
                        if(str[i]=='-') {
                            name = aux;
                            aux = "";
                            continue;
                        }
                        aux+=str[i];
                        if(i == (int)str.size() - 1) {
                            diag = aux;
                            aux = "";
                        }
                    }
                    hospital.addPaciente(make_shared<Paciente>(name, diag));
                }
            }
            else if(cmd == "addMeds") {
                string str, name, diag, aux{};
                while(ss>>str) {
                    for (int i=0; i<(int)str.size(); i++) {
                        if(str[i]=='-') {
                            name = aux;
                            aux = "";
                            continue;
                        }
                        aux+=str[i];
                        if(i == (int)str.size()- 1) {
                            diag = aux;
                            aux = "";
                        }
                    }
                    hospital.addMedico(make_shared<Medico>(name, diag));
                }
            }
            else if(cmd == "tie") {
                string medico, str;
                ss>>medico;
                while(ss>>str) {
                    hospital.vincular(medico, str);
                }
            }
            else if(cmd == "show") {
                cout<<hospital;
            }
        } catch (runtime_error e) {
            cout<<"error "<<e.what()<<endl;
        }
    }
}
