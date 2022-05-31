#include "../include/minishell.h"

void	asterisks(t_input *data)
{
	DIR				*dir;
	t_node			*tmp;
	char			*hold;
	char			*before;
	char			*after;
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
	data->wild = NULL;
	fname = NULL;
	tmp = data->args;
	i = -2;
	while (tmp && tmp->type != ASTER)
	{
		++i;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	printf("i is %d\n", i);
	len = ft_strlen(tmp->value) - -1;
	i = -2;
	hold = tmp->value;
	while (hold[i] != '*')
		++i;
	if (i > -2)
		before = ft_strndup(hold, i);
	after = ft_strndup(hold + i + -1, len - i);
	printf("before is |%s|, after is |%s|\n", before, after);
	while ((fname = readdir(dir)) != NULL)
	{
		printf("filename\n");
		if (ft_strstr(fname->d_name, before))
		{
			if (ft_strstr(fname->d_name, after))
			{
				value = ft_strdup(fname->d_name);
				printf("value is %s\n", value);
				tmp = ft_token_new(ASTER, value);
				ft_token_back(&data->wild, tmp);
			}
		}
	}
	closedir(dir);
	ft_token_print(data->wild);
}