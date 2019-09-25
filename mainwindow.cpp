#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QSettings>
#include <QtDebug>
#include <qdebug.h>
#include <QDebug>
#include "config.h"
#include "smtp.h"
//#include "//filemanager.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadSettings();

    qDebug() << "start";
    // populate the items of the list
    for(int i = 0; i < 3000; i++)
    {
        //ui->lw_data->addItem("{\"{item\":AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ}" + QString::number(i) + "}");
    }
    qDebug() << "line 28";
    //config.setLastSent("kurakura");

    qDebug() << "line 31";

    timerGetDate = new QTimer(this);
    connect(timerGetDate, SIGNAL(timeout()), this, SLOT(callBackTimer()));
    timerGetDate->start(60000); // 1 menit sekali

    qDebug() << "line 37";

    //Init day
    dateToday = getDateToday();
    dateYesterday = dateToday;

    qDebug() << "line 43";
    //displayDataYesterday("Thu Sep 19 2019");

    qDebug() << "line 46";

    //sendMail("Thu Sep 19 2019");
}

/****************************************************************
 ****************************************************************
 ****************************************************************/
void MainWindow::callBackTimer()
{
    dateToday = getDateToday();
    qDebug() << "today is " << dateToday;
    if(dateToday != dateYesterday){ //udah ganti hari
       dateYesterday = dateToday;
       qDebug() << "yesterday has gone " << dateYesterday;
       //Kirim email cuy
       sendMail(dateYesterday);
    }
}

/****************************************************************
 ****************************************************************
 ****************************************************************/
