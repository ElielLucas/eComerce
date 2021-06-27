#include "AdicionarPedido.h"
#include "ui_AdicionarPedido.h"

AdicionarPedido::AdicionarPedido(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdicionarPedido)
{
    ui->setupUi(this);
    iniciarListas();
    limparIncluir();
    limparListar();
    limparPesquisar();
    limparListaPorCliente();
}

AdicionarPedido::~AdicionarPedido()
{
    limparAsLista();
    delete ui;
}

void AdicionarPedido::on_btnPesquisarCliente_clicked()
{
    try
    {
        limparAsLista();
        QString idcliente = ui->txtIdCliente->text();
        HEV::PersistenciaCliente aux("ArquivoCliente.txt");
        HEV::Cliente busca;
        busca.montarDados(aux.pesquisar(idcliente).toStdString());

        ui->frClienteNovo->setVisible(true);

        ui->lblIdClienteNovo->setText(busca.getKey());
        ui->lblNomeNovo->setText(busca.getNome());
        ui->lblEnderecoNovo->setText(busca.getEndereco());
        ui->lblTelefoneNovo->setText(busca.getTelefone());
        ui->lblCPFNovo->setText(busca.getCPF());
        ui->frNovoPedido->setVisible(false);
    }
    catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
        limparIncluir();
    }
}

void AdicionarPedido::on_btnNovoPedido_clicked()
{
    try
    {
        limparAsLista();
        int id = ui->lblIdClienteNovo->text().toUInt();
        if (id > 0){
            ui->frNovoPedido->setVisible(true);
            criarLista();
            gerarLista();
        }else{
            QMessageBox::information(this,"Novo Pedido","Encontre um cliente");
        }

    }
    catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }
}

void AdicionarPedido::on_btnAdicionar_clicked()
{
    try {
        if (ui->twProdutos->currentRow() >= 0){
            int linha = ui->twProdutos->currentRow();
            int id = ui->twProdutos->item(linha, 0)->text().toUInt();
            double qtde = ui->twProdutos->item(linha, 2)->text().toDouble();
            bool ok;
            double num = (QInputDialog::getText(this, "Quantidade de produto", "Digite a quantidade que deseja desse produto: ",QLineEdit::Normal,QString(),&ok)).toDouble();
            if (ok){
                if (num > qtde || num < 0){
                    QMessageBox::information(this, "Invalido", "Quantidade invalida");
                }else
                {
                    HEV::Produto aux;
                    HEV::Produto cacar;
                    cacar.setCodigo(QString::number(id));
                    comprarProduto.remove(cacar, &aux);
                    if ((qtde - num) > 0){
                        aux.setQuantidade(QString::number(qtde-num));
                        comprarProduto.insert(&aux);
                    }
                    HEV::Produto novo = aux;
                    if (escolhidos.remove(cacar, &novo)){
                        int n = novo.getQuantidade().toUInt();
                        novo.setQuantidade(QString::number(n + num));
                    }else{
                        novo.setQuantidade(QString::number(num));
                    }
                    escolhidos.insert(&novo);
                    gerarLista();
                    gerarListaDeCompra();
                }
            }
        }

    }
    catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }
}

void AdicionarPedido::on_btnExcluir_clicked()
{
    try {
        if (ui->twPedido->currentRow() >= 0){
            int linha = ui->twPedido->currentRow();
            int id = ui->twPedido->item(linha, 0)->text().toUInt();
            HEV::Produto aux, procurar;
            HEV::Produto cacar;
            cacar.setCodigo(QString::number(id));
            escolhidos.remove(cacar, &aux);
            if (comprarProduto.remove(cacar, &procurar)){
                int qtde = procurar.getQuantidade().toInt() + aux.getQuantidade().toInt();
                aux.setQuantidade(QString::number(qtde));

            }
            comprarProduto.insert(&aux);
            gerarLista();
            gerarListaDeCompra();
        }

    }
    catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }
}

