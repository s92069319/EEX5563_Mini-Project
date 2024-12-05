#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int size;
    bool isAllocated;
} Block;

void nextFit(int processSizes[], int numProcesses, Block blocks[], int numBlocks) {
    int pointer = 0; // Points to the next block to search

    for (int i = 0; i < numProcesses; i++) {
        int processSize = processSizes[i];
        bool allocated = false;

        for (int j = 0; j < numBlocks; j++) {
            int index = (pointer + j) % numBlocks; // Wrap around to simulate circular traversal

            if (!blocks[index].isAllocated && blocks[index].size >= processSize) {
                blocks[index].size -= processSize;
                blocks[index].isAllocated = true;
                pointer = index + 1; // Update search pointer
                printf("Process %d: Allocated %d KB in Block %d\n", i + 1, processSize, index + 1);
                allocated = true;
                break;
            }
        }

        if (!allocated) {
            printf("Process %d of size %d could not be allocated.\n", i + 1, processSize);
        }
    }
}

int main() {
    int numBlocks, numProcesses;

    // Input number of blocks and their sizes
    printf("Enter the number of memory blocks: ");
    scanf("%d", &numBlocks);

    Block blocks[numBlocks];
    printf("Enter the sizes of the memory blocks:\n");
    for (int i = 0; i < numBlocks; i++) {
        scanf("%d", &blocks[i].size);
        blocks[i].isAllocated = false; // Initially all blocks are free
    }

    // Input number of processes and their sizes
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    int processSizes[numProcesses];
    printf("Enter the sizes of the processes:\n");
    for (int i = 0; i < numProcesses; i++) {
        scanf("%d", &processSizes[i]);
    }

    // Perform next fit allocation
    nextFit(processSizes, numProcesses, blocks, numBlocks);

    // Print final state of memory blocks
    printf("\nFinal memory state in blocks:\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("Block %d: %d KB free\n", i + 1, blocks[i].size);
    }

    return 0;
}
