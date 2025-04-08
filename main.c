#include "includes/minishell.h"

t_list *g_gbc;

int	is_delimiter(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	hundel_spe_char(char *s, char **str, int *i, int *c)
{
	int	j;

	j = 1;
	if ((s[*i] == '<' && s[*i + 1] == '<') || (s[*i] == '>' && s[*i + 1] == '>'))
		j++;
	str[*c] = (char *)ft_malloc(sizeof(char) * (j + 1));
	if (!str[*c])
		allocation_fails();
	ft_memcpy(str[*c], s + *i, j);
	str[*c][j] = '\0';
	*i = *i + j;
	c++;
}

void	skip_quotes(char *s, int *i, char c)
{
	int	j;

	j = *i + 1;
	while (s[j])
	{
		if (s[j] == c)
			break;
		j++;
	}
	if (s[j] != '\0')
		*i = j;
	else if (s[j] == '\0')
		*i = j - 1;
}

void	add_word(char *s, char **str, int *i, int *c)
{
	int	j;

	j = *i;
	while (s[j])
	{
		if (s[j] == '"' || s[j] == '\'')
			skip_quotes(s, &j, s[j]);
		if (!is_delimiter(s[j]) && !is_special_char(s[j]))
			j++;
		else
			break ;
	}
	str[*c] = (char *)ft_malloc(sizeof(char) * (j - *i + 1));
	if (!str[*c])
		allocation_fails();
	ft_memcpy(str[*c], s + *i, sizeof(char) * (j - *i));
	str[*c][j - *i] = '\0';
	*i = j;
	c++;
}

void	fill_split(char **str, char *s)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'' || (!is_delimiter(s[i]) && !is_special_char(s[i])))
		{
			add_word(s, str, &i, &c);
			c++;
		}
		else if(is_special_char(s[i]))
			hundel_spe_char(s, str, &i, &c);
		else if(is_delimiter(s[i]))
			i++;
	}
}

int	word_counter(char *s)
{
	int	c;
	int	i;
	int	f;

	c = 0;
	i = 0;
	f = 0;
	while (s[i])
	{
		if ((s[i] == '"' || s[i] == '\''))
			skip_quotes(s, &i, s[i]);
		else if(is_special_char(s[i]))
		{
			if ((s[i] == '<' && s[i + 1] == '<') || (s[i] == '>' && s[i + 1] == '>'))
				i++;
			c++;
			f = 0;
		}
		else if(!is_delimiter(s[i] && !is_special_char(s[i]) && f == 0))
		{
			c++;
			f = 1;	
		}
		else if(is_delimiter(s[i]))
			f = 0;
		i++;
	}
	return (c);
}

char	**split_words(char *s)
{
	char	**str;
	
	if (!s)
		return (NULL);
	str = (char **)ft_malloc(sizeof(char *) * (word_counter(s) + 1));
	if (!str)
		allocation_fails();
	fill_split(str, s);
	return (str);
}

int main(int ac, char **av)
{
	printf("%i\n",word_counter(av[1]));
}