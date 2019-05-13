#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QWidget>
#include <QTableWidgetItem>

#include <iostream>
#include <fstream>
#include <QDataStream>
#include <QFile>
#include <QTextCodec>
#include <QDebug>

#include <QString>

#include <QMessageBox>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    fstream inFile;
    //int value1;
    int32_t IntRead;
    int posx;
    //int idv;
    //char asdf [407];
    //char asdf1 [15];
    char TextVV [100];
    char TextMnemo [255];
    char16_t TestSymb;
    int InsR = 0;
    long long toPos;
    inFile.open("d:\\Askmem\\NV\\data\\vv.dat", ios::binary | ios::in);
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
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setHorizontalHeaderLabels({"Header 1", "Header 2", "Header 3"});
    //////////////////////
    //inFile.read((char*)&value1, sizeof(value1));
    //QMessageBox::about(this, "Значення", QString::number(value1));

    inFile.seekg(0);
    while(!inFile.eof()){
    //while(inFile.read((char*)&posx, sizeof(posx))){
        long long ppos = inFile.tellg();
        for (int var = 0; var < 9; ++var) {
            IntRead = NULL;
            inFile.read(reinterpret_cast<char*>(&IntRead), sizeof(int));
            if (var == 0)
                posx = IntRead;
        }

        inFile.read(reinterpret_cast<char*>(&TextVV), sizeof(TextVV));

        toPos = inFile.tellg();
        if (toPos > 2) {
        toPos += 2;
        inFile.seekg(toPos);
        }

        //inFile.read(reinterpret_cast<char*>(&TestSymb), sizeof(TestSymb));
        inFile.read(reinterpret_cast<char*>(&TextMnemo), sizeof(TextMnemo));
        toPos = inFile.tellg();
        if (toPos > 2) {
        toPos += 3;
        inFile.seekg(toPos);
        }

        //inFile.read(reinterpret_cast<char*>(&TestSymb), sizeof(TestSymb));

        /*toPos = inFile.tellg();
        toPos += 359;
        inFile.seekg(toPos);
        */

        for (int var = 0; var < 9; ++var) {
            inFile.read(reinterpret_cast<char*>(&IntRead), sizeof(int));
        }

        /*
        if ((inFile.tellg()-ppos) > 434) {
            toPos = inFile.tellg();
            toPos -= (inFile.tellg()-ppos);
            toPos += 432;
            inFile.seekg(toPos);
        }
        */
        //inFile.read(reinterpret_cast<char*>(&idv), sizeof(idv));
        //inFile.read(reinterpret_cast<char*>(&asdf), sizeof(asdf));
       // QMessageBox::about(this, "Значення", (QString::number(posx))+" "+(QString::number(inFile.tellg())));
        //cout << aaa.posx << std::endl;
        //cout << aaa.text << std::endl;

        ui->tableWidget->insertRow(InsR);
        ui->tableWidget->setItem(InsR,1, new QTableWidgetItem((QString::number(ppos))));
        ui->tableWidget->setItem(InsR,2, new QTableWidgetItem((QString::number(inFile.tellg()))));
        ui->tableWidget->setItem(InsR,3, new QTableWidgetItem((QString::number(inFile.tellg()-ppos))));
        ui->tableWidget->setItem(InsR,4, new QTableWidgetItem(QString::fromLocal8Bit(TextVV)));
        ui->tableWidget->setItem(InsR,5, new QTableWidgetItem(QString::fromLocal8Bit(TextMnemo)));
        //inFile.read(reinterpret_cast<char*>(&posx), sizeof(int));
        ui->tableWidget->setItem(InsR,0, new QTableWidgetItem((QString::number(posx))));
        ui->tableWidget->setRowHeight(InsR,16);
        InsR += 1;
    }

    //ui->tableWidget->insertRow(0);
    //ui->tableWidget->insertRow(1);
    //ui->tableWidget->setItem(0,0, new QTableWidgetItem((QString::number(posx))));

    /*
    for (int var = 10350; var < 10400; ++var) {
        ui->tableWidget->insertRow(InsR);
        ui->tableWidget->setItem(InsR,1, new QTableWidgetItem((QString::number(var))));
        inFile.seekg(var);
        inFile.read(reinterpret_cast<char*>(&posx), sizeof(int));

        ui->tableWidget->setItem(InsR,0, new QTableWidgetItem((QString::number(posx))));
        InsR += 1;
    }
    */
    inFile.close();
    for (int var = 0; var<InsR; var ++) {

    }

    //ui->tableWidget->setRowHeight(0,20);
    //ui->tableWidget->setColumnWidth(0,20);
    ui->tableWidget->resizeColumnsToContents();
    // Растягиваем последнюю колонку на всё доступное пространство
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

}
