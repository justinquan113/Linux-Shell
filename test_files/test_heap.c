#include <stdio.h>
#include "myheap.h"

int main(void)
{
    int passed = 0;
    int total = 0;

    free_all();

    /* Test allocation of a small block */
    total++;
    char *first = alloc(10);

    if (first != NULL) {
        printf("PASS: alloc small block\n");
        passed++;
    } else {
        printf("FAIL: alloc small block\n");
    }

    /* Test that allocations do not overlap */
    total++;
    char *second = alloc(20);

    if (second != NULL &&
        second == first + 10) {
        printf("PASS: sequential allocations\n");
        passed++;
    } else {
        printf("FAIL: sequential allocations\n");
    }

    /* Test zero-size allocation */
    total++;
    if (alloc(0) == NULL) {
        printf("PASS: zero-size allocation rejected\n");
        passed++;
    } else {
        printf("FAIL: zero-size allocation rejected\n");
    }

    /* Reset the allocator */
    free_all();

    total++;
    char *reset = alloc(10);

    if (reset != NULL && reset == first) {
        printf("PASS: free_all resets heap\n");
        passed++;
    } else {
        printf("FAIL: free_all resets heap\n");
    }

    /* Test heap exhaustion */
    free_all();

    total++;
    char *whole_heap = alloc(10000);

    if (whole_heap != NULL && alloc(1) == NULL) {
        printf("PASS: heap exhaustion handled\n");
        passed++;
    } else {
        printf("FAIL: heap exhaustion handled\n");
    }

    /* Test requests larger than the heap */
    free_all();

    total++;
    if (alloc(10001) == NULL) {
        printf("PASS: oversized allocation rejected\n");
        passed++;
    } else {
        printf("FAIL: oversized allocation rejected\n");
    }

    printf("\nHeap tests: %d/%d passed\n", passed, total);

    return passed == total ? 0 : 1;
}