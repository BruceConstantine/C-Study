#ifndef ROOM_H_
#define ROOM_H_
#include <QString>
#include <map>
#include <string>
#include <vector>
using namespace std;
using std::vector;

#include "item.h"

class Room {

private:
    string name;
	string description;
	map<string, Room*> exits;
	string exitString();
    vector <Item> itemsInRoom;


public:
    int numberOfItems();
    Room();
    Room(string name,string description);
    void setExits(Room *north = NULL, Room *east = NULL, Room *south = NULL, Room *west = NULL);
    void changeDescription(QString newDes);
    inline string shortDescription() {return description;}
    inline string getName(){return name;}
    string longDescription();
	Room* nextRoom(string direction);
    void addItem(Item *inItem);
    string displayItem();
    Item *isItemInRoom(string inString);
    void removeItemFromRoom(int location);
};

#endif
