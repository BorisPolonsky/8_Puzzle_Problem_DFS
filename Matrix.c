#include "Matrix.h"

STATUS SetMatrix(TypeDefMatrix *Matrix)
{
	unsigned int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			printf("Row:%d Column:%d\n'0' represents a void.\n\nEnter a number(0-9). ",i+1,j+1);
			scanf_s("%d",&(Matrix->Element[3*i+j]));
		}
	}
	return(DONE);
}

void PrintMatrix(TypeDefMatrix Matrix)
{
	unsigned int i;
	for(i=0;i<3;i++)
	{
		if(Matrix.Element[i]!=0)
			printf("|%d",Matrix.Element[i]);
		else
			printf("| ");
	}
	printf("|\n-------\n");
	for(i=3;i<6;i++)
	{
		if(Matrix.Element[i]!=0)
			printf("|%d",Matrix.Element[i]);
		else
			printf("| ");
	}
	printf("|\n-------\n");
	for(i=6;i<9;i++)
	{
		if(Matrix.Element[i]!=0)
			printf("|%d",Matrix.Element[i]);
		else
			printf("| ");
	}
	printf("|\n");
}

BOOL MatrixCmp(TypeDefMatrix MatrixA,TypeDefMatrix MatrixB)
{
	unsigned int i;
	for(i=0;i<9;i++)
	{
		if(MatrixA.Element[i]!=MatrixB.Element[i])
			return(UNEQ);
	}
	return(EQ);
}

unsigned int FindZeroInMatrix(TypeDefMatrix Matrix)
{
	unsigned int i;
	for(i=0;i<9;i++)
	{
		if(Matrix.Element[i]==0)
			return(i+1);
	}
	return(0);
}

STATUS MoveZeroUp(TypeDefMatrix *Matrix)
{
	unsigned int num;
	num=FindZeroInMatrix(*Matrix);
	if(num>3)
	{
		Matrix->Element[num-1]=Matrix->Element[num-4];
		Matrix->Element[num-4]=0;
		return(DONE);
	}
	else
		return(ERROR);
}

STATUS MoveZeroDown(TypeDefMatrix *Matrix)
{
	unsigned int num;
	num=FindZeroInMatrix(*Matrix);
	if(num>0&&num<7)
	{
		Matrix->Element[num-1]=Matrix->Element[num+2];
		Matrix->Element[num+2]=0;
		return(DONE);
	}
	else
		return(ERROR);
}
STATUS MoveZeroLeft(TypeDefMatrix *Matrix)
{
	unsigned int num;
	num=FindZeroInMatrix(*Matrix);
	if(num%3!=1&&num!=0)
	{
		Matrix->Element[num-1]=Matrix->Element[num-2];
		Matrix->Element[num-2]=0;
		return(DONE);
	}
	else
		return(ERROR);
}
STATUS MoveZeroRight(TypeDefMatrix *Matrix)
{
	unsigned int num;
	num=FindZeroInMatrix(*Matrix);
	if(num%3!=0)
	{
		Matrix->Element[num-1]=Matrix->Element[num];
		Matrix->Element[num]=0;
		return(DONE);
	}
	else
		return(ERROR);
}

//Solution Must be an empty Stack
int USER_SearchSolution(TypeDefMatrix Origin,TypeDefMatrix Target,TypeDefStack *Solution,unsigned int MaximumDepth)
{
	int NumofSolutionTested = 0,i;
	BOOL*SolutionTested, *P;
	if ((SolutionTested = (BOOL*)malloc(375313600 * sizeof(BOOL))) == NULL)
	{
		printf("Unable to acquire Enough space. Search aborted. \n");
	}
	else
	{
		P = SolutionTested;
		for (i = 0; i < 375313600; i++)
			P[i] = 0xFF;//Insane
		SearchSolution(Origin, Target, Solution, SolutionTested, 0, MaximumDepth, &NumofSolutionTested);
		free(P);
	}
	return(NumofSolutionTested);
}

