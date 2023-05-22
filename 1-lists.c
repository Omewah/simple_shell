#include "shell.h"

/**
 * _lgtLL_pfunc - measures the area of the linked list
 * @ptr: this is a pointer to the first node
 * Return: measured length of the linked list
 */
size_t _lgtLL_pfunc(const list_t *ptr)
{
	size_t a = 0;

	while (ptr)
	{
		ptr = ptr->next_nodeIN;
		a++;
	}
	return (a);
}

/**
 * _strlist_pfunc - appends string arrays to the linked list
 * @ptr: this is a pointer to the first node
 * Return: the appened string arrays to the LL
 */
char **_strlist_pfunc(list_t *ptr)
{
	list_t *pnde = ptr;
	size_t a = _lgtLL_pfunc(ptr);
	size_t b;
	char **ss_grp;
	char *s_lst;

	if (!ptr || !a)
		return (NULL);
	ss_grp = malloc(sizeof(char *) * (a + 1));
	if (!ss_grp)
		return (NULL);
	for (a = 0; pnde; pnde = pnde->next_nodeIN, a++)
	{
		s_lst = malloc(_lenstrn_pfunc(pnde->stringIN) + 1);
		if (!s_lst)
		{
			for (b = 0; b < a; b++)
				free(ss_grp[b]);
			free(ss_grp);
			return (NULL);
		}

		s_lst = _copystr_pfunc(s_lst, pnde->stringIN);
		ss_grp[a] = s_lst;
	}
	ss_grp[a] = NULL;
	return (ss_grp);
}


/**
 * printLL_pfunc - a function that prints all LL elements
 * @ptr: this is a pointer to the first node
 * Return: the printed linked list
 */
size_t printLL_pfunc(const list_t *ptr)
{
	size_t a = 0;

	while (ptr)
	{
		_puts_pfunc(ddconvert_pfunc(ptr->nnumIN, 10, 0));
		_putchar_pfunc(':');
		_putchar_pfunc(' ');
		_puts_pfunc(ptr->stringIN ? ptr->stringIN : "(nil)");
		_puts_pfunc("\n");
		ptr = ptr->next_nodeIN;
		a++;
	}
	return (a);
}

/**
 * nodeST_pfunc - outputs the prefix of the string
 * @pnde: the pointer to prefix of the LL
 * @pfx: the matching string to compare
 * @ch: the character to be matched after compare
 * Return: the matched node
 */
list_t *nodeST_pfunc(list_t *pnde, char *pfx, char ch)
{
	char *b = NULL;

	while (pnde)
	{
		b = checkpoint_pfunc(pnde->stringIN, pfx);
		if (b && ((ch == -1) || (*b == ch)))
			return (pnde);
		pnde = pnde->next_nodeIN;
	}
	return (NULL);
}

/**
 * nodeIX_pfunc - a function that calls the node index
 * @ptr: this is a pointer to the first node
 * @pnde: the pointer to prefix of the LL
 * Return: the node index, Else -1
 */
ssize_t nodeIX_pfunc(list_t *ptr, list_t *pnde)
{
	size_t a = 0;

	while (ptr)
	{
		if (ptr == pnde)
			return (a);
		ptr = ptr->next_nodeIN;
		a++;
	}
	return (-1);
}
