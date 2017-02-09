#ifndef PARSER_H_
#define PARSER_H_

#include "Command.h"
#include "CommandWords.h"
#include <QLineEdit>

class Parser {
private:
	CommandWords *commands;
    QTextBrowser *gameArea_TB ;
    QString commandQString;
public:
	Parser();
	Command* getCommand();
    void showCommands(QTextBrowser *qTB);
    void setGameArea(QTextBrowser *qTB);
    void setCommandQString(QString inCommandQString);
};

#endif /*PARSER_H_*/