void AdicionarPedido::on_btnFinalizarPedido_clicked()
{
    try {

        HEV::PedidoVenda novo;
        QString data;
        novo.setIDCliente(ui->lblIdClienteNovo->text());
        novo.setDataCompra(ui->txtDia->text().toUInt(),ui->txtMes->text().toUInt(),ui->txtAno->text().toUInt());
        novo.setValorTotal(ui->lblValorTotal->text());
        novo.setLista(&escolhidos);
        HEV::PersistenciaPedidoVenda pedido("arquivoPedidosVendas.txt");
        pedido.incluir(novo.desmontarDados());

        pedido.atualizarEstoque(&comprarProduto);
        QMessageBox::information(this,"Compra", "Compra realizada com sucesso.");
        limparIncluir();
    }
    catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }
}

void AdicionarPedido::on_btnPesquisarPedido_clicked()
{
    try {
        HEV::PersistenciaPedidoVenda pedido("arquivoPedidosVendas.txt");
        QString idpedido = ui->txtIdPedido->text();
        HEV::PedidoVenda pesquisa;
        pesquisa.montarDados(pedido.pesquisar(idpedido).toStdString());
        HEV::Cliente busca;
        HEV::PersistenciaCliente aux("ArquivoCliente.txt");
        busca.montarDados(aux.pesquisar(pesquisa.getIDCliente()).toStdString());
        ui->frDadosPedido->setVisible(true);
        ui->frClientePesquisar->setVisible(true);

        ui->lblIdPedidoPesquisar->setText(pesquisa.getKey());
        ui->lblIdClientePesquisar->setText(pesquisa.getIDCliente());
        ui->lblNomePesquisar->setText(busca.getNome());
        ui->lblEnderecopesquisar->setText(busca.getEndereco());
        ui->lblTelefonePesquisar->setText(busca.getTelefone());
        ui->lblCPFpesquisar->setText(busca.getCPF());
        ui->lblDataPesquisar->setText(pesquisa.getDataCompra());
        ui->lblValorTotalPesquisar->setText(pesquisa.getValorTotal());

        mostrar = pesquisa.getListaCurso();
        gerarListaDePesquisa();

    }
    catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
        limparPesquisar();
    }
}

void AdicionarPedido::on_btnMostrarLista_clicked()
{
    try {
        limparListar();
        HEV::PersistenciaPedidoVenda pedido("arquivoPedidosVendas.txt");
        pedidovenda = pedido.criarLista();
        gerarListaDePedido();
        ui->frMostrarLista->setVisible(true);
    }
    catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
        limparListar();
    }
}

void AdicionarPedido::on_btnMostrarPedido_clicked()
{
    try {
        int linha = ui->twListarPedido->currentRow();
        QString id = ui->twListarPedido->item(linha, 0)->text();
        HEV::PersistenciaPedidoVenda pedido("arquivoPedidosVendas.txt");
        HEV::PedidoVenda pesquisa;
        pesquisa.montarDados(pedido.pesquisar(id).toStdString());
        HEV::Cliente busca;
        HEV::PersistenciaCliente aux("ArquivoCliente.txt");
        busca.montarDados(aux.pesquisar(pesquisa.getIDCliente()).toStdString());
        ui->frClienteMostrar->setVisible(true);
        ui->frMostrarLista->setVisible(true);

        ui->lblIdPedidoMostrar->setText(pesquisa.getKey());
        ui->lblIdClienteMostrar->setText(pesquisa.getIDCliente());
        ui->lblNomeMostrar->setText(busca.getNome());
        ui->lblEnderecoMostrar->setText(busca.getEndereco());
        ui->lblTelefoneMostrar->setText(busca.getTelefone());
        ui->lblCPFMostrar->setText(busca.getCPF());
        ui->lblDataMostrar->setText(pesquisa.getDataCompra());
        ui->lblValorTotalMostrar->setText(pesquisa.getValorTotal());

        mostrar = pesquisa.getListaCurso();
        gerarListaDeMostrar();

    }
    catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
        limparListar();
    }
}

