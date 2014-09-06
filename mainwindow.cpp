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
    QFile raw(Constants::IMG_RAW);
    QFile ref(Constants::IMG_REF);
    if ( raw.exists() && ref.exists() ){
        on_bttnStep_clicked();
        ui->lineParking->setText(Constants::IMG_RAW);
        ui->lineReference->setText(Constants::IMG_REF);
    }
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

    QFile raw_image(fileName);
    QFile::remove(Constants::IMG_RAW);
    raw_image.copy(Constants::IMG_RAW);
}

void MainWindow::on_fileBttnReference_clicked()
{
    //Dialogo para abrir la ubicación de la foto de referencia del parqueo
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"~/",tr("Mp3 Files (*.jpg)"));
    qDebug() << fileName;
    ui->lineReference->setText(fileName);

    QFile ref_image(fileName);
    QFile::remove(Constants::IMG_REF);
    ref_image.copy(Constants::IMG_REF);
}

void MainWindow::on_bttnStep_clicked()
{
    ImageProcessingStrategy* strategy = new ImageProcessingStrategy();
    QImage imageRaw, imageRef;

    switch(Constants::STEP_STATE){
        case Constants::RAW:
            //Constants::IMG_RAW = const_cast<char *>(ui->lineParking->text().toStdString().c_str());
            imageRaw.load(Constants::IMG_RAW);
            imageRef.load(Constants::IMG_REF);
            qDebug() << imageRaw.bits();
            qDebug() << Constants::IMG_RAW;
            //next state
            Constants::STEP_STATE = Constants::LAPLACE;
            break;
        case Constants::BLUR:
            if (strategy->processBlur()) showErrorMessage();
            imageRaw.load(Constants::IMG_RAW_BLUR);
            imageRef.load(Constants::IMG_REF_BLUR);
            //next state
            Constants::STEP_STATE = Constants::SUBS;
            break;
        case Constants::LAPLACE:
            strategy->processLaplacian();
            imageRaw.load(Constants::IMG_RAW_LAPLACE);
            imageRef.load(Constants::IMG_REF_LAPLACE);
            //next state
            Constants::STEP_STATE = Constants::BLUR;
            break;
        case Constants::EDGES:
            strategy->processEdge();
            imageRaw.load(Constants::IMG_EDGES);
            imageRef.allGray();
            //next state
            Constants::STEP_STATE = Constants::CONTOURNS;
            break;
        case Constants::SUBS:
            strategy->processSubs();
            imageRaw.load( Constants::IMG_SUBS );
            imageRef.allGray();
            //next state
            Constants::STEP_STATE = Constants::EDGES;
            break;
        case Constants::CONTOURNS:
            strategy->processContourns();
            imageRaw.load( Constants::IMG_CONTOURNS );
            imageRef.load(Constants::IMG_FINAL);
            ui->bttnStep->setEnabled(false);
            break;
    }


    ui->imgRaw->setPixmap(QPixmap::fromImage(imageRaw.scaled(ui->imgRaw->width(),ui->imgRaw->height())));
    ui->imgRef->setPixmap(QPixmap::fromImage( imageRef.scaled(ui->imgRef->width(),ui->imgRef->height())));
}

void MainWindow::showErrorMessage(){
    QMessageBox msgBox;
     msgBox.setText("Se detecto un problema al abrir la imagen, por favor intente de nuevo");
     msgBox.exec();
}

void MainWindow::on_bttnRestart_clicked()
{
    ui->bttnStep->setEnabled(true);
    Constants::STEP_STATE = Constants::RAW;
    on_bttnStep_clicked();
}
