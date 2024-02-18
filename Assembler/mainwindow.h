#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QString>
#include <QDebug>
#include <QTextCodec>
#include <QTextBlock>
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>
#include <vector>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_transbtn_clicked();

    void on_savebtn_clicked();

    void on_clrresbtn_clicked();

    void on_clrbtn_clicked();

    void on_importbtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
