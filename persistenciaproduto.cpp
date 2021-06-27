#include "persistenciaproduto.h"
namespace HEV
{
    PersistenciaProduto::PersistenciaProduto(QString nomeDoArquivo):
            nomeDoArquivoP(nomeDoArquivo)
    {       
    }
    void PersistenciaProduto::incluir(QString valor)
    {
        fstream arquivo;
        arquivo.open(nomeDoArquivoP.toStdString().c_str(), std::ios::in |std::ios::out | std::ios::app);

        if(!arquivo.is_open())
             throw QString("Arquivo nao foi aberto");

        string linha;
        List<Produto> lista;
        Produto inserir;
        bool ok = false;
        inserir.montarDados(valor.toStdString());

        while(getline(arquivo,linha))
        {
             Produto aux;
             aux.montarDados(linha);
             if(aux.getCodigo()==inserir.getCodigo())
             {
                  ok=true;
             }else lista.insert(&aux);
        }

        if (!ok)lista.insert(&inserir);

        arquivo.close();

        ofstream temp;
        temp.open("temp.txt", std::ios::out | std::ios::app);

        if(!temp.is_open())
            throw QString("Arquivo nao foi aberto");

        while(!lista.isEmpty())
        {
            Produto aux=lista.pegarPrimeiro();
            QString texto=aux.desmontarDados();         
            temp<<texto.toStdString()+"\n";
        }
        temp.close();
        remove(nomeDoArquivoP.toStdString().c_str());
        rename("temp.txt", nomeDoArquivoP.toStdString().c_str());
        if (ok)
           throw QString("No estoque, já existe outro produto com este código");
    }

    List<Produto> PersistenciaProduto::criarLista()
    {
        fstream arquivo;
        arquivo.open(nomeDoArquivoP.toStdString().c_str(), std::ios::in |std::ios::out | std::ios::app);

        if(!arquivo.is_open())
            throw QString("Arquivo nao foi aberto");
        if(arquivo.eof())
            throw QString("Nao foi possivel gerar lista.\n Nao tem estoque!");

        string linha;
        List<Produto> lista;

        while(getline(arquivo,linha))
        {
            Produto p;
            p.montarDados(linha);
            lista.insert(&p);
        }
        arquivo.close();
        return lista;
    }

    QString PersistenciaProduto::excluir(QString valor)
    {
        ifstream arquivo;
        arquivo.open(nomeDoArquivoP.toStdString().c_str(), std::ios::in);
        if(!arquivo.is_open())
            throw QString("Arquivo nao foi aberto");

        if(arquivo.eof())
            throw QString("Nao foi possivel excluir.\n Nao tem estoque!");

        ofstream temp;
        temp.open("temp.txt", std::ios::out);
        if(!temp.is_open())
            throw QString("Erro de arquivo");

        string linha;
        Produto aux,dat;
        bool ok=false;
        while(getline(arquivo, linha))
        {          
            aux.montarDados(linha);
            if(aux.getKey() != valor)
                temp << linha + "\n";
            else
            {
                dat = aux;
                ok = true;
            }
        }
        arquivo.close();
        temp.close();

        remove(nomeDoArquivoP.toStdString().c_str());
        rename("temp.txt", nomeDoArquivoP.toStdString().c_str());

        if(!ok)throw QString("O produto não foi encontrado em estoque!");

        return dat.desmontarDados();
    }
    QString PersistenciaProduto::pesquisar(QString valor)
    {
        ifstream arquivo;
        arquivo.open(nomeDoArquivoP.toStdString().c_str(), std::ios::in);
        if(!arquivo.is_open())
            throw QString("Arquivo não foi aberto");
        if(arquivo.eof())
            throw QString("Nao foi possivel procurar.\n Nao tem estoque!");

        string linha;
        Produto aux,arm;
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
            throw QString("Produto nao encontrado");

        return arm.desmontarDados();
    }
    void PersistenciaProduto::alterar(QString obj)
    {
            ifstream arquivo;
            arquivo.open(nomeDoArquivoP.toStdString().c_str(), std::ios::in);
            if(!arquivo.is_open())
                throw QString("Arquivo não foi aberto");
            if(arquivo.eof())
                throw QString("Nao foi possivel alterar.\n Nao tem estoque!");

            ofstream temp;
            temp.open("temp.txt", std::ios::out);
            if(!temp.is_open())
                throw QString("Erro de arquivo");

            string linha;
            Produto aux,arm,dadosAlterados;
            dadosAlterados.montarDados(obj.toStdString());
            bool ok=false;
            while(getline(arquivo, linha))
            {
                aux.montarDados(linha);
                if(aux.getCodigo() == dadosAlterados.getCodigo())
                {
                    aux.setDescricao(dadosAlterados.getDescricao());
                    aux.setQuantidade(dadosAlterados.getQuantidade());
                    aux.setPreco(dadosAlterados.getPreco());

                    linha=aux.desmontarDados().toStdString();
                    ok=true;
                }
                temp << linha + "\n";
            }
            arquivo.close();
            temp.close();

            remove(nomeDoArquivoP.toStdString().c_str());
            rename("temp.txt", nomeDoArquivoP.toStdString().c_str());
            if(!ok)
                throw QString("Não foi possível alterar!");
    }

}

