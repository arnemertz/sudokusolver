# Modernizing a sudoku solver

During a workshop for modern C++, the trainees decided to do a coding challenge using C++14/17.
Since we were not interested in spending too much time on solving the design challenge itself, we decided to copy an existing C++ solution (as in "C with classes") and modernize it.
This repository shows a way from the orignal not-so-modern C++ code to a more modern style.
Check out the individual commits, including commit messages, for the stepwise refactoring.

The original code by "rathbhupendra" can be found here: https://www.geeksforgeeks.org/sudoku-backtracking-7/

## Testing

For refactoring it is crucial to have at least some tests in place.
The original code is not particularly large, so, while some, but not all functions could be unit tested, a simple pinning test should suffice for starters.
The pinning test simply takes the example sudoku already present in the code and asserts that the solution is correct.

