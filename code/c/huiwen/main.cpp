#include <iostream>
#include <stack>
using namespace std;

/*此处是链栈数据结构定义*/
typedef char DataType;
struct node
{
    DataType  info;
    struct node* link;
};

typedef struct node* PNode;

struct LinkQueue {
    PNode  front, rear;
};
typedef struct LinkQueue* PLinkQueue;


//第一关
PLinkQueue createNullQueue_link()
{//此处填写代码，创建一个空的链队 
    PLinkQueue l = new struct LinkQueue;
    l->front = NULL;
    l->rear = NULL;
    return l;
}

//第二关
int isNullQueue_link(PLinkQueue L)
{
    //判断队列是否为空，若为空，返回值为1，否则返回值为0,若队列不存在，则返回-1
    if (L == NULL) {
        return -1;
    }
    else if(L->front==NULL) {
        return 1;
    }
    else {
        return 0;
    }
}




//第三关
int EnQueue_link(PLinkQueue L, DataType x)
{//在队列插入数据元素x，若插入不成功，返回0；插入成功返回值为1
    PNode p = new struct node;
    p->info = x;
    p->link = NULL;
    //队列是空的
    if (isNullQueue_link(L) == 1) {
        L->front = p;
        L->rear = p;
    }
    //队列非空
    else if (isNullQueue_link(L) == 0) {
        L->rear->link = p;
        L->rear = p;
    }
    //队列不存在
    else {
        return 0;
    }
    return 1;
}



//第四关
DataType DeQueue_link(PLinkQueue L)
{//删除队首元素并返回被删除元素，若队列为空，则返回-1
    if (isNullQueue_link(L) != 0) {
        return -1;
    }
    else {
        int temp = L->front->info;
        PNode p = L->front;
        L->front = p->link;
        delete(p);
        return temp;
    }
}

//第五关
DataType front_link(PLinkQueue L)
{// 取队首元素返回，若队列为空，则返回-1
    if (isNullQueue_link(L) != 0) {
        return -1;
    }
    else {
        return L->front->info;
    }
}
bool isPalindrome(string s) {
    //特殊情况
    if (s.length() < 2) {
        return true;
    }

    stack<char> stack;  // 栈 （懒得自己写了）
    PLinkQueue queue = createNullQueue_link();  // 链队列

    // 将字符串s的每个字符压栈 入列
    for (char c : s) {
        stack.push(c);
        EnQueue_link(queue, c);
    }

    // 依次出栈和出队列比较每个字符
    while (!stack.empty() && !isNullQueue_link(queue)) {
        //取队首 栈顶
        char stackTop = stack.top();
        char queueFront = front_link(queue);
        stack.pop();
        DeQueue_link(queue);
        if (stackTop != queueFront) {
            return false;
        }
    }
    return true;
}


int main() {
    string str;
    cin >> str;
    if (isPalindrome(str)) {
        cout << str << "是回文\n";
    }
    else {
        cout << str << "不是回文\n";
    }
    return 0;
}
