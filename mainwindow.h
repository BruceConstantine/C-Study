#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QWidget>
#include <string>
#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "item.h"
#include "Character.h"
#include<QCloseEvent>

#undef new

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTextBrowser *getGameArea();
    QLineEdit *getInputArea();
    Ui::MainWindow *ui;

    void play();
    string go(string direction);
protected:
    virtual void closeEvent(QCloseEvent *event);//this function in parents class also are virtual

private:
    QTextBrowser *gameArea_TB;
    Parser parser;
    Room *currentRoom;
    Room *roomList[11];
    int cld_MovesNUM;
    int cld_ScordsNUM;
    Character *player;

    void createRooms();
    void printWelcome();
    bool processCommand(Command command);
    void printHelp();
    void goRoom(Command command);
    void createItems();
    void displayItems();


private slots:
    void on_lineEdit_typeIn_returnPressed();
    void on_btn_w_clicked();
    void on_btn_n_clicked();
    void on_btn_s_clicked();
    void on_btn_e_clicked();
    void on_pushButton_clicked();
    void on_actionQuit_Exit_triggered();
    void on_actionHelp_triggered();
    void on_actionRestart_Game_triggered();
    void on_actionInfomation_triggered();
};
#endif // MAINWINDOW_H
