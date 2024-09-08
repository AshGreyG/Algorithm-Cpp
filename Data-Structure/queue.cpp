#include <iostream>
#include <vector>

template<typename T>
struct Queue {
  private:
    std::vector<T> container_;
    unsigned int head_,
                 tail_,
                 size_;
    T default_ele_;
    void printState() {
        unsigned int ref = head_;
        while (ref != tail_) {
            if (ref == size_ + 1) {
                ref = 1;
            }
            if (ref == tail_) break;
            std::cout << container_.at(ref) << " ";
            ref++;
        }
        std::cout << "\n";
    }
    void printRealState() {
        for (int i = 1; i <= size_; ++i) {
            if (tail_ >= head_ && (i < head_ || i >= tail_)) {
                std::clog << "* ";
            } else if (tail_ >= head_ && (i >= head_ && i < tail_)) {
                std::clog << container_.at(i) << " ";
            } else if (tail_ < head_ && (i >= tail_ && i < head_)) {
                std::clog << "* ";
            } else {
                std::clog << container_.at(i) << " ";
            }
        }
        std::clog << "\n";
    }
    bool isFull() {
        return head_ == tail_ % (size_ + 1) + 1;
    }
    bool isEmpty() {
        return head_ == tail_;
    }
  public:
    Queue(T d, unsigned int s)
        : default_ele_(d), size_(s), head_(1), tail_(1) {
        container_.resize(size_ + 2, default_ele_);
    }
    ~Queue() = default;
    void enqueue(T input) {
        if (isFull()) {
            std::cerr << "overflow\n";
            return;
        }
        container_.at(tail_) = input;
        if (tail_ == size_ + 1) {
            tail_ = 1;
        } else {
            tail_++;
        }
        printState();
        printRealState();
    }
    T dequeue() {
        if (isEmpty()) {
            std::cerr << "underflow\n";
            return default_ele_;
        }
        T temp = container_.at(head_);
        if (head_ == size_ + 1) {
            head_ = 1;
        } else {
            head_++;
        }
        printState();
        printRealState();
        return temp;
    }
};