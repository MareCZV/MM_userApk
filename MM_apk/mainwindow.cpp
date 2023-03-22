#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>
#include "adduserwindow.h"
#include "jsonfiles.h"
#include <QPixmap>
#include <QRegularExpression>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // postavljanje deafult slike u labelu
    QPixmap pic(":/Images/blank.png");
    int ImgLabelwidth,ImgLabelheight;
    ImgLabelwidth = ui->ImgLabel->width();
    ImgLabelheight= ui->ImgLabel->height();
    ui->ImgLabel->setPixmap(pic.scaled(ImgLabelwidth,ImgLabelheight,Qt::KeepAspectRatio));
    // ucitavanje JSON file-a u listWidget
    QFile file(":/JSON directory/userList.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
       qDebug() << "Failed to open file";
    }
    QJsonDocument doc=QJsonDocument::fromJson(file.readAll());
    QJsonObject root_obj = doc.object(); // dobijanje root objekta iz JSON file-a
    QJsonArray user_list=root_obj.value("userList").toArray(); // ukazivanje na niz
    for(int i=0;i<user_list.size();i++)
    {
        QJsonObject user_obj = user_list[i].toObject(); //dobijanje objekta sa indeksom i
        QJsonValue nameVal =user_obj.value("Name");
        QJsonValue lastNameVal =user_obj.value("lastName");
        QJsonValue emailVal =user_obj.value("email");
        ui->listWidget->addItem(nameVal.toString()+" "+lastNameVal.toString()+"  -  "+emailVal.toString());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newButton_clicked()
{
    //otvaranje novog prozora preko dugmeta
    adduserwindow drugiwindow;
        drugiwindow.setModal(true);
        drugiwindow.exec();
}

void MainWindow::on_deleteButton_clicked()
{
    QFile file(":/JSON directory/userList.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
       qDebug() << "Failed to open file";
    }
    QJsonDocument doc=QJsonDocument::fromJson(file.readAll());
    QJsonObject root_obj = doc.object();
    QJsonArray user_list=root_obj.value("userList").toArray();
    QMessageBox::StandardButton reply;
    reply=QMessageBox::question(this,"Delete User","Are you sure you want to delete this user?", QMessageBox::Yes|QMessageBox::No);
    if(reply==QMessageBox::Yes)
    {
        QMessageBox::information(this,"User deleted","User deleted");
        user_list.removeAt(ui->listWidget->currentRow()); //uklanjanje objekta iz JSON file niza
    }
    else
    {
        QMessageBox::information(this,"User not deleted","User not deleted");
    }
}

void MainWindow::on_showDetailsButton_clicked()
{
    QFile file(":/JSON directory/userList.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
       qDebug() << "Failed to open file";
    }
    QJsonDocument doc=QJsonDocument::fromJson(file.readAll());
    QJsonObject root_obj = doc.object();
    QJsonArray user_list=root_obj.value("userList").toArray();
    QJsonObject user_obj = user_list[ui->listWidget->currentRow()].toObject();
    // dobijanje vrednosti koje se nalaze u JSON file-u
    QJsonValue nameVal =user_obj.value("Name");
    QJsonValue lastNameVal =user_obj.value("lastName");
    QJsonValue emailVal =user_obj.value("email");
    QJsonValue genderVal =user_obj.value("gender");
    QJsonValue dobVal =user_obj.value("dateOfBirth");
    QJsonValue streetVal =user_obj.value("street");
    QJsonValue cityVal =user_obj.value("city");
    QJsonValue postVal =user_obj.value("postalCode");
    QJsonValue phoneVal =user_obj.value("phone");
    QJsonValue imgVal =user_obj.value("imagePath");
    //ispisivanje vrednosti na mesto labela
    ui->clabelName->setText(nameVal.toString());
    ui->clabelLastName->setText(lastNameVal.toString());
    ui->clabelEmail->setText(emailVal.toString());
    ui->clabelGender->setText(genderVal.toString());
    ui->clabelDoB->setText(dobVal.toString());
    ui->clabelStreet->setText(streetVal.toString());
    ui->clabelCity->setText(cityVal.toString());
    ui->clabelPost->setText(postVal.toString());
    ui->clabelPhone->setText(phoneVal.toString());
    if(imgVal==NULL)
    {
        QPixmap pic(":/Images/blank");
        int ImgLabelwidth,ImgLabelheight;
        ImgLabelwidth = ui->ImgLabel->width();
        ImgLabelheight= ui->ImgLabel->height();
        ui->ImgLabel->setPixmap(pic.scaled(ImgLabelwidth,ImgLabelheight,Qt::KeepAspectRatio));
    }
    else
    {
        QPixmap pic(":/Images/"+imgVal.toString());
        int ImgLabelwidth,ImgLabelheight;
        ImgLabelwidth = ui->ImgLabel->width();
        ImgLabelheight= ui->ImgLabel->height();
        ui->ImgLabel->setPixmap(pic.scaled(ImgLabelwidth,ImgLabelheight,Qt::KeepAspectRatio));
    }
}

void MainWindow::on_refreshButton_clicked()
{
    // dugme koje obnavlja listu
    ui->listWidget->clear();
    QFile file(":/JSON directory/userList.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
       qDebug() << "Failed to open file";
    }
    QJsonDocument doc=QJsonDocument::fromJson(file.readAll());
    QJsonObject root_obj = doc.object();
    QJsonArray user_list=root_obj.value("userList").toArray();
    for(int i=0;i<user_list.size();i++)
    {
        QJsonObject user_obj = user_list[i].toObject();
        QJsonValue nameVal =user_obj.value("Name");
        QJsonValue lastNameVal =user_obj.value("lastName");
        QJsonValue emailVal =user_obj.value("email");
        QJsonValue idVal =user_obj.value("id");
        ui->listWidget->addItem(nameVal.toString()+" "+lastNameVal.toString()+" -  "+emailVal.toString());

    }
    ui->searchLineEdit->clear();
}

void MainWindow::on_searchButton_clicked()
{
    QString searchString = ui->searchLineEdit->text();
    if(searchString.isEmpty())
    {
        QMessageBox::information(this,"Empty Search Field","Please enter the value");
    }
    else
    {
        for(int row(0); row < ui->listWidget->count(); row++ )
            ui->listWidget->item(row)->setHidden(true);
        QList<QListWidgetItem*> matches ( ui->listWidget->findItems(searchString, Qt::MatchFlag::MatchContains) );
          for(QListWidgetItem* item : matches)
            item->setHidden(false);
    }
}

