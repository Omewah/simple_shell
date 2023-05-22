#include "shell.h"

/**
 * nodeplus - appends a node at the LL prefix
 * @hd: the head node
 * @ndstr: the string node
 * @nnum: the history nth node index
 * Return: new node added to the list
 */
list_t *nodeplus(list_t **hd, const char *ndstr, int nnum)
{
	list_t *nHD;

	if (!hd)
		return (NULL);
	nHD = malloc(sizeof(list_t));
	if (!nHD)
		return (NULL);
	_set_constmem_pfunc((void *)nHD, 0, sizeof(list_t));
	nHD->nnumIN = nnum;
	if (ndstr)
	{
		nHD->stringIN = _doublestr_pfunc(ndstr);
		if (!nHD->stringIN)
		{
			free(nHD);
			return (NULL);
		}
	}
	nHD->next_nodeIN = *hd;
	*hd = nHD;
	return (nHD);
}

/**
 * nodeplusE - appends a node to the LL suffix
 * @hd: the head node
 * @ndstr: the string node
 * @nnum: the history nth node index
 * Return: new node at the end
 */
list_t *nodeplusE(list_t **hd, const char *ndstr, int nnum)
{
	list_t *nND;
	list_t *sumN;

	if (!hd)
		return (NULL);

	sumN = *hd;
	nND = malloc(sizeof(list_t));
	if (!nND)
		return (NULL);
	_set_constmem_pfunc((void *)nND, 0, sizeof(list_t));
	nND->nnumIN = nnum;
	if (ndstr)
	{
		nND->stringIN = _doublestr_pfunc(ndstr);
		if (!nND->stringIN)
		{
			free(nND);
			return (NULL);
		}
	}
	if (sumN)
	{
		while (sumN->next_nodeIN)
			sumN = sumN->next_nodeIN;
		sumN->next_nodeIN = nND;
	}
	else
		*hd = nND;
	return (nND);
}

/**
 * _printL_pfunc - a funtion to print the LL string element
 * @pnode: the pointer to the head node
 * Return: the printed list string element size
 */
size_t _printL_pfunc(const list_t *pnode)
{
	size_t a = 0;

	while (pnode)
	{
		_puts_pfunc(pnode->stringIN ? pnode->stringIN : "(nil)");
		_puts_pfunc("\n");
		pnode = pnode->next_nodeIN;
		a++;
	}
	return (a);
}

/**
 * del_nodeIN - abates a node from the LL index
 * @hd: the head node
 * @ndx: the node index to be abated
 * Return: 1 (Success), Else 0
 */
int del_nodeIN(list_t **hd, unsigned int ndx)
{
	list_t *sumN;
	list_t *pND;
	unsigned int a = 0;

	if (!hd || !*hd)
		return (0);

	if (!ndx)
	{
		sumN = *hd;
		*hd = (*hd)->next_nodeIN;
		free(sumN->stringIN);
		free(sumN);
		return (1);
	}
	sumN = *hd;
	while (sumN)
	{
		if (a == ndx)
		{
			pND->next_nodeIN = sumN->next_nodeIN;
			free(sumN->stringIN);
			free(sumN);
			return (1);
		}
		a++;
		pND = sumN;
		sumN = sumN->next_nodeIN;
	}
	return (0);
}

/**
 * nodefree_pfunc - this funtion frees all
 * @hdptr: the pointer to the head node to free
 * Return: void
 */
void nodefree_pfunc(list_t **hdptr)
{
	list_t *sumN;
	list_t *nND;
	list_t *hd;

	if (!hdptr || !*hdptr)
		return;
	hd = *hdptr;
	sumN = hd;
	while (sumN)
	{
		nND = sumN->next_nodeIN;
		free(sumN->stringIN);
		free(sumN);
		sumN = nND;
	}
	*hdptr = NULL;
}
