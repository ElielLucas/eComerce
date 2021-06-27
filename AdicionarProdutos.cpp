#include "AdicionarProdutos.h"
#include "ui_AdicionarProdutos.h"

AdicionarProdutos::AdicionarProdutos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdicionarProdutos)
{
    ui->setupUi(this);
    produt = new HEV::PersistenciaProduto("arquivoProdutos.txt");
    iniciarLista();
}

AdicionarProdutos::~AdicionarProdutos()
{
    delete ui;
}

void AdicionarProdutos::on_btnIncluir_clicked()
{
    try
    {
        QString cod=ui->txtCodigoIncluir->text();
        QString desc=ui->txtDescricaoIncluir->text();
        QString quant=ui->txtQtdeIncluir->text();
        QString preco=ui->txtPrecoIncluir->text();

        HEV::Produto x(cod,desc,quant,preco);

        produt->incluir(x.desmontarDados());
        QMessageBox::information(this,"Incluir Produto","O produto foi incluído!");
    } catch(QString erro)
    {
            QMessageBox::information(this,"Incluir Produto",erro);
    }
}

void AdicionarProdutos::on_btnPesquisar_clicked()
{
    try
    {
        QString codProd = ui->txtCodigoEdit->text();

        QString objDesmontado=produt->pesquisar(codProd);
        HEV::Produto novo;
        novo.montarDados(objDesmontado.toStdString());

        ui->frDadosEdit->setVisible(true);
        ui->txtDescricaoEdit->setText(novo.getDescricao());
        ui->txtQtdeEdit->setText(novo.getQuantidade());
        ui->txtPrecoEdit->setText(novo.getPreco());

    } catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }
}

void AdicionarProdutos::on_btnEdit_clicked()
{
    try
    {
        QString cod, desc, quant, preco;
        cod = ui->txtCodigoEdit->text();
        desc = ui->txtDescricaoEdit->text();
        quant = ui->txtQtdeEdit->text();
        preco = ui->txtPrecoEdit->text();

        HEV::Produto aux(cod, desc, quant, preco);
        produt->alterar(aux.desmontarDados());
        QMessageBox::information(this,"Editar Produto","O dados do produto foram alterados.");

    } catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }
}

void AdicionarProdutos::on_btnExcluir_clicked()
{
    try
    {
        QString codProd = ui->txtCodigoExcluir->text();
        QString objDesmontado= produt->excluir(codProd);
        HEV::Produto velho;
        velho.montarDados(objDesmontado.toStdString());

        ui->lblDadosExcluidos->setText(velho.print());
        QMessageBox::information(this,"Excluir Produto","O produto foi excluido!");

    } catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }
}

void AdicionarProdutos::limparDadosIncluir()
{
    ui->txtCodigoIncluir->setText("");
    ui->txtDescricaoIncluir->setText("");
    ui->txtQtdeIncluir->setText("");
    ui->txtPrecoIncluir->setText("");
}

void AdicionarProdutos::limparDadosPesquisar()
{
    ui->txtCodigoEdit->setText("");
    ui->txtDescricaoEdit->setText("");
    ui->txtQtdeEdit->setText("");
    ui->txtPrecoEdit->setText("");
    ui->frDadosEdit->setVisible(false);
}

void AdicionarProdutos::limparDadosExcluir()
{
    ui->txtCodigoExcluir->setText("");
    ui->lblDadosExcluidos->setText("");
}

void AdicionarProdutos::iniciarLista()
{
    ui->twProdutos->clear();
    ui->twProdutos->clearContents();
    ui->twProdutos->setColumnCount(4);

    //definir o cabecalho da tabela
    QStringList cabecalhos = {"Código", "Descrição", "Qtde Estoque", "Preço unitário"};
    ui->twProdutos->setHorizontalHeaderLabels(cabecalhos);
    //nao poder editar os itens da tabela
    ui->twProdutos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha toda
    ui->twProdutos->setSelectionBehavior(QAbstractItemView::SelectRows);
    //sumir com a linha ao lado
    ui->twProdutos->verticalHeader()->setVisible(false);
    //cor da seleçao
    ui->twProdutos->setStyleSheet("QTableView {selection-background-color:blue}");
}

void AdicionarProdutos::mostrarLista()
{
    int n = ui->twProdutos->rowCount();
    for (int i = n; i >= 0; i--){
        ui->twProdutos->removeRow(i);
    }

}

void AdicionarProdutos::on_btnMostrarLista_clicked()
{
    mostrarLista();
    HEV::PersistenciaProduto aux("arquivoProdutos.txt");
    HEV::List<HEV::Produto> nova = aux.criarLista();
    int linha = 0;
    nova.definirIT();
    while (!nova.isEmpty())
    {
        ui->twProdutos->insertRow(linha);
        HEV::Produto n = nova.pegarPrimeiro();
        ui->twProdutos->setItem(linha,0,new QTableWidgetItem(n.getKey()));
        ui->twProdutos->setItem(linha,1,new QTableWidgetItem(n.getDescricao()));
        ui->twProdutos->setItem(linha,2,new QTableWidgetItem(n.getQuantidade()));
        ui->twProdutos->setItem(linha,3,new QTableWidgetItem(n.getPreco()));
        linha++;
    }
    ui->twProdutos->setRowCount(linha);
}

void AdicionarProdutos::on_tabProdutos_currentChanged(int index)
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
