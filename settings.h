/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   settings.h
 * Author: Utilizador
 *
 * Created on 18 de Novembro de 2020, 18:09
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

using namespace std;

class settings {
    string tipo_global,nome;
    int res, p_prod, p_ouro;
public:
    settings(string tipo_global,string nome, int res, int p_prod, int p_ouro);
    ~settings();
    string getAsString() const;
    void setP_ouro(int p_ouro);
    int getP_ouro() const;
    void setP_prod(int p_prod);
    int getP_prod() const;
    void setRes(int res);
    int getRes() const;
    void setNome(string nome);
    string getNome() const;
    void setTipo_global(string tipo_global);
    string getTipo_global() const;
    //tolower
};

#endif /* SETTINGS_H */

