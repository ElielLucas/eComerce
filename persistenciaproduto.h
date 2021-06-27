#ifndef PERSISTENCIAPRODUTO_H
#define PERSISTENCIAPRODUTO_H
#include<fstream>
#include<QString>
#include<interfacecrud.h>
#include<produto.h>
#include<list.h>
using std::ifstream;
using std::ofstream;
using std::string;
namespace HEV
{
    class PersistenciaProduto: public InterfaceCRUD
    {
        private:
            QString nomeDoArquivoP;
        public:
            PersistenciaProduto(QString nomeDoArquivo);
            virtual void incluir(QString valor);
            virtual QString excluir(QString valor);
            virtual QString pesquisar(QString valor);
            void alterar(QString obj);
            List<Produto> criarLista();
    };
}
#endif // PERSISTENCIAPRODUTO_H
