#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextBrowser>
#include <QLineEdit>
#include <QLabel>
#include "tracer.h"

#include "redefinenewkeyword.h"
#ifdef new
#undef new
#endif
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
#define new new(__FILE__,__LINE__)
    ui->setupUi(this);
    cld_MovesNUM = 0;
    cld_ScordsNUM = 0;
    setWindowFlags(Qt::WindowCloseButtonHint);
    statusBar()->showMessage("Ready",2000);
    ui->mainGameArea_TB->setPalette( QPalette(QPalette::Base, QColor(0,0,0)) );
    ui->mainGameArea_TB->setFont( QFont("Arial",-1,3,false));
    ui->mainGameArea_TB->setTextColor(Qt::white);

    ui->mainGameArea_TB->setText("Press 'ENTER' and Start.");
    ui->mainGameArea_TB->append("");

    ui->lcdNumber_moves->setStyleSheet("border: 1px solid black; background: silver;");
    this->gameArea_TB = ui->mainGameArea_TB;

    createRooms();
    player = new Character();

    parser.setGameArea( gameArea_TB );
    printWelcome();
}


MainWindow::~MainWindow()
{
    delete ui;
}

QTextBrowser *MainWindow::getGameArea()
{
    return ui->mainGameArea_TB;
}
QLineEdit *MainWindow::getInputArea()
{
    return ui->lineEdit_typeIn;
}


// SLOT FUNC

//////////// Move this argument into ZorkUL.h


void MainWindow::on_lineEdit_typeIn_returnPressed()
{
    ui->mainGameArea_TB->append("\n--> "+ ui->lineEdit_typeIn->text());
    parser.setCommandQString(ui->lineEdit_typeIn->text());
    ui->lineEdit_typeIn->clear();
    ///set the number of lcd Num inditor.
    play();
    ui->mainGameArea_TB->append("");
    ui->lcdNumber_moves->display(++cld_MovesNUM);
}


void MainWindow::on_btn_w_clicked()
{
    gameArea_TB->append("-->go west");
    parser.setCommandQString("go west");
    goRoom(*parser.getCommand());
    gameArea_TB->append("");
    ui->lcdNumber_moves->display(++cld_MovesNUM);
}

void MainWindow::on_btn_n_clicked()
{
    gameArea_TB->append("-->go north");
    parser.setCommandQString("go north");
    goRoom(*parser.getCommand());
    gameArea_TB->append("");
    ui->lcdNumber_moves->display(++cld_MovesNUM);
}

void MainWindow::on_btn_s_clicked()
{
    gameArea_TB->append("-->go south");
    parser.setCommandQString("go south");
    goRoom(*parser.getCommand());
    gameArea_TB->append("");
    ui->lcdNumber_moves->display(++cld_MovesNUM);
}

void MainWindow::on_btn_e_clicked()
{
    gameArea_TB->append("-->go east");
    parser.setCommandQString("go east");
    goRoom(*parser.getCommand());
    gameArea_TB->append("");
    ui->lcdNumber_moves->display(cld_MovesNUM);
}

///////////////////////////////////////////////////////////////