BOOL SearchSolution(TypeDefMatrix Origin, TypeDefMatrix Target, TypeDefStack *Solution, BOOL *SolutionTested, unsigned int CurrentDepth, unsigned int MaximumDepth, int *NumofSolutionTested)
{
	TypeDefMatrix MatrixTemp[4],MatrixTest;
	int PuzzleID;
	unsigned int H[4],Hmin,NumNextNode,i;
	PuzzleID = MatrixID(Origin);
	PushStack(Solution,Origin);
	(*NumofSolutionTested)++;
	if (SolutionTested[PuzzleID]>CurrentDepth)
	{
		SolutionTested[PuzzleID] = (CurrentDepth & 0xFF);
	}
	if(MatrixCmp(Origin,Target)==EQ)
		return(TRUE);
	else if(CurrentDepth==MaximumDepth)	
	{
		PopStack(Solution,&MatrixTemp[0]);
		return(FALSE);
	}
	/*MatrixTemp=Origin;
	if ((MoveZeroLeft(&MatrixTemp) == DONE) && (ElementInStack(MatrixTemp, *SolutionTested) == FALSE))
	{
		if(SearchSolution(MatrixTemp,Target,Solution,SolutionTested,CurrentDepth+1,MaximumDepth)==TRUE)
			return(TRUE);
	}
	MatrixTemp=Origin;
	if (MoveZeroRight(&MatrixTemp) == DONE && (ElementInStack(MatrixTemp, *SolutionTested) == FALSE))
	{
		if(SearchSolution(MatrixTemp,Target,Solution,SolutionTested,CurrentDepth+1,MaximumDepth)==TRUE)
			return(TRUE);
	}
	MatrixTemp=Origin;
	if ((MoveZeroUp(&MatrixTemp) == DONE) && (ElementInStack(MatrixTemp, *SolutionTested) == FALSE))
	{
		if(SearchSolution(MatrixTemp,Target,Solution,SolutionTested,CurrentDepth+1,MaximumDepth)==TRUE)
			return(TRUE);
	}
	MatrixTemp=Origin;
	if ((MoveZeroDown(&MatrixTemp) == DONE) && (ElementInStack(MatrixTemp, *SolutionTested) == FALSE))
	{
		if(SearchSolution(MatrixTemp,Target,Solution,SolutionTested,CurrentDepth+1,MaximumDepth)==TRUE)
			return(TRUE);
	}*/
	while (1)
	{
		NumNextNode = 0;
		MatrixTemp [NumNextNode]= Origin;
		if (MoveZeroUp(MatrixTemp+NumNextNode) == TRUE && SolutionTested[MatrixID(MatrixTemp[NumNextNode])]> (CurrentDepth+1))
		{
			H[NumNextNode] = HeuristicFunction(MatrixTemp[NumNextNode], Target);
			NumNextNode++;
		}
		MatrixTemp[NumNextNode] = Origin;
		if (MoveZeroDown(MatrixTemp + NumNextNode) == TRUE && SolutionTested[MatrixID(MatrixTemp[NumNextNode])] > (CurrentDepth+1))
		{
			H[NumNextNode] = HeuristicFunction(MatrixTemp[NumNextNode], Target);
			NumNextNode++;
		}
		MatrixTemp[NumNextNode] = Origin;
		if (MoveZeroLeft(MatrixTemp + NumNextNode) == TRUE && SolutionTested[MatrixID(MatrixTemp[NumNextNode])] > (CurrentDepth+1))
		{
			H[NumNextNode] = HeuristicFunction(MatrixTemp[NumNextNode], Target);
			NumNextNode++;
		}
		MatrixTemp[NumNextNode] = Origin;
		if (MoveZeroRight(MatrixTemp + NumNextNode) == TRUE && SolutionTested[MatrixID(MatrixTemp[NumNextNode])] > (CurrentDepth+1))
		{
			H[NumNextNode] = HeuristicFunction(MatrixTemp[NumNextNode], Target);
			NumNextNode++;
		}
		if (NumNextNode == 0)
			break;
		else
		{
			MatrixTest = MatrixTemp[0];
			Hmin = H[0];
			for (i = 0; i < NumNextNode; i++)
			{
				if (Hmin > H[i])
				{
					Hmin = H[i];
					MatrixTest = MatrixTemp[i];
				}
			}
			if (SearchSolution(MatrixTest, Target, Solution, SolutionTested, CurrentDepth + 1, MaximumDepth, NumofSolutionTested) == TRUE)
				return(TRUE);
		}
	}
	PopStack(Solution,&MatrixTemp[0]);
	return(FALSE);
}

