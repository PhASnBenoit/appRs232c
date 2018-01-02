#include "cihmapprs232c.h"
#include "ui_cihmapprs232c.h"

CIhmAppRs232c::CIhmAppRs232c(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CIhmAppRs232c)
{
    ui->setupUi(this);
    ui->gbRs->setEnabled(false);

    QStringList stringList;
    QList<QSerialPortInfo> spi;
    spi = QSerialPortInfo::availablePorts();
    for (int i=0 ; i<spi.size() ; i++) {
        QString str = spi.at(i).portName();
        stringList.append(str);
    } // for
    ui->cbPorts->addItems(stringList);
}

CIhmAppRs232c::~CIhmAppRs232c()
{
    delete m_rs;
    delete ui;
}

void CIhmAppRs232c::on_pbEnvoyer_clicked()
{
    m_rs->ecrire(ui->leTexte->text().toStdString().c_str(), ui->leTexte->text().length());
}

void CIhmAppRs232c::on_pbOuvrir_clicked()
{
    if (ui->pbOuvrir->text() == "Ouvrir") {
        m_rs = new CRs232c(this, "/dev/"+ui->cbPorts->currentText());
        connect(m_rs, SIGNAL(sigErreur(QSerialPort::SerialPortError)), this, SLOT(on_erreur(QSerialPort::SerialPortError)));
        connect(m_rs, SIGNAL(sigData(QByteArray)), this, SLOT(on_recevoirDataDuPeriph(QByteArray)));
        m_rs->ouvrirPort();
        m_rs->initialiser(QSerialPort::Baud9600,
                              QSerialPort::Data8,
                              QSerialPort::NoParity,
                              QSerialPort::OneStop,
                              QSerialPort::NoFlowControl);
        ui->gbRs->setEnabled(true);
        ui->pbOuvrir->setText("Fermer");
    } else {
        ui->pbOuvrir->setText("Ouvrir");
        ui->gbRs->setEnabled(false);
        delete m_rs;
    } // else
}

void CIhmAppRs232c::on_erreur(QSerialPort::SerialPortError err)
{
   ui->teTexte->append("Erreur voie série !");
}

void CIhmAppRs232c::on_recevoirDataDuPeriph(QByteArray txt)
{
    ui->teTexte->append(QString(txt));
}