void MainWindow::createRooms(){
    Room *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k;

    a = new Room("Flatland","Flatland\nIn the north of you, there is a grand view - big rainbow over a giant canyon.\nIn south, a piece of forest block your sight, you cannot go that way.\nBut you can go east, this's a plain as well");
    b = new Room("Midstream", "Middle stream.\nHere has boat, you can take it.\nHowever, the river is too rapid to allow you pass.\nBut in the opposite, some visiters are camping out.");
        Item  * boat= new Item("boat"," :) Let us sway twin oars\\\n", true, false, false);
        b->addItem(boat);

    c = new Room("Path"," Norrow path\nSomeone is yelling, and you look back the capsule - that was burned out by savages...\nThey are rushing to you!!\n");
    d = new Room("Forest","Big Forest\nMany hunge trees block your north direction.\nWest direction leading a big wooden house.\nJust now, you meeted carpenter, he told you, 'you are a thief! Do not go in my sight!!', so you cann't go east...\n");
    e = new Room("Downstream","Downstream\nHere, it has spare forest.\nA Wooden house in font of you, an sharp Axe lying on the ground.\nAnd a path in the west leading to a big forest.\n");
        Item *axe = new Item("axe", "cut! cut! cut!\nshit!shit!shit!\t Nothing could block me!~~!\n", false, true, false);
        e->addItem( axe );

    f = new Room("Canyon","Canyon\nIn the east of canyon has a rope leting you down the canyon. In west, it has a little building standing on the halfway up the hill, with closed door. However, the door is likely could be destroied by some 'cold iron'\n");
    g = new Room("Upstream" ,"Upstream\nThe river sluggishly flow.\nIt's likely could allowing you put a dinghy at here.\n");
    h = new Room("Graveyard" ,"Closed Goth Soldier Graveyard\nA gun lying on a tombstone wirting 'Moixzx Ixn Wonsa Oi va' by Gothese language.");
        Item * gun = new Item("gun","I am 007. @@<-/-\\-- Bong! Shakalaka...\n",false,false,true);
        h->addItem(gun);

    i = new Room("??", "??\nYou dead.\nA savage spoted you! He killed you by his arrow...\nMy God...");
        Item * aircraft = new Item("aircraft","... ... ... \n:( It just likes a pile of scrap iron..\n", true, false, false);
        i->addItem(aircraft);

    j = new Room("You Win.","New Land\nYou go the opposite of the big river, and tell you story to visiters. Then, they take you away immediately.\nThis is the new world!\nYou have gotten off the power of The Goth Clan.\nYou WIN!\n");
    k = new Room("Capsule","Capsule\nWelcome Zork UL!\nNow You are at a capsule in the top of montain, The Goth Clan want catch you for making your yummy body as a meal!!!\nRUN NOW!\n");

//             (N, E, S, W)
    a->setExits(f, b, NULL, c);         // d->N = a after use axe in room in d.
    b->setExits(NULL, NULL, NULL, a);
    c->setExits(NULL, a);   // c->West is NULL rather k. k room is start room ,can not back to that. wild savage burned up that room.
    d->setExits(NULL, NULL, NULL, i);   // d->e != e coz only e to d cannot d to e: the carpenter do not allow you go that way for you stoled his axe..; d->N = a after use axe in room in d.
    e->setExits(NULL, NULL, NULL, d);   // f->w = h after 'use axe' in room f.
    f->setExits(NULL, g, a);
    // g->w != f coz you cannot climb the cliff only by a rope, but you can down the canyon by this.
    // h->e = f after 'use axe' in room f.
    i->setExits(NULL, d);
    // room j is final room : NO Exit. 'Use' keyword associated with 'woods'-> change currentRoom = j;
    k->setExits(NULL,c);
    roomList[0] = k;
    roomList[1] = b;
    roomList[2] = c;
    roomList[3] = d;
    roomList[4] = e;
    roomList[5] = f;
    roomList[6] = g;
    roomList[7] = h;
    roomList[8] = i;
    roomList[9] = a;
    roomList[10] = j;

    currentRoom = k;
}

/**
 *  Main play routine.  Loops until end of play.
 */
void MainWindow::play() {
    // Enter the main command loop.  Here we repeatedly read commands and
    // execute them until the ZorkUL game is over.
    // You need not the while loop because the QApplication.exec() is an event loop
    // Add while(){} will contribute to the GUI Thread blocked.
    // Create pointer to command and give it a command.
    Command* command = parser.getCommand();
    // Pass dereferenced command and check for end of game.
    bool finished = processCommand(*command);
    if( finished )
    {
        gameArea_TB->append("");
        gameArea_TB->append("--********** End ***********--");
        tracer->setStatue(true);
    }

    // Free the memory allocated by "parser.getCommand()"
    //   with ("return new Command(...)")
    delete command;
}

void MainWindow::printWelcome() {
    gameArea_TB->append("info for help");
    gameArea_TB->append("");
    gameArea_TB->append(QString::fromStdString(currentRoom->longDescription() ));
}

#if  1
/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the ZorkUL game, true is returned, otherwise false is
 * returned.
 */
