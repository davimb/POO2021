#include <bits/stdc++.h>

using namespace std;

//BUSCA
bool existe(vector<int> fila, int valor) {
    
    for (int i = 0; i < (int)fila.size(); i++) {
        if(fila[i] == valor)
            return true;
    }
    return false;

}

int contar(vector<int> fila, int valor) {

    int cont=0;

    for (int i = 0; i < (int)fila.size(); i++) {
        if(fila[i] == valor)
            cont++;
    }
    return cont;

}

int procura_valor(vector<int> fila, int valor) {

    for (int i = 0; i < (int)fila.size(); i++) {
        if(fila[i] == valor)
            return i;
    }
    return -1;

}

int procurar_valor_apos(vector<int> fila, int valor, int pos) {
    
    for (int i = pos; i < (int)fila.size(); i++) {
        if(fila[i] == valor)
            return i;
    }
    return -1;

}

//MELHOR CASO
int procurar_menor(vector<int> fila) {
    
    int menor = 110;

    for (int i = 0; i < (int)fila.size(); i++)
        menor = min(fila[i], menor);

    return menor;

}

int procurar_maior(vector<int> fila) {
    
    int maior = -110;

    for (int i = 0; i < (int)fila.size(); i++)
        maior = max(fila[i], maior);

    return maior;

}

int procurar_menor_pos(vector<int> fila) {
      
    int menor = 110, resp;

    for (int i = 0; i < (int)fila.size(); i++) {
        menor = min(fila[i], menor);
        
        if(menor == fila[i])
            resp = i;
    }
    return resp;

}

int procurar_menor_pos_apos(vector<int> fila, int P) {
      
    int menor = 110, resp;

    for (int i = P+1; i < (int)fila.size(); i++) {
        menor = min(fila[i], menor);
        
        if(menor == fila[i])
            resp = i;
    }
    return resp;

}

int procurar_melhor_se(vector<int> fila) {
    
    int maior = -110, resp;

    for (int i = 0; i < (int)fila.size(); i++) {
        maior = max(fila[i], maior);
    
        if(maior ==  fila[i])
            resp = i;
    }
    return resp;

}

//CONTAGEM
double calcular_stress_medio(vector<int> fila) {

    double media = 0;
    
    for (int i = 0; i < (int)fila.size(); i++)
        media += abs(fila[i]);

    media /= (int)fila.size();
    return media;

}

string mais_homens_ou_mulheres(vector<int> fila) {

    int homem = 0, mulher = 0;

    for (int i = 0; i < (int)fila.size(); i++) {
        if(fila[i] < 0)
            mulher++;
        else
            homem++;
    }
    if(homem > mulher)
        return "mais homens";
    else
        return "mais mulheres";

}

string qual_metade_eh_mais_estressada(vector<int> fila) {
    
    int stress = 0, sinal = 1;

    for (int i=0; i<(int)fila.size(); i++) {
        if(i==(int)fila.size()/2)
            sinal=-1;
        stress+=sinal*abs(fila[i]);
    }
    if(stress>0)
        return "primeira metade";
    else 
        return "segunda metade";

}

string homens_sao_mais_estressados_que_mulheres(vector<int> fila) {

    double mediam = 0, mediah = 0;
    int contm = 1, conth = 1;

    for (int i = 0; i < (int)fila.size(); i++) {
        if(fila[i] < 0) {
            mediam += abs(fila[i]);
            contm++;
        }
        else{
            mediah = fila[i];
            conth++;
        }
    }
    mediam /= contm;
    mediah /= conth;

    if(mediam > mediah)
        return "nao";
    else
        return "sim";
        
}

//FILTER
vector<int> clonar(vector<int> fila) {

    vector<int> clone;

    for (int i = 0; i < (int)fila.size(); i++) {
        clone.push_back(fila[i]);
    }
    return clone;
    
}

vector<int> pegar_homens(vector<int> fila) {

    vector<int> homens;
    
    for (int i = 0; i < (int)fila.size(); i++) {
        if(fila[i] > 0)
            homens.push_back(fila[i]);
    }
    return homens;

}

vector<int> pegar_calmos(vector<int> fila) {

    vector<int> calmos;
    
    for (int i = 0; i < (int)fila.size(); i++) {
        if(abs(fila[i]) < 10)
            calmos.push_back(fila[i]);
    }
    return calmos;

}

vector<int> pegar_mulheres_calmas(vector<int> fila) {

    vector<int> mcalmas;
    
    for (int i = 0; i < (int)fila.size(); i++) {
        if(fila[i]<-10)
            mcalmas.push_back(fila[i]);
    }
    return mcalmas;

}

//ACESSO
vector<int> inverter_com_copia(vector<int> fila) {

    vector<int> invertido;
    
    for (int i = (int)fila.size() - 1; i >= 0; i--) {
        invertido.push_back(fila[i]);
    }
    return invertido;

}

void reverter_inplace(vector<int>& fila) {
    
    int tam = (int)fila.size()-1, aux;

    for (int i = 0; i < (int)fila.size() / 2; i++) {
        aux = fila[i];
        fila[i] = fila[tam];
        fila[tam] = aux;
        tam--;
    }

}

