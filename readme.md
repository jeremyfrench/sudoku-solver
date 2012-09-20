== Journey of a Sudoku solver.==

This project is an attempt to build a fast Sudoku solver. Starting with an algorithm which is basic and slow. Incrementally improving until it is hopefully quite good.

Originally I wanted to build in ASM from scratch, but as I have little experience in ASM I decided to start in C++ (which I also have little experience in but which is less hard). Eventually I hope to push a lot of the code to ASM.

I am benchmarking using the data here http://units.maths.uwa.edu.au/~gordon/sudoku17 

Every new improvement I make to the code I will git tag and add a benchmark to the tag commit comment.

Realizing quite fast that the simple approach I took is good enough for most sim
ple newspaper puzzles, but there is a lot left to learn about Sudoku solving.

=Releases=
 
* journey/0.0.1 First pass solves some boards but by no means all
* journey/0.0.2 Replace int with unsigned char for board and compairsons 25% improvement in run time.

=Roadmap=

0.0 versions should probalby solve no more tools but do it faster. 

* Try some profiling tools to work out the current bottlenecks
* Consider unwrapping 2d array into 1d as it is a human construct would have thought the compiler would work this out
* Hard refs for the cross reference variables especially the bigsquare ones
* cache possible values for each square

0.1 Versions will look at solving more problems using known solutions

Future versions are unknown will possibly include brute force and asm.
