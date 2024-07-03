#include "wonlevel.h"
#include "game.h"
#include "ui_wonlevel.h"
#include <QPushButton>
#include<QMediaPlayer>
#include<QAudioOutput>
extern Game *g;
extern int* hard;
extern int Volume;
WonLevel::WonLevel(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WonLevel)
{
    delete g;
    ui->setupUi(this);
    ui->LevelLabel->setText("Level "+ QString::number(*hard));
    ui->LevelLabel->setVisible(true);
    ui->pushButton->setText("Proceed to Level" + QString::number(*hard+1));
    qDebug()<<"Level "+ QString::number(*hard);
    QPixmap p(":/new/images/images/NextLevel.png");
    p=p.scaled(ui->nextlevellabel->size());
    ui->nextlevellabel->setPixmap(p);
    QMediaPlayer *Q = new QMediaPlayer;
    Q ->setSource(QUrl("qrc:/new/Sound/Sound/level-win-6416.mp3"));

    QAudioOutput *audio = new QAudioOutput;
    Q->setAudioOutput(audio);
    audio->setVolume(Volume);
    Q->play();

}

WonLevel::~WonLevel()
{
    delete ui;
}


void WonLevel::on_pushButton_clicked()
{

    *hard+=1;
    g=new Game(*hard);
    this->hide();
    g->showview();

}

