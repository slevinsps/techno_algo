#include "stdio.h"
#include <iostream>

#define OK 0
#define NORTHING_SEARCH -1
#define MEMORY_ERROR -2

// Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m]
// значения массива строго возрастают, а на интервале [m, n-1] строго убывают.
// Найти m за O( log m ). 2 ≤ n ≤ 10000.

int bin_search(int left, int right, int *arr, int size_arr)
{

    while(left < right)
    {
        int mid = (left + right) / 2;
        if (mid == size_arr - 1)
            return mid;
        if (mid == 0)
        {
            if (arr[mid] > arr[mid + 1])
                return mid;
            else
                return NORTHING_SEARCH;
        }
        else if (mid == size_arr - 2)
        {
            if (arr[mid] < arr[mid + 1] && arr[mid] > arr[mid - 1])
                return mid + 1;
        }

        if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1])
        {
            return mid;
        }
        else if (arr[mid] > arr[mid - 1] && arr[mid] < arr[mid + 1])
        {
            left = mid + 1;
        }
        else if (arr[mid] < arr[mid - 1] && arr[mid] > arr[mid + 1])
        {
            right = mid;
        }
    }
    return NORTHING_SEARCH;
}

int find_index(int size_arr, int *arr)
{
    if (size_arr == 2)
    {
        if (arr[0] > arr[1])
            return 0;
        else
            return 1;
    }
    int prev_ind = 1;
    int next_ind = 2;
    int ans_ind = 0;
    while (prev_ind < size_arr) {
        ans_ind = bin_search(prev_ind - 1, next_ind - 1, arr, size_arr);
        if (ans_ind != NORTHING_SEARCH)
            break;
        prev_ind = next_ind;
        next_ind *= 2;
        if (next_ind > size_arr)
            next_ind = size_arr;

    }
    return ans_ind;
}

int main() {
    int size_arr;
    int *arr;
    scanf("%d", &size_arr);
    arr = (int *)malloc(sizeof(int) * size_arr);
    if (!arr)
        return MEMORY_ERROR;

    for(int i = 0; i < size_arr; i++)
        scanf("%d", &(arr[i]));

    int index = find_index(size_arr, arr);
    printf("%d", index);
    free(arr);
    return OK;
}
