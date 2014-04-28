#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    crearTabla();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::crearTabla()
{
    ui->listWidget->addItem("algo");

    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(clickElemento()));
}

void MainWindow::clickElemento()
{
    QMessageBox *box = new QMessageBox();
    box->setGeometry(200,200,200,200);
    box->setText("LOL FUNCA!");
    box->show();
}

void MainWindow::on_pushButton_clicked()
{
    this->close();
}
