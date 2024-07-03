#ifndef LOSTWINDOW_H
#define LOSTWINDOW_H

#include <QDialog>

namespace Ui {
class LostWindow;
}

class LostWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LostWindow(QWidget *parent = nullptr);
    ~LostWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LostWindow *ui;
};

#endif // LOSTWINDOW_H
