#include "pas.h"

size_t		ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void		ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void		ft_putstr_fd(const char *s, int fd)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (i < ft_strlen(s))
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
}

void		ft_bzero(void *str, size_t n)
{
	unsigned char	*n_str;
	size_t			i;

	i = 0;
	n_str = (unsigned char *)str;
	while (i < n)
	{
		n_str[i] = '\0';
		i++;
	}
}

void		*ft_memalloc(size_t size)
{
	void	*str;

	str = (char *)malloc(sizeof(char) * size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, size);
	return (str);
}

int			ft_err_skobki(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] <= 0x20 || str[i] >= 0x7F)
			return (-1);
		if (str[i] == '{')
			count++;
		if (str[i] == '}' && count - 1 != 0)
			return (-1);
		if (str[i] == '}' && count - 1 == 0)
			count = 0;
		i++;
	}
	return (0);
}

int			ft_err_val(char *str)
{
	int i;
	int	size;
	int	count;

	i = 0;
	count = 0;
	size = ft_strlen(str);
	while (i < size)
	{
		if (str[i] != '{')
			return (-1);
		i = i + 6;
	}
	i = 4;
	while (i < size)
	{   
		if (str[i] != '}')
			return (-1);
		i = i + 6;
	}
	for (i = 1; i < size; i = i + 6)
	{
		if (str[i + 2])
		{
			if (str[i + 2] - str[i] < 0)
				return (-1);
			switch(str[i + 2])
			{
				case 0x30 ... 0x39:
					if (str[i] < 0x30 || str[i] > 0x39)
						return(-1);
					break;
				case 0x21 ... 0x2f:
					if (str[i] < 0x21 || str[i] > 0x2f)
						return (-1);
					break;
				case 0x3a ... 0x40:
					if (str[i] < 0x3a || str[i] > 0x40)
						return (-1);
					break;
				case 0x5b ... 0x60:
					if (str[i] < 0x5b || str[i] > 0x60)
						return (-1);
					break;
				case 0x7b ... 0x7e:
					if (str[i] < 0x7b || str[i] > 0x7e)
						return (-1);
					break;
				case 0x61 ... 0x7a:
					if (str[i] < 0x61 || str[i] > 0x7a)
						return (-1);
					break;
				case 0x41 ... 0x5a:
					if (str[i] < 0x41 || str[i] > 0x5a)
						return (-1);
					break;
			}
		}
	}
	i = 2;
	while (i < size)
	{
		if (str[i] != '-')
			return (-1);
		i = i + 6;
	}
	i = 5;
	while (i < size)
	{
		if (str[i] != '+')
			return (-1);
		count++;
		i = i + 6;
	}
	return (count + 1);
}

int			ft_errors(char *str)
{
	int	count;
	
	if (ft_err_skobki(str) < 0)
		return (-1);
	count = ft_err_val(str);
	if (count < 0)
		return (-1);
	return (count);
}

long double	entropy(char *str, int len, int letter_count)
{
	long double	sum;
	long double	res;
	long double entropy;
	int			j;
	int			min;
	int			max;
	int			num;
	int			spec;
	int			i;

	sum = 0;
	j = 1;
	i = 0;
	min = 0;
	max = 0;
	num = 0;
	spec = 0;
	while (j < len)
	{
		if (str[j] >= 0x61 && str[j + 2] <= 0x7a && min != 1)
		{
			sum = sum + 26;
			min++;
		}
		if (str[j] >= 0x41 && str[j + 2] <= 0x5a && max != 1)
		{
			sum = sum + 26;
			max++;
		}
		if (str[j] >= 0x30 && str[j + 2] <= 0x39 && num != 1)
		{
			sum = sum + 10;
			num++;
		}
		if (spec != 1)
		{
			switch(str[j])
			{
				case 0x21 ... 0x2f:
				case 0x3a ... 0x40:
				case 0x5b ... 0x60:
				case 0x7b ... 0x7e:
					i = 1;
			}
			if (i = 1)
			{
				switch(str[j + 2])
				{
					case 0x21 ... 0x2f:
					case 0x3a ... 0x40:
					case 0x5b ... 0x60:
					case 0x7b ... 0x7e:
						sum = sum + 32;
				}
			}
			spec++;
		}
		j = j + 6;
	}
	fprintf(stderr, "sum = %Lf\n", sum);
	res = log2l(sum);
	entropy = letter_count * res;
	fprintf(stderr, "Result %Lf\n", entropy);
	return (entropy);
}

int			main(int argc, char **argv)
{
	int		i;
	int		j;
	int		word_count;
	int		letter_count;
	char	*str;
	char	*mstr;
	int		fd;
	int		len;

	i = 0;
	j = 1;
	len = ft_strlen(argv[1]);
	srand(time(NULL));
	if (argc != 2 && argc != 3)
	{
		ft_putstr_fd("usage: ./a.out {with_letter-to_letter}+{with_letter-to_letter}+...+{with_letter-to_letter} number_of_passswords1 file_for_passwords\n", 2);
		return (1);
	}
	letter_count = ft_errors(argv[1]);
	if (letter_count < 0)
	{
		ft_putstr_fd("usage: ./a.out {with_letter-to_letter}+{with_letter-to_letter}+...+{with_letter-to_letter} number_of_passswords2 file_for_passwords\n", 2);
		return (1);
	}
	if (argc == 3)
		fd = open(argv[2], O_CREAT | O_RDWR, 777);
	else
		fd = 1;
	if (fd < 0)
	{
		ft_putstr_fd("Problems with open file\n", 2);
		return (1);
	}
	str = ft_memalloc(letter_count);
	if (!(str))
	{
		ft_putstr_fd("Problems with malloc\n", 2);
		return (1);
	}
	mstr = ft_memalloc(letter_count);
	if (!(mstr))
	{
		ft_putstr_fd("Problems with malloc\n", 2);
		return (1);
	}
	ft_putstr_fd("Passwords....\n", 2);
	j = 1;
	for (i = 0 ; i < letter_count ; i++)
	{
		str[i] = argv[1][j] - 1;
		mstr[i] = argv[1][j + 2];
		j = j + 6;
	}
	i = 0;
	do
	{
		str[i]++;
		if (str[i] > mstr[i])
		{
			str[i] = argv[1][i * 6 + 1] - 1;
			i--;
		}
		else
		{
			if(i < (letter_count - 1))
				i++;
			else
			{
				for(j = 0; j < letter_count; j++)
					ft_putchar_fd(str[j], fd);
				ft_putchar_fd('\n', fd);
			}
		}
	}
	while (i >= 0);
	free(str);
	ft_putstr_fd("Passwords....Done\n", 2);
	if (argc == 4)
		close(fd);
	ft_putstr_fd("\nPassword entropy calculation\n", 2);
	fprintf(stderr, "Result %Lf\n", entropy(argv[1], len, letter_count));
	return (0);
}
