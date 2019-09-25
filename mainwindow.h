#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include "filemanager.h"
#include <QObject>
#include <QFile>
#include <QDir>
#include <qdir.h>
#include <QTextStream>
#include <QtDebug>
#include <qdebug.h>
#include <QDebug>
#include <QTimer>
#include "config.h"
#include "smtp.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnWrite_clicked();
    void on_btnRead_clicked();
    void on_btnRemove_clicked();
    void on_btnFind_clicked();
    void on_btnInsert_clicked();
    void on_btnSendMail_clicked();
    void mailSent(QString);
    void callBackTimer();

private:
    Ui::MainWindow *ui;
    QString fileFirstFound(QString dir);
    bool fileWrite(int i, QString path, QString data);
    QString fileRead(QString path);
    bool fileDelete(QString path);
    void loadSettings(void);
    QString getDateToday(void);
    void sendMail(QString dateStr);
    void displayDataYesterday(QString dateStr);

    //QString m_sSettingsFile;
    QString dateYesterday;
    QString dateToday;

    // Config
    Config config;

    QTimer *timerGetDate;
};

/*
class filemanager : public QObject
{
    Q_OBJECT
public:
    explicit filemanager(QObject *parent = nullptr);
    QString fileFirstFound(QString dir);
    bool fileWrite(int i, QString path, QString data);
    QString fileRead(QString path);
    bool fileDelete(QString path);
signals:

public slots:
};
*/
#endif // MAINWINDOW_H
