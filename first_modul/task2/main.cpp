#include "stdio.h"
#include <iostream>

#define OK 0
#define NORTHING_SEARCH -1
#define MEMORY_ERROR -2

// Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m]
// значения массива строго возрастают, а на интервале [m, n-1] строго убывают.
// Найти m за O( log m ). 2 ≤ n ≤ 10000.

int bin_search(int left, int right, int *arr)
{
    while(left < right)
    {
        int mid = (left + right) / 2;

        if (mid == left)
        {
            if (arr[mid] > arr[mid + 1])
                return mid;
            else
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
    return left;
}

int find_index(int size_arr, int *arr)
{
    if (size_arr == 1 || arr[0] > arr[1]) {
        return 0;
    }

    if (size_arr == 2) {
            return 1;
    }

    int prev_ind = 1;
    int next_ind = 2;
    int ans_ind = 0;
    int flag_binary = 0;
    if (next_ind >= size_arr - 1)
        next_ind = size_arr - 2;

    do {
        if (arr[prev_ind - 1] < arr[prev_ind] && arr[next_ind] > arr[next_ind + 1]) {
            ans_ind = bin_search(prev_ind, next_ind, arr);
            flag_binary = 1;
            break;
        }
        prev_ind = next_ind;
        next_ind *= 2;
        if (next_ind >= size_arr - 1)
            next_ind = size_arr - 2;
    } while (prev_ind != next_ind);

    if (!flag_binary)
        ans_ind = size_arr - 1;

    return ans_ind;
}

int main() {
    int size_arr = 0;
    scanf("%d", &size_arr);
    int *arr = (int *)malloc(sizeof(int) * size_arr);
    if (!arr)
        return MEMORY_ERROR;

    for(int i = 0; i < size_arr; i++)
        scanf("%d", &(arr[i]));
    int index = find_index(size_arr, arr);
    printf("%d", index);
    free(arr);
    return OK;
}
