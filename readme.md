== Journy of a Sudoku solver.==

This project is an attempt to build a fast Sudoku solver. Starting with an algorithm which is basic and slow. Incrementally improving until it is hopefully quite good.

Originally I wanted to build in ASM from scratch, but as I have little experience in ASM I decided to start in C++ (which I also have little experience in but which is less hard). Eventually I hope to push a lot of the code to ASM.

I am benchmarking using the data here http://units.maths.uwa.edu.au/~gordon/sudoku17 

Every new improvement I make to the code I will git tag and add a benchmark to the tag commit comment.

Realizing quite fast that the simple approach I took is good enough for most sim
ple newspaper puzzles, but there is a lot left to learn about Sudoku solving.

