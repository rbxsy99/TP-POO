/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   settings.cpp
 * Author: Utilizador
 * 
 * Created on 18 de Novembro de 2020, 18:09
 */

#include "settings.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

settings::settings(string tipo_global,string nome, int res, int p_prod, int p_ouro) {
    this->tipo_global = tipo_global;
    this->nome = nome;
    this->res = res;
    this->p_prod = p_prod;
    this->p_ouro = p_ouro;
}


settings::~settings() {
}

string settings::getAsString() const{
    ostringstream os;
    os << "Territorio:" << nome << "\nResistencia: " << res << "\nProd Produtos: " << p_prod << "\nProd Ouro:" << p_ouro;
    os << "-------------------\n";
    return os.str();
}

void settings::setP_ouro(int p_ouro) {
    this->p_ouro = p_ouro;
}

int settings::getP_ouro() const {
    return p_ouro;
}

void settings::setP_prod(int p_prod) {
    this->p_prod = p_prod;
}

int settings::getP_prod() const {
    return p_prod;
}

void settings::setRes(int res) {
    this->res = res;
}

int settings::getRes() const {
    return res;
}

void settings::setNome(string nome) {
    this->nome = nome;
}

string settings::getNome() const {
    return nome;
}

void settings::setTipo_global(string tipo_global) {
    this->tipo_global = tipo_global;
}

string settings::getTipo_global() const {
    return tipo_global;
}

