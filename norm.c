#include "pas.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

void		ft_putstr(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (i < ft_strlen(s))
		{
			ft_putchar(s[i]);
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	FILE	*stream;
	size_t	i;
	size_t	len;
	ssize_t	f_read;
	char	*line;

	i = 0;
	len = 0;
	if (argc != 2)
	{
		ft_putstr("Usage: ./a.out file_with_passwords\n");
		return (1);
	}
	stream = fopen(argv[1], "r");
		if (stream == NULL)
			exit(EXIT_FAILURE);
	while ((f_read = getline(&line, &len, stream)) != -1)
	{
		len =f_read;
		for ( i = 0 ; i < len-1 ; i++ ) {
			switch(line[i])
			{
				case 0x30 ... 0x39:
					ft_putstr("{0-9}");
					break;
				case 0x21 ... 0x2f:
					ft_putstr("{!-/}");
					break;
				case 0x3a ... 0x40:
					ft_putstr("{:-@}");
					break;
				case 0x5b ... 0x60:
					ft_putstr("{[-`}");
					break;
				case 0x7b ... 0x7e:
					ft_putstr("{{-~}");
					break;
				case 0x61 ... 0x7a:
					ft_putstr("{a-z}");
					break;
				case 0x41 ... 0x5a:
					ft_putstr("{A-Z}");
					break;
				case 0xa: continue;
				default:
					fprintf(stderr,"file is not valid (%X)\n",line[i]);
					return __LINE__;
			}
			if (i < len - 2) ft_putchar('+');
			else ft_putchar('\n');
		}
		free(line);
		line=NULL;
	}
	fclose(stream);
	return(0);
}
