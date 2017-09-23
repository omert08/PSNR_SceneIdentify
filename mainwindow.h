#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:

    void on_randomValid_btn_clicked();

    void on_sizeValid_btn_clicked();

    void on_GetRandomImage_btn_clicked();


    void on_GetSameImage_btn_3_clicked();

    void on_matchtest4all_btn_2_clicked();

    void on_sizeTest4All_btn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
