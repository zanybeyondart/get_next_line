/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 02:10:12 by zvakil            #+#    #+#             */
/*   Updated: 2023/08/07 05:14:04 by zvakil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static	char * assigning_line(char *str, int fd)
{
	char	*buffer;
	int		r_val;
	
	buffer = (char *) malloc (BUFFER_SIZE + 1);
	if (!buffer)
		return(NULL);
	while(r_val != 0 && !ft_strchr(str, '\n'))
	{
		r_val = read (fd, buffer, BUFFER_SIZE);
		if (r_val == -1)
		{
			free(buffer);
			return(NULL);
		}
		buffer[r_val] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*fix_line(char *str)
{
	int		a;
	char	*line;

	a = 0;
	while(str[a] != '\n')
		a++;
	return (ft_substr(str, 0, a));
	
}

char	*remaining(char *str)
{
	char *temp;
	int	a;
	int	start;
	
	start = 0;
	while(str[start] != '\n')
		start++;
	a = ft_strlen(str);
	if (start + 1 == a)
	{
		free(str);
		return (str);
	}
	temp = (char *) malloc ((a - start) + 1);
	if(!temp)
		return(NULL);
	temp = ft_substr(str, start, a - start);
	free(str);
	return(temp);
}

char	*get_next_line(int fd)
{
	static	char* str;
	char		*line;

	str = assigning_line(str, fd);
	line = fix_line(str);
	str = remaining(str);
	return (line);
}