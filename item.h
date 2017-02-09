#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
using namespace std;


class Item {
private:
    string description;
	string longDescription;
    bool moveAble;
    bool changeMapAble;
	bool weaponCheck;
   /** Qt has not copy constructor: Item (Item const &inItem);*/

public:

    Item (string itemName, string description, bool canItChageRoom, bool canItChangeMapStructure, bool canItKillSB);
    Item (): description(""), longDescription(""),moveAble(false), changeMapAble(false), weaponCheck(false) {}
    inline string getShortDescription(){return description;}
    inline string getLongDescription(){return  description + ":\t" + longDescription +"\n";}

    inline bool get_WeaponCheck(){return weaponCheck;}
    inline void set_WeaponCheck(bool inWeaponCheck){weaponCheck = inWeaponCheck;}
    inline bool get_MoveAble(){return moveAble;}
    inline void set_MoveAble(bool inMoveAble){moveAble = inMoveAble;}
    inline bool get_ChangeMapAble(){return changeMapAble;}
    inline void set_ChangeMapAble(bool inChangeMapAble){changeMapAble = inChangeMapAble;}
};

#endif /*ITEM_H_*/
