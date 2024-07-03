#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include <QDialog>

namespace Ui {
class OptionsWindow;
}

class OptionsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsWindow(QWidget *parent = nullptr);
    ~OptionsWindow();

private slots:
    void on_ReturnButton_clicked();

    void on_applyButton_clicked();

    void on_VolumeSlider_valueChanged(int value);

    void on_LoadMap_clicked();

private:
    Ui::OptionsWindow *ui;
};

#endif // OPTIONSWINDOW_H
