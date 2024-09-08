#include <iostream>
#include <vector>

template<typename T>
struct Stack {
  private:
    std::vector<T> container_;
    unsigned int size_;
    unsigned int top_;
    T default_ele_;
    void printState() {
        for (int i = 1; i <= top_; ++i) {
            std::cout << container_.at(i) << " ";
            /* TODO
             *   printState() function may
             *   cause the problem that T
             *   doesn't match << operator
             */
        }
        std::cout << "\n";
    }
    bool isFull() {
        return top_ == size_;
    }
    bool isEmpty() {
        return top_ == 0;
    }
  public:
    Stack(T d, unsigned int s) 
        : default_ele_(d), size_(s), top_(0) {
        container_.resize(size_ + 1, default_ele_);
    }
    ~Stack() = default;
    void push(T input) {
        if (isFull()) {
            std::cerr << "overflow\n";
            return;
        }
        top_++;
        container_.at(top_) = input;
        printState();
    }
    T pop() {
        if (isEmpty()) {
            std::cerr << "underflow\n";
            return default_ele_;
        }
        T temp_ = container_.at(top_);
        container_.at(top_) = default_ele_;
        top_--;
        printState();
        return temp_;
    }
};