int sortear(vector<int> fila) {

    unsigned seed = time(0);
    srand(seed);
    return fila[rand()%(int)fila.size()];
    
}

void embaralhar(vector<int>& fila) {
  
    unsigned seed = time(0);
    srand(seed);

    int aux, random;

    for (int i = 0; i < (int)fila.size() / 2; i++) {
        random = rand()%(int)fila.size();

        if(random == i)
            continue;
            
        aux = fila[i];
        fila[i] = fila[random];
        fila[random] = aux;
    }

}

void ordenar(vector<int>& fila) {

    int pos, aux;
    
    for (int i = 0; i < (int)fila.size() - 1; i++) {
        pos = procurar_menor_pos_apos(fila, i-1);
        
        if(pos == i) 
            continue;

        aux = fila[i];
        fila[i] = fila[pos];
        fila[pos] = aux;
    }

}

//CONJUNTOS
vector<int> exclusivos(vector<int> fila) {

    vector<int> exclu;
    exclu = clonar(fila);

    for (int i = 0; i < (int)exclu.size() - 1; i++) {
        for (int j = i+1; j < (int)exclu.size(); j++) {
            
            if(exclu[i] == exclu[j]) {
                exclu.erase(exclu.begin()+j);
                j--;

            }
        }
    }
    return exclu;

}

vector<int> diferentes(vector<int> fila) {

    vector<int> dif;
    dif = clonar(fila);

    for (int i = 0; i < (int)dif.size() - 1; i++)
        dif[i] = abs(dif[i]);

    for (int i = 0; i < (int)dif.size() - 1; i++) {
        for (int j = i+1; j < (int)dif.size(); j++) {
            
            if(dif[i] == dif[j]){
                dif.erase(dif.begin()+j); 
                j--;
            }

        }
    }

    return dif;
}

vector<int> abandonados(vector<int> fila) {
    
    vector<int> exemplar, resp;
    exemplar = clonar(fila);
    
    for (int i = 0; i < (int)exemplar.size() - 1; i++) {
        for (int j = i+1; j < (int)exemplar.size(); j++) {
            
            if(exemplar[i] == exemplar[j]){
                exemplar.erase(exemplar.begin()+j); 
                j--;
            }

        }
    }
    
    int cont = 0;

    for (int i = 0; i < (int)fila.size(); i++) {
        for (int j = 0; j < (int)exemplar.size(); j++) {
            
            if(fila[i] == exemplar[j]) {
                exemplar.erase(exemplar.begin()+j);
                cont = 1;
                continue;
            }

        }
        if(cont == 0)
            resp.push_back(fila[i]);
            
        cont = 0;

    }
    return resp;

}

//MAP
vector<int> sozinhos(vector<int> fila) {
    
    vector<int> sozim;
    sozim = clonar(fila);
    int cont = 0;

    for (int i = 0; i < (int)sozim.size() - 1; i++) {
        for (int j = i+1; j < (int)sozim.size(); j++) {

            if(abs(sozim[i]) == abs(sozim[j])) {
                sozim.erase(sozim.begin()+j);
                cont = 1;
                j--;
            }

        }
        if(cont == 1){
            sozim.erase(sozim.begin()+i);
            i--;
        }
        cont = 0;
        
    }
    return sozim;

}

int mais_ocorrencias(vector<int> fila) {
    
    int maior = 0, contador = 1;

    for (int i = 0; i < (int)fila.size() - 1; i++) {
        for (int j = i+1; j < (int)fila.size(); j++) {
            
            if(abs(fila[i]) == abs(fila[j])) {
                fila.erase(fila.begin()+j);
                j--;
                contador++;
            }

        }
        fila.erase(fila.begin()+i);
        i--;
        maior = max(contador, maior);
        contador=1;
        
    }
    return maior;

}

vector<int> mais_recorrentes(vector<int> fila) {
    
    vector<int> resp;
    vector<pair<int, int>> recorrencia;
    int maior = 0, contador = 1;

    for (int i = 0; i < (int)fila.size() - 1; i++) {
        for (int j = i+1; j < (int)fila.size(); j++) {

            if(abs(fila[i]) == abs(fila[j])) {
                fila.erase(fila.begin()+j);
                j--;
                contador++;
            }

        }
        recorrencia.push_back(make_pair(fila[i], contador));
        fila.erase(fila.begin()+i);
        i--;
        maior = max(contador, maior);
        contador = 1;
        
    }
    
    for (int i = 0; i < (int)recorrencia.size(); i++) {
        if(recorrencia[i].second == maior) {
            resp.push_back(recorrencia[i].first);    
        }
    }
    return resp;

}

//PROXIMIDADE
int briga(vector<int> fila) {

    int contador = 0;

    for (int i = 1; i < (int)fila.size() - 1; i++) {
        if(fila[i] > 50 and fila[i-1] > 30 and fila[i+1] > 30){
            contador++;
        }
    }
    return contador;

}

