#include "persistenciacliente.h"
namespace HEV
{
    void PersistenciaCliente::incluir(QString valor)
    {
        fstream arquivo;
        arquivo.open(nomeDoArquivoC.toStdString().c_str(), std::ios::in |std::ios::out | std::ios::app);
        QString id = "1";
        if(!arquivo.is_open())
            throw QString("Arquivo nao foi aberto");

        ofstream tempC;
        tempC.open("tempC.txt", std::ios::out | std::ios::app);

        if(!tempC.is_open())
            throw QString("Arquivo nao foi aberto");

        string linha;
        int novoid =0;
        bool ok = false;
        Cliente objInclud;
        objInclud.montarDados(valor.toStdString());
        getline(arquivo,linha);
        while(!arquivo.eof())
        {
            Cliente aux;
            aux.montarDados(linha);
            tempC << linha  + "\n";
            novoid = aux.getKey().toUInt();        
            id = QString::number(novoid + 1);

            if(aux.getCPF() == objInclud.getCPF()) ok = true;

            getline(arquivo,linha);
        }
        if(ok)
        {
            tempC.close();
            remove("tempC.txt");
            arquivo.close();
            throw QString("CPF ja inserido");
        }

        objInclud.setID(id);
        tempC << objInclud.desmontarDados().toStdString() + "\n";
        arquivo.close();
        tempC.close();

        remove(nomeDoArquivoC.toStdString().c_str());
        rename("tempC.txt", nomeDoArquivoC.toStdString().c_str());       
    }

    QString PersistenciaCliente::excluir(QString valor)
    {
        ifstream arquivo;
        arquivo.open(nomeDoArquivoC.toStdString().c_str(), std::ios::in);
        if(!arquivo.is_open())
            throw QString("Arquivo nao foi aberto");

        if(arquivo.eof())
            throw QString("Nao foi possivel excluir.\n A lista esta vazia!");

        ofstream tempC;
        tempC.open("tempC.txt", std::ios::out);
        if(!tempC.is_open())
            throw QString("Erro de arquivo");

        string linha;
        Cliente aux, dat;
        bool ok=false;
        while(getline(arquivo, linha))
        {
            aux.montarDados(linha);
            if(aux.getKey() != valor)
                tempC << linha + "\n";
            else
            {
                dat = aux;
                ok = true;
            }
        }
        arquivo.close();
        tempC.close();

        remove(nomeDoArquivoC.toStdString().c_str());
        rename("tempC.txt", nomeDoArquivoC.toStdString().c_str());

        if(!ok)throw QString("O cliente não foi encontrado!");

        return dat.desmontarDados();
    }

    QString PersistenciaCliente::pesquisar(QString valor)
    {
        ifstream arquivo;
        arquivo.open(nomeDoArquivoC.toStdString().c_str(), std::ios::in);
        if(!arquivo.is_open())
            throw QString("Arquivo não foi aberto");
        if(arquivo.eof())
            throw QString("Nao foi possivel procurar.\n A lista esta vazia!");

        string linha;
        Cliente aux,arm;
        bool ok=false;
        getline(arquivo, linha);
        while(!arquivo.eof())
        {
            aux.montarDados(linha);
            if(aux.getKey() == valor)
            {
                arm=aux;
                ok=true;
            }
            getline(arquivo, linha);
        }

        arquivo.close();
        if (!ok)
            throw QString("Cliente nao encontrado");

        return arm.desmontarDados();
    }

    void PersistenciaCliente::alterar(QString obj)
    {
        ifstream arquivo;
        arquivo.open(nomeDoArquivoC.toStdString().c_str(), std::ios::out);
        if(!arquivo.is_open())
            throw QString("Arquivo não foi aberto");
        if(arquivo.eof())
            throw QString("Nao foi possivel alterar.\n A lista esta vazia!");

        ofstream temp;
        temp.open("tempC.txt", std::ios::out);
        if(!temp.is_open())
            throw QString("Erro de arquivo");

        string linha;
        Cliente aux,arm, dadosAlterados;
        dadosAlterados.montarDados(obj.toStdString());
        bool ok = false;
        while(getline(arquivo, linha))
        {
            aux.montarDados(linha);
            if(aux.getKey() == dadosAlterados.getKey())
            {
                aux.setNome(dadosAlterados.getNome());
                aux.setEndereco(dadosAlterados.getEndereco());
                aux.setTelefone(dadosAlterados.getTelefone());
                aux.setCpf(dadosAlterados.getCPF());

                linha = aux.desmontarDados().toStdString();
                ok = true;
            }
            temp << linha + "\n";
        }
        arquivo.close();
        temp.close();

        remove(nomeDoArquivoC.toStdString().c_str());
        rename("tempC.txt", nomeDoArquivoC.toStdString().c_str());
        if(!ok)
            throw QString("Nao foi possível alterar!");
    }

    List<Cliente> PersistenciaCliente::criarLista()
    {
        fstream arquivo;
        arquivo.open(nomeDoArquivoC.toStdString().c_str(), std::ios::in |std::ios::out | std::ios::app);

        if(!arquivo.is_open())
            throw QString("Arquivo nao foi aberto");
        if(arquivo.eof())
            throw QString("Nao foi possivel gerar a lista.\n A lista esta vazia!");

        string linha;
        List<Cliente> lista;

        while(getline(arquivo,linha))
        {
            Cliente p;
            p.montarDados(linha);
            lista.insert(&p);
        }
        arquivo.close();
        return lista;
    }


}
