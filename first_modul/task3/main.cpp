#include <assert.h>
#include <stdio.h>

class CDeq
{
public:
        CDeq();
        ~CDeq();
        CDeq(const CQueue&) = delete;

        CDeq(CQueue&&) = delete;

        CDeq& operator=(const CDeq&) = delete;

        CDeq& operator=(CDeq&&) = delete;

        // Добавить неотрицательное число в очередь
        void Push_front(int data);
        void Push_back(int data);
        const int Pop_front(void);
        const int Pop_back(void);

        bool IsEmpty() const;
private:
        struct CNode
        {
                int Data;
                CNode *Next;
                CNode *Prev;
                explicit CNode(int data) : Data(data), Next(nullptr), Prev(nullptr) {}
        };

        CNode *head;
        CNode *tail;
};

CDeq::CDeq()
{
        head = nullptr;
        tail = nullptr;
}

CDeq::~CDeq()
{
        while (head != nullptr)
        {
                CNode *toDelete = head;
                head = head->Next;
                delete toDelete;
        }
}

bool CDeq::IsEmpty() const
{

        return head == nullptr;
}

void CDeq::Push_front(int data)
{
    struct CNode *tmp = new CNode(data);
    tmp->Prev = tail;
    tail
    head = ListItem(x, head, null);
    head.next.prev = head;

    if (head == nullptr) {
            assert(tail == nullptr);
            head = tail = new CNode(data);
    } else {
            assert(tail == nullptr);
            tail->Next = new CNode(data);
            tail = tail->Next;
    }
}

void CDeq::Push_back(int data)
{
        if (head == nullptr)
                return -1;
        CNode *toDelete = head;
        const int retNumber = head->Data;
        head = head->Next;
        if (head == nullptr)
                tail = nullptr;
        return retNumber;
}



function initialize():
  head = ListItem(null, null, null)
  tail = ListItem(null, null, head)
  head.next = tail

function pushBack(x : T):
  head = ListItem(x, head, null)
  head.next.prev = head
T popBack():
  data = head.data
  head = head.next
  return data
function pushFront(x : T):
  tail = ListItem(x, null, tail)
  tail.prev.next = tail
T popFront():
  data = tail.data
  tail = tail.prev
  return data


int main(int argc, char* argv[])
{
        int commandCount = 0;
        scanf("%d", commandCount);

        CQueue queue;
        for (int i = 0; i < commandCount; i++){
                int command = 0;
                int data = 0;
                scanf("%d %d", command, data);
                switch (command) {
                case 2:
                        if (queue.Dequeue() != data) {
                                printf("NO");
                        }
                        break;
                case 3:
                        queue.Enqueue(data);
                        break;
                }
        }
}