vector<int> apaziguado(vector<int> fila) {
    
    vector<int> pos;

    for (int i = 0; i < (int)fila.size(); i++) {
        if(fila[i] > 80){
            if(i > 0 and fila[i-1] < 10)
                pos.push_back(i);
            else if(i < (int)fila.size() - 1 and fila[i+1] < 10)
                pos.push_back(i);
        }
        
    }
    return pos;

}

//SEQUENCIAS
int quantos_times(vector<int> fila) {
    
    int cont = 0, contador = 0;

    for (int i = 0; i < (int)fila.size(); i++) {

        if(fila[i] < 0 and cont == -1) {
            contador++;
            cont--;
        }
        else if(fila[i] < 0 and cont >= 0)
            cont = -1;

        if(fila[i] > 0 and cont == 1) {
            contador++;
            cont++;
        }
        else if(fila[i] > 0 and cont <= 0)
            cont = 1;

    }
    return contador;

}

int maior_time(vector<int> fila) {
    
    int cont = 0, contador = 1, maior = 0;

    for (int i = 0; i < (int)fila.size(); i++) {

        if(fila[i] < 0 and cont == -1) {
            contador++;
            maior = max(maior, contador);
        }
        else if(fila[i] < 0 and cont >= 0) {
            cont = -1;
            contador = 1;
        }

        if(fila[i] > 0 and cont == 1) {
            contador++;
            maior = max(maior, contador);
        }
        else if(fila[i] > 0 and cont <= 0) {
            cont = 1;
            contador = 1;
        }

    }
    return maior;

}

int sozinho(vector<int> fila) {
    
    int cont = 0, contador = 0;

    for (int i = 0; i < (int)fila.size(); i++) {

        if(fila[i] > 0 and (cont == 0 or cont == 1))
            cont = 10;
        else if(fila[i] < 0 and cont == 10) {
            if(fila[i+1] > 0 and i < (int)fila.size() - 1)
                contador++;
            cont = -10;
        }

        if(fila[i] < 0 and (cont == 0 or cont == -1))
            cont = -10;
        else if(fila[i] > 0 and cont == -10) {
            if(fila[i+1] < 0 and i < (int)fila.size() - 1)
                contador++;
            cont = 10;
        }

        if(i == (int)fila.size() - 1){
            if(fila[i-1] > 0 and fila[i] < 0)
                contador++;
            if(fila[i-1] < 0 and fila[i] > 0)
                contador++;
        }

        if(i == 0) {
            if(fila[i+1] > 0 and fila[i] <0)
                contador++;
            if(fila[i+1] < 0 and fila[i] > 0)
                contador++;
        }

    }
    return contador;

}

//GRUPOS
int casais(vector<int> fila) {
    
    vector<int> casal;
    casal = clonar(fila);
    int contador = 0, cont = 0;
    
    for (int i = 0; i < (int)casal.size() - 1; i++) {
        for (int j = i+1; j < (int)casal.size(); j++) {
            
            if(casal[i] == -casal[j]) {
                casal.erase(casal.begin()+j);
                cont = 1;
                j--;
                contador++;
                break;
            }
        }
        if(cont == 1) {
            casal.erase(casal.begin()+i);
            i--;
        }
        cont = 0;

    }
    return contador;

}

int trios(vector<int> fila) {
    vector<int> exclu;
    exclu = clonar(fila);
    int contador = 0, cont = 0;
    
    for (int i = 0; i < (int)exclu.size() - 1; i++) {
        for (int j = i+1; j < (int)exclu.size(); j++) {

            if(cont == 2) {
                contador++;
                break;
            }
            if(abs(exclu[i]) == abs(exclu[j])) {
                exclu.erase(exclu.begin()+j);
                cont++;
                j--;
            }
            
        }
        if(cont == 1) {
            exclu.erase(exclu.begin()+i);
            i--;
        }
        cont = 0;

    }
    return contador;
}

//ALTERACAO
void remove(vector<int>& fila, int pessoa) {

    int i = 0;

    for (; i < (int)fila.size(); i++) 
        if(fila[i] == pessoa)
            break;

    fila.erase(fila.begin()+i);
    
}

void insert(vector<int>& fila, int pessoa, int pos) {

    vector<int> inserir;

    for (int i = 0; i < (int)fila.size(); i++) {
        if( i== pos)
            inserir.push_back(pessoa);

        inserir.push_back(fila[i]);
    }
    if(pos == (int)fila.size())
        inserir.push_back(pessoa);
        
    inserir.swap(fila);

}

void dance(vector<int>&fila) {

    int cont = 1;

    while (cont > 0) {
        cont = 0;

        for (int i = 0; i < (int)fila.size() - 1; i++) {
            if(abs(fila[i]) == abs(fila[i+1])) {
                fila.erase(fila.begin()+i+1);
                fila.erase(fila.begin()+i);
                i--;
                cont++;
            }
        }

    }
    
}

int main () {

    vector<int> exemplo = {1,-1,2,12,1,2,1};

    for (int i = 0; i < (int)exemplo.size(); i++) 
        cout<<exemplo[i]<<" ";

}
