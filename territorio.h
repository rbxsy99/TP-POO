/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   territorio.h
 * Author: Utilizador
 *
 * Created on 18 de Novembro de 2020, 17:26
 */

#ifndef TERRITORIO_H
#define TERRITORIO_H

#include <string>

using namespace std;

class territorio {
    int id_territorio;
    string tipo_global,nome;
    int res, p_prod, p_ouro, conquistado;
    int forca_mil;
    static int contador; //Para adicionar ao nome de territorio 
    //conquistado = 1 -> conquistado
    //territorio inicial
public:
    territorio(string tipo_global,string nome, int res, int p_prod, int p_ouro);
    ~territorio();
    std::string getAsString() const;
    void SetP_ouro(int p_ouro);
    int GetP_ouro() const;
    void SetP_prod(int p_prod);
    int GetP_prod() const;
    void SetRes(int res);
    int GetRes() const;
    void SetNome(string nome);
    string GetNome() const;
    void SetTipo_global(string tipo_global);
    string GetTipo_global() const;
    void Conquista();
    void setForca_mil(int forca_mil);
    int getForca_mil() const;
    void setConquistado(int conquistado);
    int getConquistado() const;
    void RecolhaUtils();
};

#endif /* TERRITORIO_H */

