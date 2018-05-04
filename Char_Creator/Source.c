#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int is_input_int(char data[20])
{
	//function to check if an input is an integer
	for (int i = 0; data[i] != '\0'; i++)
	{
		if (data[i] >= '0' && data[i] <= '9')
		{
			return 0;
		}
	}
	printf("Don't be a retard, put a number in\nNow... ");
	return 1;
}
int string_to_int(char data[20])
{
	//function which turns a c-string of ascii into integers, specifically  from 0-9
	int number = 0;
	for (int i = 0; data[i] != '\0'; i++)
	{
		number += (data[i] - '0');
		number *= 10;
	}
	return number / 10;
}
int dice_roller(int die_type)
{
	//variable dice roller
	return ((rand() % (die_type)) + 1); 
}
int ab_mod(int ability_score)
{
	//calculates an ability modifier
	return ((ability_score - 10 )/2);
}
enum Ras
{
	//list of races
	_HUMAN, 
	_ELF,
	_DWARF,
	_TIEFLING,
	_ORC
};
enum Ability_Score_id
{
	//list of ability scores
	STRENGTH,
	DEXTERITY,
	CONSTITUTION,
	INTELLIGENCE,
	WISDOM,
	CHARISMA,
};
enum KLASS
{
	//list of classes
	_BARBARIAN,
	_BARD,
	_MONK,
	_PALADIN,
	_WARLOCK
};
struct Race
{
	//structure of what details a race has
	int r_id;
	int r_mod[6];
	char r_name[15];
};
struct Klass
{
	//structure of what details a class has
	int k_id;
	int k_hit_die[2];
	char k_name[15];
};
struct Race get_race(int id)
{
	//compiles race type with stat bonuses and written name
	struct Race races[5] = {

		{ _HUMAN,{ 1, 1, 1, 1, 1, 1 }, "Human" },
		{ _ELF,{ 0, 2, 0, 0, 0, 0 }, "Elf" },
		{ _DWARF,{ 0, 0, 2, 0, 0, 0 }, "Dwarf" },
		{ _TIEFLING,{ 0, 0, 0, 1, 0, 2 }, "Tiefling" },
		{ _ORC,{ 2, 0, 1, 0, 0, 0 }, "Human" },
	};
	return races[id];
};
struct Klass get_klass(int id)
{
	//compiles class type with stat bonuses and written name
	struct Klass klasses[5] = {

		{ _BARBARIAN,{ 1, 12 }, "Barbarian" },
		{ _BARD,{ 1, 8 }, "Bard" },
		{ _MONK,{ 1, 8 }, "Monk" },
		{ _PALADIN,{ 1, 10	 }, "Barbarian" },
		{ _WARLOCK,{ 1, 8 }, "Barbarian" },
	};
	return klasses[id];
}
struct Stats
{	
	//structure for the various character statistics
	int id;
	int strength;
	int dexterity;
	int constitution;
	int intelligence;
	int wisdom;
	int charisma;
	int hp;
	int race;
	int klass;
};
struct Stats stat_roller(int id)
{
	//dice roller for the ability scores
	struct Stats temp;
	temp.id = id;
	temp.strength = (rand() % 12) + 6;
	temp.dexterity = (rand() % 12) + 6;
	temp.constitution = (rand() % 12) + 6;
	temp.intelligence = (rand() % 12) + 6;
	temp.wisdom = (rand() % 12) + 6;
	temp.charisma = (rand() % 12) + 6;

	return temp;
}
void stat_block(struct Stats entity)
{
	//prints the rolled stats
	printf("Constitution : %6d \nDexterity  : %8d \nStrength  : %9d\nIntelligence  : %5d\nWisdom  : %11d\nCharisma  : %9d\n", entity.constitution, entity.dexterity, entity.strength, entity.intelligence, entity.wisdom, entity.charisma);
}
int main(void)
{
	srand((unsigned int)time(0));

	int vald_ras;
	int input;
	int hp;
	do
	{
		printf("What race do you want to play as? \n1. Human\n2. Elf\n3. Dwarf\n4. Tiefling\n5. Orc\n> ");
		scanf("%d", &input);
	} 
	while (input < 1 || input > 5);
	vald_ras = input;

	do
	{
	printf("What class´do you want to play as? \n1. Barbarian\n2. Bard\n3. Monk\n4. Paladin\n5. Warlock\n> ");
	scanf("%d", &input);
	} 
	while (input < 1 || input > 5);

	struct Klass chosen_class = get_klass(input - 1);
	struct Stats character;
	character = stat_roller(1);
	character.klass = input - 1;

	printf("\n\nRolled Stats\n\n");
	stat_block(character);
	printf("\nStats after race bonus\n\n");
	
	struct Race chosen_race = get_race(vald_ras - 1);
	character.race = vald_ras;
	character.strength = character.strength + chosen_race.r_mod[STRENGTH];
	character.dexterity = character.dexterity + chosen_race.r_mod[DEXTERITY];
	character.constitution = character.constitution + chosen_race.r_mod[CONSTITUTION];
	character.intelligence = character.intelligence + chosen_race.r_mod[INTELLIGENCE];
	character.wisdom = character.wisdom + chosen_race.r_mod[WISDOM];
	character.charisma = character.charisma + chosen_race.r_mod[CHARISMA];
		
	stat_block(character);

	//calculates hp after chosen race and constitution modifier
	hp = (dice_roller(chosen_class.k_hit_die[1]) + ab_mod(character.constitution));
	printf("Your HP, after rolling, is: %d", hp);

	return 0;	
}