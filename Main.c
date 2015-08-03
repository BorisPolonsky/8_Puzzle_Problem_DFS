#include "Main.h"

void main()
{
	TypeDefMatrix OriginalMatrix,TargetMatrix;
	TypeDefStack Solution;
	unsigned int totalsteps,steplimit;
	int NumofSolutionTested;
	clock_t t_begin, t_end;
	InitStack(&Solution);
	printf("Original Matrix:\n");
	SetMatrix(&OriginalMatrix);
	printf("%Origin:\n");
	PrintMatrix(OriginalMatrix);
	printf("Target Matrix:\n");
	SetMatrix(&TargetMatrix);
	printf("Target:\n");
	PrintMatrix(TargetMatrix);
	printf("Step limit(0-255). \n");
	scanf_s("%d",&steplimit);
	system("cls");
	printf("Origin:\n");
	PrintMatrix(OriginalMatrix);
	printf("Target:\n");
	PrintMatrix(TargetMatrix);
	printf("Step limit:%d\n",steplimit);
	system("pause");
	t_begin = clock();
	NumofSolutionTested=USER_SearchSolution(OriginalMatrix,TargetMatrix,&Solution,steplimit);
	t_end = clock();
	if(StackEmpty(Solution)==FALSE)
	{
		printf("Solution exists. \n");
		totalsteps=Solution_Show(Solution);
		printf("%d%s",totalsteps," step(s) in total. \n");
	}
	else
	{
		printf("No solution within %d steps. \n",steplimit);
	}
	NumofSolutionTested=USER_SearchSolution(OriginalMatrix,TargetMatrix,&Solution,steplimit);
	printf("%d Solution Tested. \n", NumofSolutionTested);
	printf("Total time elapsed: \n%ld ms\n", (t_end - t_begin));
	DestroyStack(&Solution);
	system("pause");
}