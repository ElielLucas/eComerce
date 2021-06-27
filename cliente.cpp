#include "cliente.h"
namespace HEV
{
Cliente::Cliente():
    id(""),
    nome(""),
    endereco(""),
    telefone(""),
    cpf("")
{

}
Cliente::Cliente(QString id, QString nome, QString endereco, QString telefone, QString cpf)
{
    setID(id);
    setNome(nome);
    setEndereco(endereco);
    setTelefone(telefone);
    setCpf(cpf);
}

void Cliente::setNome(QString nome)
{
    int i;
    for (i = 0; i < nome.size() && ((nome[i] >= 'A' && nome[i] <= 'Z') || (nome[i] == ' ') || (nome[i] >= 'a' && nome[i] <= 'z')); i++);
    if (i != nome.size())
        throw QString("Nome invalido");

    QString aux="";
    QChar p=nome[0];
    aux+=p.toUpper();
    for(int i=1;i<nome.size();i++)
    {
        aux+=nome[i].toLower();
    }
    this->nome = aux;
}

void Cliente::setEndereco(QString endereco)
{
    if (endereco == "")
        throw QString("Endereco invalido");
    QString aux="";
    QChar p=endereco[0];
    aux+=p.toUpper();
    for(int i=1;i<endereco.size();i++)
    {
        aux+=endereco[i].toLower();
    }

    this->endereco = aux;
}

void Cliente::setTelefone(QString telefone)
{
    int i;
    // verificar se so tem numeros
    for (i = 0; i < telefone.size() && (telefone[i] >= '0' && telefone[i] <= '9'); i++);
    if (i != telefone.size())
        throw QString("Telefone invalido");
    this->telefone = telefone;

}
void Cliente::montarDados(string Dat)
{
    QString copDat=QString::fromStdString(Dat),aux="";

    int i = 0;
    for(;i<copDat.size() && copDat[i] != ';';i++){
        aux+=Dat[i];
    }
    id=aux;
    aux = "";
    for(i++;i<copDat.size() && copDat[i] != ';';i++){
        aux+=Dat[i];
    }
    nome=aux;
    aux = "";
    for(i++;i<copDat.size() && copDat[i] != ';';i++){
        aux+=Dat[i];
    }
    endereco=aux;
    aux = "";
    for(i++;i<copDat.size() && copDat[i] != ';';i++){
        aux+=Dat[i];
    }
    telefone=aux;
    aux="";
    for(i++;i<copDat.size() && copDat[i] != ';';i++){
        aux+=Dat[i];
    }
    cpf=aux;
}

QString Cliente::desmontarDados()
{
    QString aux="";
    aux+=id+";";
    aux+=nome+";";
    aux+=endereco+";";
    aux+=telefone+";";
    aux+=cpf+";";

    return aux;
}
void Cliente::setCpf(QString CPF)
{
    QString aux;
    // Elimina CPFs invalidos conhecidos
    if (CPF.length() != 11   ||
        CPF == "00000000000" ||
        CPF == "11111111111" ||
        CPF == "22222222222" ||
        CPF == "33333333333" ||
        CPF == "44444444444" ||
        CPF == "55555555555" ||
        CPF == "66666666666" ||
        CPF == "77777777777" ||
        CPF == "88888888888" ||
        CPF == "99999999999" ||
        CPF == "")
        throw QString("CPF inválido!");

    int digito1=0;
    int digito2=0;
    /*/////////////////////Digito1//////////////////////////////////*/
    for(int i = 0, j = 10; i < CPF.length()-2; i++, j--)
    {
        aux=CPF[i];
        digito1+=aux.toInt()*j;
    }
    digito1%=11;
    if(digito1 < 2) digito1 = 0;
    else digito1 = 11 - digito1%11;

    aux=CPF[9];
    if((aux.toInt()) != digito1) throw QString("CPF inválido!");

    /*//////////////////////Digito2/////////////////////////////////*/
    for(int i = 0, j = 11; i < CPF.length()-1; i++, j--)
    {
        aux=CPF[i];
        digito2+=aux.toInt()*j;
    }
    digito2%=11;
    if(digito2 < 2) digito2 = 0;
    else digito2 = 11 - digito2%11;

    aux=CPF[10];
    if((aux.toInt()) != digito2) throw QString("CPF inválido!");

    cpf=CPF;
}

QString Cliente::print()
{
    QString saida="";

    saida+="ID do Cliente: "+id;
    saida+="\nNome: "+nome;
    saida+="\nEndereço: "+endereco;
    saida+="\nTelefone: "+telefone;
    saida+="\nCPF: "+cpf+"\n\n";

    return saida;
}




}
