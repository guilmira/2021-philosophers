/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:40:01 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/15 14:33:33 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** PURPOSE : Auxiliar for main parser. Detects the following:
 * 1. Error if string does not contain a number, spaces, or a character.
 * 2. Error if in the whole string there is not a single digit.
 * 3. Error if int is > or < than int limit. */
//ultima linea no esta chekeada
static t_bool	check_argument(char *str)
{
	int	i;
	int	pass;

	pass = 0;
	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]) && !ft_isspaces(str[i]) \
		&& str[i] != '+' && str[i] != '-')
			return (1);
		if (ft_isdigit(str[i]))
			pass++;
	}
	if (!pass)
		return (1);
	return (0);
}

/** PURPOSE : Checks string for adjacent signs, i.e. "++"
 * Also checks for signs that might appear after digits, i.e "503-" */
static t_bool	double_sign(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '+' || str[i] == '-')
			if (str[i + 1] == '+' || str[i + 1] == '-')
				return (1);
		if (ft_isdigit(str[i]))
			if (str[i + 1] == '+' || str[i + 1] == '-')
				return (1);
	}
	return (0);
}

/** PURPOSE : Evaluate if input number is beyond the
 * range of an int. i.e. -2,147,483,648 to 2,147,483,647 */
static t_bool	beyond_range(char *str)
{
	unsigned int	n;
	unsigned int	i;
	int				sign;

	sign = 1;
	i = 0;
	n = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || \
	str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (str[i] - '0') + n * 10;
		if (n > 2147483647 && sign == 1)
			return (1);
		else if (n > 2147483648 && sign == -1)
			return (1);
		i++;
	}
	return (0);
}

/** PURPOSE : Evaluate if number is below one */
static t_bool	below_one(int nbr)
{
	if (nbr < 1)
		return (1);
	return (0);
}

/** PURPOSE : Evaluates input and decides whether there is an error or not.
 * 1. Arguments must be 5 or 6.
 * 2. Number must be passed clean. Check auxiliar functions.
 * 3. Number cannot contain double sign.
 * 4. Number cannot exceed int range.
 * 5 Times cannot be less than one. */
t_bool	parser(int argc, char *argv[])
{
	int	i;

	if (argc != OPT_1 && argc != OPT_2)
		return (1);
	i = 0;
	while (++i < argc)
	{
		if (check_argument(argv[i]))
			return (1);
		if (double_sign(argv[i]))
			return (1);
		if (beyond_range(argv[i]))
			return (1);
		if (below_one(ft_atoi(argv[i])))
			return (1);
	}
	if (ft_atoi(argv[1]) < 3)
		return (1);
	return (0);
}
