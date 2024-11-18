#include <iostream>
#include <memory>
#include <stdexcept>

template<typename T>
struct LinkedList {
  private:
    struct Node {
        T data_;
        std::weak_ptr<Node> prev_;
        std::shared_ptr<Node> next_;
        Node(const T& value) : data_(value) {
            prev_.reset();
            next_.reset();
        }
        Node() = default;
        ~Node() {
            std::clog << "Node has been destroyed.\n";
        }
    };
    std::shared_ptr<Node> head_ = nullptr;
    std::shared_ptr<Node> tail_ = nullptr;
    size_t size_;
  public:
    static const int npos = -1;
    LinkedList() : size_(0) { }
    ~LinkedList() {
        std::clog << "LinkedList has been destroyed.\n";
    }
    int search(T key) {
        int index = 0;
        auto pointer = head_;
        while (pointer != nullptr && pointer->data_ != key) {
            pointer = pointer->next_;
            index++;
        }
        if (pointer == nullptr) {
            return npos;
        } else {
            return index;
        }
    }
    T operator[](int index) {
        try {
            if (index < 0) {
                throw std::out_of_range("The index should not be negative.");
            } else if (index >= size_) {
                throw std::out_of_range("The index should not be greater than size.");
            }
        } catch (std::out_of_range& err) {
            std::cerr << err.what();
        }
        int pointer_index = 0;
        auto pointer = head_;
        while (pointer != nullptr) {
            if (pointer_index == index) {
                return pointer->data_;
            } else {
                pointer_index++;
            }
        }
    }

    // begin append data function :

    void appendFront(T new_data) {
        auto new_node = std::make_shared<Node>(new_data);
        if (head_ == nullptr) {
            head_ = tail_ = new_node;
            head_->prev_.reset();
            head_->next_.reset();
        } else {
            head_->prev_ = new_node;
            new_node->prev_.reset();
            new_node->next_= head_;
            head_ = new_node;
        }
        size_++;
    }
    void appendBack(T new_data) {
        auto new_node = std::make_shared<Node>(new_data);
        if (tail_ == nullptr) {
            head_ = tail_ = new_node;
            tail_->prev_.reset();
            tail_->next_.reset();
        } else {
            tail_->next_ = new_node;
            new_node->next_.reset();
            new_node->prev_ = tail_;
            tail_ = new_node;
        }
        size_++;
    }
    void insertFromKey(T new_data, T key) {
        auto pointer = head_;
        auto new_node = std::make_shared<Node>(new_data);
        while (pointer != nullptr) {
            if (pointer->data_ == key) {
                new_node->prev_ = pointer;
                new_node->next_ = pointer->next_;
                pointer->next_ = new_node;
                pointer->next_->prev_ = new_node;
                return;
            } else {
                pointer = pointer->next_;
            }
        }
    }
    void insertFromIndex(T new_data, int index) {
        try {
            if (index < 0) {
                throw std::out_of_range("The index should not be negative.");
            } else if (index >= size_) {
                throw std::out_of_range("The index should not be greater than size.");
            }
        } catch (std::out_of_range& err) {
            std::cerr << err.what();
        }
        auto new_node = std::make_shared<Node>(new_data);
        unsigned int pointer_index = 0;
        auto pointer = head_;
        while (pointer != nullptr) {
            if (pointer_index == index) {
                new_node->prev_ = pointer;
                new_node->next_ = pointer->next_;
                pointer->next_ = new_node;
                pointer->next_->prev_ = new_node;
                return;
            } else {
                pointer = pointer->next_;
                pointer_index++;
            }
        }
    }

    // end append data function

    // begin delete data function:

    void deleteFront() {
        if (head_ == nullptr) {
            std::cerr << "List is empty!";
            return;
        } else if (size_ == 1) {
            head_ = tail_ = nullptr;
        } else {
            head_ = head_->next_;
            head_->prev_.reset();
            size_--;
        }
    }
    void deleteBack() {
        if (tail_ == nullptr) {
            std::cerr << "List is empty!";
            return;
        } else if (size_ == 1) {
            head_ = tail_ = nullptr;
        } else {
            tail_ = tail_->prev_.lock();
            tail_->next_.reset();
            size_--;
        }
    }
    void deleteFromKey(T key) {
        auto pointer = head_;
        while (pointer != nullptr) {
            if (pointer->data_ == key) {
                pointer->prev_->next_ = pointer->next_;
                pointer->next_->prev_ = pointer->prev_;
            } else {
                pointer = pointer->next_;
            }
        }
    }
    void deleteFromIndex(int index) {
        try {
            if (index < 0) {
                throw std::out_of_range("The index should not be negative.");
            } else if (index >= size_) {
                throw std::out_of_range("The index should not be greater than size.");
            }
        } catch (std::out_of_range& err) {
            std::cerr << err.what();
        }
        unsigned int pointer_index = 0;
        auto pointer = head_;
        while (pointer != nullptr) {
            if (pointer_index == index) {
                pointer->prev_->next_ = pointer->next_;
                pointer->next_->prev_ = pointer->prev_;
            } else {
                pointer = pointer->next_;
                pointer_index++;
            }
        }
    }

    // end delete data function

    void printFromFront() {
        auto pointer = head_;
        while (pointer != nullptr) {
            std::cout << pointer->data_ << " ";
            pointer = pointer->next_;
        }
    }
    void printFromBack() {
        auto pointer = tail_;
        while (pointer != nullptr) {
            std::cout << pointer->data_ << " ";
            pointer = pointer->prev_.lock();
        }
    }
    size_t size() {
        return size_;
    }
};