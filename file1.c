#include "shell.h"

/**
 * interactive - Returns true if the shell is in interactive mode.
 * @info: Pointing the info_t struct.
 *
 * Return: If in interactive mode 1, otherwise 0.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Checking if a character is a delimiter.
 * @c: The character that has to be checked.
 * @delim: The delimiter string.
 *
 * Return: If the character is a delimiter 1, otherwise 0.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}

/**
 * _isalpha - Checking for an alphabetic character.
 * @c: The char to check.
 *
 * Return: If c is alphabetic 1, otherwise 0.
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - Converting a string to an integer.
 * @s: The string to be converted.
 *
 * Return: If no numbers in string 0, otherwise the converted number
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
