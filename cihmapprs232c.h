#ifndef CIHMAPPRS232C_H
#define CIHMAPPRS232C_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include "/home/pi/devQt/biblis/crs232c.h"

namespace Ui {
class CIhmAppRs232c;
}

class CIhmAppRs232c : public QMainWindow
{
    Q_OBJECT

public:
    explicit CIhmAppRs232c(QWidget *parent = 0);
    ~CIhmAppRs232c();

private slots:
    void on_pbEnvoyer_clicked();
    void on_pbOuvrir_clicked();
    void on_erreur(QSerialPort::SerialPortError err);
    void on_recevoirDataDuPeriph(QByteArray txt);

private:
    Ui::CIhmAppRs232c *ui;
    CRs232c *m_rs;
};

#endif // CIHMAPPRS232C_H
