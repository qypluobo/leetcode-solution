#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE_SIZE   100

struct QueueNode {
    int x1;
    int y1;
    int x2;
    int y2;
};

typedef struct {
    struct QueueNode *nodes[BASE_SIZE];
    int front;
    int rear;
} MyQueue;

void initQueue(MyQueue *queue)
{
    if (queue == NULL) {
        return;
    }
    queue->front = 0;
    queue->rear = 0;
}

void pushQueue(MyQueue *queue, struct QueueNode *node)
{
    if (queue == NULL || node == NULL) {
        return;
    }
    
    int next = (queue->rear + 1 + BASE_SIZE) % BASE_SIZE;
    if (next != queue->front) {
        queue->nodes[queue->rear] = node;
        queue->rear = next;
    }
}

struct QueueNode *popQueue(MyQueue *queue)
{
    if (queue == NULL) {
        return NULL;
    }
    
    if (queue->rear == queue->front) {
        return NULL;
    }
    
    struct QueueNode *node = queue->nodes[queue->front];
    queue->front = (queue->front + 1 + BASE_SIZE) % BASE_SIZE;
    return node;
}

int isQueueEmpty(MyQueue *queue)
{
    if (queue == NULL) {
        return 1;
    }
    
    if (queue->rear == queue->front) {
        return 1;
    }
    
    return 0;
}

int getQueueSize(MyQueue *queue)
{
    return (queue->rear + BASE_SIZE - queue->front) % BASE_SIZE;
}

void deinitQueue(MyQueue *queue)
{
    if (queue == NULL) {
        return;
    }
    queue->front = 0;
    queue->rear = 0;
}

int minimumMoves(int** grid, int gridSize, int* gridColSize){
    if (grid == NULL || gridSize == 0) {
        return 0;
    }

    MyQueue queue;
    initQueue(&queue);

    struct QueueNode* node = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    struct QueueNode* tmp;
    node->x1 = 0;
    node->y1 = 0;
    node->x2 = 0;
    node->y2 = 1;

    pushQueue(&queue, node);

    int steps = 0;
    int qLen = 0;
    while (isQueueEmpty(&queue) == 0) {
        qLen = getQueueSize(&queue);

        while (qLen > 0) {
            qLen--;
            node = popQueue(&queue);

            if (node->x1 == gridSize - 1 && node->y1 == gridSize - 2 && node->x2 == gridSize - 1 && node->y2 == gridSize - 1) {
                return steps;
                break;
            }

            printf("[%d, %d, %d, %d]\n", node->x1, node->y1, node->x2, node->y2);

            // 平行，右移一格
            if (node->x1 == node->x2 && node->y2 < gridSize - 1 && grid[node->x1][node->y2 + 1] != 1) {
                tmp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
                tmp->x1 = node->x1;
                tmp->y1 = node->y1 +1;
                tmp->x2 = node->x2;
                tmp->y2 = node->y2 +1;
                pushQueue(&queue, tmp);
            }
            
            // 平行，下移一格
            if (node->x1 == node->x2 && node->x1 < gridSize - 1 && grid[node->x1 + 1][node->y1] != 1 && grid[node->x2 + 1][node->y2] != 1) {
                tmp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
                tmp->x1 = node->x1 + 1;
                tmp->y1 = node->y1;
                tmp->x2 = node->x2 + 1;
                tmp->y2 = node->y2;
                pushQueue(&queue, tmp);
            }

            // 平行，旋转
            if (node->x1 == node->x2 && node->x2 < gridSize - 1 && grid[node->x2 + 1][node->y2 - 1] != 1) {
                tmp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
                tmp->x1 = node->x1;
                tmp->y1 = node->y1;
                tmp->x2 = node->x2 + 1;
                tmp->y2 = node->y2 - 1;
                pushQueue(&queue, tmp);
            }

            // 垂直，右移一格
            if (node->y1 == node->y2 && node->y1 < gridSize - 1 && grid[node->x1][node->y1 + 1] != 1 && grid[node->x2][node->y2 + 1] != 1) {
                tmp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
                tmp->x1 = node->x1;
                tmp->y1 = node->y1 + 1;
                tmp->x2 = node->x2;
                tmp->y2 = node->y2 + 1;
                pushQueue(&queue, tmp);
            }
            
            // 垂直，下移一格
            if (node->y1 == node->y2 && node->x2 < gridSize - 1 && grid[node->x2 + 1][node->y2] != 1) {
                tmp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
                tmp->x1 = node->x1 + 1;
                tmp->y1 = node->y1;
                tmp->x2 = node->x2 + 1;
                tmp->y2 = node->y2;
                pushQueue(&queue, tmp);
            }

            // 垂直，旋转
            if (node->y1 == node->y2 && node->y2 < gridSize - 1 && grid[node->x2 - 1][node->y2 + 1] != 1) {
                tmp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
                tmp->x1 = node->x1;
                tmp->y1 = node->y1;
                tmp->x2 = node->x2 - 1;
                tmp->y2 = node->y2 + 1;
                pushQueue(&queue, tmp);
            }

            free(node);
        }

        steps++;
    }

    return -1;
}

void test1()
{
    int gridSize = 6;
    int gridColSize[] = {6, 6, 6, 6, 6, 6};
    int** grid = (int**)malloc(sizeof(int*) * gridSize);
    int data[][6] = {{0,0,0,0,0,1},
                     {1,1,0,0,1,0},
                     {0,0,0,0,1,1},
                     {0,0,1,0,1,0},
                     {0,1,1,0,0,0},
                     {0,1,1,0,0,0}};
    for (int i = 0; i < gridSize; i++) {
        grid[i] = (int*)malloc(sizeof(int) * gridColSize[i]);
        memcpy(grid[i], data[i], sizeof(data[i]));
    }

    int steps = minimumMoves(grid, gridSize, gridColSize);
    printf("steps: %d\n", steps);
}

int main()
{
    test1();
    return 0;
}