unsigned int HeuristicFunction(TypeDefMatrix MatrixA, TypeDefMatrix MatrixB)
{
	int i, j,H=0;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (MatrixA.Element[i] != 0 && MatrixA.Element[i] == MatrixB.Element[j])
				H = H + abs(i / 3 - j / 3) + abs(i % 3 - j % 3);
		}
	}
	return (H);
}

int MatrixID(TypeDefMatrix Matrix)
{
	unsigned int i;
	int PuzzleID=0;
	for (i = 0; i < 9; i++)
		PuzzleID = PuzzleID + Matrix.Element[i]*pow(9, i);//6053444~381360744
	return(PuzzleID-6053444);
}


STATUS InitStack(TypeDefStack *Stack)
{
	TypeDefMatrix *p;
	p=(TypeDefMatrix*)malloc(STACK_INIT_SIZE*sizeof(TypeDefMatrix));
	if(p!=NULL)
	{
		Stack->base=p;
		Stack->top=p;
		Stack->StackSize=STACK_INIT_SIZE;
		return(DONE);
	}
	else
		return(ERROR);
}

BOOL StackFull(TypeDefStack Stack)
{
	if(Stack.top-Stack.base==Stack.StackSize)
		return(TRUE);
	else
		return(FALSE);
}

BOOL StackEmpty(TypeDefStack Stack)
{
	if(Stack.top-Stack.base==0)
		return(TRUE);
	else
		return(FALSE);
}

STATUS PushStack(TypeDefStack *Stack,TypeDefMatrix Matrix)
{
	TypeDefMatrix *p;
	if(StackFull(*Stack)==TRUE)
	{
		p=(TypeDefMatrix*)realloc(Stack->base,(Stack->StackSize+STACK_SIZE_INCREMENT)*sizeof(TypeDefMatrix));
		if(p==NULL)
			return(ERROR);
		Stack->base=p;
		Stack->top=p+Stack->StackSize;
		Stack->StackSize=Stack->StackSize+STACK_SIZE_INCREMENT;
	}
	*(Stack->top)=Matrix;
	Stack->top++;
	return(DONE);
}

STATUS PopStack(TypeDefStack *Stack,TypeDefMatrix *Matrix)
{
	if(StackEmpty(*Stack)==TRUE)
		return(ERROR);
	else
	{
		Stack->top--;
		*Matrix=*(Stack->top);
		return(DONE);
	}
}

BOOL ElementInStack(TypeDefMatrix Matrix,TypeDefStack Stack)
{
	TypeDefMatrix *p=Stack.base;
	while(p!=Stack.top)
	{
		if(MatrixCmp(Matrix,*p)==EQ)
			return(TRUE);
		p++;
	}
	return(FALSE);
}

BOOL ElementInStack_ReverseSearch(TypeDefMatrix Matrix, TypeDefStack Stack)
{
	TypeDefMatrix *p = Stack.top-1;
	if (StackEmpty(Stack) == TRUE)
		return(FALSE);
	while (p >= Stack.base)
	{
		if (MatrixCmp(Matrix, *p) == EQ)
			return(TRUE);
		p--;
	}
	return(FALSE);
}

int Solution_Show(TypeDefStack Solution)
{
	int i=0;
	TypeDefMatrix *p=Solution.base;
	while(p!=Solution.top)
	{	
		printf("%s%d\n","Step Number:",i);
		PrintMatrix(*p);
		p++;
		i++;
	}
	i--;
	return(i);
}

STATUS DestroyStack(TypeDefStack *Stack)
{
	free(Stack->base);
	Stack->base=NULL;
	Stack->top=NULL;
	return(DONE);
}
