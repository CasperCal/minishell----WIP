#include "minishell.h"

void	asterisks(t_input *data)
{
	DIR				*dir;
	t_node			*wild;
	t_node			*tmp;
	char			*value;
	struct dirent	*fname;
	int				i;
	int				len;

	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		exit (EXIT_FAILURE);
	}
	wild = NULL;
	tmp = data->args;
	i = 0;
	while (data->args->type != ASTER)
		++i;
	len = ft_strlen(data->args->value[i]) - 1;
	while (fname = readdir(dir))
	{
		if (ft_strnstr(fname->d_name, data->args->value[i], len))
		{
			value = ft_strdup
		}
	}
}