#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

void	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
}

char	*replace_var(char *s, char *var, char *value, int *k)
{
	int		len;
	char	*str;
	int		i;

	i = *k;
	len = ft_strlen(s) + ft_strlen(value) - ft_strlen(var) + 1;
	printf("%i\n",len);
	str = (char *)malloc(sizeof(char) * (len));
	ft_strncpy(str, s, *k);
	printf("%s\n",str);
	ft_strncpy(str + *k, value, ft_strlen(value));
	printf("%s\n",str);
	*k = *k + ft_strlen(value);
	ft_strncpy(str + *k, s + i + ft_strlen(var), len - *k);
	printf("final %s\n",str);
	return (str);
}

int main()
{
	char	*str;
	int		i = 6;
	str = replace_var("hello its me", "its", "looooooooooooool", &i);
	printf("%i\n", i);
	printf("%s\n", str);
}
