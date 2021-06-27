#ifndef ADICIONARPRODUTOS_H
#define ADICIONARPRODUTOS_H

#include <QDialog>
#include<interfacecrud.h>
#include<persistenciacliente.h>
#include<persistenciapedidovenda.h>
#include<persistenciaproduto.h>
#include<QMessageBox>

namespace Ui {
class AdicionarProdutos;
}

class AdicionarProdutos : public QDialog
{
    Q_OBJECT

public:
    explicit AdicionarProdutos(QWidget *parent = nullptr);
    ~AdicionarProdutos();

private slots:
    void on_btnIncluir_clicked();

    void on_btnPesquisar_clicked();

    void on_btnEdit_clicked();

    void on_btnExcluir_clicked();

    void on_btnMostrarLista_clicked();

    void on_tabProdutos_currentChanged(int index);

private:
    Ui::AdicionarProdutos *ui;
    HEV::InterfaceCRUD * produt;

    void limparDadosIncluir();
    void limparDadosPesquisar();
    void limparDadosExcluir();
    void iniciarLista();
    void mostrarLista();
};

#endif // ADICIONARPRODUTOS_H