bool MainWindow::processCommand(Command command) {
    if (command.isUnknown()) {
        gameArea_TB->append("invalid input");
        return false;
    }

    string commandWord = command.getCommandWord();
    if (commandWord.compare("info") == 0)
        printHelp();

    else if (commandWord.compare("map") == 0)
        {
            gameArea_TB->append("          [h] --- [f] --- [g]");
            gameArea_TB->append("                    |         " );
            gameArea_TB->append("                    |         ");
            gameArea_TB->append("[k] --- [c] --- [a] --- [b] --- [j]" );
            gameArea_TB->append("                    |         " );
            gameArea_TB->append("                    |         " );
            gameArea_TB->append("          [i] --- [d] --- [e]" );
        }

    else if (commandWord.compare("go") == 0)
        goRoom(command);

//TAKE command
    else if (commandWord.compare("take") == 0)
    {
        if (!command.hasSecondWord()) {
            gameArea_TB->append("incomplete input");
        }
        else if (command.hasSecondWord()) {
            gameArea_TB->append("you're trying to take " + QString::fromStdString(command.getSecondWord()));
            Item *isItemInRoom = currentRoom->isItemInRoom(command.getSecondWord());
            if ( isItemInRoom == NULL    && (player->get_gotGun()
                                          || player->get_gotAxe()
                                          || player->get_gotBoat()
                                          || player->get_gotAircraft() ))
                gameArea_TB->append("Actually, you had gotten it..." );
            else if ( isItemInRoom == NULL )
                gameArea_TB->append("item is not at here...\nWhat are you really want to take??" );
            else{
                cld_MovesNUM++;
                player->addItem(isItemInRoom);
                if(command.getSecondWord().compare("boat") == 0){
                    player->set_gotBoat(true);
                }
                else if(command.getSecondWord().compare("axe") == 0){
                    player->set_gotAxe(true);
                }
                else if(command.getSecondWord().compare("gun") == 0){
                    player->set_gotGun(true);
                    roomList[7]->changeDescription("Nothing else in this graveyard.\nJust a kind of sorrow...");
                }
                else if(command.getSecondWord().compare("aircraft") == 0){
                    player->set_gotAircraft(true);;
                }
                gameArea_TB->append(QString::fromStdString(isItemInRoom->getShortDescription()+": "+isItemInRoom->getLongDescription()));
                gameArea_TB->append("\nYou take it now.");
                gameArea_TB->append("");
            }
        }
    }

#if 1
    else if (commandWord.compare("use") == 0)
    {
        if (!command.hasSecondWord()) {
            gameArea_TB->append("incomplete input");
        }
        else if (command.hasSecondWord()) {
            bool gotcha = player->isHasItemNow(command.getSecondWord());
            if ( !gotcha )
                gameArea_TB->append("you have not gotten this item...\n");
            else{
                cld_MovesNUM++;
                gameArea_TB->append("");
                if(command.getSecondWord().compare("boat") == 0
                      && currentRoom == roomList[6] //g
                      && player->get_gotBoat()){
                // use boat to room e
                    gameArea_TB->append("The river take you far away...\nLong time later, You came here:");
                    currentRoom = roomList[4];
                    gameArea_TB->append(QString::fromStdString(currentRoom->longDescription()));
                    roomList[4]->changeDescription("Downstream\nHere, it has spare forest.\n");
                }
                else if(command.getSecondWord().compare("axe") == 0
                      && currentRoom == roomList[3] // d
                      && player->get_gotAxe()){
                // change map setExits(d<->a)
                    roomList[3]->setExits(roomList[9],NULL, NULL, roomList[8]);
                    roomList[9]->setExits(roomList[5],roomList[1],roomList[3],roomList[2]);
                    roomList[3]->changeDescription("Big Forest\nWest direction leading a big wooden house.\nAnd, you know - Cann't go east...\n");
                    roomList[9]->changeDescription("Plain/Flatland\nYou can go any direction - all of safe");
                    gameArea_TB->append("You cut down the northest forest!\nYou can go through this land");
                    player->set_hadUsedAxeIn_roomD(true);
                }
                else if(command.getSecondWord().compare("axe") == 0
                      && currentRoom == roomList[5] // f
                      && player->get_gotAxe()){
                    // change map setExits(h<->f)
                    roomList[5]->setExits(NULL, roomList[6], roomList[9], roomList[7]);
                    roomList[7]->setExits(NULL, roomList[5]);
                    roomList[5]->changeDescription("Canyon\nIn the east of canyon has a rope\nIn west, graveyard..\n");
                    gameArea_TB->append("\n------------------------------------\nYou open the old graveyard gate (west) -_-...\n------------------------------------\n\n");
                    player->set_hadUsedAxeIn_roomF(true);
                }
                else if(command.getSecondWord().compare("aircraft") == 0
                      && currentRoom == roomList[1] //g
                      && player->get_gotAircraft()){
                    // use aircraft to room j roomList[11]
                    currentRoom = roomList[10];
                    gameArea_TB->append(QString::fromStdString(currentRoom->longDescription()));
                    ui->btn_e->setEnabled(false);
                    ui->btn_n->setEnabled(false);
                    ui->btn_s->setEnabled(false);
                    ui->btn_w->setEnabled(false);
                    ui->actionRestart_Game->setEnabled(false);
                    ui->lineEdit_typeIn->setEnabled(false);
                }
                else if(command.getSecondWord().compare("gun") == 0
                      && currentRoom == roomList[3] //d
                      && player->get_gotGun()){
                    // use gun to change the player->set_hadUsedGun(true): room i roomList[8] could enter.
                    player->set_hadUsedGun(true);
                    gameArea_TB->append("good job!\nYou kill all the savages in this room!!\n +*+_+'Bong Bang! Yeah\n");
                    roomList[8]->changeDescription("Here is the Arenal of Goth, nothing is useful to excluding a very litte aircraft which could only take you to fly a distance like the width of river.");
                }
                else{
                    gameArea_TB->append("You cannot use the gay at here....\nIt is a sad story..\n");
                }
            }
        }
    }
#endif

    else if (commandWord.compare("quit") == 0) {
        if (command.hasSecondWord())
            gameArea_TB->append("overdefined input");
        else{
            ui->lineEdit_typeIn->setEnabled(false);
            ui->mainGameArea_TB->setEnabled(false);
            ui->btn_e->setEnabled(false);
            ui->btn_w->setEnabled(false);
            ui->btn_s->setEnabled(false);
            ui->btn_n->setEnabled(false);
            ui->actionRestart_Game->setEnabled(false);
            return true; /**signal to quit*/
         }
    }
    return false;
}
/** COMMANDS **/