void AdicionarPedido::iniciarListas()
{
    //Lista de produtos
    ui->twProdutos->setColumnCount(4);
    //definir o cabecalho da tabela
    QStringList cabecalhos = {"Código", "Descrição", "Qtde em Estoque", "Preço unitário"};
    ui->twProdutos->setHorizontalHeaderLabels(cabecalhos);
    //nao poder editar os itens da tabela
    ui->twProdutos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha toda
    ui->twProdutos->setSelectionBehavior(QAbstractItemView::SelectRows);
    //sumir com a linha ao lado
    ui->twProdutos->verticalHeader()->setVisible(false);
    //cor da seleçao
    ui->twProdutos->setStyleSheet("QTableView {selection-background-color:blue}");
    //definir tamanho das colunas
    ui->twProdutos->setColumnWidth(0,70);
    ui->twProdutos->setColumnWidth(1,170);
    ui->twProdutos->setColumnWidth(2,140);
    ui->twProdutos->setColumnWidth(3,110);

    //Lista de inserir produtos
    ui->twPedido->setColumnCount(5);
    QStringList cabecalho = {"Código", "Descrição", "Qtde", "Preço unitário", "valor total"};
    ui->twPedido->setHorizontalHeaderLabels(cabecalho);
    //nao poder editar os itens da tabela
    ui->twPedido->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha toda
    ui->twPedido->setSelectionBehavior(QAbstractItemView::SelectRows);
    //sumir com a linha ao lado
    ui->twPedido->verticalHeader()->setVisible(false);
    //cor da seleçao
    ui->twPedido->setStyleSheet("QTableView {selection-background-color:blue}");
    //definir tamanho das colunas
    ui->twPedido->setColumnWidth(0,70);
    ui->twPedido->setColumnWidth(1,170);
    ui->twPedido->setColumnWidth(2,140);
    ui->twPedido->setColumnWidth(3,110);
    ui->twPedido->setColumnWidth(4,110);

    //Lista de inserir pesquisar
    ui->twProdutosPedido->setColumnCount(5);
    ui->twProdutosPedido->setHorizontalHeaderLabels(cabecalho);
    //nao poder editar os itens da tabela
    ui->twProdutosPedido->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha toda
    ui->twProdutosPedido->setSelectionBehavior(QAbstractItemView::SelectRows);
    //sumir com a linha ao lado
    ui->twProdutosPedido->verticalHeader()->setVisible(false);
    //cor da seleçao
    ui->twProdutosPedido->setStyleSheet("QTableView {selection-background-color:blue}");
    //definir tamanho das colunas
    ui->twProdutosPedido->setColumnWidth(0,70);
    ui->twProdutosPedido->setColumnWidth(1,170);
    ui->twProdutosPedido->setColumnWidth(2,140);
    ui->twProdutosPedido->setColumnWidth(3,110);
    ui->twProdutosPedido->setColumnWidth(4,110);

    //Lista Mostrar pedido marcado
    ui->twProdutosLista->setColumnCount(5);
    ui->twProdutosLista->setHorizontalHeaderLabels(cabecalho);
    //nao poder editar os itens da tabela
    ui->twProdutosLista->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha toda
    ui->twProdutosLista->setSelectionBehavior(QAbstractItemView::SelectRows);
    //sumir com a linha ao lado
    ui->twProdutosLista->verticalHeader()->setVisible(false);
    //cor da seleçao
    ui->twProdutosLista->setStyleSheet("QTableView {selection-background-color:blue}");
    //definir tamanho das colunas
    ui->twProdutosLista->setColumnWidth(0,70);
    ui->twProdutosLista->setColumnWidth(1,170);
    ui->twProdutosLista->setColumnWidth(2,140);
    ui->twProdutosLista->setColumnWidth(3,110);
    ui->twProdutosLista->setColumnWidth(4,110);

    //Lista Mostrar pedido marcado por cliente
    ui->twMostrarPesqC->setColumnCount(5);
    ui->twMostrarPesqC->setHorizontalHeaderLabels(cabecalho);
    //nao poder editar os itens da tabela
    ui->twMostrarPesqC->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha toda
    ui->twMostrarPesqC->setSelectionBehavior(QAbstractItemView::SelectRows);
    //sumir com a linha ao lado
    ui->twMostrarPesqC->verticalHeader()->setVisible(false);
    //cor da seleçao
    ui->twMostrarPesqC->setStyleSheet("QTableView {selection-background-color:blue}");
    //definir tamanho das colunas
    ui->twMostrarPesqC->setColumnWidth(0,70);
    ui->twMostrarPesqC->setColumnWidth(1,170);
    ui->twMostrarPesqC->setColumnWidth(2,140);
    ui->twMostrarPesqC->setColumnWidth(3,110);
    ui->twMostrarPesqC->setColumnWidth(4,110);

    //Lista de mostrar Pedidos
    ui->twListarPedido->setColumnCount(4);
    QStringList cab = {"ID Pedido", "ID Cliente", "Data do Pedido", "Valor Total"};
    ui->twListarPedido->setHorizontalHeaderLabels(cab);
    //nao poder editar os itens da tabela
    ui->twListarPedido->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha toda
    ui->twListarPedido->setSelectionBehavior(QAbstractItemView::SelectRows);
    //sumir com a linha ao lado
    ui->twListarPedido->verticalHeader()->setVisible(false);
    //cor da seleçao
    ui->twListarPedido->setStyleSheet("QTableView {selection-background-color:blue}");
    //definir tamanho das colunas
    ui->twListarPedido->setColumnWidth(0,80);
    ui->twListarPedido->setColumnWidth(1,80);
    ui->twListarPedido->setColumnWidth(2,120);
    ui->twListarPedido->setColumnWidth(3,100);

    //Lista de mostrar Pedidos por cliente
    ui->twPedidoPesqC->setColumnCount(4);
    ui->twPedidoPesqC->setHorizontalHeaderLabels(cab);
    //nao poder editar os itens da tabela
    ui->twPedidoPesqC->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //selecionar a linha toda
    ui->twPedidoPesqC->setSelectionBehavior(QAbstractItemView::SelectRows);
    //sumir com a linha ao lado
    ui->twPedidoPesqC->verticalHeader()->setVisible(false);
    //cor da seleçao
    ui->twPedidoPesqC->setStyleSheet("QTableView {selection-background-color:blue}");
    //definir tamanho das colunas
    ui->twPedidoPesqC->setColumnWidth(0,80);
    ui->twPedidoPesqC->setColumnWidth(1,80);
    ui->twPedidoPesqC->setColumnWidth(2,120);
    ui->twPedidoPesqC->setColumnWidth(3,100);
}

