#include "Room.h"
#include "Command.h"


Room::Room(string name , string description) {
    this->description = description;
    this->name = name;
}

Room::Room() {}

void Room::setExits(Room *north , Room *east , Room *south , Room *west ) {
	if (north != NULL)
		exits["north"] = north;
	if (east != NULL)
		exits["east"] = east;
	if (south != NULL)
		exits["south"] = south;
	if (west != NULL)
		exits["west"] = west;
}

void Room::changeDescription(QString newDes){
    this->description =  newDes.toStdString();
}

string Room::longDescription() {
    return "room = " + description + ".\n\n" + displayItem() + "\n" + exitString();
}

string Room::exitString() {
    string returnString = "\nYou can go: ";
	for (map<string, Room*>::iterator i = exits.begin(); i != exits.end(); i++)
		// Loop through map
		returnString += "  " + i->first;	// access the "first" element of the pair (direction as a string)
	return returnString;
}

Room* Room::nextRoom(string direction) {
    map<string, Room*>::iterator next = exits.find(direction); //returns an iterator for the "pair"
	if (next == exits.end())
		return NULL; // if exits.end() was returned, there's no room in that direction.
	return next->second; // If there is a room, remove the "second" (Room*)
				// part of the "pair" (<string, Room*>) and return it.
}

void Room::addItem(Item *inItem) {
    //cout <<endl;
    //cout << "Just added" + inItem->getLongDescription();
    itemsInRoom.push_back(*inItem);
}

string Room::displayItem() {
    string tempString = "items in room = ";
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        tempString = "no items in room";
        }
    else if (itemsInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            tempString = tempString + itemsInRoom[x].getShortDescription() + "  " ;
            x++;
            }
        }
    return tempString;
    }

int Room::numberOfItems() {
    return itemsInRoom.size();
}


Item* Room::isItemInRoom(string inString)
{
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1)
        return NULL;
    else if (itemsInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
                int tempFlag = inString.compare( itemsInRoom[x].getShortDescription());
                if (tempFlag == 0) {
                    ///In case of danging pointer -- use 'new' keyword
                    Item *temp = new Item(itemsInRoom[x].getShortDescription(),
                                         itemsInRoom[x].getLongDescription(),
                                         itemsInRoom[x].get_MoveAble(),
                                         itemsInRoom[x].get_ChangeMapAble(),
                                         itemsInRoom[x].get_WeaponCheck());

                    itemsInRoom.clear();
                    return temp;
                }
                x++;
            }
    }
    return NULL;
}

#if 0
int Room::isItemInRoom(string inString)
{
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        return false;
        }
    else if (itemsInRoom.size() > 0) {
       int x = (0);
#include<iostream>
        for (int n = sizeItems; n > 0; n--) {
            // compare inString with short description

            int tempFlag = inString.compare( itemsInRoom[x].getShortDescription());
            if (tempFlag == 0) {
                std::cout << itemsInRoom[x].getShortDescription() << std::endl;
                itemsInRoom.clear();
                std::cout << itemsInRoom[x].getShortDescription() << std::endl;
                return x;
            }
            x++;
            }
        }
    return -1;
}
#endif
