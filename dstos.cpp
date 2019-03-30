#include "dstos.h"
#include <iostream>
#include <stdlib.h>
#include <memory.h>

using namespace std;

dStack* dInitStack()
{
	return NULL;
}

void dRemoveStack(dStack** dpStack)
{
	while (!disEmpty(*dpStack))
		ddel(dpStack);
	*dpStack = NULL;
}

void dpush(double n, dStack** dpStack)
{
	dStack* v = (dStack*)malloc(sizeof(dStack));
	if (v)
	{
		memset(v, 0, sizeof(dStack));
		v->nKey = n;
		v->dpNext = *dpStack;
		*dpStack = v;
	}
	else perror("ERROR push: stack overflow!");
}

double dpop(dStack** dpStack)
{
	if (!disEmpty(*dpStack))
	{
		double n = dtop(*dpStack);
		ddel(dpStack);
		return n;
	}
	return 0;
}

double dtop(dStack* dpStack)
{
	if (!disEmpty(dpStack))
		return dpStack->nKey;
	return 0;
}

void ddel(dStack** dpStack)
{
	if (!disEmpty(*dpStack))
	{
		dStack* p = *dpStack;
		*dpStack = p->dpNext;
		free(p);

	}
	else
		perror("ERROR pop: stack underflow!");
}

int disEmpty(dStack* dpStack)
{
	return !dpStack;
}