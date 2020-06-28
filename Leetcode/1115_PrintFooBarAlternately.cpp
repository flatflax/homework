// 1115. Print FooBar Alternately
// https://leetcode.com/problems/print-foobar-alternately/

// cv.notify_one(); 随机唤醒一个等待的线程

class FooBar {
private:
    int n;
    bool status;
    mutex mtx;
    condition_variable cv;
public:
    FooBar(int n) {
        this->n = n;
        status = true;
    }

    void foo(function<void()> printFoo) {
        unique_lock<mutex> lck(mtx);
        for (int i = 0; i < n; i++) {
            cv.wait(lck, [this](){ return status==true; });
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            status = false;
            cv.notify_one();
        }
    }

    void bar(function<void()> printBar) {
        unique_lock<mutex> lck(mtx);
        for (int i = 0; i < n; i++) {
            cv.wait(lck, [this](){ return status==false; });
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            status = true;
            cv.notify_one();
        }
    }
};