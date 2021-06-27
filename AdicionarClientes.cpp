#include "AdicionarClientes.h"
#include "ui_AdicionarClientes.h"
#include<QMessageBox>

AdicionarClientes::AdicionarClientes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdicionarClientes)
{
    ui->setupUi(this);
    client = new HEV::PersistenciaCliente("ArquivoCliente.txt");
    iniciarLista();
}

AdicionarClientes::~AdicionarClientes()
{
    delete ui;
}

void AdicionarClientes::on_btnIncluir_clicked()
{
    try
    {
        QString cod,nome, endereco, telefone, cpf;
        cod="";
        nome = ui->txtNomeIncluir->text();
        endereco = ui->txtEnderecoIncluir->text();
        telefone = ui->txtTelefoneIncluir->text();
        cpf = ui->txtCPFIncluir->text();
        HEV::Cliente obj(cod,nome,endereco,telefone,cpf);
        client->incluir(obj.desmontarDados());
        QMessageBox::information(this,"Incluir Cliente","O cliente foi incluido.");

    } catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }
}

void AdicionarClientes::on_btnPesquisar_clicked()
{
    try
    {
        QString idcliente = ui->txtIdClienteEdit->text();

        QString objDesmontado=client->pesquisar(idcliente);
        HEV::Cliente novo;
        novo.montarDados(objDesmontado.toStdString());
        ui->frPesquisarCliente->setVisible(true);
        ui->txtNomeEdit->setText(novo.getNome());
        ui->txtEnderecoEdit->setText(novo.getEndereco());
        ui->txtTelefoneEdit->setText(novo.getTelefone());
        ui->txtCPFEdit->setText(novo.getCPF());

    } catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }
}

void AdicionarClientes::on_btnEdit_clicked()
{
    try
    {
        QString idcliente, nome, endereco, telefone, cpf;
        idcliente = ui->txtIdClienteEdit->text();
        nome = ui->txtNomeEdit->text();
        endereco = ui->txtEnderecoEdit->text();
        telefone = ui->txtTelefoneEdit->text();
        cpf = ui->txtCPFEdit->text();
        HEV::Cliente aux(idcliente, nome, endereco, telefone, cpf);
        client->alterar(aux.desmontarDados());
        QMessageBox::information(this,"Editar Cliente","O dados do cliente foram alterados.");


    } catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }

}

void AdicionarClientes::on_btnExcluir_clicked()
{
    try
    {
        QString idcliente = ui->txtIdClienteExcluir->text();
        QString objDesmontado= client->excluir(idcliente);
        HEV::Cliente velho;
        velho.montarDados(objDesmontado.toStdString());

        ui->lblDadoExcluido->setText(velho.print());

        QMessageBox::information(this,"Excluir Cliente","O cliente foi excluido!");

    } catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }
}

void AdicionarClientes::limparDadosIncluir()
{
    ui->txtNomeIncluir->setText("");
    ui->txtEnderecoIncluir->setText("");
    ui->txtTelefoneIncluir->setText("");
    ui->txtCPFIncluir->setText("");
}

void AdicionarClientes::limparDadosPesquisar()
{
    ui->txtIdClienteEdit->setText("");
    ui->txtNomeEdit->setText("");
    ui->txtEnderecoEdit->setText("");
    ui->txtTelefoneEdit->setText("");
    ui->txtCPFEdit->setText("");
    ui->frPesquisarCliente->setVisible(false);
}

void AdicionarClientes::limparDadosExcluir()
{
    ui->txtIdClienteExcluir->setText("");
    ui->lblDadoExcluido->setText("");
}

void AdicionarClientes::iniciarLista()
{
    ui->twCliente->clear();
    ui->twCliente->clearContents();
    ui->twCliente->setColumnCount(5);

    //definir o cabecalho da tabela
    QStringList cabecalhos = {"ID cliente", "Nome", "Endereco", "Telefone", "CPF"};
    ui->twCliente->setHorizontalHeaderLabels(cabecalhos);
    //nao poder editar os itens da tabela
    ui->twCliente->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha toda
    ui->twCliente->setSelectionBehavior(QAbstractItemView::SelectRows);
    //sumir com a linha ao lado
    ui->twCliente->verticalHeader()->setVisible(false);
    //cor da seleçao
    ui->twCliente->setStyleSheet("QTableView {selection-background-color:blue}");
}

void AdicionarClientes::mostrarLista()
{
    int n = ui->twCliente->rowCount();
    for (int i = n; i >= 0; i--){
        ui->twCliente->removeRow(i);
    }
}

void AdicionarClientes::on_tabCliente_currentChanged(int index)
{
    if (index == 0){
        //incluir
        limparDadosIncluir();
        limparDadosPesquisar();
        limparDadosExcluir();
        mostrarLista();
    }else if (index == 1){
        //pesquisar ou editar
        limparDadosIncluir();
        limparDadosPesquisar();
        limparDadosExcluir();
        mostrarLista();
    }else if (index == 2){
        //excluir
        limparDadosIncluir();
        limparDadosPesquisar();
        limparDadosExcluir();
        mostrarLista();
    }else if (index == 3){
        //listar
        limparDadosIncluir();
        limparDadosPesquisar();
        limparDadosExcluir();
        mostrarLista();
    }
}

void AdicionarClientes::on_btnMostrarLista_clicked()
{
    mostrarLista();
    HEV::PersistenciaCliente aux("ArquivoCliente.txt");
    HEV::List<HEV::Cliente> nova = aux.criarLista();
    int linha = 0;
    nova.definirIT();
    while (!nova.isEmpty()){
        ui->twCliente->insertRow(linha);
        HEV::Cliente n = nova.pegarPrimeiro();
        ui->twCliente->setItem(linha,0,new QTableWidgetItem(n.getKey()));
        ui->twCliente->setItem(linha,1,new QTableWidgetItem(n.getNome()));
        ui->twCliente->setItem(linha,2,new QTableWidgetItem(n.getEndereco()));
        ui->twCliente->setItem(linha,3,new QTableWidgetItem(n.getTelefone()));
        ui->twCliente->setItem(linha,4,new QTableWidgetItem(n.getCPF()));
        linha++;
    }
    ui->twCliente->setRowCount(linha);

}
