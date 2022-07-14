/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Utilizador
 *
 * Created on 18 de Novembro de 2020, 17:26
 */

#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <ctime>
#include "territorio.h"
#include "settings.h"

using namespace std;

class Registo{
    vector<territorio *> territorios;
public:
    void registaTerritorio(territorio *t);
    void mostraT(string nome_ter);
    void deleteReg();
    void proc_conquista(string nome_ter);
    void proc_recolha();
};

string to_min(string inst){ //Função para colocar todas as letras em minusculo
    for(auto &c : inst){
        c = tolower(c);
    }
    return inst;
}

void Registo::proc_conquista(string nome_ter){ //Processo de conquista com as verificações necessárias
    nome_ter = to_min(nome_ter);
    string nome;
    int random =  (rand() %6) + 1; //Fator random / sorte
    int resist,forcam, conq;
    for(auto a : territorios){
        nome = a->GetNome();
        resist = a->GetRes();
        forcam = a->getForca_mil();
        conq = a->getConquistado();
        if(nome_ter == nome){ //Se esse territorio existir
            if((random+forcam) >= resist){  //verifica se o fator sorte + a força militar for superior ou igual à resistencia conquista
                if(conq != 1){
                    a->Conquista();
                }else{
                    cout << "Territorio ja foi conquistado" << endl;
                }
            }else{  //Senao cumprir as verificações falha a conquista
                cout << "Processo de conquistado falhado." << endl;
            }
        }
    }
}

void Registo::registaTerritorio(territorio *p){
    territorios.push_back(p);
}

void Registo::mostraT(string nome_ter){
    if(nome_ter == "todos"){
        //Mostra dados sobre territorio
        for(auto a: territorios){
            cout << a->getAsString();
        }
    }else{
        //Mostra apenas os territorios pretendidos
        nome_ter = to_min(nome_ter);
        string nome;
        for(auto a:territorios){
            nome = a->GetNome();
            if(nome == nome_ter){
                cout << a->getAsString();
            }
        }
    }
}

void Registo::deleteReg(){
    territorios.clear();
}

void Registo::proc_recolha(){
    for(auto a:territorios){
        a->RecolhaUtils();
    }
    cout << "Fase de Recolha completa" << endl;
}

/*
 * 
 */
