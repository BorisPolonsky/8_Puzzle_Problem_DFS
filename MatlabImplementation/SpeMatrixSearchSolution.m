function Ret = SpeMatrixSearchSolution(Puzzle,Target,Solution,InvalidTrajectory,CurrentDepth,MaximumDepth)
%SpeMatrixSearchSolution This function will find out a solution trajectory
%(if exists)from Puzzle to Target, which are both SpeMatrices. 
%   The form of return:[SolutionStatusVector,Solution,InvalidTrajectory] 
%   The SolutionStatusVector is defined as below.
%   [StatusSolutionConfirmed;0;0]
%   StatusSolutionConfirmed will be 1 if existence of Solution Trajectory 
%   is confirmed, otherwise it will be 0.
%
%   Solution and InvalidTrajectory are stacks that contains several
%   SpeMatrices. 
%   The form of stack is defined as below:
%   [Begin,SpeMatrix1,SpeMatrix2,SpeMatrix3,...,SpeMatrixN], where Begin
%   is a 3-order empty matrix. 
%


if(MatrixValid(Puzzle)==0||MatrixValid(Target==0))
    Ret=[[0;0;0],Solution,InvalidTrajectory];
    return
end
if(Puzzle==Target)
    Ret=([[1;0;0],Solution,InvalidTrajectory]);
    Solution=Push(Solution,Puzzle);
    fprintf('Solution Exists. \n');
    PrintSolution(Solution)
    return
end
if(CurrentDepth==MaximumDepth)
    Ret=[[0;0;0],Solution,InvalidTrajectory];
    return
end
Solution=Push(Solution,Puzzle);
fprintf('Testing Trajectory:\n');
disp(Puzzle);
TEMP=MoveZeroLeft(Puzzle);
if(MatrixInStack(Solution,TEMP)==0&&MatrixInStack(InvalidTrajectory,TEMP)==0)
    retofSpeMatrixSearchSolution=SpeMatrixSearchSolution(TEMP,Target,Solution,InvalidTrajectory,CurrentDepth+1,MaximumDepth);
    InvalidTrajectory=GetInvalidTrajectory(retofSpeMatrixSearchSolution);
    if(SolutionExists(retofSpeMatrixSearchSolution)==1)
        Solution=GetSolution(retofSpeMatrixSearchSolution);
        Ret=[[1;0;0],Solution,InvalidTrajectory];
        return
    end
end

TEMP=MoveZeroRight(Puzzle);
if(MatrixInStack(Solution,TEMP)==0&&MatrixInStack(InvalidTrajectory,TEMP)==0)
    retofSpeMatrixSearchSolution=SpeMatrixSearchSolution(TEMP,Target,Solution,InvalidTrajectory,CurrentDepth+1,MaximumDepth);
    InvalidTrajectory=GetInvalidTrajectory(retofSpeMatrixSearchSolution);
    if(SolutionExists(retofSpeMatrixSearchSolution)==1)
        Solution=GetSolution(retofSpeMatrixSearchSolution);
        Ret=[[1;0;0],Solution,InvalidTrajectory];
        return
    end
end

TEMP=MoveZeroUp(Puzzle);
if(MatrixInStack(Solution,TEMP)==0&&MatrixInStack(InvalidTrajectory,TEMP)==0)
    retofSpeMatrixSearchSolution=SpeMatrixSearchSolution(TEMP,Target,Solution,InvalidTrajectory,CurrentDepth+1,MaximumDepth);
    InvalidTrajectory=GetInvalidTrajectory(retofSpeMatrixSearchSolution);
    if(SolutionExists(retofSpeMatrixSearchSolution)==1)
        Solution=GetSolution(retofSpeMatrixSearchSolution);
        Ret=[[1;0;0],Solution,InvalidTrajectory];
        return
    end
end

TEMP=MoveZeroDown(Puzzle);
if(MatrixInStack(Solution,TEMP)==0&&MatrixInStack(InvalidTrajectory,TEMP)==0)
    retofSpeMatrixSearchSolution=SpeMatrixSearchSolution(TEMP,Target,Solution,InvalidTrajectory,CurrentDepth+1,MaximumDepth);
    InvalidTrajectory=GetInvalidTrajectory(retofSpeMatrixSearchSolution);
    if(SolutionExists(retofSpeMatrixSearchSolution)==1)
        Solution=GetSolution(retofSpeMatrixSearchSolution);
        Ret=[[1;0;0],Solution,InvalidTrajectory];
        return
    end
end

InvalidTrajectory=Push(InvalidTrajectory,Puzzle);
Solution=Pop(Solution);
fprintf('Invalid Trajectory found:\n');
disp(Puzzle)
Ret=[[0;0;0],Solution,InvalidTrajectory];
return
end


function [ Row,Column ] = VerifyPositionOfZero( Matrix )
%VerifyPositionOfZero Verify the position of first zero in matrix. If
%there's no zero in matrix, return[0,0]
%   The summary itself is clear enough. 
for i=1:3
    for j=1:3
        if(Matrix(i,j)==0)
            Row=i;
            Column=j;
            return
        end
    end
Row=0;
Column=0;
end
end

function ret = MatrixValid( InputMatrix )
%MatrixValid
%   If Matrix contains only contains one zero. Return 1, otherwise return
%   0.
sum=0;
for i=1:3
    for j=1:3
        if(InputMatrix(i,j)==0)
            sum=sum+1;
        end
    end
