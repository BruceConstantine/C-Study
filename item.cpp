#include "item.h"
#include "redefinenewkeyword.h"
/*
Item::Item( Item const & inItem)
{
    description = * new string("");
    description = inItem.getShortDescription();
    longDescription = inItem.getLongDescription();
    moveAble = inItem.get_MoveAble();
    changeMapAble = inItem.get_ChangeMapAble();
    weaponCheck = inItem.get_WeaponCheck();
}
*/

Item::Item(string inShortDescription,
            string inLongDescription,
            bool inMoveAble,
            bool inChangeMapAble,
            bool inWeaponCheck
            )
{
    description = inShortDescription;
    longDescription = inLongDescription;
    moveAble = inMoveAble;
    changeMapAble = inChangeMapAble;
    weaponCheck = inWeaponCheck;
}



#if 0 // previous code -> useless codes
void Item::setWeight(int inWeightGrams)
{
    if (inWeightGrams > 9999 || inWeightGrams < 0)
       cout << "weight invalid, must be 0<weight<9999" ;
    else
	   weightGrams = inWeightGrams;
}

void Item::setValue(float inValue)
{
    if (inValue > 9999 || inValue < 0)
       cout << "value invalid, must be 0<value<9999" ;
    else
	   value = inValue;
}

void Item::setWeaponCheck(int isWeapon)
{
    if(isWeapon > 0 || isWeapon < 0)
        cout << "Item not a weapon" ;
    else
        cout << "Item is a weapon" ;
}
#endif
