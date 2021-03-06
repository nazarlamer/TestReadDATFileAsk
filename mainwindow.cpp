#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QWidget>
#include <QTableWidgetItem>

#include <iostream>
#include <fstream>
#include <QDataStream>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QTextCodec>
#include <QDebug>

#include <QString>

#include <QMessageBox>
#include "data.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->loadFileButton, &QPushButton::clicked, this, &MainWindow::onLoadFileButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    fstream inFile;
    inFile.open(_datFile.toStdString(), ios::binary | ios::in);
    if (!inFile)
    {
        QMessageBox::critical(this, "Помилка файла", "Файл відсутній");
        return;
    }

    //////////////////////
    // Разрешаем выделение только одного элемента
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnCount(20);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setHorizontalHeaderLabels({"POSX", "POSY", "STATUS", "ZALEGN", "NOMER", "KODV", "KODN", "KODAB", "ATTR", "TEXT",
                                                "TEXTMNEMO", "TMNPX", "TMNPY", "IDSQL", "VVODIV", "VV1", "VV2", "VV3", "VV4", "TUPZALEGN"});
    //////////////////////

    Serializing::Data DATRecord;
    const size_t bufferSize = 9;
    int buffer[bufferSize] = {0};
    QString FullString;
    int SizeStr = 0;
    int InsR = 0;

    inFile.seekg(0);
    while(!inFile.eof())
    {
        inFile.read(reinterpret_cast<char*>(buffer), bufferSize * sizeof (int));
        DATRecord.posx = buffer[0];
        DATRecord.posy = buffer[1];
        DATRecord.status = buffer[2];
        DATRecord.zalegn = buffer[3];
        DATRecord.nomer = buffer[4];
        DATRecord.kodv = buffer[5];
        DATRecord.kodn = buffer[6];
        DATRecord.kodab = buffer[7];
        DATRecord.attr = buffer[8];

        FullString = "";
        int8_t dataLen = 0;
        inFile.read(reinterpret_cast<char*>(&dataLen), sizeof(int8_t));
        SizeStr = dataLen;

        char inBuffer [100];
        inFile.read(inBuffer, 100);
        FullString = QString::fromLocal8Bit(inBuffer);
        FullString = FullString.mid(0, SizeStr);
        DATRecord.text = FullString;

        DATRecord.textmnemo = "";
        inFile.read(reinterpret_cast<char*>(&dataLen), sizeof(int8_t));
        SizeStr = dataLen;
        char inBuffer2[258];
        inFile.read(inBuffer2, 258);

        FullString = QString::fromLocal8Bit(inBuffer2);
        if (SizeStr == 0)
            FullString.clear();
        else
            FullString = FullString.mid(0, SizeStr);

        DATRecord.textmnemo = FullString;

        // clear buffer
        for (int &i : buffer)
            i = 0;

        inFile.read(reinterpret_cast<char*>(buffer), bufferSize * sizeof (int));
        DATRecord.tmnpx = buffer[0];
        DATRecord.tmnpy = buffer[1];
        DATRecord.idsql = buffer[2];
        DATRecord.vvodiv = buffer[3];
        DATRecord.vv1 = buffer[4];
        DATRecord.vv2 = buffer[5];
        DATRecord.vv3 = buffer[6];
        DATRecord.vv4 = buffer[7];
        DATRecord.tupzalegn = buffer[8];

        ui->tableWidget->insertRow(InsR);
        ui->tableWidget->setItem(InsR,0, new QTableWidgetItem((QString::number(DATRecord.posx))));
        ui->tableWidget->setItem(InsR,1, new QTableWidgetItem((QString::number(DATRecord.posy))));
        ui->tableWidget->setItem(InsR,2, new QTableWidgetItem((QString::number(DATRecord.status))));
        ui->tableWidget->setItem(InsR,3, new QTableWidgetItem((QString::number(DATRecord.zalegn))));
        ui->tableWidget->setItem(InsR,4, new QTableWidgetItem((QString::number(DATRecord.nomer))));
        ui->tableWidget->setItem(InsR,5, new QTableWidgetItem((QString::number(DATRecord.kodv))));
        ui->tableWidget->setItem(InsR,6, new QTableWidgetItem((QString::number(DATRecord.kodn))));
        ui->tableWidget->setItem(InsR,7, new QTableWidgetItem((QString::number(DATRecord.kodab))));
        ui->tableWidget->setItem(InsR,8, new QTableWidgetItem((QString::number(DATRecord.attr))));
        ui->tableWidget->setItem(InsR,9, new QTableWidgetItem((DATRecord.text)));
        ui->tableWidget->setItem(InsR,10, new QTableWidgetItem((DATRecord.textmnemo)));
        ui->tableWidget->setItem(InsR,11, new QTableWidgetItem((QString::number(DATRecord.tmnpx))));
        ui->tableWidget->setItem(InsR,12, new QTableWidgetItem((QString::number(DATRecord.tmnpy))));
        ui->tableWidget->setItem(InsR,13, new QTableWidgetItem((QString::number(DATRecord.idsql))));
        ui->tableWidget->setItem(InsR,14, new QTableWidgetItem((QString::number(DATRecord.vvodiv))));
        ui->tableWidget->setItem(InsR,15, new QTableWidgetItem((QString::number(DATRecord.vv1))));
        ui->tableWidget->setItem(InsR,16, new QTableWidgetItem((QString::number(DATRecord.vv2))));
        ui->tableWidget->setItem(InsR,17, new QTableWidgetItem((QString::number(DATRecord.vv3))));
        ui->tableWidget->setItem(InsR,18, new QTableWidgetItem((QString::number(DATRecord.vv4))));
        ui->tableWidget->setItem(InsR,19, new QTableWidgetItem((QString::number(DATRecord.tupzalegn))));
        ui->tableWidget->setRowHeight(InsR,16);
        InsR += 1;
    }

    inFile.close();

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::onLoadFileButtonClicked()
{
    static QString fileLocation = QDir::currentPath();
    fileLocation = QFileDialog::getOpenFileName(this, "Load dat file",
                                                QDir::currentPath(), "dat files (*.dat)");

    _datFile = fileLocation;
}
