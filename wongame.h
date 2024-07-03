#ifndef WONGAME_H
#define WONGAME_H

#include <QDialog>

namespace Ui {
class wongame;
}

class wongame : public QDialog
{
    Q_OBJECT

public:
    explicit wongame(QWidget *parent = nullptr);
    ~wongame();

private slots:
    void on_pushButton_clicked();

private:
    Ui::wongame *ui;
};

#endif // WONGAME_H
