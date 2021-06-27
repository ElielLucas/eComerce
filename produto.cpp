#include "produto.h"
namespace HEV
{
Produto::Produto():
    codigo(""),
    descricao(""),
    quantidade(""),
    preco("")
{
}
Produto::Produto(QString codigo, QString descricao, QString quantidade, QString preco)
{
    setCodigo(codigo);
    setDescricao(descricao);
    setQuantidade(quantidade);
    setPreco(preco);
}
void Produto::setCodigo(QString codigo)
{
    long long int aux=codigo.toUInt();
    if(aux<=0)throw QString("Código inválido!");
    this->codigo=codigo;
}
void Produto::setDescricao(QString descricao)
{
    if(descricao=="")throw QString("Descrição inválida!");
    QString aux="";
    QChar p=descricao[0];
    aux+=p.toUpper();
    for(int i=1;i<descricao.size();i++)
    {
        aux+=descricao[i].toLower();
    }
    this->descricao=aux;
}
void Produto::setQuantidade(QString quantidade)
{
    int n=quantidade.toInt();
    if(n<=0)throw QString("Essa quantidade é inválida!");
    this->quantidade=quantidade;
}
void Produto::setPreco(QString preco)
{
    int n;

    for (n = 0; n < preco.size() && ((preco[n] >= '0' && preco[n] <= '9') || preco[n] == '.'); n++);
    if (n != preco.size())
        throw QString("Preco invalido");
    int i = 0;
    QString nova ="", aux = preco;
    for (; i < aux.size() && aux[i] != '.'; i++){
        nova+=aux[i];
    }
    nova += ".";
    if (i == aux.size()){
        nova += "00";
    }else{
        nova += aux[i+1];
        if (i+ 2 == aux.size()){
            nova += "0";
        }else{
            nova += aux[i+2];
        }
    }
    preco = nova;
    this->preco=preco;
}

void Produto::incQuantidade(int n)
{
    int aux=quantidade.toInt()+n;
    quantidade=QString::number(aux);
}
void Produto::montarDados(string Dat)
{
    QString copDat=QString::fromStdString(Dat),aux="";

    int i = 0;
    for(;i<copDat.size() && copDat[i] != ';';i++){
        aux+=Dat[i];
    }
    codigo=aux;
    aux = "";
    for(i++;i<copDat.size() && copDat[i] != ';';i++){
        aux+=Dat[i];
    }
    descricao=aux;
    aux = "";
    for(i++;i<copDat.size() && copDat[i] != ';';i++){
        aux+=Dat[i];
    }
    quantidade=aux;
    aux = "";
    for(i++;i<copDat.size() && copDat[i] != ';';i++){
        aux+=Dat[i];
    }
    preco=aux;
}
QString Produto::desmontarDados()
{
    QString aux="";
    aux+=codigo+";";
    aux+=descricao+";";
    aux+=quantidade+";";
    aux+=preco+";";

    return aux;
}

QString Produto::print()
{
    QString aux="";
    aux+="Código: "+codigo+"\n";
    aux+="Descrição: "+descricao+"\n";
    aux+="Quantidade: "+quantidade+"\n";
    aux+="Preço unitário: "+preco+"\n";

    return aux;
}

}
