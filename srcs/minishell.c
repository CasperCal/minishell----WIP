#include "../include/minishell.h"

int		check_field(char **buf)
{
	int		i;
	int		quote;
	int		quote_d;
	char	*tmp;

	i = 0;
	quote = 0;
	quote_d = 0;
	tmp = *buf;
	while (tmp[i])
	{
		if (tmp[i] == '\'')
			++quote;
		else if (tmp[i] == '\"')
			++quote_d;
		++i;
	}
	if (quote && quote % 2 != 0)
	{
		while (1)
		{
			tmp = readline("quote>");
			*buf = ft_charjoin_free(*buf, '\n');
			*buf = ft_strjoin_free(*buf, tmp);
			if (ft_strchr(tmp, '\''))
			{
				free(tmp);
				break;
			}
			free(tmp);
		}
	}
	else if (quote_d &&quote_d % 2 != 0)
	{
		while (1)
		{
			tmp = readline("dquote>");
			*buf = ft_charjoin_free(*buf, '\n');
			*buf = ft_strjoin_free(*buf, tmp);
			if (ft_strchr(tmp, '\"'))
			{
				free(tmp);
				break;
			}
			free(tmp);
		}
	}
	return (0);
}

void	create_envp(t_input *data, char *envp[])
{
	int		i;
	int		start;
	int		end;
	char	*type;
	char	*value;
	t_env	*tmp;

	i = 0;
	while (envp[i])
	{
		start = 0;
		end = 0;
		while (envp[i][start] != '=')
			++start;
		while (envp[i][end])
			++end;
		type = ft_strndup(envp[i], start);
		value = ft_strndup(envp[i] + start + 1, end - start - 1);
		tmp = ft_envp_new(type, value);
		ft_envp_back(&data->envp_n, tmp);
		++i;
	}
}

void	create_token(t_input *data)
{
	t_node	*tmp;
	char	*value;
	size_t	i;
	size_t	start;
	int		type;

	i = 0;
	start = 0;
	while (data->buf[i])
	{
		while (check_charset(data->buf[i], " \f\n\r\t\v\\;"))
			++i;
		start = i;
		while (data->buf[i] && !check_charset(data->buf[i], "\"$\'&<>=*| \f\n\r\t\v\\;()"))
			++i;
		type = WORD;
		value = ft_strndup(data->buf + start, i - start);
		tmp = ft_token_new(type, value);
		ft_token_back(&data->args, tmp);
		if (check_charset(data->buf[i], "\"$\'&<>=*|()"))
		{
			type = check_charset(data->buf[i], "\"$\'&<>=*|()");
			value = ft_strndup(data->buf + i, 1);
			tmp = ft_token_new(type, value);
			ft_token_back(&data->args, tmp);
			if (data->buf[i + 1] && data->buf[i + 1] != type)
				++i;
		}
	}
}

struct builtin builtins[] =
{
	{"pwd", &yo_pwd},
	{"cd", &yo_cd},
	{"echo", &yo_echo},
	{"export", &yo_export},
	{"env", &yo_env},
	{"unset", &yo_unset},
	{"exit", &yo_exit}
};

void	data_init(t_input *data, char *envp[])
{
	data->envp = envp;
	data->status = 0;
	data->envp_n = NULL;
	data->args = NULL;
	create_envp(data, envp);
	// ft_envp_print(data->envp_n);
	// data->envp_n = ft_free_envp(data->envp_n);
	data->argv = ft_split_space(data->buf, " \f\n\r\t\v\\;");
	create_token(data);
	data->argc = ft_token_size(data->args);
	data->builtins = builtins;
	// while (data->argv[data->argc])
	// {
	// 	// printf("argv[%d] is |%s|\n", data->argc, data->argv[data->argc]);
	// 	++data->argc;
	// }
	printf("argc is %d\n", data->argc);
	ft_token_print(data->args);
	// data->args = ft_free_token(data->args);
	// ft_free(data->argv);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_input data;
	// int		exit_status;

	// exit_status = 0;
	if (argc != 1)
		exit(EXIT_FAILURE);
	(void) argv;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	while (1)
	{
		data.buf = readline("yo> ");
		if (data.buf)
			add_history(data.buf);
		check_field(&data.buf);
		// printf("buf is %s\n", data.buf);
		data_init(&data, envp);
		// asterisks(&data);
		execute(&data);
	}
	return ((data.status >> 8) & 0xff);
}
