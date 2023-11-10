#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "accountspage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    newWindow = new AccountsPage;
    ui->error->setVisible(false);
    ui->enterPass->setEchoMode(QLineEdit::Password);
    connect(newWindow, &AccountsPage::newWin, this ,&MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_enterBut_clicked()
{
    QString code = "1234";
    if (ui->enterPass->text() == code)
    {
        this->close();
        newWindow->show();
    }
    else
    {
        ui->error->setVisible(true);
    }

}


