#include "config.h"
#include <QFile>
#include "qfile.h"


Config::Config()
{

}

void Config::setFile(QString fileName)
{
    settings = new QSettings(fileName, QSettings::IniFormat);
	settings->beginGroup("SMTP");
    settings->setValue("SERVER", settings->value("SERVER","").toString());
    settings->setValue("PORT", settings->value("PORT","").toString());
    settings->setValue("USER", settings->value("USER","").toString());
    settings->setValue("PASSWORD", settings->value("PASSWORD","").toString());
    settings->setValue("RECIPANT", settings->value("RECIPANT","").toString());
    settings->setValue("LASTSENT", "kodok");
    settings->endGroup();

    /*
    settings->beginGroup("SERVER");
    settings->setValue("HOSTNAME", hostName);
    settings->setValue("DATABASE", database);
    settings->setValue("USER", user);
    settings->setValue("PASSWORD", password);
    settings->endGroup();
    */
}

void Config::setLastSent(QString strData)
{
    settings->beginGroup("HISTORY");
    settings->setValue("LASTSENT", strData);
    settings->endGroup();
}

// void Config::server(QString hostName, QString database, QString user, QString password)
// {
    // settings->beginGroup("SERVER");
    // settings->setValue("HOSTNAME", hostName);
    // settings->setValue("DATABASE", database);
    // settings->setValue("USER", user);
    // settings->setValue("PASSWORD", password);
    // settings->endGroup();
// }

// void Config::hardware(QString comport, QString baudrate)
// {
    // settings->beginGroup("HARDWARE");
    // settings->setValue("COMPORT", comport);
    // settings->setValue("BAUDRATE", baudrate);
    // settings->endGroup();
// }

// void Config::setHostName(QString hostName)
// {
    // settings->beginGroup("SERVER");
    // settings->setValue("HOSTNAME", hostName);
    // settings->endGroup();
// }

// void Config::setDatabase(QString dbName)
// {
    // settings->beginGroup("SERVER");
    // settings->setValue("DATABASE", dbName);
    // settings->endGroup();
// }

// void Config::setDbUser(QString userName)
// {
    // settings->beginGroup("SERVER");
    // settings->setValue("USER", userName);
    // settings->endGroup();
// }

// void Config::setDbPassword(QString password)
// {
    // settings->beginGroup("SERVER");
    // settings->setValue("PASSWORD", password);
    // settings->endGroup();
// }

// void Config::setComport(QString comport)
// {
    // settings->beginGroup("HARDWARE");
    // settings->setValue("COMPORT", comport);
    // settings->endGroup();
// }

// void Config::setBaudrate(QString baudrate)
// {
    // settings->beginGroup("HARDWARE");
    // settings->setValue("BAUDRATE", baudrate);
    // settings->endGroup();
// }

// void Config::setPictures(QString url)
// {
    // settings->beginGroup("SERVER");
    // settings->setValue("PICTURES", url);
    // settings->endGroup();
// }

// QString Config::getHostName()
// {
    // settings->beginGroup("SERVER");
    // QString read = settings->value("HOSTNAME","").toString();
    // settings->endGroup();
    // return read;
// }

QString Config::getSmtpServer()
{
    settings->beginGroup("SMTP");
    QString read = settings->value("SERVER","").toString();
    settings->endGroup();
    return read;
}

QString Config::getPort()
{
    settings->beginGroup("SMTP");
    QString read = settings->value("PORT","").toString();
    settings->endGroup();
    return read;
}

QString Config::getUser()
{
    settings->beginGroup("SMTP");
    QString read = settings->value("USER","").toString();
    settings->endGroup();
    return read;
}

QString Config::getPassword()
{
    settings->beginGroup("SMTP");
    QString read = settings->value("PASSWORD","").toString();
    settings->endGroup();
    return read;
}

QString Config::getRecipant()
{
    settings->beginGroup("SMTP");
    QString read = settings->value("RECIPANT","").toString();
    settings->endGroup();
    return read;
}

QString Config::getSavePath()
{
    settings->beginGroup("SMTP");
    QString read = settings->value("PATH","").toString();
    settings->endGroup();
    return read;
}

QString Config::getLastSent()
{
    settings->beginGroup("HISTORY");
    QString read = settings->value("LASTSENT","").toString();
    settings->endGroup();
    return read;
}

// QString Config::getDatabase()
// {
    // settings->beginGroup("SERVER");
    // QString read = settings->value("DATABASE","").toString();
    // settings->endGroup();
    // return read;
// }

// QString Config::getDbUser()
// {
    // settings->beginGroup("SERVER");
    // QString read = settings->value("USER","").toString();
    // settings->endGroup();
    // return read;
// }

// QString Config::getDbPassword()
// {
    // settings->beginGroup("SERVER");
    // QString read = settings->value("PASSWORD","").toString();
    // settings->endGroup();
    // return read;
// }

// QString Config::getComport()
// {
    // settings->beginGroup("HARDWARE");
    // QString read = settings->value("COMPORT","").toString();
    // settings->endGroup();
    // return read;
// }

// QString Config::getBaudrate()
// {
    // settings->beginGroup("HARDWARE");
    // QString read = settings->value("BAUDRATE","").toString();
    // settings->endGroup();
    // return read;
// }

// QString Config::getPictures()
// {
    // settings->beginGroup("SERVER");
    // QString read = settings->value("PICTURES","").toString();
    // settings->endGroup();
    // return read;
// }

// QString Config::getIpCamUrl()
// {
    // settings->beginGroup("HARDWARE");
    // QString read = settings->value("CAMERAURL","").toString();
    // settings->endGroup();
    // return read;
// }

// QString Config::getLokasi()
// {
    // settings->beginGroup("PARKIR");
    // QString read = settings->value("LOKASI","").toString();
    // settings->endGroup();
    // return read;
// }

// QString Config::getAlamat()
// {
    // settings->beginGroup("PARKIR");
    // QString read = settings->value("ALAMAT","").toString();
    // settings->endGroup();
    // return read;
// }

// QString Config::getIpCamVidUrl()
// {
    // settings->beginGroup("HARDWARE");
    // QString read = settings->value("IPCAMURL","").toString();
    // settings->endGroup();
    // return read;
// }