void AdicionarPedido::criarLista()
{
    try {
        HEV::PersistenciaProduto comprarp("arquivoProdutos.txt");
        comprarProduto = comprarp.criarLista();
    }
    catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }
}

void AdicionarPedido::gerarLista()
{
    try {
        int n = ui->twProdutos->rowCount();
        for (int i = n; i >= 0; i--){
            ui->twProdutos->removeRow(i);
        }
        int linha = 0;
        comprarProduto.definirIT();
        int tam = comprarProduto.size();
        for (int i = 0; i < tam; i++, linha++){
            ui->twProdutos->insertRow(linha);
            HEV::Produto n = comprarProduto.mostrarIT();
            ui->twProdutos->setItem(linha,0,new QTableWidgetItem(n.getKey()));
            ui->twProdutos->setItem(linha,1,new QTableWidgetItem(n.getDescricao()));
            ui->twProdutos->setItem(linha,2,new QTableWidgetItem(n.getQuantidade()));
            ui->twProdutos->setItem(linha,3,new QTableWidgetItem(n.getPreco()));
            ui->twProdutos->setCurrentCell(0,0);
        }
        ui->twProdutos->setRowCount(linha);
    }
    catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }
}

void AdicionarPedido::gerarListaDeCompra()
{
    try {
        int n = ui->twPedido->rowCount();
        for (int i = n; i >= 0; i--){
            ui->twPedido->removeRow(i);
        }
        int linha = 0;
        double total = 0;
        escolhidos.definirIT();
        int tam = escolhidos.size();
        for (int i = 0; i < tam; i++, linha++){
            ui->twPedido->insertRow(linha);
            HEV::Produto n = escolhidos.mostrarIT();
            ui->twPedido->setItem(linha,0,new QTableWidgetItem(n.getKey()));
            ui->twPedido->setItem(linha,1,new QTableWidgetItem(n.getDescricao()));
            ui->twPedido->setItem(linha,2,new QTableWidgetItem(n.getQuantidade()));
            ui->twPedido->setItem(linha,3,new QTableWidgetItem(n.getPreco()));
            double valor = n.getQuantidade().toDouble() * n.getPreco().toDouble();
            total += valor;
            QString v = valorDuasCasa(QString::number(valor));
            ui->twPedido->setItem(linha,4,new QTableWidgetItem(v));
            ui->twPedido->setCurrentCell(0,0);
        }
        QString t = valorDuasCasa(QString::number(total));
        ui->lblValorTotal->setText(t);
        ui->twPedido->setRowCount(linha);
    }
    catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }
}

