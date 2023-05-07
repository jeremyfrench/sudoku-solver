# Journey of a Sudoku solver


This project is an attempt to build a fast Sudoku solver. Starting with an algorithm which is basic and slow. Incrementally improving until it is hopefully quite good.

Originally I wanted to build in ASM from scratch, but as I have little experience in ASM I decided to start in C++ (which I also have little experience in but which is less hard). Eventually I hope to push a lot of the code to ASM.

I am benchmarking using the data here http://units.maths.uwa.edu.au/~gordon/sudoku17 

Every new improvement I make to the code I will git tag and add a benchmark to the tag commit comment.

Realizing quite fast that the simple approach I took is good enough for most sim
ple newspaper puzzles, but there is a lot left to learn about Sudoku solving.

## Releases  
 
*  journey/0.0.1 First pass solves some boards but by no means all
*  journey/0.0.2 Replace int with unsigned char for board and compairsons 25% improvement in run time.
*  journey/0.0.3 Change the calculations for the for the bigsquare into a lookup table and moved the array to be a 1d array, while in memory this isn't much different there is less computation needed to lookup addresses. This aslo resulted in more boards being sovled, I'm assuming that there was a bug in earlier versions.
*  journey/0.0.4 Added some board state so that possible value count is not calucated each time and moved the board into a global variable.
*  journey/0.0.5 Unwrapped some of the loops more code but a faster time. 
*  journey/0.0.6 Save board state and use bit masks rather than booleans
*  journey/0.0.7 Calculate cross references for a square before proccessing boards so that loop and branching can be simplified while setting and checking numbers.

## Roadmap 

Look at doing a tick toc approach, on the tic (even versions) speed up the solver on the tock (odd versions) solve more problems.

*  0.0 versions should probalby not solve more boards but do it faster. 
   * Try some profiling tools to work out the current bottlenecks.
   * Look at using bitmasks and binay operations to use less cycles.

*  0.1 Versions will look at solving more problems using known solutions
*  0.2 ASM here we come
*  0.3 Branching and guessing



NB: This project was coded mostly while commuting and sleep deprived. 
