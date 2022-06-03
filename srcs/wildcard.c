#include "../include/minishell.h"

// void	asterisks(t_input *data)
// {
// 	DIR				*dir;
// 	t_node			*tmp;
// 	t_node			*node_tmp;
// 	struct dirent	*fname;

// 	dir = opendir(".");
// 	if (!dir)
// 	{
// 		perror("opendir");
// 		exit (EXIT_FAILURE);
// 	}
// 	data->wild = NULL;
// 	fname = NULL;
// 	tmp = data->args;
// 	while (tmp && tmp->type != ASTER)
// 		tmp = tmp->next;
// 	if (!tmp)
// 		return ;
// 	while ((fname = readdir(dir)) != NULL)
// 	{
// 		if (!ft_strncmp(fname->d_name, tmp->prev->value, ft_strlen(tmp->prev->value)))
// 		{
// 			if (!tmp->next->value || ft_strstr(fname->d_name, tmp->next->value))
// 			{
// 				data->tmp = ft_strdup(fname->d_name);
// 				printf("value is %s\n", data->tmp);
// 				node_tmp = ft_token_new(ASTER, data->tmp);
// 				ft_token_back(&data->wild, node_tmp);
// 			}
// 		}
// 	}
// 	closedir(dir);
// 	ft_token_print(data->wild);
// }