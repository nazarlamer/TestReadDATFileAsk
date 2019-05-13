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
#include "data.h"

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
    Serializing::Data DATRecord;

    fstream inFile;
    //int value1;
    int posx;
    //int idv;
    //char asdf [407];
    //char asdf1 [15];
    char TextVV [102];
    char TextMnemo [258];
    char16_t TestSymb;
    int InsR = 0;
    long long toPos;
    inFile.open("d:\\Askmem_3\\NV\\data\\vv.dat", ios::binary | ios::in);
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
    ui->tableWidget->setHorizontalHeaderLabels({"POSX", "POSY", "STATUS", "ZALEGN", "NOMER", "KODV", "KODN", "KODAB", "ATTR", "TEXT", "TEXTMNEMO",
                                                "TMNPX", "TMNPY", "IDSQL", "VVODIV", "VV1", "VV2", "VV3", "VV4", "TUPZALEGN"});
    //////////////////////

/*
kodn:integer;
kodab:integer;
attr:integer;
text:string[100];
textmnemo:string[255];*/

    //inFile.read((char*)&value1, sizeof(value1));
    //QMessageBox::about(this, "Значення", QString::number(value1));

    inFile.seekg(0);
    while(!inFile.eof()){
    //while(inFile.read((char*)&posx, sizeof(posx))){
        long long ppos = inFile.tellg();
        for (int var = 0; var < 9; ++var) {
            int IntRead;
            inFile.read(reinterpret_cast<char*>(&IntRead), sizeof(int));
            switch (var) {
                case 0: DATRecord.posx = IntRead; break;
                case 1: DATRecord.posy = IntRead; break;
                case 2: DATRecord.status = IntRead; break;
                case 3: DATRecord.zalegn = IntRead; break;
                case 4: DATRecord.nomer = IntRead; break;
                case 5: DATRecord.kodv = IntRead; break;
                case 6: DATRecord.kodn = IntRead; break;
                case 7: DATRecord.kodab = IntRead; break;
                case 8: DATRecord.attr = IntRead; break;
            }
        }

        /*
        // 2 text string
        char charBuffer1[100];
        char charBuffer2[255];
        stream.read(charBuffer1, 100);
        stream.read(charBuffer2, 255);
        data.text = QString::fromLocal8Bit(charBuffer1);
        data.textmnemo = QString::fromLocal8Bit(charBuffer2);
        */

        //inFile.read(reinterpret_cast<char*>(&TextVV), sizeof(TextVV));
        DATRecord.text = "";
        char charBuffer1 [100];
        inFile.read(charBuffer1, 1);
        inFile.read(charBuffer1, 100);
        DATRecord.text = QString::fromLocal8Bit(charBuffer1);

        /*toPos = inFile.tellg();
        if (toPos > 2) {
        toPos += 2;
        inFile.seekg(toPos);
        }*/

        //inFile.read(reinterpret_cast<char*>(&TestSymb), sizeof(TestSymb));
        //inFile.read(reinterpret_cast<char*>(&TextMnemo), sizeof(TextMnemo));

        /*toPos = inFile.tellg();
        if (toPos > 2) {
        toPos += 3;
        inFile.seekg(toPos);
        }*/
        DATRecord.textmnemo = "";
        char charBuffer2[255];
        inFile.read(charBuffer1, 1);
        inFile.read(charBuffer2, 255);
        DATRecord.textmnemo = QString::fromLocal8Bit(charBuffer2);
        inFile.read(charBuffer2, 3);

        //inFile.read(reinterpret_cast<char*>(&TestSymb), sizeof(TestSymb));

        /*toPos = inFile.tellg();
        toPos += 359;
        inFile.seekg(toPos);
        */

        for (int var = 0; var < 9; ++var) {
            int IntRead;
            inFile.read(reinterpret_cast<char*>(&IntRead), sizeof(int));
            switch (var) {
                case 0: DATRecord.tmnpx = IntRead; break;
                case 1: DATRecord.tmnpy = IntRead; break;
                case 2: DATRecord.idsql = IntRead; break;
                case 3: DATRecord.vvodiv = IntRead; break;
                case 4: DATRecord.vv1 = IntRead; break;
                case 5: DATRecord.vv2 = IntRead; break;
                case 6: DATRecord.vv3 = IntRead; break;
                case 7: DATRecord.vv4 = IntRead; break;
                case 8: DATRecord.tupzalegn = IntRead; break;
            }
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


    //ui->tableWidget->setRowHeight(0,20);
    //ui->tableWidget->setColumnWidth(0,20);
    ui->tableWidget->resizeColumnsToContents();
    // Растягиваем последнюю колонку на всё доступное пространство
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

}