void AdicionarPedido::gerarListaDePesquisa()
{
    try {
        int n = ui->twProdutosPedido->rowCount();
        for (int i = n; i >= 0; i--){
            ui->twProdutosPedido->removeRow(i);
        }
        int linha = 0;
        double total = 0;
        mostrar.definirIT();
        int tam = mostrar.size();
        for (int i = 0; i < tam; i++, linha++){
            ui->twProdutosPedido->insertRow(linha);
            HEV::Produto n = mostrar.pegarPrimeiro();
            ui->twProdutosPedido->setItem(linha,0,new QTableWidgetItem(n.getKey()));
            ui->twProdutosPedido->setItem(linha,1,new QTableWidgetItem(n.getDescricao()));
            ui->twProdutosPedido->setItem(linha,2,new QTableWidgetItem(n.getQuantidade()));
            ui->twProdutosPedido->setItem(linha,3,new QTableWidgetItem(n.getPreco()));
            double valor = n.getQuantidade().toDouble() * n.getPreco().toDouble();
            total += valor;
            QString v = valorDuasCasa(QString::number(valor));
            ui->twProdutosPedido->setItem(linha,4,new QTableWidgetItem(v));
        }
        ui->twProdutosPedido->setRowCount(linha);
    }
    catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }
}

void AdicionarPedido::gerarListaDePedido()
{
    try {
        int n = ui->twListarPedido->rowCount();
        for (int i = n; i >= 0; i--){
            ui->twListarPedido->removeRow(i);
        }
        int linha = 0;
        pedidovenda.definirIT();
        int tam = pedidovenda.size();
        for (int i = 0; i < tam; i++, linha++){
            ui->twListarPedido->insertRow(linha);
            HEV::PedidoVenda n = pedidovenda.pegarPrimeiro();
            ui->twListarPedido->setItem(linha,0,new QTableWidgetItem(n.getKey()));
            ui->twListarPedido->setItem(linha,1,new QTableWidgetItem(n.getIDCliente()));
            ui->twListarPedido->setItem(linha,2,new QTableWidgetItem(n.getDataCompra()));
            ui->twListarPedido->setItem(linha,3,new QTableWidgetItem(n.getValorTotal()));
            ui->twListarPedido->setCurrentCell(0,0);
        }
        ui->twListarPedido->setRowCount(linha);
        while (!pedidovenda.isEmpty()){
            pedidovenda.pegarPrimeiro();
        }
    }
    catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }
}

void AdicionarPedido::gerarListaDeMostrar()
{
    try {
        int n = ui->twProdutosLista->rowCount();
        for (int i = n; i >= 0; i--){
            ui->twProdutosLista->removeRow(i);
        }
        int linha = 0;
        double total = 0;
        mostrar.definirIT();
        int tam = mostrar.size();
        for (int i = 0; i < tam; i++, linha++){
            ui->twProdutosLista->insertRow(linha);
            HEV::Produto n = mostrar.pegarPrimeiro();
            ui->twProdutosLista->setItem(linha,0,new QTableWidgetItem(n.getKey()));
            ui->twProdutosLista->setItem(linha,1,new QTableWidgetItem(n.getDescricao()));
            ui->twProdutosLista->setItem(linha,2,new QTableWidgetItem(n.getQuantidade()));
            ui->twProdutosLista->setItem(linha,3,new QTableWidgetItem(n.getPreco()));
            double valor = n.getQuantidade().toDouble() * n.getPreco().toDouble();
            total += valor;
            QString v = valorDuasCasa(QString::number(valor));
            ui->twProdutosLista->setItem(linha,4,new QTableWidgetItem(v));
        }
        ui->twProdutosLista->setRowCount(linha);
    }
    catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }
}

