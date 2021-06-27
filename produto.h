#ifndef PRODUTO_H
#define PRODUTO_H
#include<QString>
#include<transformardados.h>
#include<iostream>
using namespace std;
namespace HEV
{
    class Produto: public TransformarDados
    {
    private:
        QString codigo;
        QString descricao;
        QString quantidade;
        QString preco;
    public:
        Produto();
        Produto(QString codigo, QString descricao, QString quantidade, QString preco);

        void setCodigo(QString codigo);
        void setDescricao(QString descricao);
        void setQuantidade(QString quantidade);
        void setPreco(QString preco);
        void incQuantidade(int n);

        QString getCodigo()const{return codigo;}
        QString getDescricao()const{return descricao;}
        QString getQuantidade()const{return quantidade;}
        QString getPreco()const{return preco;}


        virtual void montarDados(string Dat);
        virtual QString desmontarDados();
        virtual QString getKey(){return codigo;}
        virtual QString print();

        bool operator != (Produto &P){return codigo.toLongLong()!=P.codigo.toLongLong();}
        bool operator == (Produto &P){return codigo.toLongLong()==P.codigo.toLongLong();}
        bool operator >= (Produto &P){return codigo.toLongLong()>=P.codigo.toLongLong();}
};







}
#endif // PRODUTO_H
