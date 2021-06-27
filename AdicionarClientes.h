#ifndef ADICIONARCLIENTES_H
#define ADICIONARCLIENTES_H

#include <QDialog>
#include<interfacecrud.h>
#include<persistenciacliente.h>
#include<persistenciapedidovenda.h>
#include<persistenciaproduto.h>
#include<QMessageBox>

namespace Ui {
class AdicionarClientes;
}

class AdicionarClientes : public QDialog
{
    Q_OBJECT

public:
    explicit AdicionarClientes(QWidget *parent = nullptr);
    ~AdicionarClientes();

private slots:
    void on_btnIncluir_clicked();

    void on_btnPesquisar_clicked();

    void on_btnEdit_clicked();

    void on_btnExcluir_clicked();

    void on_tabCliente_currentChanged(int index);

    void on_btnMostrarLista_clicked();

private:
    Ui::AdicionarClientes *ui;
    HEV::InterfaceCRUD * client;

    void limparDadosIncluir();
    void limparDadosPesquisar();
    void limparDadosExcluir();
    void limparDadosLista();
    void iniciarLista();
    void mostrarLista();
};

#endif // ADICIONARCLIENTES_H