void MainWindow::goRoom(Command command) {
    if (!command.hasSecondWord()) {
        gameArea_TB->append("incomplete input");
        return;
    }

    string direction = command.getSecondWord();

    // Try to leave current room.
    Room* nextRoom = currentRoom->nextRoom(direction);

//singal direction needn't change
    if(direction.compare("west") == 0 && currentRoom == roomList[6]){
        gameArea_TB->append("You can not climb the cliff just by a rope...\nBut you can down the canyon by that...");
    }
    else if(player->get_hadOff_roomE() && 0 == direction.compare("east") && currentRoom ==  roomList[3]){//d
        gameArea_TB->append("The fucking carpenter do not allow you pass this way...\nHe anger you...");
    }
    else if(direction.compare("west") == 0 && currentRoom ==  roomList[2]){//c
        gameArea_TB->append("The Goth savages are on the montain top, They are looking for you...\nYou'd better run away now...");
    }
    else if(direction.compare("west") == 0 && currentRoom == roomList[4]){
        player->set_hadOff_roomE(true);
        currentRoom = nextRoom;
        gameArea_TB->append( QString::fromStdString(currentRoom->longDescription()) );
        ++cld_MovesNUM;
    }
//double null direction Needn't change
    else if(direction.compare("east") == 0 && currentRoom ==  roomList[1]){//b
        gameArea_TB->append("Nobody can over the river without tools.\n");
    }
//Double null direction-Need change exits WHEN: use 'axe'
    else if( (false == player->get_hadUsedAxeIn_roomF()) && (0 == direction.compare("west")) && currentRoom ==  roomList[5]){//f
        gameArea_TB->append("You can't go to there. That door could be open by some tools...\n");
    }
    else if( (false == player->get_hadUsedAxeIn_roomD()) && (0 == direction.compare("south")) && currentRoom ==  roomList[9]){ //a
        gameArea_TB->append("A piece of forest block you.\n");
    }
    else if( (false == player->get_hadUsedAxeIn_roomD()) && (0 == direction.compare("north")) && currentRoom ==  roomList[3]){//d
        gameArea_TB->append("You should cat down all trees.\n");
    }
//room[8]:i check savages be killed by gun or not
    else if( player->get_hadUsedGun() == false && direction.compare("west") == 0 && currentRoom ==  roomList[3]){//i
        gameArea_TB->append(QString::fromStdString(currentRoom->shortDescription()));
        ui->lineEdit_typeIn->setEnabled(false);
        ui->mainGameArea_TB->setEnabled(false);
        ui->btn_e->setEnabled(false);
        ui->btn_w->setEnabled(false);
        ui->btn_s->setEnabled(false);
        ui->btn_n->setEnabled(false);
    }
    else if (nextRoom == NULL){
        gameArea_TB->append("You cannot go that way");
        //bool b = roomList[3] == currentRoom;
        //QString str = QString::number(b);
        //gameArea_TB->append(str);
        //gameArea_TB->append(QString::fromStdString(direction));
    }
    else {
        currentRoom = nextRoom;
        gameArea_TB->append( QString::fromStdString(currentRoom->longDescription()) );
        ++cld_MovesNUM;
        ui->labelCurrentPlace->setText(QString::fromStdString(currentRoom->getName()));
    }
}

