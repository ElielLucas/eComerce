#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnProdutos_clicked()
{
    AdicionarProdutos produtos;
    produtos.exec();
}

void MainWindow::on_btnClientes_clicked()
{
    AdicionarClientes client;
    client.exec();
}

void MainWindow::on_btnPedidos_clicked()
{
    AdicionarPedido pedido;
    pedido.exec();
}