void AdicionarPedido::gerarListaDePedidoPorCliente()
{
    try {
        int n = ui->twPedidoPesqC->rowCount();
        for (int i = n; i >= 0; i--){
            ui->twPedidoPesqC->removeRow(i);
        }
        int linha = 0;
        pedidoporcliente.definirIT();
        int tam = pedidoporcliente.size();
        for (int i = 0; i < tam; i++, linha++){
            ui->twPedidoPesqC->insertRow(linha);
            HEV::PedidoVenda n = pedidoporcliente.pegarPrimeiro();
            ui->twPedidoPesqC->setItem(linha,0,new QTableWidgetItem(n.getKey()));
            ui->twPedidoPesqC->setItem(linha,1,new QTableWidgetItem(n.getIDCliente()));
            ui->twPedidoPesqC->setItem(linha,2,new QTableWidgetItem(n.getDataCompra()));
            ui->twPedidoPesqC->setItem(linha,3,new QTableWidgetItem(n.getValorTotal()));
            ui->twPedidoPesqC->setCurrentCell(0,0);
        }
        ui->twPedidoPesqC->setRowCount(linha);
        while (!pedidoporcliente.isEmpty()){
            pedidoporcliente.pegarPrimeiro();
        }
    }
    catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }
}

void AdicionarPedido::gerarListaMostrarPorCliente()
{
    try {
        int n = ui->twMostrarPesqC->rowCount();
        for (int i = n; i >= 0; i--){
            ui->twMostrarPesqC->removeRow(i);
        }
        int linha = 0;
        double total = 0;
        mostrar.definirIT();
        int tam = mostrar.size();
        for (int i = 0; i < tam; i++, linha++){
            ui->twMostrarPesqC->insertRow(linha);
            HEV::Produto n = mostrar.pegarPrimeiro();
            ui->twMostrarPesqC->setItem(linha,0,new QTableWidgetItem(n.getKey()));
            ui->twMostrarPesqC->setItem(linha,1,new QTableWidgetItem(n.getDescricao()));
            ui->twMostrarPesqC->setItem(linha,2,new QTableWidgetItem(n.getQuantidade()));
            ui->twMostrarPesqC->setItem(linha,3,new QTableWidgetItem(n.getPreco()));
            double valor = n.getQuantidade().toDouble() * n.getPreco().toDouble();
            total += valor;
            QString v = valorDuasCasa(QString::number(valor));
            ui->twMostrarPesqC->setItem(linha,4,new QTableWidgetItem(v));
        }
        ui->twMostrarPesqC->setRowCount(linha);
    }
    catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }

}

void AdicionarPedido::on_tabWidget_currentChanged(int index)
{
    if (index == 0){
        limparAsLista();
        limparIncluir();
        limparListar();
        limparPesquisar();
        limparListaPorCliente();
    }else if (index == 1){
        limparAsLista();
        limparIncluir();
        limparListar();
        limparPesquisar();
        limparListaPorCliente();
    }else if (index == 2){
        limparAsLista();
        limparIncluir();
        limparListar();
        limparPesquisar();
        limparListaPorCliente();
    }else if (index == 3){
        limparAsLista();
        limparIncluir();
        limparListar();
        limparPesquisar();
        limparListaPorCliente();
    }
}

QString AdicionarPedido::valorDuasCasa(QString aux)
{
    int i = 0;
    QString nova ="";
    for (; i < aux.size() && aux[i] != '.'; i++){
        nova+=aux[i];
    }
    nova += ".";
    if (i == aux.size()){
        nova += "00";
    }else{
        nova += aux[i+1];
        if (i+ 2 == aux.size()){
            nova += "0";
        }else{
            nova += aux[i+2];
        }
    }
    return nova;
}

void AdicionarPedido::limparIncluir()
{
     ui->frNovoPedido->setVisible(false);
     ui->frClienteNovo->setVisible(false);

     ui->txtIdCliente->setText("");
     ui->lblIdClienteNovo->setText("");
     ui->lblNomeNovo->setText("");
     ui->lblEnderecoNovo->setText("");
     ui->lblTelefoneNovo->setText("");
     ui->lblCPFNovo->setText("");

     int n = ui->twProdutos->rowCount();
     for (int i = n; i >= 0; i--){
         ui->twProdutos->removeRow(i);
     }

     n = ui->twPedido->rowCount();
     for (int i = n; i >= 0; i--){
         ui->twPedido->removeRow(i);
     }

}

void AdicionarPedido::limparPesquisar()
{
    ui->frDadosPedido->setVisible(false);
    ui->frClientePesquisar->setVisible(false);

    ui->txtIdPedido->setText("");
    ui->lblIdPedidoPesquisar->setText("");
    ui->lblIdClientePesquisar->setText("");
    ui->lblNomePesquisar->setText("");
    ui->lblEnderecopesquisar->setText("");
    ui->lblTelefonePesquisar->setText("");
    ui->lblCPFpesquisar->setText("");
    ui->lblDataPesquisar->setText("");
    ui->lblValorTotalPesquisar->setText("");
    int n = ui->twProdutosPedido->rowCount();
    for (int i = n; i >= 0; i--){
        ui->twProdutosPedido->removeRow(i);
    }
}

