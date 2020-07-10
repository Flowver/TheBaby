#pragma once
class AttributeComponent
{
public:
	//Leveling
	int level;
	int exp;
	int expNext;
	int attributePoints;

	//Attributes
	int vitality;
	int strength;
	int dexterity;
	int agility;
	int intelligence;

	//Stats
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int defence;
	int luck;
	float sprint;
	float sprintMax;
	float sprintTime;

	//Con / Des
	AttributeComponent(int level);
	virtual ~AttributeComponent();

	//Functions
	std::string debugPrint() const;

	void loseHP(const int hp);
	void gainHP(const int hp);
	void loseEXP(const int exp);
	void gainExp(const int exp);
	void loseSprint(const float sprint);
	void gainSprint(const float sprint);

	const bool isDead() const;

	void updateStats(const bool reset);
	void updateLevel();

	void update();
};

