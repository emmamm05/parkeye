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
    QImage imageRaw, imageRef;

    switch(Constants::STEP_STATE){
        case Constants::PRE:
            qDebug() << "###PRE###";
            //Resetear estado
            //Constants::IMG_RAW = const_cast<char *>(ui->lineParking->text().toStdString().c_str());
            QFile::remove(QString(Constants::BLUR));
            QFile::remove(QString(Constants::LAPLACE));
            QFile::remove(QString(Constants::EDGES));
            imageRaw.load(Constants::IMG_RAW);
            imageRef.load(Constants::IMG_REF);
            qDebug() << imageRaw.bits();
            qDebug() << Constants::IMG_RAW;
            //next state
            Constants::STEP_STATE = Constants::RAW;
            break;
        case Constants::RAW:
            qDebug() << "###RAW###";
            if (strategy->processBlur()) showErrorMessage();
            imageRaw.load(Constants::IMG_RAW_BLUR);
            imageRef.load(Constants::IMG_REF_BLUR);
            //next state
            Constants::STEP_STATE = Constants::BLUR;
            break;
        case Constants::BLUR:
            qDebug() << "###BLUR###";
            strategy->processLaplacian();
            imageRaw.load(Constants::IMG_RAW_LAPLACE);
            imageRef.load(Constants::IMG_REF_LAPLACE);
            //next state
            Constants::STEP_STATE = Constants::LAPLACE;
            break;
        case Constants::LAPLACE:
            qDebug() << "###LAPLACIAN###";
            strategy->processEdge();
            imageRaw.load(Constants::IMG_RAW_EDGES);
            imageRef.load(Constants::IMG_REF_EDGES);
            //next state
            Constants::STEP_STATE = Constants::EDGES;
            break;
        case Constants::EDGES:
            qDebug() << "###EDGES###";
            strategy->processSubs();
            imageRaw.load( Constants::IMG_SUBS );
            imageRef.allGray();
            ui->bttnStep->setEnabled(false);
            //next state
            Constants::STEP_STATE = Constants::SUBS;
            break;
    }

    ui->imgRaw->setPixmap(QPixmap::fromImage(imageRaw));
    ui->imgRef->setPixmap(QPixmap::fromImage(imageRef));
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
