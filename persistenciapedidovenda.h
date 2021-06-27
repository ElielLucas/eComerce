#ifndef PERSISTENCIAPEDIDOVENDA_H
#define PERSISTENCIAPEDIDOVENDA_H
#include<fstream>
#include<QString>
#include<interfacecrud.h>
#include<pedidovenda.h>
#include<list.h>

using std::ifstream;
using std::ofstream;
using std::string;
namespace HEV
{
    class PersistenciaPedidoVenda: public InterfaceCRUD
    {
        private:
            QString nomeDoArquivoPV;
        public:
            PersistenciaPedidoVenda(QString nomeDoArquivo): nomeDoArquivoPV(nomeDoArquivo){}
            virtual void incluir(QString valor);
            virtual QString pesquisar(QString valor);
            virtual QString  excluir(QString valor){}//podem ser inseridas em uma atualizacao
            virtual void alterar(QString obj){}//podem ser inseridas em uma atualizacao
            List<PedidoVenda> criarLista();
            List<PedidoVenda> criarListaporCliente(QString n);
            void atualizarEstoque(List<Produto>* listProd);
    };
}

#endif // PERSISTENCIAPEDIDOVENDA_H