int main(int argc, char** argv) {
    srand(time(NULL));
    string texto;
    string tipo_global,nome;
    int res, p_prod, p_ouro;
    //Variaveis adicionais para inserir os novos territorios pelos comandos
    string tipoG;
    int count_turno = 0; //Contador de turnos 12 turnos
    int rest, prod, ouro;
    //char c;
    Registo r; //registo de novos territorios
    vector<settings *> def;
    ifstream ter_settings("settings.txt");
    //cout << "Teste\n";
    if(ter_settings.is_open()){
        while(getline(ter_settings, texto)){
            //Ler linha a linha
            //cout << texto << endl;
            istringstream buffer(texto);
            if(buffer >> tipo_global && buffer >> nome && buffer >> res &&  buffer >> p_prod 
                        && buffer >> p_ouro){ //Ler os dados no ficheiro settings.txt 
                def.push_back(new settings(tipo_global, nome, res, p_prod, p_ouro)); //Introduzir as settings dos territorios
            }
        }
    }else{
        cout << "Não foi encontrado o ficheiro com as definições dos territorios\n";
    }
    //Mostra as pessoas no vetor settings
    /*for(auto x: def){
        x->getAsString();
    }*/
    string inst_inicial, inst, inst_f;
    string getNome;
    int quant_cria;
    cout << "Bem-vindo ao jogo" << endl;
    cout << "Introduza as instrucoes iniciais de jogo (Comandos: cria [ou] carrega)" << endl;
    getline(cin,inst_inicial); //Ler instrucoes cria <ter> <n> ou carrega <ficheiro>
    inst_inicial = to_min(inst_inicial); //Colocar para minusculo instrucao inicial
    //Criação do territorio Inicial
    r.registaTerritorio(new territorio("Territorio Inicial","Territorio Inicial", 9,1, 1)); 
    //Fase inicial 
    do{
        istringstream buffer_inst(inst_inicial);
        if(buffer_inst >> inst && getline(buffer_inst, inst_f)){
            //Separar as instrucoes dadas pelo jogador
            if(inst == "cria"){ //se indicar a opção criar, ler o nome do territorio e quantidade
                //cout << "\nComando: cria \n";
                istringstream buffer_cria(inst_f);
                string ter_nome; //Nome do territorio a criar
                int quant_ter; // Quantidade de territorios a criar
                if(buffer_cria >> ter_nome && buffer_cria >> quant_ter ){ //Se seguir este modelo de indicação
                    //Criar os novos territorios com os nomes e quantidades indicadas
                    for(auto x: def){ //Verifica se o nome do territorio é valido 
                        getNome = to_min(x->getNome());
                        if(getNome == ter_nome){ 
                            for(int i=0; i<quant_ter; i++){
                                tipoG = x->getTipo_global();
                                rest = x->getRes();
                                prod = x->getP_prod();
                                ouro = x->getP_ouro();
                                //cout << x->getNome() << " Q:" << quant_ter << " Res: " << x->getRes() << endl;
                                r.registaTerritorio(new territorio(tipoG,ter_nome, rest,prod, ouro));
                                //cout << ter_nome+to_string(i+1) << endl;
                            }
                        }
                    }
                }
            }else if(inst == "carrega"){ //se indicar a opção carrega, ler o nome do ficheiro e abrir com as definicoes dos territorios
                //cout << "\nComando: carrega \n";
                istringstream buffer_GetFicheiro(inst_f);
                string fich_texto;
                if(buffer_GetFicheiro >> fich_texto){ //Receber apenas o nome do ficheiro retirando o espaço inicial
                    cout << "Ficheiro:" << fich_texto << endl;
                    ifstream ter_carrega(fich_texto);
                    if(ter_carrega.is_open()){
                        string  nome_ter, fich_dados;
                        int quant;
                        //Abre o ficheiro com os territorios predefinidos
                        //Are o fichiro e compara com os já guardados
                        while(getline(ter_carrega, fich_dados)){ //Lê linha a linha
                            istringstream buffer_LeFich(fich_dados);
                            if(buffer_LeFich >> nome_ter && buffer_LeFich >> quant){ //Divide o nome do territorio da quantidade de territorios a criar de maneira a ficar territorio1, ...
                                for(auto x: def){ //Verifica se o nome do territorio é valido 
                                    nome_ter = to_min(nome_ter);
                                    getNome = to_min(x->getNome());
                                    if(getNome == nome_ter){ 
                                        for(int i=0; i<quant; i++){
                                            tipoG = x->getTipo_global();
                                            rest = x->getRes();
                                            prod = x->getP_prod();
                                            ouro = x->getP_ouro();
                                            //cout << x->getNome() << " Q:" << quant_ter << " Res: " << x->getRes() << endl;
                                            r.registaTerritorio(new territorio(tipoG,nome_ter, rest,prod, ouro));
                                            //cout << nome_ter+to_string(i+1) << endl;
                                        }
                                    }
                                }
                            }
                            //Só avança dps de ler "avança"
                        }
                    }else{
                        cout << "Erro ao abrir o ficheiro, tente novamente\n";
                    }
                }
            }else if(inst == "lista"){
                istringstream buffer_lista(inst_f);
                //Comando lista mostra os territorios
                string territ;
                if(buffer_lista >> territ){
                    r.mostraT(territ); //Mostra apenas o territorio indicado
                }else{
                    r.mostraT("todos"); //Mostra todos os territorios
                }
            }else{
                cout << "Erro ao ler a instrucao tente novamente.\n";
            }
        }
        //Se o utilizador quiser ver os territorios todos
        if(inst_inicial == "lista"){
            r.mostraT("todos"); //Mostra todos os territorios
        }
        cout << "Introduza as instrucoes iniciais de jogo (Comandos: cria [ou] carrega)" << endl;
        getline(cin,inst_inicial);
        inst_inicial = to_min(inst_inicial);
    }while(inst_inicial != "avanca");
    //Fase da Conquista
    string inst_sec;
    cout << "Introduza o comando a executar:" << endl;
    getline(cin, inst_sec); //Lê a instrução a executar
    do{
        istringstream buffer_inst(inst_sec);
        if(buffer_inst >> inst && getline(buffer_inst, inst_f) || getline(buffer_inst, inst)){  //Separar as intruções dadas pelo jogador
            if(inst == "conquista"){ //Inicia o processo de conquista
                istringstream buffer_conquista(inst_f);
                string n_ter;
                if(buffer_conquista >> n_ter){
                    r.proc_conquista(n_ter); //Adiciona o nome ao processo de conquista
                }
                //Fase de recolha de produtos e ouro
                r.proc_recolha();
                count_turno++;
            }else if(inst == "lista"){
                istringstream buffer_lista(inst_f);
                //Comando lista mostra os territorios
                string territ;
                if(buffer_lista >> territ){
                    r.mostraT(territ); //Mostra apenas o territorio indicado
                }else{
                    r.mostraT("todos"); //Mostra todos os territorios
                }
            }else{
                cout << "Erro ao ler a instrucao tente novamente.\n";
            }
        }
        //Se o utilizador quiser ver os territorios todos
        if(inst_sec == "lista"){
            r.mostraT("todos"); //Mostra todos os territorios
        }else if(inst_sec == "passa"){ //O processo de conquistar é passado
            cout << "Processo de conquistado passado." << endl;
            //Fase de recolha de produtos e ouro
            r.proc_recolha();
            count_turno++;
        }
        cout << "Introduza o comando a executar:" << endl;
        getline(cin, inst_sec); //Lê a instrução a executar
        inst_sec = to_min(inst_sec);
    }while(inst_sec != "avanca" && count_turno <= 12);
    //Mostra os dados todos do vetor territorios
    r.mostraT("todos"); //Mostra todos os territorios
    r.deleteReg(); //Apaga os dados 
    return 0;
}

