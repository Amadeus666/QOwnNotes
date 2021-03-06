#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "build_number.h"
#include "version.h"
#include <QFile>
#include <QDate>
#include <QTextStream>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    // load the about.html
    QFile f(":/html/about.html");
    if ( f.open( QFile::ReadOnly | QFile::Text ) )
    {
        QTextStream istream (&f);
        QString html = istream.readAll();
        QDate date = QDate::currentDate();

        // fill in the variables
        html = html.replace( "BUILD_NUMBER", QString::number( BUILD ) );
        html = html.replace( "BUILD_DATE", __DATE__ );
        html = html.replace( "VERSION", QString( VERSION ) );
        html = html.replace( "CURRENT_YEAR", QString::number( date.year() ) );

        // put the html to the text browser in the about dialog
        ui->textBrowser->setHtml( html );
        f.close();
    }
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
