/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   territorio.cpp
 * Author: Utilizador
 * 
 * Created on 18 de Novembro de 2020, 17:26
 */

#include "territorio.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <ctime>
using namespace std;

int territorio::contador = 0;

territorio::territorio(string tipo_global,string nome, int res, int p_prod, int p_ouro) {
    contador++;
    this->id_territorio = contador;
    this->tipo_global = tipo_global;
    //Adicionar id ao nome
    if(nome != "Territorio Inicial"){
        this->nome = nome + to_string(contador);
    }else{
        this->nome = nome;
    }
    
    this->res = res;
    this->p_prod = p_prod;
    this->p_ouro = p_ouro;
    this->conquistado = 0;
    this->forca_mil = 0;
    //cout << "A criar territorio \n" << getAsString(); //Mostra os territorios adicionados
}

void territorio::setForca_mil(int forca_mil) {
    this->forca_mil = forca_mil;
}

int territorio::getForca_mil() const {
    return forca_mil;
}

void territorio::setConquistado(int conquistado) {
    this->conquistado = conquistado;
}

int territorio::getConquistado() const {
    return conquistado;
}


territorio::~territorio() {
    
}

string territorio::getAsString() const{
    ostringstream os;
    os << "-------------------\n";
    os << "ID Territorio: " << id_territorio << endl;
    os << "Tipo Global: " << tipo_global << "\nTerritorio: " << nome << "\nResistencia: " << res << "\nProd Produtos: " << p_prod << "\nProd Ouro: " << p_ouro << endl;
    if(conquistado == 1){
        os << "Conquistado: Sim" << endl;
    }else{
        os << "Conquistado: Nao" << endl;
    }
    os << "-------------------\n";
    return os.str();
}

void territorio::SetP_ouro(int p_ouro) {
    this->p_ouro = p_ouro;
}

int territorio::GetP_ouro() const {
    return p_ouro;
}

void territorio::SetP_prod(int p_prod) {
    this->p_prod = p_prod;
}

int territorio::GetP_prod() const {
    return p_prod;
}

void territorio::SetRes(int res) {
    this->res = res;
}

int territorio::GetRes() const {
    return res;
}

void territorio::SetNome(string nome) {
    this->nome = nome;
}

string territorio::GetNome() const {
    return nome;
}

void territorio::SetTipo_global(string tipo_global) {
    this->tipo_global = tipo_global;
}

string territorio::GetTipo_global() const {
    return tipo_global;
}



void territorio::Conquista(){
    this->conquistado = 1;
    cout << "Territorio " << this->nome << " Conquistado" << endl;
}

void territorio::RecolhaUtils(){
    int n_p,n_o;
    n_p = this->p_prod;
    n_o = this->p_ouro;
    if(n_p < 5){
        this->p_prod ++;
    }else{
        cout << "Armazem de produtos do territorio " << this->nome << " está cheio." << endl;
    }
    if(n_o < 5){
        this->p_ouro ++;
    }else{
        cout << "Armazem de ouro do territorio " << this->nome << " está cheio" << endl;
    }
}



