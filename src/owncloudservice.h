#ifndef OWNCLOUDSERVICE_H
#define OWNCLOUDSERVICE_H

#include <QNetworkAccessManager>
#include <QAuthenticator>
#include <QNetworkReply>
#include <QObject>
#include "libraries/simplecrypt/simplecrypt.h"
#include "mainwindow.h"
#include "settingsdialog.h"

#define QOWNNOTESAPI_MIN_VERSION "0.4.1"

class OwnCloudService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool busy READ isBusy NOTIFY busyChanged)

public:
    explicit OwnCloudService(SimpleCrypt *crypto, QObject *parent = 0);
    void settingsConnectionTest( SettingsDialog *dialog );
    bool isBusy();
    void loadVersions(QString notesPath, QString fileName, MainWindow *mainWindow);
    void loadTrash(QString notesPath, MainWindow *mainWindow);
    void restoreTrashedNoteOnServer(QString notesPath, QString fileName, int timestamp, MainWindow *mainWindow);
private:
    QString serverUrl;
    QString userName;
    QString password;
    QString localOwnCloudPath;
    SimpleCrypt *crypto;
    QNetworkAccessManager *networkManager;
    MainWindow *mainWindow;
    static const QString rootPath;
    static const QString format;
    QString versionListPath;
    QString trashListPath;
    QString appInfoPath;
    QString capabilitiesPath;
    QString ownCloudTestPath;
    QString restoreTrashedNotePath;
    SettingsDialog *settingsDialog;
    void checkAppInfo(QNetworkReply *reply);
    bool busy;
    void readSettings();
    void addAuthHeader(QNetworkRequest *r);
    QString getServerNotesPath(QString notesPath);
    void handleVersionsLoading(QString data);
    void handleTrashedLoading(QString data);
signals:
    void busyChanged(bool busy);

private slots:
    void slotAuthenticationRequired ( QNetworkReply * reply, QAuthenticator * authenticator );
    void slotReplyFinished ( QNetworkReply* );
};

#endif // OWNCLOUDSERVICE_H
