// arrays.c - Basic Array DSA Questions

#include <stdio.h>

// Q1: Reverse an array in-place
void reverse(int *arr, int n) {
    int i = 0, j = n - 1, temp;
    while (i < j) {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++; j--;
    }
}

// Q2: Find duplicate elements in an array
void findDuplicates(int *arr, int n) {
    printf("Duplicates: ");
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            if(arr[i] == arr[j]) {
                printf("%d ", arr[i]);
                break;
            }
        }
    }
}

int main() {
    int arr[] = {1, 2, 3, 2, 4, 5, 1};
    int size = sizeof(arr) / sizeof(arr[0]);

    reverse(arr, size);
    printf("Reversed: ");
    for(int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");

    findDuplicates(arr, size);
    return 0;
}
