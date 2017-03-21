function Main(Puzzle,Target,MaximumDepth)
%Main Run this function and see the result
%   Set Puzzle,Target and MaximumDepth first.  
%   In matrix Puzzle and Target, Zero represents a void.
Solution=zeros(3);
InvalidTrajectory=zeros(3);
tic;
ret=SpeMatrixSearchSolution(Puzzle,Target,Solution,InvalidTrajectory,0,MaximumDepth);
if(ret(1,1)==0)
    fprintf('No solution found in %d step(s)\n',MaximumDepth);
toc;
end