end
if(sum==1)
    ret=1;
else
    ret=0;
end
end

function OutputMatrix = MoveZeroUp( InputMatrix )
%MoveZeroUp If possible, switch zero with the element up to it and return the matrix after operation. 
%   Operation applies to the first zero detected only.
%   If unable to operate, return InputMatrix. 
[i,j]=VerifyPositionOfZero(InputMatrix);
if(i<=1)
    OutputMatrix=InputMatrix;
    return
else
    InputMatrix(i,j)=InputMatrix(i-1,j);
    InputMatrix(i-1,j)=0;
    OutputMatrix=InputMatrix;
end
end

function OutputMatrix = MoveZeroDown( InputMatrix )
%MoveZeroDown If possible, switch zero with the element down to it and return the matrix after operation. 
%   Operation applies to the first zero detected only.
%   If unable to operate, return InputMatrix. 
[i,j]=VerifyPositionOfZero(InputMatrix);
if(i==1||i==2)
    InputMatrix(i,j)=InputMatrix(i+1,j);
    InputMatrix(i+1,j)=0;
    OutputMatrix=InputMatrix;
    return
else
    OutputMatrix=InputMatrix;
end
end

function OutputMatrix = MoveZeroLeft( InputMatrix )
%MoveZeroLeft If possible, switch zero with the element left to it and return the matrix after operation. 
%   Operation applies to the first zero detected only.
%   If unable to operate, return InputMatrix. 
[i,j]=VerifyPositionOfZero(InputMatrix);
if(j<=1)
    OutputMatrix=InputMatrix;
    return
else
    InputMatrix(i,j)=InputMatrix(i,j-1);
    InputMatrix(i,j-1)=0;
    OutputMatrix=InputMatrix;
end
end

function OutputMatrix = MoveZeroRight( InputMatrix )
%MoveZeroLeft If possible, switch zero with the element right to it and return the matrix after operation. 
%   Operation applies to the first zero detected only.
%   If unable to operate, return InputMatrix. 
[i,j]=VerifyPositionOfZero(InputMatrix);
if(j==1||j==2)
    InputMatrix(i,j)=InputMatrix(i,j+1);
    InputMatrix(i,j+1)=0;
    OutputMatrix=InputMatrix;
    return
else
    OutputMatrix=InputMatrix;
end
end

function MatrixStack = StackInit( MatrixStack )
%StackInit
%   Create a Matrix that indicates the bottom of the stack. 
MatrixStack=zeros(3);
end


function MatrixStack = Push( MatrixStack,InputMatrix )
%Push Push InputMatrix into MatrixStack
%   Simply combine two matrixs. 
MatrixStack=[MatrixStack,InputMatrix];
end

function MatrixStack = Pop( MatrixStack )
%Pop Pop a matrix from the stack
%   Simply discard the last three columns of the MatrixStack
[i,j]=size(MatrixStack);
if(j>3)
    MatrixStack=MatrixStack(:,1:j-3);
end
end

function  ret= MatrixInStack( MatrixStack,InputMatrix )
%MatrixInStack Determine whether a specific Matrix is in Stack
%   Stack must not be empty. 
[i,j]=size(MatrixStack);
k=fix(j/3)-1;
for i=1:k
    TEMP=MatrixStack(:,i*3+1:i*3+3);
    if(TEMP==InputMatrix)
        ret=1;
        return
    end
end
ret=0;
end

function  PrintSolution(MatrixStack)
%PrintSolution Show every steps of the solution. 
%   0 represents a void.  
[i,j]=size(MatrixStack);
k=fix(j/3)-1;
for i=1:k
    fprintf('Step:%d\n',i-1);
    CurrentStep=MatrixStack(:,i*3+1:i*3+3);
    disp(CurrentStep);
end
end

function  ret=SolutionExists(retofSpeMatrixSearchSolution)
%SolutionExist Determine whether solution exists by the return value of function SpeMatrixSearchSolution() 
%   ret=1 Solution exists.
%   ret=0 Solution doesn't exist.
if (retofSpeMatrixSearchSolution(1,1)==0);
    ret=0;
else
    ret=1;
end
end

function  Solution=GetSolution(retofSpeMatrixSearchSolution)
%GetSolution Get Solution from the return value of function
%SpeMatrixSearchSolution()
%   No detail. 
[i,j]=size(retofSpeMatrixSearchSolution);
for i=1:((fix(j-1)/3)-1)
    TEMP=retofSpeMatrixSearchSolution(:,i*3+2:i*3+4);
    if(TEMP==zeros(3))
        Solution=retofSpeMatrixSearchSolution(:,2:i*3+1);
        return
    end
end
end

function  InvalidTrajectory=GetInvalidTrajectory(retofSpeMatrixSearchSolution)
%GetInvalidTrajectory Get InvalidTrajectory from the return value of function
%SpeMatrixSearchSolution()
%   No detail. 
[i,j]=size(retofSpeMatrixSearchSolution);
for i=1:((fix(j-1)/3)-1)
    TEMP=retofSpeMatrixSearchSolution(:,i*3+2:i*3+4);
    if(TEMP==zeros(3))
        InvalidTrajectory=retofSpeMatrixSearchSolution(:,i*3+2:j);
        return
    end
end
end

