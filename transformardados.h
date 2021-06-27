#ifndef TRANSFORMARDADOS_H
#define TRANSFORMARDADOS_H
#include<QString>
#include<ctype.h>
#include<QStringList>
#include<iostream>
using namespace std;
namespace HEV
{
    class TransformarDados
    {
        public:
            TransformarDados(){}
            virtual void montarDados(string Dat)=0;
            virtual QString desmontarDados()=0;
            virtual QString getKey()=0;
            virtual QString print()=0;
    };
}
#endif // TRANSFORMARDADOS_H
