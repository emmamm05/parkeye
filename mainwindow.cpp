#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QDebug"
#include <QPicture>
#include "imageprocessingstrategy.h"

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
    Constants::IMG_RAW = const_cast<char *>(fileName.toStdString().c_str());

    //Cargar Imagen
    QImage image;
    image.load(fileName);

    //Visualizar Imagen
    ui->lineParking->setText(fileName);
    ui->imgParking->setPixmap(QPixmap::fromImage(image));

    //Resetear estado
    Constants::STEP_STATE = Constants::RAW;
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
            break;
    }

    ui->imgParking->setPixmap(QPixmap::fromImage(image));
}
