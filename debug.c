////
///		This is file is for debugging purposes. Don't push it to project directory
///
//
//// deneme 


#include "libft/libft.h"
#include <stdio.h>

void	print_table(char **table)
{
	int i = 0;
	while (table[i])
	{
		printf("[%d]\t%s\n", i, table[i]);
		i++;
	}
}

void	print_list(t_list *list)
{
	while(list->content)
	{
		printf("%s\n", (char *)list->content);
		list = list->next;
	}
}
