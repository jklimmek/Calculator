#include "stos.h"
#include <iostream>
#include <stdlib.h>
#include <memory.h>

using namespace std;

Stack* InitStack()
{
	return NULL;
}

void RemoveStack(Stack** pStack)
{
	while (!isEmpty(*pStack))
		del(pStack);
	*pStack = NULL;
}

void push(char c, Stack** pStack)
{
	Stack* v = (Stack*)malloc(sizeof(Stack));
	if (v)
	{
		memset(v, 0, sizeof(Stack));
		v->cKey = c;
		v->pNext = *pStack;
		*pStack = v;
	}
	else perror("ERROR push: stack overflow!");
}

char pop(Stack** pStack)
{
	if (!isEmpty(*pStack))
	{
		char c = top(*pStack);
		del(pStack);
		return c;
	}
	return 0;
}

char top(Stack* pStack)
{
	if (!isEmpty(pStack))
		return pStack->cKey;
	return 0;
}

void del(Stack** pStack)
{
	if (!isEmpty(*pStack))
	{
		Stack* p = *pStack;
		*pStack = p->pNext;
		free(p);

	}
	else
		perror("ERROR pop: stack underflow!");
}

int isEmpty(Stack* pStack)
{
	return !pStack;
}