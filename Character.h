#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <vector>
using std::vector;
#include "item.h"

class Character {
private:
     //string description;
     vector < Item > itemsInCharacter;
     bool hadUsedGun;   // change room i description
     bool hadUsedAxeIn_roomF; // change room f & h des and h/f->setExits();
     bool hadUsedAxeIn_roomD; // change room d & a des and d/a->setExits();
     bool hadOff_roomE; // change the room d description after frist came room e
// all gotXXX Attributes used in else if( command == 'use') processCommand() funciton
     bool gotBoat;      // send warning when at room f for sure to 'go east'
     bool gotAxe;
     bool gotGun;
     bool gotAircraft;


public:
    void addItem(Item &inItem);
    void addItem(Item *inItem);
    Character(/*string description*/);
    inline ~Character(){delete this;}
    bool isHasItemNow(string itemName);
    inline vector < Item > getItemList_inCharacter(){return itemsInCharacter;}
    inline bool get_hadUsedGun(){return hadUsedGun;}
    inline bool get_hadUsedAxeIn_roomF(){return hadUsedAxeIn_roomF;}
    inline bool get_hadUsedAxeIn_roomD(){return hadUsedAxeIn_roomD;}
    inline bool get_hadOff_roomE(){return hadOff_roomE;}
    inline bool get_gotBoat(){return gotBoat;}
    inline bool get_gotAxe(){return gotAxe;}
    inline bool get_gotGun(){return gotGun;}
    inline bool get_gotAircraft(){return gotAircraft;}
    inline void set_gotAircraft(bool in_gotAircraft){gotAircraft = in_gotAircraft;}
    inline void set_gotBoat(bool in_gotBoat){gotBoat = in_gotBoat;}
    inline void set_gotGun(bool in_gotGun){gotGun= in_gotGun;}
    inline void set_gotAxe(bool in_gotAxe){gotAxe= in_gotAxe;}
    inline void set_hadUsedAxeIn_roomF(bool in_hadUsedAxeIn_roomF){hadUsedAxeIn_roomF = in_hadUsedAxeIn_roomF;}
    inline void set_hadUsedAxeIn_roomD(bool in_hadUsedAxeIn_roomD){hadUsedAxeIn_roomD = in_hadUsedAxeIn_roomD;}
    inline void set_hadUsedGun(bool in_hadUsedGun){hadUsedGun = in_hadUsedGun;}
    inline void set_hadOff_roomE(bool in_hadOff_roomE){hadOff_roomE = in_hadOff_roomE;}

    //string shortDescription();
    //string longDescription();

};

#endif /*CHARACTER_H_*/
