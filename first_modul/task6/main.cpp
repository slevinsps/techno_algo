#include <iostream>
#include "stdio.h"
#include "stdlib.h"
void my_swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

int Partition( int* a, int left, int right ) {
    if( right - left <= 0 ) {
        return left;
    }
    const int& pivot = a[right];
    int i = left;
    int j = right - 1;
    while( i <= j ) {
        for( ; a[i] < pivot; ++i ) {}
        for( ; j >= left && a[j] >= pivot; --j ) {}
        if( i < j ) {
            my_swap(a[i++], a[j--] );
        }
    }
    my_swap( a[i], a[right] );
    return i;
}


int findOrderStatistic(int* arr, int pos, int size) {
  int left = 0, right = size - 1;
  while (true) {
    int i = Partition(arr, left, right);
    /*printf("0 --  %d %d %d\n",i, left, right);
    for (int i = 0; i < size; i++)
                {
                    printf("%d ", arr[i]);
                }*/


    //printf("%d %d\n", i, left);
    if (i == pos) {
      return arr[i];
    }
    else if (pos < i) {
      right = i-1;
    }
    else {
      //pos -= i + 1;
      left = i + 1;
    }
  }
  return 0;
}

int main(void)
{
    int size = 0;
    int pos = 0;

    std::cin >> size;
    std::cin >> pos;
    int *a = (int *)calloc(size,sizeof(int));
    for(int i = 0; i < size; i++)
        std::cin >> a[i];


    //int i = Partition( a, size );
    //while(i != pos)
    //{
    //    /*printf("\n0 -  %d \n",i);
    //    for (int i = 0; i < size; i++)
    //        {
    //            printf("%d ", a[i]);
    //        }*/
    //
    //    if (i > pos) {
    //        size = i;
    //        i = Partition( a, size );
    //        /*printf("1 -  %d \n",i);
    //        for (int i = 0; i < size; i++)
    //            {
    //                printf("%d ", a[i]);
    //            }*/
    //    } else {
    //        i++;
    //        a += i;
    //        size -= i;
    //        pos -= i;
    //        i = Partition( a, size);
    //        /*printf("\n2 -  %d \n",i);
    //        for (int i = 0; i < size; i++)
    //            {
    //                printf("%d ", a[i]);
    //            }*/
    //    }
    //}

    printf("%d", findOrderStatistic(a,pos,size));
    /*int left=1, right = size - 1;
    int i = Partition(a, 0, right);
    for (int i = 0; i < size; i++)
                {
                    printf("%d ", a[i]);
                }
    i = Partition(a, left, right);
    printf("\n%d %d %d\n",i, left, right);
    for (int i = 0; i < size; i++)
                {
                    printf("%d ", a[i]);
                }*/
    /*for (int i = 0; i < size; i++)
    {
        printf("%d ", a[i]);
    }*/
    free(a);
}
