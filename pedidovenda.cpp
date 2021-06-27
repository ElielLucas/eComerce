#include "pedidovenda.h"

namespace HEV
{
    PedidoVenda::PedidoVenda():
        idPedido("0"),
        idCliente(""),
        dataCompra(""),
        listaProduto()
    {
    }
    PedidoVenda::PedidoVenda(QString idPedido, QString idCliente, int dia, int mes, int ano, QString total)
    {
        setIDPedido(idPedido);
        setIDCliente(idCliente);
        setDataCompra(dia, mes, ano);
        setValorTotal(total);
    }

    void PedidoVenda::setDataCompra(int dia, int mes, int ano)
    {
        int tmes[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
        if(ano > 2020 || ano < 2000)
            throw QString("Ano Inválido");
        if(mes > 12 || mes < 1)
            throw QString("Mês Inválido");
        if(dia > tmes[mes-1] || dia < 1)
            throw QString("Dia Inválido");
        dataCompra = QString::number(dia) + "/" + QString::number(mes) + "/" + QString::number(ano);
    }

    void PedidoVenda::setValorTotal(QString total)
    {
        int n;
        // verificar se so tem numeros e o ponto
        for (n = 0; n < total.size() && ((total[n] >= '0' && total[n] <= '9') || total[n] == '.'); n++);
        if (n != total.size())
            throw QString("Total invalido");
        QString nova ="", aux = total;
        int i;
        for (i = 0; i < aux.size() && aux[i] != '.'; i++){
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
        total = nova;
        valorTotal = total;
    }

    void PedidoVenda::setLista(List<Produto> *lista)
    {
        while (!(lista)->isEmpty()){
            Produto p = lista->pegarPrimeiro();
            listaProduto.insert(&p);
        }
    }

    void PedidoVenda::montarDados(string Dat)
    {   
        QString copDat=QString::fromStdString(Dat),aux="";
        Produto x;

        int i = 0;
        for(;i<copDat.size() && copDat[i] != ';';i++){
            aux+=Dat[i];
        }
        idCliente=aux;
        aux = "";
        for(i++;i<copDat.size() && copDat[i] != ';';i++){
            aux+=Dat[i];
        }
        idPedido=aux;
        aux = "";
        for(i++;i<copDat.size() && copDat[i] != ';';i++){
            aux+=Dat[i];
        }
        dataCompra=aux;
        aux = "";
        for(i++;i<copDat.size() && copDat[i] != ';';i++){
            aux+=Dat[i];
        }
        valorTotal=aux;
        aux="";
        i=i+2;
        while (copDat[i] != '-') {
            for(;i<copDat.size() && copDat[i] != ';';i++){
                aux+=Dat[i];
            }       
            x.setCodigo(aux);          
            aux = "";
            for(i++;i<copDat.size() && copDat[i] != ';';i++){
                aux+=Dat[i];
            }
            x.setDescricao(aux);
            aux = "";
            for(i++;i<copDat.size() && copDat[i] != ';';i++){
                aux+=Dat[i];
            }
            x.setQuantidade(aux);
            aux = "";
            for(i++;i<copDat.size() && copDat[i] != '*';i++){
                aux+=Dat[i];
            }
            x.setPreco(aux);          
            aux = "";
            listaProduto.insert(&x);          
            i++;
        }

    }

    QString PedidoVenda::desmontarDados()
    {
        QString saida = "";
        saida += idCliente+";";
        saida += idPedido +";";
        saida += dataCompra+";";
        saida += valorTotal+";";
        saida += "*";

        while(!listaProduto.isEmpty())
        {
            Produto x=listaProduto.pegarPrimeiro();
            saida+=x.getCodigo()+";"+x.getDescricao()+";"+x.getQuantidade()+";"+x.getPreco()+"*";
        }
        saida+="-";
        return saida;
    }
    
    QString PedidoVenda::print()
    {
        QString saida="";
        saida+="ID do Pedido: "+idPedido+"\n";
        saida+="ID do Cliente: "+idCliente+"\n";
        saida+="Data da Compra: "+dataCompra+"\n";
        saida+="Valor total: "+valorTotal+"\n\n";
        List<Produto> aux=listaProduto;       
        int cont=1;
        while(!aux.isEmpty())
        {
            saida+="Produto "+QString::number(cont)+":"+"\n";
            saida+=aux.pegarPrimeiro().print();
            cont++;
        }       
        return saida;
    }

} // namespace HEV
