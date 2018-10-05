#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <iostream>

int get_number_razr(unsigned long long int num, int razr)
{
    // printf("fdf %lld ", num);
    int ans = 0;
    for(int i = 0; i < razr; i++)
    {
        ans = num % 10;
        num /= 10;
    }
    //printf(" %d  %d\n", razr, ans);
    return ans;
}

void radixSort(unsigned long long int *arr, int n)
{
    int k = 25;
    int m = 25;
    for (int i = 1; i < m; i++)
    {
        for (int  j = 0 ; j < n - 1; j++)
            for (int  r = j + 1 ; r < n ; r++)
                if (get_number_razr(arr[j],i) > get_number_razr(arr[r],i))
                {
                    unsigned long long tmp = arr[j];
                    arr[j] = arr[r];
                    arr[r] = tmp;
                }
    }
}


int main(void)
{
    int n;// = 2;

    //long long int arr[] = {400, 0};

    std::cin >> n;
    unsigned long long int *arr = (unsigned long long int *)malloc(n * sizeof(unsigned long long int));
    for(int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    radixSort(arr,n);
    for(int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    printf("\n");

}
