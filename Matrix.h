#ifndef __Matrix_H
#define __Matrix_H


#define FALSE 0
#define TRUE !FALSE
#define EQ 0
#define UNEQ !EQ
#define ERROR 0
#define DONE 1
#define STACK_INIT_SIZE 100
#define STACK_SIZE_INCREMENT 50

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef unsigned char BOOL;
typedef unsigned int STATUS;

typedef struct ElemTypeMatrix
{
	unsigned int Element[9];
}TypeDefMatrix;

typedef struct ElemTypeStack
{
	TypeDefMatrix *base,*top;
	int StackSize;
}TypeDefStack;

STATUS SetMatrix(TypeDefMatrix*);
void PrintMatrix(TypeDefMatrix);
BOOL MatrixCmp(TypeDefMatrix,TypeDefMatrix);
unsigned int FindZeroInMatrix(TypeDefMatrix Matrix);

STATUS MoveZeroUp(TypeDefMatrix*);
STATUS MoveZeroDown(TypeDefMatrix*);
STATUS MoveZeroLeft(TypeDefMatrix*);
STATUS MoveZeroRight(TypeDefMatrix*);

int USER_SearchSolution(TypeDefMatrix,TypeDefMatrix,TypeDefStack*,unsigned int);
BOOL SearchSolution(TypeDefMatrix,TypeDefMatrix,TypeDefStack*,BOOL*,unsigned int,unsigned int,int*);
unsigned int HeuristicFunction(TypeDefMatrix,TypeDefMatrix);
int MatrixID(TypeDefMatrix);

STATUS InitStack(TypeDefStack*);
BOOL StackFull(TypeDefStack);
BOOL StackEmpty(TypeDefStack);
STATUS PushStack(TypeDefStack*,TypeDefMatrix);
STATUS PopStack(TypeDefStack*,TypeDefMatrix*);
BOOL ElementInStack(TypeDefMatrix,TypeDefStack);
BOOL ElementInStack_ReverseSearch(TypeDefMatrix, TypeDefStack);
int Solution_Show(TypeDefStack);
STATUS DestroyStack(TypeDefStack*);

#endif