#include <stdio.h>
#include <stdlib.h>

int comp(const void *a, const void *b) {
    return (*(int **)a)[0] - (*(int **)b)[0];
}

void input(int ***ans, int *returnSize, int x, int y) {
    *returnSize += 1;
    *ans = realloc(*ans, sizeof(int *) * (*returnSize));
    (*ans)[*returnSize - 1] = malloc(sizeof(int) * 2);
    (*ans)[*returnSize - 1][0] = x;
    (*ans)[*returnSize - 1][1] = y;
}

int maxHeight(int *heights, int start, int end) {
    int max = 0;
    for (int i = start; i < end; ++i) {
        if (heights[i] > max) {
            max = heights[i];
        }
    }
    return max;
}

int **getSkyline(int **buildings, int buildingsSize, int *buildingsColSize, int *returnSize, int **returnColumnSizes) {
    int **ans = NULL;
    *returnSize = 0;
    *returnColumnSizes = NULL;

    if (buildingsSize == 0) {
        return ans;
    }

    int *heights = malloc(sizeof(int) * (buildingsSize * 2));
    for (int i = 0; i < buildingsSize * 2; ++i) {
        heights[i] = 0;  // Initialize heights array
    }

    qsort(buildings, buildingsSize, sizeof(int *), comp);

    for (int i = 0; i < buildingsSize; ++i) {
        while (*returnSize > 0 && ans[*returnSize - 1][1] >= buildings[i][2]) {
            (*returnSize)--;
        }

        if (*returnSize == 0 || ans[*returnSize - 1][1] < buildings[i][2]) {
            input(&ans, returnSize, buildings[i][0], buildings[i][2]);
        }

        int maxH = maxHeight(heights, buildings[i][0], buildings[i][1]);
        if (*returnSize == 0 || ans[*returnSize - 1][1] < maxH) {
            input(&ans, returnSize, buildings[i][1], maxH);
        }

        // Update heights array
        for (int j = buildings[i][0]; j < buildings[i][1]; ++j) {
            if (heights[j] < buildings[i][2]) {
                heights[j] = buildings[i][2];
            }
        }
    }

    free(heights);

    *returnColumnSizes = malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = 2;
    }

    return ans;
}

int main() {
    // Example input: buildings represented by [left, right, height]
    int buildings[][3] = {{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}};
    int buildingsSize = sizeof(buildings) / sizeof(buildings[0]);
    int buildingsColSize[] = {3};

    int returnSize;
    int *returnColumnSizes;

    int **skyline = getSkyline((int **)buildings, buildingsSize, buildingsColSize, &returnSize, &returnColumnSizes);

    // Print the result
    printf("Skyline:\n");
    for (int i = 0; i < returnSize; i++) {
        printf("[%d, %d] ", skyline[i][0], skyline[i][1]);
        free(skyline[i]); // Free each sub-array
    }
    printf("\n");

    // Free the array of pointers
    free(skyline);
    free(returnColumnSizes);

    return 0;
}
