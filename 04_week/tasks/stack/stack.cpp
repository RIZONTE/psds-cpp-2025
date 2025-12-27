#include <vector>


class Stack {
public:
    Stack() = default;
    void Push(const int value);
    bool Pop();
    int& Top();
    const int& Top() const;
    bool Empty() const;
    size_t Size() const;
    void Clear();
    void Swap(Stack& other);
    bool operator==(const Stack& rhs) const;
    bool operator!=(const Stack& rhs) const;

private:
    std::vector<int> data_;
};

void Stack::Push(const int value) {
    data_.push_back(value);
}
bool Stack::Pop() {
    if(data_.empty()) return false;
    data_.pop_back();
    return true;
}
int& Stack::Top() {
    return data_.back();
}
const int& Stack::Top() const {
    return data_.back();
}
bool Stack::Empty() const {
    return data_.empty();
}
size_t Stack::Size() const {
    return data_.size();
}
void Stack::Clear() {
    data_.clear();
}
void Stack::Swap(Stack& other) {
    data_.swap(other.data_);
}

bool Stack::operator==(const Stack& rhs) const {
    return data_ == rhs.data_;
}
bool Stack::operator!=(const Stack& rhs) const {
    return data_ != rhs.data_;
}
