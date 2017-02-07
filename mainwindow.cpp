#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
            /*qDebug() << "Name        : " << info.portName();
            qDebug() << "Description : " << info.description();
            qDebug() << "Manufacturer: " << info.manufacturer();*/

            // Example use QSerialPort
            QSerialPort serial;
            serial.setPort(info);
            if (serial.open(QIODevice::ReadWrite))
            {
                ui->comboBox->addItem(info.portName()+" "+"("+info.description()+")");
                serial.close();
            }
    }
    My_serialport = new QSerialPort;
    timerRecv = new QTimer;
    connect(timerRecv,SIGNAL(timeout()),this,SLOT(Myserial_Revc()),Qt::DirectConnection);
}

MainWindow::~MainWindow()
{
    if(timerRecv->isActive()==true)
    {
        timerRecv->stop();

    }
    delete timerRecv;
    delete My_serialport;
    delete ui;
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    QByteArray byte0 = arg1.toLocal8Bit();
    QByteArray byte1;
    for(short int temp=0;byte0[temp] != ' ';temp++)
    {
        byte1[temp] = byte0[temp];
    }

    My_serialport->setPortName(QString(byte1));
    My_serialport->open(QIODevice::ReadWrite);
    My_serialport->setBaudRate(115200);//bps 115200
    My_serialport->setDataBits(QSerialPort::Data8);//8
    My_serialport->setParity(QSerialPort::NoParity);//n
    My_serialport->setStopBits(QSerialPort::OneStop);//1
    My_serialport->setFlowControl(QSerialPort::NoFlowControl);

    timerRecv->start(30);
}

void MainWindow::Myserial_Revc()
{
    QString str1 = My_serialport->readAll();
    if(str1.isEmpty()==false)
    {
        ui->lineEdit->setText(str1);
    }
}

void MainWindow::on_pushButton_clicked()
{
    Senddata[0] = 2;
    Senddata[1] = 0xfa;
    My_serialport->write((char *)Senddata,2);
}
