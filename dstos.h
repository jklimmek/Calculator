#ifndef D_STACK_H
#define D_STACK_H
typedef struct dtagStack
{
	double nKey;
	dtagStack* dpNext;

} dStack;
dStack* dInitStack();
void dRemoveStack(dStack** dpStack);
void dpush(double n, dStack** dpStack);
double dpop(dStack** dpStack);
double dtop(dStack* dpStack);
void ddel(dStack** dpStack);
int disEmpty(dStack* dpStack);
#endif