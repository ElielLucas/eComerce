#ifndef PERSISTENCIACLIENTE_H
#define PERSISTENCIACLIENTE_H
#include<cliente.h>
#include<list.h>
#include<fstream>
#include<QString>
#include<interfacecrud.h>
using std::ifstream;
using std::ofstream;
using std::string;
namespace HEV
{
    class PersistenciaCliente: public InterfaceCRUD
    {
        private:
            QString nomeDoArquivoC;
        public:
            PersistenciaCliente(QString nomeDoArquivo):nomeDoArquivoC(nomeDoArquivo){}
            virtual void incluir(QString valor);
            virtual QString excluir(QString valor);
            virtual QString pesquisar(QString valor);
            virtual void alterar(QString obj);
            List<Cliente> criarLista();
    };

}

#endif // PERSISTENCIACLIENTE_H
