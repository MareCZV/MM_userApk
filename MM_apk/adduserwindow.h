#ifndef ADDUSERWINDOW_H
#define ADDUSERWINDOW_H

#include <QDialog>

namespace Ui {
class adduserwindow;
}

class adduserwindow : public QDialog
{
    Q_OBJECT

public:
    explicit adduserwindow(QWidget *parent = nullptr);
    ~adduserwindow();


private slots:
    void on_buttonBox_accepted();

private:
    Ui::adduserwindow *ui;
};

#endif // ADDUSERWINDOW_H
