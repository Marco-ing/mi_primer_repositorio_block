#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->plainTextEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbrir_triggered()
{
    QFile arch;
    QTextStream io;
    QString Nombre = QFileDialog::getOpenFileName(this,"Abrir nota");
    if(Nombre.isEmpty()){
        return;
    }
    arch.setFileName(Nombre);
    arch.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!arch.isOpen()){
        QMessageBox::critical(this,"Error",arch.errorString());
        return;
    }
    io.setDevice(&arch);
    ui->plainTextEdit->setPlainText(io.readAll());
    arch.close();

}

void MainWindow::on_actionGuardar_como_triggered()
{
    QFile arch;
    QTextStream io;
    QString NombreSalida;
    NombreSalida = QFileDialog::getSaveFileName(this,"Guardar nota");
    if(NombreSalida.isEmpty()){
        return;
    }
    arch.setFileName(NombreSalida);
    arch.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!arch.isOpen()){
        QMessageBox::critical(this,"Error al guardar",arch.errorString());
        return;
    }
    io.setDevice(&arch);
    io << ui->plainTextEdit->toPlainText();
    arch.flush();
    arch.close();


}

void MainWindow::on_actionCopiar_triggered()
{
    ui->plainTextEdit->copy();
}

void MainWindow::on_actionCortar_triggered()
{
    ui->plainTextEdit->cut();
}

void MainWindow::on_actionPegar_triggered()
{
    ui->plainTextEdit->paste();
}

void MainWindow::on_actionAcerca_de_triggered()
{
    QMessageBox::aboutQt(this,"Qt");
}

void MainWindow::on_actionAcerca_de_2_triggered()
{
    QString autor = "Autor de Bloc de Notas mark.\n";
              autor += "Marco Antonio Martinez Cruz\n";
              autor += "Fecha 31/agosto/2019";
    QMessageBox::about(this,"Informacion",autor);
}

void MainWindow::on_actionCerrar_2_triggered()
{
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Advertencia", "Quieres salir sin guardar",
                                    QMessageBox::Yes|QMessageBox::Save);
      if (reply == QMessageBox::Yes) {
          QApplication::quit();
        } else {
          on_actionGuardar_como_triggered();
        }

}
