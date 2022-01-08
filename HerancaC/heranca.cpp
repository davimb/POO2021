#include <iostream>
using namespace std;

class Automovel {
    private:
        bool working{true};
    protected:
        string mark{"Automovel"};
    public:
        Automovel() {

        }
        
        virtual void dirigir() {
            cout<<mark<<" esta andando"<<endl;
        }
        
        virtual void broke() {  
            working = false;    
        }

        virtual bool itWorks() {
            return working;
        }

    friend std::ostream& operator<<(std::ostream& os, const Automovel& automovel) {
        os << automovel.mark << " esta " << (automovel.working ? "funcionando" : "quebrado")<<endl;
        return os;
    }

};

class Carro : public Automovel{
    private:
        string marca;
        string modelo;
        int VelMax;
    public:
        Carro(string marca, string modelo, int VelMax) : marca{marca}, modelo{modelo}, VelMax{VelMax} {
            mark =  "Carro";
        }
        
        virtual int getVelMax() {
            return VelMax;
        }

        virtual void broke() {
            VelMax = 0;
            Automovel::broke();
        }

        friend std::ostream& operator<<(std::ostream& os, Carro& carro) {
            Automovel* automovel = &carro;
            os << *automovel << endl << "Marca = " << carro.marca << " : Modelo = " << carro.modelo << " : Velocidade Max = " << carro.VelMax<<endl;
            return os;
        }
};

class Ferrari : public Carro{
    private:
    public:
        Ferrari(string modelo, int VelMax) : Carro("Ferrari", modelo, VelMax) {
            mark = "Ferrari";
        }
        
        virtual void dirigir() {
            if(getVelMax()>=300) {
                cout<<mark<<" esta voando"<<endl;
            }
            else
                Automovel::dirigir();
        }

        virtual void broke() {
            cout<<"quebrou, mas como somos ricos ja compramos outra do mesmo modelo"<<endl;
        }

    friend std::ostream& operator<<(std::ostream& os, Ferrari& ferrari) {
        Carro* carro = &ferrari;
        os << *carro << endl << "Pronto para acelerar"<<endl;
        return os;
    }
};

int main () {

    Ferrari ferrari("Italia", 320);
    Automovel &automovel = ferrari;
    automovel.broke();
}