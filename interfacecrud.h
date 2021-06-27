#ifndef HEV_INTERFACECRUD_H
#define HEV_INTERFACECRUD_H
#include<QString>
#include<pedidovenda.h>
#include<produto.h>
#include<cliente.h>
#include<pedidovenda.h>

namespace HEV
{

    class InterfaceCRUD
    {
    public:
        InterfaceCRUD(){};
        virtual void incluir(QString valor) = 0;
        virtual QString pesquisar(QString valor)=0;
        virtual QString excluir(QString valor)=0;
        virtual void alterar(QString obj)=0;
    };

} // namespace HEV

#endif // HEV_INTERFACECRUD_H