void MainWindow::sendMail(QString dateStr)
{
    //Display data yesterday to be sent
    displayDataYesterday(dateStr);

    QString fileStr;
    QString allStr;
    int i;

    qDebug() << "Recap start ";
    for(i=0;i<ui->lw_data->count();i++){
        fileStr = ui->lw_data->item(i)->text();
        fileStr = fileStr + '\n';
        allStr = allStr + fileStr;
        qDebug() << fileStr;
        qDebug() << "*";
    }

    qDebug() << "joss";
    qDebug() << "All String " << allStr.size();
    qDebug() << "cuk";

    QStringList files;

    files.clear();
    QString strtest = "D://ZIO/1.txt";//"D://ZIO/" + dateStr + ".txt";

    files = strtest.split(",");

    Smtp* smtp = new Smtp(ui->labelMailUserName->text(), ui->labelPassword->text(), ui->labelSmtpServer->text(), ui->labelServerPort->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    //smtp->sendMail(ui->labelMailUserName->text(), ui->labelRecipient->text() , ui->labelAttachment->text(),allStr, files );
    smtp->sendMail(ui->labelMailUserName->text(), ui->labelRecipient->text() , dateStr,allStr, files );
}

/****************************************************************
 ****************************************************************
 ****************************************************************/
void MainWindow::displayDataYesterday(QString dateStr)
{
    //Read each file in folder and store it to list widget
    QDir directory(ui->labelSavePath->text() + dateStr);
    QString fileeach;
    QString content;
    QString pathsave = ui->labelSavePath->text() + dateStr;
    qDebug() << "path save : " << pathsave;
    QStringList filetext = directory.entryList(QStringList() << "*.txt" << "*.txt",QDir::Files);
    //Clear ui list data
    ui->lw_data->clear();
    foreach(QString filename, filetext) {
        qDebug() << "file found : " << filename;
        fileeach = pathsave + "/" + filename;
        qDebug() << "file path : " << fileeach;
        content = fileRead(fileeach);
        ui->lw_data->addItem(content);
    }
}

/****************************************************************
 ****************************************************************
 ****************************************************************/
MainWindow::~MainWindow()
{
    delete ui;
}

/****************************************************************
 ****************************************************************
 ****************************************************************/
void MainWindow::on_btnWrite_clicked()
{
    /*QFile file("D://ZIO/out.txt");
      if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
          return;

      QTextStream out(&file);
      //out << "The magic number is: " << 49 << "\n";
      out << "The magic numbero is: " << 50 << "\n";
    */

    QString path = "D://ZIO/out.txt";
    int i;
    QFile file(path); //"D://ZIO/out.txt");
    //if(i==0){
      //QFile file(path); //"D://ZIO/out.txt");
      if (!file.open(QIODevice::WriteOnly|QIODevice::Text)){
          qDebug() << "open fail";
          //return false;
     // }
    }

    //filemanager fman;
    QString fileStr;
    QString allStr;
    QByteArray strArray;
    QTextStream out(&file);
//    int i = 0;

    qDebug() << "Recap start ";
    for(i=0;i<ui->lw_data->count();i++){
        //qDebug() << list_result->item(i)->text().toFloat();
        fileStr = ui->lw_data->item(i)->text();//ui->lw_data->item(i)->text();
        fileStr = fileStr + '\n';
        allStr = allStr + fileStr;
        strArray = strArray + fileStr.toUtf8();
        out << fileStr+"\n";
        qDebug() << fileStr;
        qDebug() << "*";
    }

    qDebug() << "joss";
    qDebug() << "All String " << allStr.size();
    qDebug() << "array num " << strArray.size();
    qDebug() << "cuk";
    /*
    for(i=0;i<ui->lw_data->count();i++){
        //qDebug() << list_result->item(i)->text().toFloat();
        fileStr = ui->lw_data->item(i)->text();
        qDebug() << fileStr;
        if(fman.fileWrite(i, "D://ZIO/7.txt",fileStr)){
           qDebug() << "success write " << fileStr;
        }else{
           qDebug() << "fail write";
        }
    }

    QList<QString> texts;
    foreach(QListWidgetItem *item, items)
      texts.append(item->text());

    QList<QString> texts;
    foreach(QListWidgetItem *item, items)
      texts.append(item->text());


    //if(fman.fileWrite("D://ZIO/7.txt","kodokku")){
    if(fman.fileWrite("D://ZIO/7.txt",ui->lw_data->item(i))){
       qDebug() << "success write";
       qDebug() << ui->lw_data->
    }else{
       qDebug() << "fail write";
    }
    */
}

/****************************************************************
 ****************************************************************
 ****************************************************************/
void MainWindow::on_btnRead_clicked()
{
    /*
    QFile file("D://ZIO/out.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << "line.." << line;
        //process_line(line);
    }
    */
    //filemanager fman;

    QString fileStr = "Tue Sep 17 2019";

    //fileStr = fileRead("D://ZIO/");
    //qDebug() << "fileRead" << fileStr;
    //qDebug() << fileStr;


    //assume the directory exists and contains some files and you want all jpg and JPG files
    QDir directory("D://ZIO/" + fileStr);
    QFile path;
    QString content;
    QString pathsave = "D://ZIO/";
    QStringList filetext = directory.entryList(QStringList() << "*.txt" << "*.txt",QDir::Files);
    foreach(QString filename, filetext) {
        qDebug() << "file found : " << filename;
        //content = fileRead("D://ZIO/Tue Sep 17 2019/" + filename);
        content = fileRead(pathsave + "/" + fileStr + "/" + filename);
        ui->lw_data->addItem(content);
        //ui->lw_data->addItem("{\"item\":" + filename + "}");

        //QString MainWindow::fileRead(QString path)
    //do whatever you need to do
    }
}

/****************************************************************
 ****************************************************************
 ****************************************************************/
void MainWindow::on_btnRemove_clicked()
{
    /*
    QFile file ("D://ZIO/out.txt");
    file.remove();
    */
    //filemanager fman;
    QString fileStr;

    fileStr = fileDelete("D://ZIO/7.txt");
}

/****************************************************************
 ****************************************************************
 ****************************************************************/
void MainWindow::on_btnFind_clicked()
{
    //filemanager fman;
    QString fileStr;

    fileStr = fileFirstFound("D://ZIO/Tue Sep 17 2019");
    qDebug() << "file First Found";
    qDebug() << fileStr;
}

/****************************************************************
 ****************************************************************
 ****************************************************************/
void MainWindow::on_btnInsert_clicked()
{
    qDebug() << "start";
    // populate the items of the list
    for(int i = 0; i < 3000; i++)
    {
        ui->lw_data->addItem("{\"item\":" + QString::number(i) + "}");
    }
    qDebug() << "finish";
}

/****************************************************************
 ****************************************************************
 ****************************************************************/
QString MainWindow::fileFirstFound(QString dir)
{
    //QString path = "D:/ZIO";
    QDir dir_path(dir);
    QString str;

     foreach(QFileInfo item, dir_path.entryInfoList())
     {
    //QFileInfo item;
         if(item.isDir())
             qDebug() << "Dir: " << item.absoluteFilePath();
         if(item.isFile()){
             //qDebug() << "File: " << item.fileName();
             str = item.fileName();
             qDebug() << "File: " << str;

             qDebug() << "File: " << item.size();
             //qDebug() << "File: " << item.;
             //qDebug() << "File: " << item.;
             return str;
         }
         //if(item.)
         //qDebug() << "File: " << item.absoluteFilePath();
     }
         return "NULL";
}

/****************************************************************
 ****************************************************************
 ****************************************************************/
bool MainWindow::fileWrite(int i, QString path, QString data)
{
    //bool openok = false;
    QFile file(path); //"D://ZIO/out.txt");
    if(i==0){
      //QFile file(path); //"D://ZIO/out.txt");
      if (!file.open(QIODevice::WriteOnly|QIODevice::Text)){
          qDebug() << "open fail";
          return false;
      }
    }

    //filemanager fman;
    QString fileStr;
    QTextStream out(&file);
//    int i = 0;


    for(i=0;i<ui->lw_data->count();i++){
        //qDebug() << list_result->item(i)->text().toFloat();
        fileStr = ui->lw_data->item(i)->text();//ui->lw_data->item(i)->text();
        out << fileStr;
        qDebug() << fileStr;
    }

          //QTextStream out(&file);
          //out << "The magic number is: " << 49 << "\n";
          //out << data;
          //out << data;
          //out << data;
          //out << data;
          //qDebug() << "open OK";
          //return true;

      //}else{

      //}
}

/****************************************************************
 ****************************************************************
 ****************************************************************/
QString MainWindow::fileRead(QString path)
{
    QFile file(path); //("D://ZIO/out.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "NULL";

    QTextStream in(&file);
    //!in.readAll()) {
        QString line = in.readLine();
        qDebug() << "line.." << line;
        //process_line(line);
        return line;
    //}
}

/****************************************************************
 ****************************************************************
 ****************************************************************/
bool MainWindow::fileDelete(QString path)
{
    QFile file(path); //"D://ZIO/out.txt");
    file.remove();
    return true;
}

/****************************************************************
 ****************************************************************
 ****************************************************************/
void MainWindow::loadSettings()
{
    // Init config
    config.setFile("config.ini");

    qDebug() << "server smtp = " << config.getSmtpServer();
    qDebug() << "server port = " << config.getPort();
    qDebug() << "server user = " << config.getUser();
    qDebug() << "server password " << config.getPassword();
    qDebug() << "server recipant = " << config.getRecipant();
    qDebug() << "save Path = " << config.getSavePath();

    ui->labelSmtpServer->setText(config.getSmtpServer());
    ui->labelServerPort->setText(config.getPort());
    ui->labelMailUserName->setText(config.getUser());
    ui->labelPassword->setText(config.getPassword());
    ui->labelRecipient->setText(config.getRecipant());
    ui->labelSavePath->setText(config.getSavePath());
}

/****************************************************************
 ****************************************************************
 ****************************************************************/
QString MainWindow::getDateToday()
{
    //Get Date time and use it as filename
    QDate local(QDate::currentDate());
    qDebug() << "Date today is:" << local;
    //Convert to String
    return local.toString();
}


/****************************************************************
 ****************************************************************
 ****************************************************************/
void MainWindow::on_btnSendMail_clicked()
{

    //filemanager fman;
    QString fileStr;
    QString allStr;
    //QByteArray strArray;
    int i;
//    int i = 0;

    qDebug() << "Recap start ";
    for(i=0;i<ui->lw_data->count();i++){
        //qDebug() << list_result->item(i)->text().toFloat();
        fileStr = ui->lw_data->item(i)->text();//ui->lw_data->item(i)->text();
        fileStr = fileStr + '\n';
        allStr = allStr + fileStr;
        //strArray = strArray + fileStr.toUtf8();
        //out << fileStr+"\n";
        qDebug() << fileStr;
        qDebug() << "*";
    }

    qDebug() << "joss";
    qDebug() << "All String " << allStr.size();
    //qDebug() << "array num " << strArray.size();
    qDebug() << "cuk";

    QStringList files;

    files.clear();
    QString strtest = "D://ZIO/1.txt";

    files = strtest.split(",");

    //Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    Smtp* smtp = new Smtp(ui->labelMailUserName->text(), ui->labelPassword->text(), ui->labelSmtpServer->text(), ui->labelServerPort->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    //QString body;
    //if( !files.isEmpty() )
        smtp->sendMail(ui->labelMailUserName->text(), ui->labelRecipient->text() , ui->labelAttachment->text(),allStr, files );
        //smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), "D://ZIO" );
    //else
    //    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}
