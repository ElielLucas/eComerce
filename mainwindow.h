#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include<interfacecrud.h>
#include<persistenciacliente.h>
#include<persistenciapedidovenda.h>
#include<persistenciaproduto.h>
#include<AdicionarProdutos.h>
#include<AdicionarClientes.h>
#include<AdicionarPedido.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btnProdutos_clicked();

    void on_btnClientes_clicked();

    void on_btnPedidos_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
