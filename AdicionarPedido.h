#ifndef ADICIONARPEDIDO_H
#define ADICIONARPEDIDO_H

#include<interfacecrud.h>
#include<persistenciacliente.h>
#include<persistenciapedidovenda.h>
#include<persistenciaproduto.h>
#include<QMessageBox>
#include<QInputDialog>
#include <QDialog>

namespace Ui {
class AdicionarPedido;
}

class AdicionarPedido : public QDialog
{
    Q_OBJECT

public:
    explicit AdicionarPedido(QWidget *parent = nullptr);
    ~AdicionarPedido();

private slots:
    void on_btnPesquisarCliente_clicked();

    void on_btnNovoPedido_clicked();

    void on_btnAdicionar_clicked();

    void on_btnExcluir_clicked();

    void on_btnFinalizarPedido_clicked();

    void on_btnPesquisarPedido_clicked();

    void on_btnMostrarLista_clicked();

    void on_btnMostrarPedido_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_btnPesquisarPesqC_clicked();

    void on_btnMostrarPesqC_clicked();

private:
    Ui::AdicionarPedido *ui;
    HEV::InterfaceCRUD * pedidos;
    HEV::List<HEV::Produto> comprarProduto;
    HEV::List<HEV::Produto> escolhidos;
    HEV::List<HEV::Produto> mostrar;
    HEV::List<HEV::PedidoVenda> pedidovenda;
    HEV::List<HEV::PedidoVenda> pedidoporcliente;

    QString valorDuasCasa(QString aux);

    void limparIncluir();
    void limparPesquisar();
    void limparListar();
    void limparAsLista();
    void limparListaPorCliente();

    void iniciarListas();
    void criarLista();
    void gerarLista();
    void gerarListaDeCompra();
    void gerarListaDePesquisa();
    void gerarListaDePedido();
    void gerarListaDeMostrar();
    void gerarListaDePedidoPorCliente();
    void gerarListaMostrarPorCliente();
};

#endif // ADICIONARPEDIDO_H
