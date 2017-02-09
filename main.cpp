#include "mainwindow.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QElapsedTimer>
#include <QFont>
#include <QTextBrowser>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
#if 1
// set QFont for splash
    QFont splashFont;
    splashFont.setFamily("Arial");
    splashFont.setBold(true);
    splashFont.setPixelSize(22.5);
    splashFont.setStretch(125);

// splash
    QPixmap pixmap(":/images/zork.jpg");// file sys: ':' is .qrc file; '/' is prefix file name; 'images/' is the subfolder ; and filename;
    QSplashScreen screen(pixmap);
    screen.setFont(splashFont);
    screen.show();
    screen.showMessage("Welcome to Zork",Qt::AlignHorizontal_Mask,Qt::white);

// set the splashed delaye time
    QElapsedTimer timer ;
    timer.start();
    while(timer.elapsed() < 2500)/* elapsed time is 2.5 seconds*/
    {
        app.processEvents();
    }
#endif
//start mainwindow w
    MainWindow w;
    w.show();
    screen.finish(&w);
    return app.exec();
}
