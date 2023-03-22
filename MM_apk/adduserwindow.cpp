#include "adduserwindow.h"
#include "ui_adduserwindow.h"
#include "jsonfiles.h"
#include <iostream>
using namespace std;
adduserwindow::adduserwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adduserwindow)
{
    ui->setupUi(this);
}

adduserwindow::~adduserwindow()
{
    delete ui;
}

void adduserwindow::on_buttonBox_accepted()
{
    //preuzimanje podataka koje je korisnik uzeo
    QString gender;
    QString name = ui->lineEdit_name->text();
    QString lastName = ui->lineEdit_lastName->text();
    QString email = ui->lineEdit_email->text();
    if(ui->radioButton_male->isChecked())
        gender = "Male";
    if(ui->radioButton_female->isChecked())
        gender = "Female";
    QString dateOfBirth = ui->lineEdit_DoB->text();
    QString street = ui->lineEdit_street->text();
    QString city = ui->lineEdit_city->text();
    QString postalCode = ui->lineEdit_post->text();
    QString phone = ui->lineEdit_phone->text();
    QString imgPath = ui->lineEdit_imgPath->text();

    //otvaranje file-a
    QFile file(":/JSON directory/userList.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
       qDebug() << "Failed to open file";
    }

    QJsonDocument doc=QJsonDocument::fromJson(file.readAll());
    QJsonObject root_obj = doc.object();
    //kreiranje novog objekta
    QJsonObject user_obj{
        {"Name",name},
        {"lastName",lastName},
        {"email",email},
        {"gender",gender},
        {"dateOfBirth",dateOfBirth},
        {"street",street},
        {"city",city},
        {"postalCode",postalCode},
        {"phone",phone},
        {"imagePath",imgPath}
    };
    QJsonArray user_list = root_obj["userList"].toArray();
    user_list.insert(1,user_obj);
    doc.setObject(root_obj);
}



