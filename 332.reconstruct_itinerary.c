#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dfs(int** map, int mapSize, int curCityIndex, int* queue, int* queueSize)
{
    int i = 0;
    for (i = 0; i < mapSize; i++) {
        // don't count itself
        if (i == curCityIndex) {
            continue;   
        }

        // found a ticket
        if (map[curCityIndex][i] == 1) {
            map[curCityIndex][i] = 2;   // mark deleted
            dfs(map, mapSize, i, queue, queueSize);
        }
    }

    // no ticket for this city, enqueue
    queue[*queueSize] = curCityIndex;
    *queueSize += 1;
}

int cmpStr(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** findItinerary(char *** tickets, int ticketsSize, int* ticketsColSize, int* returnSize){
    char** cities = (char**)malloc(sizeof(char**) * (ticketsSize + 1));
    int cityNum = 0;
    int i = 0;
    int j = 0;
    int k = 0;

    // create city map, count city number
    cities[0] = strdup("JFK");
    cityNum = 1;
    for (i = 0; i < ticketsSize; i++) {
        for (j = 0; j < cityNum; j++) {
            // compare dest city
            if (0 == strcmp(tickets[i][1], cities[j])) {
                break;
            }
        }

        // no such city, add to list
        if (j == cityNum) {
            cities[cityNum] = strdup(tickets[i][1]);
            cityNum++;
        }
    }

    for (i = 0; i < cityNum; i++) {
        fprintf(stderr, "%s ", cities[i]);
    }
    fprintf(stderr, "\n");

    qsort(&cities[1], cityNum - 1, sizeof(char*), cmpStr);

    for (i = 0; i < cityNum; i++) {
        fprintf(stderr, "%s ", cities[i]);
    }
    fprintf(stderr, "\n");

    // create 2d array for map
    int **map = (int**)malloc(sizeof(int*) * cityNum);
    int *row = NULL;
    for (i = 0; i < cityNum; i++) {
        row = (int*)malloc(sizeof(int) * cityNum);
        map[i] = row;
        for (j = 0; j < cityNum; j++) {
            if (i == j) {
                continue;
            }

            for (k = 0; k < ticketsSize; k++) {
                if (0 == strcmp(tickets[k][0], cities[i]) && 0 == strcmp(tickets[k][1], cities[j])) {
                    row[j] = 1;
                    break;
                }
            }
        }
    }

    for (i = 0; i < cityNum; i++) {
        for (j = 0; j < cityNum; j++) {
            fprintf(stderr, "%d ", map[i][j]);
        }
        fprintf(stderr, "\n");
    }

    int *queue = (int*)malloc(sizeof(int) * cityNum);
    int queueSize = 0;
    dfs(map, cityNum, 0, queue, &queueSize);

    char **journey = (char**)malloc(sizeof(char*) * queueSize);
    int index = 0;
    for (i = queueSize - 1; i >= 0; i--) {
        journey[index++] = cities[queue[i]];
    }

    for (i = 0; i < queueSize; i++) {
        fprintf(stderr, "%s ", journey[i]);
    }
    fprintf(stderr, "\n");

    return journey;
}

void test1()
{
    char*** tickets = (char***)malloc(sizeof(char**) * 3);
    char** ticket = (char**)malloc(sizeof(char*) * 2);
    ticket[0] = "JFK";
    ticket[1] = "KUL";
    tickets[0] = ticket;

    ticket = (char**)malloc(sizeof(char*) * 2);
    ticket[0] = "JFK";
    ticket[1] = "NRT";
    tickets[1] = ticket;

    ticket = (char**)malloc(sizeof(char*) * 2);
    ticket[0] = "NRT";
    ticket[1] = "JFK";
    tickets[2] = ticket;

    int ticketsColSize = 0;
    int returnSize = 0;

    char** journey = findItinerary(tickets, 3, &ticketsColSize, &returnSize);
}

void test2()
{
    char*** tickets = (char***)malloc(sizeof(char**) * 4);
    char** ticket = (char**)malloc(sizeof(char*) * 2);
    ticket[0] = "MUC";
    ticket[1] = "LHR";
    tickets[0] = ticket;

    ticket = (char**)malloc(sizeof(char*) * 2);
    ticket[0] = "JFK";
    ticket[1] = "MUC";
    tickets[1] = ticket;

    ticket = (char**)malloc(sizeof(char*) * 2);
    ticket[0] = "SFO";
    ticket[1] = "SJC";
    tickets[2] = ticket;

    ticket = (char**)malloc(sizeof(char*) * 2);
    ticket[0] = "LHR";
    ticket[1] = "SFO";
    tickets[3] = ticket;

    int ticketsColSize = 0;
    int returnSize = 0;

    char** journey = findItinerary(tickets, 4, &ticketsColSize, &returnSize);
}

int main()
{
    test2();
    return 0;
}