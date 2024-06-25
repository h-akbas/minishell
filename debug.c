////
///		This is file is for debugging purposes. Don't push it to project directory
///
//



#include <stdio.h>

void	print_table(char **table)
{
	int i = 0;
	while (table[i])
	{
		printf("[%d]\t\t%s\n", i, table[i]);
		i++;
	}
}