void AdicionarPedido::limparListar()
{
    ui->frClienteMostrar->setVisible(false);
    ui->frMostrarLista->setVisible(false);

    ui->lblIdPedidoMostrar->setText("");
    ui->lblIdClienteMostrar->setText("");
    ui->lblNomeMostrar->setText("");
    ui->lblEnderecoMostrar->setText("");
    ui->lblTelefoneMostrar->setText("");
    ui->lblCPFMostrar->setText("");
    ui->lblDataMostrar->setText("");
    ui->lblValorTotalMostrar->setText("");
    int n = ui->twListarPedido->rowCount();
    for (int i = n; i >= 0; i--){
        ui->twListarPedido->removeRow(i);
    }
    n = ui->twProdutosLista->rowCount();
    for (int i = n; i >= 0; i--){
        ui->twProdutosLista->removeRow(i);
    }
}

void AdicionarPedido::limparAsLista()
{
    while (!comprarProduto.isEmpty()){
        comprarProduto.pegarPrimeiro();
    }
    while (!escolhidos.isEmpty()){
        escolhidos.pegarPrimeiro();
    }
}

void AdicionarPedido::limparListaPorCliente()
{
    ui->txtIdClientePesqC->setText("");
    ui->lblIdClientePesqC->setText("");
    ui->lblNomePesqC->setText("");
    ui->lblEnderecoPesqC->setText("");
    ui->lblTelefonePesqC->setText("");
    ui->lblCPFPesqC->setText("");
    ui->lblIdPedidoPesqC->setText("");
    ui->lblDataPesqC->setText("");
    ui->lblValorTotalPesqC->setText("");
    ui->frPedidoClientePesqC->setVisible(false);
    ui->frMostrarPesqC->setVisible(false);
    ui->frMostrarListaPesqC->setVisible(false);
    int n = ui->twPedidoPesqC->rowCount();
    for (int i = n; i >= 0; i--){
        ui->twPedidoPesqC->removeRow(i);
    }

}

void AdicionarPedido::on_btnPesquisarPesqC_clicked()
{
    try {
        QString id = ui->txtIdClientePesqC->text();
        HEV::PersistenciaPedidoVenda pedido("arquivoPedidosVendas.txt");
        pedidoporcliente = pedido.criarListaporCliente(id);
        HEV::PersistenciaCliente aux("ArquivoCliente.txt");
        HEV::Cliente busca;
        busca.montarDados(aux.pesquisar(id).toStdString());
        ui->lblIdClientePesqC->setText(busca.getKey());
        ui->lblNomePesqC->setText(busca.getNome());
        ui->lblEnderecoPesqC->setText(busca.getEndereco());
        ui->lblTelefonePesqC->setText(busca.getTelefone());
        ui->lblCPFPesqC->setText(busca.getCPF());
        ui->frPedidoClientePesqC->setVisible(true);
        ui->frMostrarPesqC->setVisible(true);
        ui->frMostrarListaPesqC->setVisible(false);
        gerarListaDePedidoPorCliente();
    }
    catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }

}

void AdicionarPedido::on_btnMostrarPesqC_clicked()
{

    try {
        int linha = ui->twPedidoPesqC->currentRow();
        QString id = ui->twPedidoPesqC->item(linha, 0)->text();
        HEV::PersistenciaPedidoVenda pedido("arquivoPedidosVendas.txt");
        HEV::PedidoVenda pesquisa;
        pesquisa.montarDados(pedido.pesquisar(id).toStdString());
        ui->frMostrarListaPesqC->setVisible(true);
        ui->lblIdPedidoPesqC->setText(pesquisa.getKey());
        ui->lblDataPesqC->setText(pesquisa.getDataCompra());
        ui->lblValorTotalPesqC->setText(pesquisa.getValorTotal());
        mostrar = pesquisa.getListaCurso();
        gerarListaMostrarPorCliente();

    }
    catch (QString erro)
    {
        QMessageBox::information(this,"Erro",erro);
    }
}
