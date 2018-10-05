#include "stdio.h"
#include <iostream>

#define OK 0
#define MEMORY_ERROR -1

// Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k.
// Найти количество таких пар индексов (i, j), что A[i] + B[j] = k. Время работы O(n + m). n, m ≤ 100000.
// Указание. Обходите массив B от конца к началу.

int count_pairs(int size_arr1, int size_arr2, int *arr1, int *arr2, int number) {
    int ind_arr1 = 0, ind_arr2 = size_arr2 - 1;
    int counter = 0;
    while(ind_arr1 < size_arr1 && ind_arr2 >= 0) {
        int tmp = arr2[ind_arr2] + arr1[ind_arr1];
        if (tmp == number) {
            counter++;
            ind_arr1++;
            ind_arr2--;
        }
        else if (tmp < number)
            ind_arr1++;
        else
            ind_arr2--;
    }
    return counter;
}

int main(void) {
    int size_arr1, size_arr2;
    int *arr1, *arr2;
    int number;
    scanf("%d", &size_arr1);
    arr1 = (int *)malloc(sizeof(int) * size_arr1);
    if (!arr1)
        return MEMORY_ERROR;

    for(int i = 0; i < size_arr1; i++)
        scanf("%d", &(arr1[i]));

    scanf("%d", &size_arr2);
    arr2 = (int *)malloc(sizeof(int) * size_arr2);
    if (!arr2) {
        free(arr1);
        return MEMORY_ERROR;
    }
    for(int i = 0; i < size_arr2; i++)
        scanf("%d", &(arr2[i]));

    scanf("%d", &number);

    int count = count_pairs(size_arr1, size_arr2, arr1, arr2, number);

    printf("%d", count);
    free(arr1);
    free(arr2);
    return OK;
}
