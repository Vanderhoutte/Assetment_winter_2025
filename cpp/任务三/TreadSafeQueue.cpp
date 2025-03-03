//参考了一些其他已完成项目的代码，不支持超时机制

#include<queue>
#include<mutex>
#include<condition_variable>
using namespace std;

template <typename T>

class ThreadSafeQueue{
    private:
        queue<T> data;
        mutable mutex mutex_status;
        condition_variable status;
    public:
        ThreadSafeQueue(){}//构造函数

        ThreadSafeQueue(const ThreadSafeQueue& other)//拷贝构造函数
        {
            lock_guard<mutex>lock(other.mutex_status);
            this->data = ohter.data;
        }

        ThreadSafeQueue& operator=(const ThreadSafeQueue& ohter) = delete;

        void push(T value)//进队
        {
            lock_guard<mutex>lock(this->mutex_status);
            this->data.push(move(value));
            this->status.notify_one();
        }

        bool pop(T &value)//出队
        {
            lock_guard<mutex>lock(this->mutex_status);
            this->status.wait(lock,[this]{return !data.empty()});
            value = move(this->data.front());
            this->data.pop();
        }

};
