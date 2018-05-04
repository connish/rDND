#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int is_input_int(char data[20]);
int string_to_int(char data[20]);
void dice_roller(int die_amount, int die_type)
{

	for (int i = 1; i <= die_amount; i++)
	{
		int die = (rand() % (die_type)) + 1;
		printf("%d\n", die);
	}
}
int main(void)
{
	srand(time(0));

	int die_type;
	int num_die;
	char input[20];

	printf("Dice Roller Extreme Deluxe 2000\n\n\n\n");

	char roll[2];
	roll[0] = 'y';
	roll[1] = '\0';

	while (roll[0] == 'y' || roll[0] == 'Y')
	{
		do
		{
			printf("What type of die would you like to roll? \n> d");
			scanf("%19s", input);
		} while (is_input_int(input) == 1);
		die_type = string_to_int(input);

		do
		{
			printf("How many d%d would you like to roll? \n> ", die_type);
			scanf("%19s", input);
		} while (is_input_int(input) == 1);
		num_die = string_to_int(input);

		dice_roller(num_die, die_type);

		printf("Would you like to roll more dice? y/n \n>");
		scanf("%s", &roll);
		while (roll[0] != 'y' && roll[0] != 'n')
		{
			printf("Thats not y/n, please try again.\n>");
			scanf("%s", &roll);
		}
	}
	return 0;
}
int is_input_int(char data[20])
{
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
	int number = 0;
	for (int i = 0; data[i] != '\0'; i++)
	{
		number += (data[i] - '0');
		number *= 10;
	}
	return number / 10;
}