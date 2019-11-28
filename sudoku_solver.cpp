// A Backtracking program in C++ to solve Sudoku problem 
// This is code was originally contributed by rathbhupendra
// Modernized by Arne Mertz
#include <cassert>
#include <iostream>

// UNASSIGNED is used for empty cells in Sudoku grid
constexpr auto UNASSIGNED=0;

// N is used for the size of Sudoku grid. 
// Size will be NxN 
constexpr auto N=9;

// This function finds an entry in grid 
// that is still unassigned 
bool FindUnassignedLocation(int grid[N][N],
                            int& row, int& col);

// Checks whether it will be legal 
// to assign num to the given row, col 
bool isSafe(int grid[N][N], int row,
            int col, int num);

// Pinning test
void assertCorrectSolution(const int grid[N][N]);

/* Takes a partially filled-in grid and attempts
to assign values to all unassigned locations in 
such a way to meet the requirements for 
Sudoku solution (non-duplication across rows, 
columns, and boxes) */
bool SolveSudoku(int grid[N][N])
{
    int row, col;

    // If there is no unassigned location,
    // we are done
    if (!FindUnassignedLocation(grid, row, col))
    {
        return true;
    } // success!

    // consider digits 1 to 9
    for (int num = 1; num <= 9; num++)
    {
        // if looks promising
        if (isSafe(grid, row, col, num))
        {
            // make tentative assignment
            grid[row][col] = num;

            // return, if success, yay!
            if (SolveSudoku(grid))
            {
                return true;
            }

            // failure, unmake & try again
            grid[row][col] = UNASSIGNED;
        }
    }
    return false; // this triggers backtracking
}

/* Searches the grid to find an entry that is 
still unassigned. If found, the reference 
parameters row, col will be set the location 
that is unassigned, and true is returned. 
If no unassigned entries remain, false is returned. */
bool FindUnassignedLocation(int grid[N][N],
                            int& row, int& col)
{
    for (row = 0; row < N; row++)
    {
        for (col = 0; col < N; col++)
        {
            if (grid[row][col] == UNASSIGNED)
            {
                return true;
            }
        }
    }
    return false;
}

/* Returns a boolean which indicates whether 
an assigned entry in the specified row matches 
the given number. */
bool UsedInRow(int grid[N][N], int row, int num)
{
    for (int col = 0; col < N; col++)
    {
        if (grid[row][col] == num)
        {
            return true;
        }
    }
    return false;
}

/* Returns a boolean which indicates whether 
an assigned entry in the specified column 
matches the given number. */
bool UsedInCol(int grid[N][N], int col, int num)
{
    for (int row = 0; row < N; row++)
    {
        if (grid[row][col] == num)
        {
            return true;
        }
    }
    return false;
}

/* Returns a boolean which indicates whether 
an assigned entry within the specified 3x3 box 
matches the given number. */
bool UsedInBox(int grid[N][N], int boxStartRow,
               int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (grid[row + boxStartRow]
                [col + boxStartCol] == num)
            {
                return true;
            }
        }
    }
    return false;
}

/* Returns a boolean which indicates whether 
it will be legal to assign num to the given 
row, col location. */
bool isSafe(int grid[N][N], int row,
            int col, int num)
{
    /* Check if 'num' is not already placed in
    current row, current column and current 3x3 box */
    return !UsedInRow(grid, row, num) &&
           !UsedInCol(grid, col, num) &&
           !UsedInBox(grid, row - row % 3,
                      col - col % 3, num) &&
           grid[row][col] == UNASSIGNED;
}

/* A utility function to print grid */
void printGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            std::cout << grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

// Driver Code 
int main()
{
    // 0 means unassigned cells
    int grid[N][N] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
                      {5, 2, 0, 0, 0, 0, 0, 0, 0},
                      {0, 8, 7, 0, 0, 0, 0, 3, 1},
                      {0, 0, 3, 0, 1, 0, 0, 8, 0},
                      {9, 0, 0, 8, 6, 3, 0, 0, 5},
                      {0, 5, 0, 0, 9, 0, 6, 0, 0},
                      {1, 3, 0, 0, 0, 0, 2, 5, 0},
                      {0, 0, 0, 0, 0, 0, 0, 7, 4},
                      {0, 0, 5, 2, 0, 6, 3, 0, 0}};
    auto successfullySolved = SolveSudoku(grid);
    assert(successfullySolved);

    if (successfullySolved)
    {
        assertCorrectSolution(grid);
        printGrid(grid);
    }
    else
    {
        std::cout << "No solution exists";
    }

    return 0;
}

void assertCorrectSolution(const int grid[N][N])
{
    const int expected[N][N] =
        {{3, 1, 6, 5, 7, 8, 4, 9, 2},
         {5, 2, 9, 1, 3, 4, 7, 6, 8},
         {4, 8, 7, 6, 2, 9, 5, 3, 1},
         {2, 6, 3, 4, 1, 5, 9, 8, 7},
         {9, 7, 4, 8, 6, 3, 1, 2, 5},
         {8, 5, 1, 7, 9, 2, 6, 4, 3},
         {1, 3, 8, 9, 4, 7, 2, 5, 6},
         {6, 9, 2, 3, 5, 1, 8, 7, 4},
         {7, 4, 5, 2, 8, 6, 3, 1, 9}};

    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            assert (grid[row][col] == expected[row][col]);
        }
    }
}
