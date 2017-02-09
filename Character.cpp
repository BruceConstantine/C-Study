#include "Character.h"
#if 0
Character::Character(string description) {
	this->description = description;
}
#endif // if 0 Constructor

Character::Character():
    hadUsedGun(false),
    hadUsedAxeIn_roomF(false),
    hadUsedAxeIn_roomD(false),
    hadOff_roomE(false),
    gotBoat(false),
    gotGun(false),
    gotAxe(false),
    gotAircraft(false){

}

bool Character::isHasItemNow(string itemName){
    for(vector<Item>::iterator ite = itemsInCharacter.begin();
        ite != itemsInCharacter.end();
        ++ite){
        if( ite->getShortDescription().compare(itemName) == 0){
            return true;
        }
    }
    return false;
}

void Character::addItem(Item &inItem) {
    itemsInCharacter.push_back(inItem);
}
void Character::addItem(Item *inItem) {
    itemsInCharacter.push_back(*inItem);
    //delete item;
}
#if 0
string Character::longDescription()
{
  string ret = this->description;
  ret += "\n Item list:\n";
  for (vector<Item>::iterator i = itemsInCharacter.begin(); i != itemsInCharacter.end(); i++)
    ret += "\t"+ (*i).getLongDescription() + "\n";
  return ret;
}

#endif // if 0 Character::longDescription()
