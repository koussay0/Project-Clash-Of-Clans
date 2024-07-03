#include "wongame.h"
#include "ui_wongame.h"
#include <mainwindow.h>
#include<QMediaPlayer>
#include<QAudioOutput>
extern Game *g;
extern int Volume;
wongame::wongame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wongame)
{
    ui->setupUi(this);
    QPixmap p(":/new/images/images/You win.jpg");
    p=p.scaled(ui->returnmenulabel->size());
    ui->returnmenulabel->setPixmap(p);
    QMediaPlayer *Q = new QMediaPlayer;
    Q ->setSource(QUrl("qrc:/new/Sound/Sound/WINGAME.mp3"));
    delete g;
    QAudioOutput *audio = new QAudioOutput;
    Q->setAudioOutput(audio);
    audio->setVolume(Volume);
    Q->play();

}

wongame::~wongame()
{
    delete ui;
}

void wongame::on_pushButton_clicked()
{
    MainWindow *w = new MainWindow;
    this->hide();
    w->show();
}

