#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog){
    ui->setupUi(this);    

    arduino = new QSerialPort;

    arduino->setPortName("COM8");
    arduino->open(QSerialPort::WriteOnly);
    arduino->setBaudRate(QSerialPort::Baud9600);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    arduino->setFlowControl(QSerialPort::NoFlowControl);
    _STfreq = "1000000";
}

Dialog::~Dialog(){
    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}


void Dialog::on_RefClk_valueChanged(QString RefClk){
    _refClk = RefClk;
    //qDebug() << _refClk;
}

void Dialog::on_ClkMlt_valueChanged(QString ClkMlt){
    _clkMlt = ClkMlt;
    //qDebug() << _clkMlt;
}

void Dialog::on_modeOptions_currentIndexChanged(int index){
    //single tone mode
    if(index == 1){
        _index = 1;
    }else if(index == 2){
        _index = 2;
    }else if (index == 3){
        _index = 3;
    }else{
        //qDebug() << "no valid selection!";
    }
    //qDebug() << _index;
    Dialog::initDDS();
}

void Dialog::on_terminate_clicked(){

    Dialog::writePort(QString("r%1").arg(_STfreq));

}

void Dialog::on_STFreq_valueChanged(QString STfreq){
    _STfreq = STfreq;
    //qDebug() << _STfreq;
}

void Dialog::on_STMButton_clicked(){
    Dialog::STM();
    //qDebug() << "STM activated.";

}

void Dialog::on_NDfreq0_valueChanged(QString NDfreq0){
    _NDfreq0 = NDfreq0;
    //qDebug() << _NDfreq0;
}

void Dialog::on_NDfreq1_valueChanged(QString NDfreq1){
    _NDfreq1 = NDfreq1;
    //qDebug() << _NDfreq1;
}

void Dialog::on_NDposDF_valueChanged(QString NDposDF){
    _NDposDF = NDposDF;
    //qDebug() << _NDposDF;
}

void Dialog::on_NDposRR_valueChanged(QString NDposRR){
    _NDposRR = NDposRR;
    //qDebug() << _NDposRR;
}

void Dialog::on_NDMButton_clicked(){
    Dialog::NDM();
}

void Dialog::on_LSfreq0_valueChanged(QString LSfreq0){
    _LSfreq0 = LSfreq0;
    //qDebug() << _LSfreq0;
}

void Dialog::on_LSFreq1_valueChanged(QString LSfreq1){
    _LSfreq1 = LSfreq1;
    //qDebug() << _LSfreq1;
}

void Dialog::on_LSposDF_valueChanged(QString LSposDF){
    _LSposDF = LSposDF;
    //qDebug() << _LSposDF;
}

void Dialog::on_LSposRR_valueChanged(QString LSposRR){
    _LSposRR = LSposRR;
    //qDebug() << _LSposRR;
}

void Dialog::on_LSnegDF_valueChanged(QString LSnegDF){
    _LSnegDF = LSnegDF;
    //qDebug() << _LSnegDF;
}

void Dialog::on_LSnegRR_valueChanged(QString LSnegRR){
    _LSnegRR = LSnegRR;
    //qDebug() << _LSnegRR;
}

void Dialog::on_LSMButton_clicked(){
    Dialog::LSM();
}

void Dialog::initDDS(){
       Dialog::writePort(QString("i%1i%2").arg(_refClk).arg(_clkMlt));

}

void Dialog::STM(){

    Dialog::writePort(QString("s%1").arg(_STfreq));

}

void Dialog::NDM(){

    Dialog::writePort(QString("n%1n%2n%3n%4").arg(_NDfreq0).arg(_NDfreq1).arg(_NDposDF).arg(_NDposRR));

    //Dialog::writePort(QString("n%1").arg(_NDfreq1));

    //Dialog::writePort(QString("n%1").arg(_NDposDF));

    //Dialog::writePort(QString("n%1").arg(_NDposRR));

}

void Dialog::LSM(){

    Dialog::writePort(QString("l%1l%2l%3l%4l%5l%6").arg(_LSfreq0).arg(_LSfreq1).arg(_LSposDF).arg(_LSposRR).arg(_LSnegDF).arg(_LSnegRR));
}

void Dialog::writePort(QString command){
    if(arduino->isWritable()){
       arduino->write(command.toStdString().c_str());
    }else{
        //qDebug() << "Arduino is not writable.";
    }

}




