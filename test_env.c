#include "minishell.h"
#include "stdio.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;

	char	*key_pair = create_keypair("NAME", "hakbas");
	printf("keypair: %s\n", key_pair);
	printf("name: %s\n", get_name_only(key_pair));
	printf("value: %s\n", get_value_only(key_pair));


}
