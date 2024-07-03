#include "optionswindow.h"
#include "ui_optionswindow.h"
#include"mainwindow.h"
#include<QBrush>
#include<QSlider>
#include<QFileDialog>
#include<QMessageBox>
extern int Volume;
extern QString Map;
extern QString land;
extern QString CastlePath;
extern QString fence;
extern QString BackgroundPath;
OptionsWindow::OptionsWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OptionsWindow)
{

    ui->setupUi(this);
    QPixmap m1(":/new/images/images/Map1.png.jpg");
    QPixmap m2(":/new/images/images/Map2.png.jpg");
    QPixmap m3(":/new/images/images/MAP3.png.jpg");
    QPixmap B(":/new/images/images/Greyphoto.jpg");
    m1= m1.scaled(ui->Map1->size());
    m2= m2.scaled(ui->Map2->size());
    m3= m3.scaled(ui->Map3->size());
    B=B.scaled(ui->ImageLabel->size());
    ui->Map1->setPixmap(m1);
    ui->Map2->setPixmap(m2);
    ui->Map3->setPixmap(m3);
    ui->ImageLabel->setPixmap(B);
    ui->VolumeSlider->setRange(0, 100);
    ui->VolumeSlider->setValue(50);


}


OptionsWindow::~OptionsWindow()
{
    delete ui;
}

void OptionsWindow::on_ReturnButton_clicked()
{
    MainWindow *w = new MainWindow;
    this->hide();
    w->show();
}


void OptionsWindow::on_applyButton_clicked()
{
    if(ui->MAP1_Radio->isChecked())
    {
        Map=":/ClanMaps/Clan Maps/Map1.txt";
    }
    else if(ui->Map2_Radio->isChecked())
    {
        Map=":/ClanMaps/Clan Maps/Map2.txt";
    }
    else if(ui->Map3_Radio->isChecked())
    {
        Map=":/ClanMaps/Clan Maps/Map3.txt";
    }
    if(ui->GrassRadio->isChecked())
    {
        land = ":/new/images/images/grass.png";
        CastlePath=":/new/images/images/Town_Hall.png";
            fence=":/new/images/images/fence.png";
        BackgroundPath=":/new/images/images/background.png";
    }
    else if (ui->desertRadio->isChecked())
    {
        land = ":/new/images/images/sandemptyland.jpg";
        CastlePath=":/new/images/images/dessertTown_Hall.png";
        fence=":/new/images/images/dessertfence.png";
        BackgroundPath=":/new/images/images/dessertbackground.png";
    }
    else if (ui->SnowRadio->isChecked())
    {

        land =":/new/images/images/snowemptyland.jpg";
        CastlePath =":/new/images/images/ICYTown_Hall.png";
        fence=":/new/images/images/icefence.png";
        BackgroundPath=":/new/images/images/snowybackground.png";
    }
}


void OptionsWindow::on_VolumeSlider_valueChanged(int value)
{
    Volume =value;
    qDebug()<<"Changed";
}


void OptionsWindow::on_LoadMap_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"Load Edge Data",QDir::currentPath(),"Text files (*.txt)");
    if (filePath.isEmpty()) {
        return;
    }

    Map = filePath;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::about(this, "Failed to open file for reading","ok");
        return;
    }
}

