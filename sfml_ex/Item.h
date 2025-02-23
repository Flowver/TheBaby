#ifndef ITEM_H
#define ITEM_H

enum ItemTypes { IT_DEFAULT = 0, IT_RANGEDWEAPON, IT_MELEEWEAPON };
enum ItemRarities { COMMON = 0, UNCOMMON, RARE, EPIC, LEGENDARY, MYTHIC };

class Item
{
private:
	void initVariables();

protected:
	//Variables
	short unsigned type;
	unsigned level;
	unsigned value;

public:
	Item(unsigned level, unsigned value);
	virtual ~Item();

	//Function
	virtual Item* clone() = 0;
};

#endif //Item.h