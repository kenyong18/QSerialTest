#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSerialPort *My_serialport;
    QTimer *timerRecv;
private slots:
    void on_comboBox_activated(const QString &arg1);
    void Myserial_Revc();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    unsigned char Senddata[30];
};

#endif // MAINWINDOW_H
