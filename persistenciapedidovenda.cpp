#include "persistenciapedidovenda.h"
namespace HEV
{

    void PersistenciaPedidoVenda::incluir(QString valor)
    {
       QString id="1";
       fstream arquivoPV;
       arquivoPV.open(nomeDoArquivoPV.toStdString().c_str(), std::ios::in |std::ios::out | std::ios::app);

       if(!arquivoPV.is_open())
           throw QString("Arquivo nao foi aberto");

       ofstream tempPV;
       tempPV.open("tempPV.txt", std::ios::out | std::ios::app);

       if(!tempPV.is_open())
           throw QString("Arquivo nao foi aberto");

       string linha;
       int novoid =0;     
       PedidoVenda objInclud;
       objInclud.montarDados(valor.toStdString());

       if (!arquivoPV.eof()){
           while(getline(arquivoPV,linha))
           {
                PedidoVenda aux;
                aux.montarDados(linha);
                tempPV<<linha+"\n";
                novoid=aux.getKey().toUInt();
                id= QString::number(novoid + 1);
           }
       }

       objInclud.setIDPedido(id);
       tempPV << objInclud.desmontarDados().toStdString() + "\n";
       arquivoPV.close();
       tempPV.close();

       remove(nomeDoArquivoPV.toStdString().c_str());
       rename("tempPV.txt", nomeDoArquivoPV.toStdString().c_str());
    }

    QString PersistenciaPedidoVenda::pesquisar(QString valor)
    {
        ifstream arquivo;
        arquivo.open(nomeDoArquivoPV.toStdString().c_str(), std::ios::in);
        if(!arquivo.is_open())
            throw QString("Erro ao abrir o arquivo!");
        if(arquivo.eof())
            throw QString("Não tem pedidos");

        string linha; 
        bool ok=false;
        PedidoVenda arm;
        getline(arquivo, linha);

        while(!arquivo.eof())
        {
            PedidoVenda aux;
            aux.montarDados(linha);          
            if(aux.getKey() == valor)
            {
                arm=aux;
                ok=true;
            }
            getline(arquivo, linha);
        }
        arquivo.close();

        if(!ok)
            throw QString("Pedido não encontrado!");

        return arm.desmontarDados();
    }

    List<PedidoVenda> PersistenciaPedidoVenda::criarLista()
    {
        fstream arquivo;
        arquivo.open(nomeDoArquivoPV.toStdString().c_str(), std::ios::in |std::ios::out | std::ios::app);

        if(!arquivo.is_open())
            throw QString("Arquivo nao foi aberto");
        if(arquivo.eof())
            throw QString("Arquivo esta vazio");

        string linha;
        List<PedidoVenda> lista;

        while(getline(arquivo,linha))
        {
            PedidoVenda p;
            p.montarDados(linha);
            lista.insert(&p);
        }
        arquivo.close();
        return lista;
    }

    List<PedidoVenda> PersistenciaPedidoVenda::criarListaporCliente(QString n)
    {
        fstream arquivo;
        arquivo.open(nomeDoArquivoPV.toStdString().c_str(), std::ios::in |std::ios::out | std::ios::app);

        if(!arquivo.is_open())
            throw QString("Arquivo nao foi aberto");
        if(arquivo.eof())
            throw QString("Arquivo esta vazio");

        string linha;
        List<PedidoVenda> lista;

        while(getline(arquivo,linha))
        {
            PedidoVenda p;
            p.montarDados(linha);
            if (p.getIDCliente() == n){
                lista.insert(&p);
            }
        }
        arquivo.close();
        if (lista.size() == 0)
            throw QString("O cliente não fez nenhum pedido");
        return lista;
    }

    void PersistenciaPedidoVenda::atualizarEstoque(List<Produto> * listProd)
    {
           ofstream tempP;
           tempP.open("tempP.txt", std::ios::out | std::ios::app);

           if(!tempP.is_open())
               throw QString("Arquivo nao foi aberto");

           while(!listProd->isEmpty())
           {
               Produto aux=listProd->pegarPrimeiro();
               string texto=aux.desmontarDados().toStdString();

               tempP<<texto+"\n";
           }
           tempP.close();

           remove("arquivoProdutos.txt");
           rename("tempP.txt", "arquivoProdutos.txt");
    }
}
