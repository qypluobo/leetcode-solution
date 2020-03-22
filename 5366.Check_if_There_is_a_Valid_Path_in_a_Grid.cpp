#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

#define UP      0
#define DOWN    1
#define LEFT    2
#define RIGHT   3

int visited[300][300];
bool reached;

int dirs[4][2] = {
    {-1, 0},    // UP
    {1, 0},     // DOWN
    {0, -1},    // LEFT
    {0, 1},     // RIGHT
};

bool isDirAllowed(int** grid, int x, int y, int dir)
{
    switch(dir) {
        case UP:
            if (grid[x][y] == 2 || grid[x][y] == 5 || grid[x][y] == 6) {
                return true;
            }
            break;
        case DOWN:
            if (grid[x][y] == 2 || grid[x][y] == 3 || grid[x][y] == 4) {
                return true;
            }
            break;
        case LEFT:
            if (grid[x][y] == 1 || grid[x][y] == 3 || grid[x][y] == 5) {
                return true;
            }
            break;
        case RIGHT:
            if (grid[x][y] == 1 || grid[x][y] == 4 || grid[x][y] == 6) {
                return true;
            }
            break;
        default:
            return false;
            break;
    }
    return false;
}

void dfs(int** grid, int gridSize, int gridColSize, int x, int y)
{
    if (x == gridSize - 1 && y == gridColSize - 1) {
        reached = true;
        return;
    }

    if (reached) {
        return;
    }

    //printf("%d, %d\n", x, y);

    int nx;
    int ny;

    nx = x + dirs[UP][0];
    ny = y + dirs[UP][1];
    if (nx >= 0 && nx < gridSize && ny >= 0 && ny < gridColSize && visited[nx][ny] == 0 && isDirAllowed(grid, x, y, UP) && isDirAllowed(grid, nx, ny, DOWN)) {
        visited[nx][ny] = 1;
        dfs(grid, gridSize, gridColSize, nx, ny);
        visited[nx][ny] = 0;
    }

    nx = x + dirs[DOWN][0];
    ny = y + dirs[DOWN][1];
    if (nx >= 0 && nx < gridSize && ny >= 0 && ny < gridColSize && visited[nx][ny] == 0 && isDirAllowed(grid, x, y, DOWN) && isDirAllowed(grid, nx, ny, UP)) {
        visited[nx][ny] = 1;
        dfs(grid, gridSize, gridColSize, nx, ny);
        visited[nx][ny] = 0;
    }

    nx = x + dirs[LEFT][0];
    ny = y + dirs[LEFT][1];
    if (nx >= 0 && nx < gridSize && ny >= 0 && ny < gridColSize && visited[nx][ny] == 0 && isDirAllowed(grid, x, y, LEFT) && isDirAllowed(grid, nx, ny, RIGHT)) {
        visited[nx][ny] = 1;
        dfs(grid, gridSize, gridColSize, nx, ny);
        visited[nx][ny] = 0;
    }

    nx = x + dirs[RIGHT][0];
    ny = y + dirs[RIGHT][1];
    if (nx >= 0 && nx < gridSize && ny >= 0 && ny < gridColSize && visited[nx][ny] == 0 && isDirAllowed(grid, x, y, RIGHT) && isDirAllowed(grid, nx, ny, LEFT)) {
        visited[nx][ny] = 1;
        dfs(grid, gridSize, gridColSize, nx, ny);
        visited[nx][ny] = 0;
    }
}

bool hasValidPath(int** grid, int gridSize, int* gridColSize){
    reached = false;
    memset(visited, 0, sizeof(visited));

    dfs(grid, gridSize, *gridColSize, 0, 0);
    return reached;
}

void test1()
{
    int g1[] = {2,4,3};
    int g2[] = {6,5,2};
    int* grid[] = {g1, g2};
    int colSize[] = {3, 3};
    bool ans = hasValidPath(grid, 2, colSize);
    printf("%s: %d\n", __func__, ans);
}

void test2()
{
    int g1[] = {1,2,1};
    int g2[] = {1,2,1};
    int* grid[] = {g1, g2};
    int colSize[] = {3, 3};
    bool ans = hasValidPath(grid, 2, colSize);
    printf("%s: %d\n", __func__, ans);
}

void test3()
{
    int g1[] = {1,1,2};
    int* grid[] = {g1};
    int colSize[] = {3};
    bool ans = hasValidPath(grid, 1, colSize);
    printf("%s: %d\n", __func__, ans);
}

void test4()
{
    int g1[] = {1,1,1,1,1,1,3};
    int* grid[] = {g1};
    int colSize[] = {7};
    bool ans = hasValidPath(grid, 1, colSize);
    printf("%s: %d\n", __func__, ans);
}

void test5()
{
    int g1[] = {2};
    int g2[] = {2};
    int g3[] = {2};
    int g4[] = {2};
    int g5[] = {2};
    int g6[] = {2};
    int g7[] = {6};
    int* grid[] = {g1,g2,g3,g4,g5,g6,g7};
    int colSize[] = {1, 1, 1, 1, 1, 1, 1};
    bool ans = hasValidPath(grid, 7, colSize);
    printf("%s: %d\n", __func__, ans);
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}