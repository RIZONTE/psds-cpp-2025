#include <string>
#include <utility>

class SimpleList {
public:
    SimpleList();
    SimpleList(const SimpleList& other);
    SimpleList(SimpleList&& other) noexcept;
    SimpleList& operator=(const SimpleList& other);
    SimpleList& operator=(SimpleList&& other) noexcept;
    ~SimpleList();
    void Swap(SimpleList& other);
    size_t Size() const noexcept;
    bool Empty() const noexcept;
    void PushBack(std::string& val);
    void PushBack(std::string&& val);
    void PopBack();
    void PushFront(std::string& val);
    void PushFront(std::string&& val);
    void PopFront();
    std::string& Back() const noexcept;
    std::string& Front() const noexcept;
    void Clear();

private:
    struct Node {
        Node* next;
        Node* prev;
        std::string* data;
    };
    Node* start_;
    Node* end_;
    size_t size_;

    void Unlink(Node* ptr);
    void LinkAfter(Node* new_node, Node* place);
    void LinkBefore(Node* new_node, Node* place);
};

void SimpleList::Unlink(Node* ptr) {
    Node* prev = ptr->prev;
    Node* next = ptr->next;
    
    if (prev != nullptr) {
        prev->next = next;
    } else {
        start_ = next;
    }
    
    if (next != nullptr) {
        next->prev = prev;
    } else {
        end_ = prev;
    }
    
    ptr->prev = nullptr;
    ptr->next = nullptr;
    --size_;
}

void SimpleList::LinkAfter(Node* new_node, Node* place) {
    new_node->prev = place;
    new_node->next = place->next;

    if(!(place->next)) {
        end_ = new_node;
    }
    else {
        place->next->prev = new_node;
    }
    place->next = new_node;
    ++size_;
}

void SimpleList::LinkBefore(Node* new_node, Node* place) {
    new_node->next = place;
    new_node->prev = place->prev;

    if(!(place->prev)) {
        start_ = new_node;
    }
    else {
        place->prev->next = new_node;
    }
    place->prev = new_node;
    ++size_;
}

SimpleList::SimpleList():
    start_(nullptr),
    end_(nullptr),
    size_(0) {}

SimpleList::SimpleList(const SimpleList& other):
    start_(nullptr),
    end_(nullptr),
    size_(0) {
    if(other.size_ == 0) return;

    start_ = new Node{nullptr, nullptr, new std::string(*(other.start_->data))};
    end_ = start_;
    size_ = 1;

    for (Node* iter = other.start_->next; iter != nullptr; iter = iter->next) {
        end_->next = new Node{nullptr, end_, new std::string(*(iter->data))};
        end_ = end_->next;
        ++size_;
    }
}

SimpleList::SimpleList(SimpleList&& other) noexcept:
    start_(std::exchange(other.start_, nullptr)),
    end_(std::exchange(other.end_, nullptr)),
    size_(std::exchange(other.size_, 0)) {}

void SimpleList::Clear() {
    Node* current = start_;
    while (current != nullptr) {
        Node* next = current->next;
        delete current->data;
        delete current;
        current = next;
    }
    start_ = nullptr;
    end_ = nullptr;
    size_ = 0;
}

void SimpleList::Swap(SimpleList& other) {
    std::swap(start_, other.start_);
    std::swap(end_, other.end_);
    std::swap(size_, other.size_);
}

SimpleList& SimpleList::operator=(const SimpleList& other) {
    if(this != &other) {
        Clear();
        SimpleList tmp(other);
        Swap(tmp);
    }
    return *this;
}
SimpleList& SimpleList::operator=(SimpleList&& other) noexcept {
    if(this != &other) {
        Clear();
        start_ = std::exchange(other.start_, nullptr);
        end_ = std::exchange(other.end_, nullptr);
        size_ = std::exchange(other.size_, 0);
    }
    return *this;
}

SimpleList::~SimpleList() {
    Clear();
}

size_t SimpleList::Size() const noexcept {
    return size_;
}

bool SimpleList::Empty() const noexcept {
    return size_ == 0;
}

void SimpleList::PushBack(std::string& val) {
    Node* new_node = new Node{nullptr, nullptr, new std::string(val)};
    if(size_ == 0) {
        start_ = new_node;
        end_ = new_node;
        ++size_;
        return;
    }
    LinkAfter(new_node, end_);
}

void SimpleList::PushBack(std::string&& val) {
    Node* new_node = new Node{nullptr, nullptr, new std::string(std::move(val))};
    if(size_ == 0) {
        start_ = new_node;
        end_ = new_node;
        ++size_;
        return;
    }
    LinkAfter(new_node, end_);
}

void SimpleList::PopBack() {
    if(Empty()) return;

    Node* to_delete = end_;
    Unlink(to_delete);
    delete to_delete->data;
    delete to_delete;
}

void SimpleList::PushFront(std::string& val) {
    Node* new_node = new Node{nullptr, nullptr, new std::string(val)};
    if(size_ == 0) {
        start_ = new_node;
        end_ = new_node;
        ++size_;
        return;
    }
    LinkBefore(new_node, start_);
}

void SimpleList::PushFront(std::string&& val) {
    Node* new_node = new Node{nullptr, nullptr, new std::string(std::move(val))};
    if(size_ == 0) {
        start_ = new_node;
        end_ = new_node;
        ++size_;
        return;
    }
    LinkBefore(new_node, start_);
}

void SimpleList::PopFront() {
    if(Empty()) return;

    Node* to_delete = start_;
    Unlink(to_delete);
    delete to_delete->data;
    delete to_delete;
}

std::string& SimpleList::Back() const noexcept {
    return *(end_->data);
}

std::string& SimpleList::Front() const noexcept {
    return *(start_->data);
}

void Swap(SimpleList& a, SimpleList& b) {
    a.Swap(b);
}