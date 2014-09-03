#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QDebug"
#include <QPicture>
#include "imageprocessingstrategy.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fileBttnParking_clicked()
{
    //Dialogo para abrir la ubicación de la foto del parqueo a probar
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"~/",tr("Mp3 Files (*.jpg)"));
    qDebug() << fileName;

    ui->lineParking->setText(fileName);
}

void MainWindow::on_fileBttnReference_clicked()
{
    //Dialogo para abrir la ubicación de la foto de referencia del parqueo
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"~/",tr("Mp3 Files (*.jpg)"));
    qDebug() << fileName;
    ui->lineReference->setText(fileName);
}

void MainWindow::on_bttnStep_clicked()
{
    ImageProcessingStrategy* strategy = new ImageProcessingStrategy();
    QImage image;

    switch(Constants::STEP_STATE){
        case Constants::PRE:
            qDebug() << "###PRE###";
            //Resetear estado
            Constants::IMG_RAW = const_cast<char *>(ui->lineParking->text().toStdString().c_str());
            QFile::remove(QString(Constants::BLUR));
            QFile::remove(QString(Constants::LAPLACE));
            QFile::remove(QString(Constants::EDGES));
            image.load(Constants::IMG_RAW);
            Constants::STEP_STATE = Constants::RAW;
            break;
        case Constants::RAW:
            qDebug() << "###RAW###";
            strategy->processBlur();
            image.load(Constants::IMG_BLUR);
            Constants::STEP_STATE = Constants::BLUR;
            break;
        case Constants::BLUR:
            qDebug() << "###BLUR###";
            strategy->processLaplacian();
            image.load(Constants::IMG_LAPLACE);
            Constants::STEP_STATE = Constants::LAPLACE;
            break;
        case Constants::LAPLACE:
            qDebug() << "###LAPLACIAN###";
            strategy->processEdge();
            image.load(Constants::IMG_EDGES);
            Constants::STEP_STATE = Constants::EDGES;
            ui->bttnStep->setEnabled(false);
            break;
        case Constants::EDGES:
            qDebug() << "###EDGES###";
            break;
    }

    ui->imgParking->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::showErrorMessage(){
    QMessageBox msgBox;
     msgBox.setText("Se detecto un problema al abrir la imagen, por favor intente de nuevo");
     msgBox.exec();
}

void MainWindow::on_bttnRestart_clicked()
{
    ui->bttnStep->setEnabled(true);
    Constants::STEP_STATE = Constants::PRE;
    on_bttnStep_clicked();
}
