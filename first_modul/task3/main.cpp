#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <exception>
#include <new>
#define NUMBER_MULTIPLY_CAPACITY 2

class Deq
{
public:
    Deq();
    ~Deq();
    Deq(const Deq&) = delete;

    Deq(Deq&&) = delete;

    Deq& operator=(const Deq&) = delete;

    Deq& operator=(Deq&&) = delete;

    // Добавить неотрицательное число в очередь
    void Push_front(int data);
    void Push_back(int data);
    const int Pop_front(void);
    const int Pop_back(void);

    bool IsEmpty() const;
    int Get_size() const;
    int *Realloc_in_increase_array(void);
    void Print_dec(void) const;
private:
    int capacity_;
    int index_begin_;
    int index_end_;
    int size_;
    int *array_;
};

Deq::Deq()
{
    capacity_ = NUMBER_MULTIPLY_CAPACITY;
    index_begin_ = 0;
    index_end_ = 0;
    size_ = 0;
    array_ = new int[capacity_];
}

Deq::~Deq()
{
    delete[] array_;
}

bool Deq::IsEmpty() const
{
    return size_ == 0;
}

int *Deq::Realloc_in_increase_array(void) {
    int *copy_arr = new int[capacity_ * NUMBER_MULTIPLY_CAPACITY];

    for (int i = 0; i <= capacity_ - 2; i++) {
        copy_arr[i] = array_[index_begin_];
        index_begin_ = (index_begin_ + 1) % capacity_;
    }
    delete[] array_;
    return copy_arr;

}

void Deq::Push_back(int data)
{
    if (index_begin_ == (index_end_ + 1) % capacity_) {

        array_ = Realloc_in_increase_array();
        index_begin_ = 0;
        index_end_ = capacity_ - 1;
        capacity_ *= 2;
    }
    array_[index_end_] = data;
    index_end_ = (index_end_ + 1) % capacity_;
    size_++;
}

void Deq::Push_front(int data)
{
    if (index_begin_ == (index_end_ + 1) % capacity_) {

        array_ = Realloc_in_increase_array();
        index_begin_ = 0;
        index_end_ = capacity_ - 1;
        capacity_ *= 2;
    }
    index_begin_ = (index_begin_ - 1 + capacity_) % capacity_;
    array_[index_begin_] = data;
    size_++;
}


const int Deq::Pop_front(void)
{
    if (this->IsEmpty())
        return -1;
    int ret = array_[index_begin_];
    index_begin_ = (index_begin_ + 1) % capacity_;
    size_--;
    return ret;
}

const int Deq::Pop_back(void)
{
    if (this->IsEmpty())
        return -1;
    index_end_ = (index_end_ - 1 + capacity_) % capacity_;
    int ret = array_[index_end_];
    size_--;
    return ret;
}

void Deq::Print_dec(void) const{
    int ind = index_begin_;
    while(ind != index_end_)
    {
        printf("%d ", array_[ind]);
        ind = (ind + 1) % capacity_;
    }
    printf("\n");
}

int main(void)
{
    try
    {
        int n = 0, operation = 0, value = 0, ans = 0;
        Deq new_dec;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &operation, &value);
            switch (operation) {
            case 1:
                new_dec.Push_front(value);
                break;
            case 2:
                ans = new_dec.Pop_front();
                if (ans != value) {
                    printf("NO");
                    return 0;
                }
                break;
            case 3:
                new_dec.Push_back(value);
                break;
            case 4:
                ans = new_dec.Pop_back();
                if (ans != value) {
                    printf("NO");
                    return 0;
                }
                break;
            default:
                printf("4545");
                break;
            }
        }
        printf("YES");
    }
    catch (const std::bad_alloc& e)
    {
        printf("Memory error");
        return -1;
    }
    return 0;

}