string MainWindow::go(string direction) {
    //Make the direction lowercase
    //transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
    //Move to the next room
    Room* nextRoom = currentRoom->nextRoom(direction);
    if (nextRoom == NULL)
        return("direction null");
    else
    {
        currentRoom = nextRoom;
        return currentRoom->longDescription();
    }
}

#endif

void MainWindow::printHelp() {
    gameArea_TB->append("valid inputs are " );
    parser.showCommands(gameArea_TB);
}


void MainWindow::on_pushButton_clicked()
{
    gameArea_TB->clear();
}

void MainWindow::on_actionQuit_Exit_triggered()
{
    if( Tracer::getStatue() )
        this->close();
    this->close();
}

void MainWindow::on_actionHelp_triggered()
{
    QLabel *lable_1 = new QLabel(tr("<h2><i>Help:</i></h2>"));
    QLabel *lable_2 = new QLabel(tr(" <p>Type 'map' show map, type 'info' show all command.</p>"));
    QLabel *lable_description = new QLabel(tr("<p>You are a tourist.<br/>One night, you fallen into a sleep...<br/>But! The Goth savage spot you and they want to catch you for a meal...</p>"));
    QLabel *lable_D = new QLabel(tr(" <h2><i>Game Description: </i></h2>"));
    QLabel *return_label = new QLabel("");
    QDialog *dialog = new QDialog();
    QVBoxLayout *dialog_layout = new QVBoxLayout();
    dialog_layout->addWidget(lable_1);
    dialog_layout->addWidget(return_label);
    dialog_layout->addWidget(lable_2);
    dialog_layout->addWidget(return_label);
    dialog_layout->addWidget(lable_D);
    dialog_layout->addWidget(lable_description);
    dialog->setLayout(dialog_layout);
    dialog->setWindowTitle(tr("Help."));
    dialog->show();
}

void MainWindow::on_actionRestart_Game_triggered()
{
    cld_MovesNUM = 0;
    cld_ScordsNUM = 0;
    gameArea_TB->clear();
    ui->lcdNumber_moves->display(cld_MovesNUM);
    ui->labelCurrentPlace->setText("capsule");
    ui->mainGameArea_TB->setText("Press 'ENTER' submit your command.");
    ui->mainGameArea_TB->append("The item gotton last turn, still in your bag, you can use them in this turn\n");
    currentRoom = roomList[0];
    printWelcome();
}

void MainWindow::on_actionInfomation_triggered()
{
    QLabel *lable_1 = new QLabel(tr("<h3>Program developed by <i>Zhikang Tian(Bruce)</i></h3>"));
    QLabel *lable_2 = new QLabel(tr("      <h5>Info. Copy Right|2016</h5>"));
    QLabel *return_label = new QLabel("");
    QDialog *dialog = new QDialog();
    QVBoxLayout *dialog_layout = new QVBoxLayout();
    dialog_layout->addWidget(lable_1);
    dialog_layout->addWidget(return_label);
    dialog_layout->addWidget(lable_2);
    dialog->setLayout(dialog_layout);
    dialog->setWindowTitle(tr("Copy right Info."));
    dialog->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    this->close();
}
