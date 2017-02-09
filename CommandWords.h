#ifndef COMMANDWORDS_H_
#define COMMANDWORDS_H_

#include <QTextBrowser>
#include <string>
#include <vector>
using namespace std;

//#include "redefinenewkeyword.h"

class CommandWords {
private:
	//Define a static vector for our valid command words.
	//We'll populate this in the class constructor
	static vector<string> validCommands;
public:
	CommandWords();
	bool isCommand(string aString);
    void showAll(QTextBrowser *gameArea_TB);
};


#endif /*COMMANDWORDS_H_*/
